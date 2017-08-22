#ifndef __DUISURFACE_H__
#define __DUISURFACE_H__

#pragma once

//#include <atlapp.h>
//#include <atlgdi.h>
#include <ddraw.h>

#define DECLARE_DELETE() public: virtual void Delete() { delete this; }
//#define GDI_ONLY

#define SRC_BLT_KEYCOLOR	0xFF3D3E3F

#ifndef IsLayered
#define IsLayered(hwnd) ((::GetWindowLongW(hwnd, GWL_EXSTYLE) & WS_EX_LAYERED) == WS_EX_LAYERED)
#endif // IsLayered

class CPrimarySurface;
class COffscreenSurface;

class CSurface
{
	friend COffscreenSurface;

protected:
	CComPtr<IDirectDrawSurface> _ddSurface;
	CSurface* _owner;
	BOOL _isOffscrn;	// �Ƿ����������GDI��HDC�����߱��������
	HDC _hdc;
	RECT _rc;
	ULONG _ulRef;

	CSurface(BOOL bOffscrn=FALSE) : _isOffscrn(bOffscrn), _hdc(NULL), _ulRef(0), _owner(NULL) { ::SetRectEmpty(&_rc); }
	//virtual ~CSurface()
	//{
	//	if (_ddSurface.p) _ddSurface.Release();
	//}

public:
	operator IDirectDrawSurface* () { return _ddSurface.p; }
	IDirectDrawSurface* operator->() { return _ddSurface.p; }

	CSurface* Owner() { return _owner; }

	virtual BOOL IsGDI() { return FALSE; }
	BOOL IsOffscreen() { return _isOffscrn; }

	virtual void Delete() = 0; // { delete this; } // = 0;
	virtual HDC GetDC();
	virtual void ReleaseDC(HDC hdc);
	virtual void BltToPrimary(LPRECT pRectSrc=NULL) {}		// �����������������Ч
	void FillRect(LPRECT pRect, COLORREF clr, BYTE alpha=255);
	virtual CSurface* Clone(LPRECT pRect=NULL) = 0; // Ϊ��ǰ�����ȫ����һ�����򴴽�һ���󱸱��棬��������Ҳ��������������
	virtual RECT Rect() { return _rc; } // �������ȡ���ھ��Σ���������ֱ�ӷ��� _rc;
};

class CSurfaceDC //: public CDCHandle
{
	CSurface* _surface;
	BOOL _bAutoBlt;
	int _savedc;

public:
	HDC m_hDC;

	CSurfaceDC(CSurface* surface=NULL, BOOL bAutoBlt=FALSE); // �����һ��������NULL�������Ļ��ȡDC
	~CSurfaceDC();

	operator HDC() { return m_hDC; }

	void Lock();
	void Unlock();
};

class CPrimarySurface : public CSurface
{
	friend COffscreenSurface;

	CComPtr<IDirectDraw> _dd; // ddraw
	CComPtr<IDirectDrawClipper> _ddClipper;
	HWND _hwnd;

	BOOL Init(HWND hwnd); // ��ʼ����������

	DECLARE_DELETE()

public:
	CPrimarySurface(HWND hwnd) { Init(hwnd); }
	~CPrimarySurface()
	{
		if (_ddSurface.p) _ddSurface.Release();
		if (_ddClipper.p) _ddClipper.Release();
		if (_dd.p) _dd.Release();
	};

	virtual CSurface* Clone(LPRECT pRect=NULL);
	virtual RECT Rect();
};

class COffscreenSurface : public CSurface
{
	friend CPrimarySurface;

	//RECT _rc;
	HDC _memdc;
	HBITMAP _hbmp;
	HBITMAP _hbmpOld;
	CComPtr<IDirectDrawSurface> _memdds;

	BOOL Init(CSurface* surface, LPCRECT lpRect=NULL); // ��ʼ������������

	DECLARE_DELETE()

	COffscreenSurface(CSurface* surface, LPCRECT lpRect=NULL); // ��ֱֹ��new
public:
	~COffscreenSurface();

	virtual HDC GetDC();
	virtual void ReleaseDC(HDC hdc);
	virtual void BltToPrimary(LPRECT pRectSrc=NULL);

	virtual CSurface* Clone(LPRECT pRect=NULL);
};

class COffscreenGdiSurface;
class CGdiSurface : public CSurface
{
	friend COffscreenGdiSurface;

	HWND _hwnd;
	RECT _rc;

	DECLARE_DELETE()

public:
	CGdiSurface(HWND hwnd);
	~CGdiSurface();

	virtual BOOL IsGDI() { return TRUE; }

	virtual HDC GetDC() { return _hdc; }
	virtual void ReleaseDC(HDC hdc) {}
	virtual CSurface* Clone(LPRECT pRect=NULL) { return NULL; }
};

class COffscreenGdiSurface : public CSurface
{
	CGdiSurface& _primarySurface;
	RECT _rc;
	HBITMAP _hbmp;
	HBITMAP _hbmpOld;

	DECLARE_DELETE()

public:
	COffscreenGdiSurface(CGdiSurface& surface, LPCRECT lpRect=NULL);
	~COffscreenGdiSurface();

	virtual BOOL IsGDI() { return TRUE; }

	virtual HDC GetDC() { return _hdc; }
	virtual void ReleaseDC(HDC hdc) {}
	virtual void BltToPrimary(LPRECT pRectSrc=NULL);
	virtual CSurface* Clone(LPRECT pRect=NULL) { return NULL; }
};


#endif // __DUISURFACE_H__