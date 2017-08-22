#ifndef __DUIWINDOWCONTROL_H__
#define __DUIWINDOWCONTROL_H__

#pragma once

#include "DuiManager.h"

//#define Delete_This() \
//	virtual void DeleteThis() { delete this; }

#define Final_Message() \
	/*Delete_This()*/ \
	virtual void OnFinalMessage(HWND) { /*DeleteThis()*/delete this; }

//////////////////////////////////////////////////////////////////////////
//
class CDuiManagedWnd;
class CDuiWindowControl;

class CDuiManagedWnd : public CDuiWindowBase
{
	friend CDuiWindowControl;
public:
	CDuiManagedWnd();
	virtual ~CDuiManagedWnd();

	Final_Message()

	virtual void Init(CDuiWindowControl* pOwner);
	virtual void UpdateData(BOOL bSave=TRUE) {} // DDX support

	// CDuiWindowBase virtual function
	virtual LPCTSTR GetWindowClassName() const;
	virtual LPCTSTR GetSuperClassName() const;
	//virtual UINT GetClassStyle() const;
	//virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	CDuiWindowControl* m_pOwner;
};

class CDuiWindowControl : public ControlExtension,
						public ISinkIsMyEvent,
						public ISinkOnStateChanged,
						public ISinkOnAttributeChanged,
						public ISinkOn3DSurfaceCreated
{
	friend CDuiManagedWnd;
public:
	DECLARE_CONTROL_EXTENSION(CDuiWindowControl)
	//DECLARE_CONTROL_FLAGS(DUIFLAG_TABSTOP | DUIFLAG_SETCURSOR)
	DECLARE_CLASS_CAST(CDuiWindowControl, ControlExtension, ISinkIsMyEvent, ISinkOnStateChanged, ISinkOnAttributeChanged, ISinkOn3DSurfaceCreated)

	DECLARE_BASE_CLASS_STYLE("display:inlineblock;")

	CDuiWindowControl();
	virtual ~CDuiWindowControl();

	void UpdatePos();

	// overidable
	// ִ��ʵ�ʵĴ��ڴ������̣�ͨ����һ��Ԫ���������Գ�ʼ�����֮����ã�Ĭ��ʵ�ִ��������Ĵ��ڣ�����ʵ�ֲ�Ӧ�õ��û���ʵ��
	virtual CDuiManagedWnd* OnCreateWindow();
	virtual BOOL ParseWindowStyle(LPCOLESTR lpszData, DWORD& style) { return FALSE; }
	virtual BOOL ParseWindowExtendedStyle(LPCOLESTR lpszData, DWORD& style) { return FALSE; }

	// ControlExtension
	virtual BOOL IsMyEvent(HANDLE, DuiEvent* pEvent);
	virtual void OnStateChanged(HANDLE, DWORD dwStateMask);
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
	virtual void OnAttributeChanged(HANDLE, LPCOLESTR szAttr);
	virtual void On3DSurfaceCreated(HANDLE);

protected:
	DWORD TryLoadWindowStyleFromString(LPCOLESTR lpszValue);
	DWORD TryLoadExtendedWindowStyleFromString(LPCOLESTR lpszValue);
	DWORD ParseStyleFromVariant(CComVariant v);
	DWORD ParseExtendedStyleFromVariant(CComVariant v);

	void UpdateState();

private:
	BOOL ParseGeneralWindowStyleString(LPCOLESTR lpszData, DWORD& style);
	BOOL ParseExtendedWindowStyleString(LPCOLESTR lpszData, DWORD& style);

protected:
	CDuiManagedWnd* m_pWin;

public:
	DWORD m_dwStyle;
	DWORD m_dwExStyle;
};

THIS_IS_CONTROL_EXTENSION2(CDuiWindowControl, hwnd, Window)

//////////////////////////////////////////////////////////////////////////
// <edit type="single-line" />

class CDuiEdit : public CDuiWindowControl
{
public:
	DECLARE_CONTROL_EXTENSION(CDuiEdit)
	DECLARE_CONTROL_FLAGS(DUIFLAG_TABSTOP/* | DUIFLAG_SETCURSOR*/)
	DECLARE_CLASS_CAST(CDuiEdit, CDuiWindowControl/*, CDuiSinkOnAttributeChanged*/)

	DECLARE_BASE_CLASS_STYLE("cursor:text; border:solid 1 gray; padding:3 1;")

	virtual BOOL ParseWindowStyle(LPCOLESTR lpszData, DWORD& style);

	virtual CDuiManagedWnd* OnCreateWindow();

	// ControlExtension
	virtual BOOL IsMyEvent(HANDLE, DuiEvent* pEvent);
	virtual void OnAttributeChanged(HANDLE, LPCOLESTR szAttr);
};

THIS_IS_CONTROL_EXTENSION2(CDuiEdit, Text2, Edit2)

#endif // __DUIWINDOWCONTROL_H__