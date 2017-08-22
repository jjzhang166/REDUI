// DuiBrowserApp.h : CDuiBrowserApp ������

#pragma once
#include "resource.h"       // ������

#include "DuiBrowserAuto_i.h"
#include "MainDlg.h"
#include <atlstr.h>
#include "../common/dispatchimpl.h"

extern CMainDlg* gpDlg;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CDuiBrowserApp

class ATL_NO_VTABLE CDuiBrowserApp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDuiBrowserApp, &CLSID_DuiBrowser>,
	public IDispatchImpl<IDuiBrowserApp, &IID_IDuiBrowserApp, &LIBID_DuiBrowserAutoLib, /*wMajor =*/ 0xffff, /*wMinor =*/ 0xffff>
{
public:
	static ULONG m_ulInstances;
	static CPeer m_peer;
	static IUnknown* m_peerUnk; // ����Ϊ�˱��벻����

	CDuiBrowserApp()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_DUIBROWSERAPP)
DECLARE_NO_REGISTRY()

DECLARE_NOT_AGGREGATABLE(CDuiBrowserApp)

BEGIN_COM_MAP(CDuiBrowserApp)
	COM_INTERFACE_ENTRY(IDuiBrowserApp)
	COM_INTERFACE_ENTRY(IDispatch)
	//COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_peerUnk) // ��䲻��ʹ�ã������ⲿ HTA Զ�̴��������ʱ�ᵼ�±����̱��������ٷ����೧���󴴽� IMarshal ʧ�ܡ�
END_COM_MAP()

//DECLARE_CLASSFACTORY_SINGLETON(CDuiBrowserApp)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	typedef IDispatchImpl<IDuiBrowserApp, &IID_IDuiBrowserApp, &LIBID_DuiBrowserAutoLib, /*wMajor =*/ 0xffff, /*wMinor =*/ 0xffff> baseDispatch;

	HRESULT FinalConstruct()
	{
		m_ulInstances++;
		UpdateInfo();
		return S_OK;
	}

	void FinalRelease()
	{
		m_ulInstances--;
		UpdateInfo();
	}

	static void UpdateInfo();

	// IDispatch overide
public:
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid);
	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr);

public:

	STDMETHOD(load)(BSTR xml);
	STDMETHOD(loadUrl)(BSTR url);
	STDMETHOD(activate)(VARIANT* vUrl);
	//STDMETHOD(get_version)(BSTR* pVal);
	STDMETHOD(get_visible)(VARIANT_BOOL* pVal);
	//STDMETHOD(axo)(BSTR progid, IDispatch** obj);
	//STDMETHOD(httpLoad)(BSTR url, VARIANT success, VARIANT* ret);
	//STDMETHOD(fileVersion)(BSTR path, BSTR* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(DuiBrowser), CDuiBrowserApp)
