#ifndef __DXT_H__
#define __DXT_H__

#pragma once
//#include <ddraw.h>

//#include "DirectUI.h" // Ϊ���ܱ�����Ŀʹ�ã���ֱ�Ӱ���ͷ�ļ����ĳ��ú궨��������
#include "transform/dxtrans.h"
#include "../../common/macro.h"

#define Safe_Delete(x) if (x) (x)->Delete(&(x));

// DXT Draw State
#define DXT_DS_CONTENT		0x00000001	// content + scrollbar
#define DXT_DS_BACKGROUND	0x00000002
#define DXT_DS_BORDER		0x00000004
#define DXT_DS_FOREGROUND	0x00000008
#define DXT_DS_ALL			0x0000FFFF

class DXT;
class DXTransform;
class DXSurface;

class DXT
{
	friend DXTransform;
	friend DXSurface;
private:
	CComPtr<IDXTransformFactory> _tf;
	CComPtr<IDXSurfaceFactory> _sf;

	DXT() {}
	~DXT() { _clear(); }

	BOOL _init();
	void _clear();

	static BOOL parse_to_clsid(LPCOLESTR szName, CLSID& clsid, LPCOLESTR szPrev=NULL);

public:
	static DXT& instance();
	static void clear();

	static DXTransform* create_transform(LPCOLESTR szProgId, IPropertyBag* pInitProp=NULL);
	static DXSurface* create_surface(DXTransform& t, BOOL writable=FALSE);
};

//////////////////////////////////////////////////////////////////////////
// surface

class DXSurface
{
	friend DXT;
	friend DXTransform;
private:
	BOOL _bInput;
	DXTransform& _t;
	CComPtr<IDXSurface> _s;
	CComPtr<IDXSurface> _s32; // _s �ĸ�ʽ�����ǲ�ͬ�ģ�ȫ��ת���� ARGB32 ��ʽ�����õ� Transform ��
	CComPtr<IDXDCLock> _dclock;
	HDC _hdc;

	DXSurface(DXTransform& t, BOOL writable=FALSE);
	~DXSurface();

public:
	IDXSurface* ptr() { return _s32.p?_s32.p:_s.p; }

	void Delete(DXSurface** pps=NULL)
	{
		delete this;
		if (pps) *pps = NULL;
	}
	HDC GetDC();
	void ReleaseDC();
};

//////////////////////////////////////////////////////////////////////////
// transform

// �任��ʱ֪ͨ
typedef void (CALLBACK* pfnTransformProc)(LPVOID pData, DWORD dwState);
typedef void (CALLBACK* pfnDrawToDC)(HDC hdc, LPVOID pData, DWORD dwState);
typedef void (CALLBACK* pfnDrawBackgroundToDC)(HDC hdc, LPVOID pData, const RECT rc);
typedef POINT (CALLBACK* pfnGetWindowOrg)(LPVOID pData);

//class DXTransformNotify
//{
//public:
//	virtual void OnTransform() = 0;
//};

struct DxtContext
{
	HDC _dc;
	RECT _rc;
	RECT _rcClip;
	//DXTransformNotify* _transformProc;
	LPVOID _data;
	pfnTransformProc _transformProc;
	pfnDrawToDC _drawToDC;
	pfnDrawBackgroundToDC _drawBkToDC;
	pfnGetWindowOrg _getWindowOrg;
	IPropertyBag* _props;

	DxtContext() { memset(this, 0, sizeof(DxtContext)); }
	BOOL IsValid() const { return _dc && !::IsRectEmpty(&_rc); }
};

