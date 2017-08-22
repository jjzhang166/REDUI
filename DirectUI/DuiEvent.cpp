// DuiEvent.cpp : CDuiEvent ��ʵ��

#include "stdafx.h"
#include "DuiEvent.h"
#include "DuiControl.h"
#include "duicore/DuiPluginsManager.h"


// CDuiEvent


STDMETHODIMP COleDuiEvent::get_name(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	return *pVal = ::SysAllocString(DuiNode::NameToFinalName(m_event->Name)), S_OK;
}

STDMETHODIMP COleDuiEvent::get_src(IDispatch** pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (pVal==NULL) return E_POINTER;
	*pVal = DuiHandle<DuiNode>(m_event->pSender)->GetObject(TRUE);
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP COleDuiEvent::get_x(LONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (pVal==NULL) return E_POINTER;
	*pVal = m_event->ptMouse.x;

	return S_OK;
}

STDMETHODIMP COleDuiEvent::get_y(LONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (pVal==NULL) return E_POINTER;
	*pVal = m_event->ptMouse.y;

	return S_OK;
}

STDMETHODIMP COleDuiEvent::get_cancelBubble(VARIANT_BOOL* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (pVal==NULL) return E_POINTER;
	*pVal = (m_event->cancelBubble) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP COleDuiEvent::put_cancelBubble(VARIANT_BOOL newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_event->cancelBubble = (newVal!=VARIANT_FALSE);

	return S_OK;
}

STDMETHODIMP COleDuiEvent::get_returnValue(VARIANT_BOOL* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (pVal==NULL) return E_POINTER;
	*pVal = (m_event->returnValue) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP COleDuiEvent::put_returnValue(VARIANT_BOOL newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_event->returnValue = (newVal!=VARIANT_FALSE);

	return S_OK;
}

STDMETHODIMP COleDuiEvent::get_propertyName(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (pVal==NULL) return E_POINTER;
	*pVal = ::SysAllocString(m_event->pPropertyName);

	return S_OK;
}