class DXTransform
{
	friend DXT;
	friend DXSurface;
public:
	Begin_Disp_Map(DXTransform)
		//Disp_Method(Apply, void, 71, DispFuncParams0)();		// ÿ����һ�ξͲ���һ��HDC�����ݣ�����һ���µı���
		//Disp_Method(Play, void, 72, DispFuncParams1<VARIANT>)(VARIANT vDuration);	// ������ʱ������һ��������棬��ʼ������ʱ����vDuration(VT_R4, >=0.0��)
		//Disp_Method(Stop, void, 73, DispFuncParams0)();
		//Disp_Method(test, void, 74, DispFuncParams0)();
		//Disp_Property(Enabled, VARIANT_BOOL, 1)
		Disp_Property(1, Enabled, bool)
		Disp_Method(71, Apply, void, 0)		// ÿ����һ�ξͲ���һ��HDC�����ݣ�����һ���µı���
		Disp_Method(72, Play, void, 1, float)	// ������ʱ������һ��������棬��ʼ������ʱ����vDuration(VT_R4, >=0.0��)
		Disp_Method(73, Stop, void, 0)
	End_Disp_Map()

	bool Enabled;

	void Apply();
	void Play(float fDuration = 1.0f);
	void Stop();

	void test();

private:
	CComQIPtr<IDXTransform> _t;
	CComQIPtr<IDXEffect> _effect;
	CComQIPtr<IDXTScaleOutput> _scale;
	int _outFormatIndex; // ��ʽ����
	GUID _outFormat;
	CLSID _clsid;
	DWORD _misc;	// GetMiscFlags
	ULONG _inMin, _inMax, _inDesired; // min:��Ҫ���������������(0-2)��max:��ѡ��������������(<=2)��desired:���������������(min-max)

	// ����ʱ����
	struct DXTRuntime
	{
		DxtContext _ctx;
		BOOL _started;
		float _percent; // 0.0 - 1.0  ��ǰִ����ɵİٷֱ�
		//float _duration; // ��λ��
		//ULONG _fireTotal; // ��ʱ���ص���Ҫִ�е��ܴ���
		//ULONG _fireCount; // ��ʱ���ص��Ѿ���ִ�еĴ���
		DXSurface* _out;
		DXSurface* _in;
		DXSurface* _in2;
		DXSurface* _bk;
		DWORD _timerId;

		DXTRuntime() { memset(this, 0, sizeof(DXTRuntime)); _timerId = (DWORD)-1; }
		~DXTRuntime()
		{
			Safe_Delete(_out);
			Safe_Delete(_in);
			Safe_Delete(_in2);
			Safe_Delete(_bk);
		}
	};
	DXTRuntime _runtime;

	DXTransform(IDXTransform* t, CLSID clsid);
	~DXTransform() { Stop(); }

	static void CALLBACK _timer_proc(LPVOID pData, DWORD dwId);

	HRESULT _init_1st_surface(BOOL bCapture=TRUE, BOOL bSetup=FALSE);
	HRESULT _capture_to_surface(DXSurface* surf, DWORD dwState=DXT_DS_ALL);
	HRESULT _capture_background();
	HRESULT _setup();
	HRESULT _init_properties();

public:
	IDXTransform* ptr() { return _t.p; }
	//IDispatch* DispatchPtr() { return _disp.p; }
	IDispatch* disp() { return GetDispatch(); }
	IDXEffect* effect() { return _effect.p; }
	//BOOL IsTypeSame(DXTransform* other) const { return this==other || _clsid==other->_clsid; }
	BOOL IsType(LPCOLESTR szProgId) const;

	void Delete(DXTransform** ppt=NULL)
	{
		delete this;
		if (ppt) *ppt = NULL;
	}

	void Init(DxtContext& ctx); // ����任�����λ�û��С�����仯����������µ��ô˺���
	// Like ICSSFilterDispatch
	//HRESULT Apply();	// ÿ����һ�ξͲ���һ��HDC�����ݣ�����һ���µı���
	//HRESULT Play(VARIANT vDuration);	// ������ʱ������һ��������棬��ʼ������ʱ����vDuration(VT_R4, >=0.0��)
	//HRESULT Stop();

	BOOL OnPaint(HDC hdc, const RECT& rect, DWORD stage); // stage ָ���ƽ׶Σ����� DXT_DS_BACKGROUND ��ʾ������Ʊ������������FALSE�����Ĭ�ϴ���

	void SetPercent(float percent);
};

#endif // __DXT_H__