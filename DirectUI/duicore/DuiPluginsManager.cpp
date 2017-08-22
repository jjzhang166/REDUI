#include "StdAfx.h"
#include "DuiPluginsManager.h"
#include "DuiBase.h"
#include "DuiManager.h"

// ϵͳĬ��ʵ��Ӧ��ʵ�����ȫ�ֱ���
extern PluginData g_defPlugin;

//////////////////////////////////////////////////////////////////////////
class CS
{
	CRITICAL_SECTION cs;
public:
	CS() { ::InitializeCriticalSection(&cs); }
	~CS() { ::DeleteCriticalSection(&cs); }

	operator CRITICAL_SECTION& () { return cs; }
};
class CSLocker
{
	CRITICAL_SECTION& _cs;
public:
	CSLocker(CRITICAL_SECTION& cs) : _cs(cs) { ::EnterCriticalSection(&_cs); }
	~CSLocker() { ::LeaveCriticalSection(&_cs); }
};

CS g_cs;
CSimpleArray<PluginData*> g_plugins;

//////////////////////////////////////////////////////////////////////////
/*
 *	������û�����
 */
class PluginsList : public TList<PluginsList>
{
public:
	PluginData* plugin;
	BOOL finished;

	static void BuildPluginsChain(PluginsList** ppHead)
	{
		if (ppHead==NULL) return;
		*ppHead = NULL;

		CSLocker locker(g_cs);
		int num = g_plugins.GetSize();
		if (num==0) return;
		PluginsList* p = NEW PluginsList[num];
		if (p==NULL) return;
		for (int i=0; i<num; i++)
		{
			p[i].plugin = g_plugins[num-1-i];
			p[i].finished = FALSE;
			p[i].addToList(ppHead, false);
		}
	}
};

/*
 *	API
 */
HPLUGIN DUIAPI RegisterPlugin(fnPluginCallback cb, LPVOID data, LPVOID reserved)
{
	return DuiHandle<PluginData>(PluginsManager::RegisterPlugin(cb, data, reserved));
}

BOOL DUIAPI UnregisterPlugin(HPLUGIN hPlugin)
{
	return PluginsManager::UnregisterPlugin(DuiHandle<PluginData>(hPlugin));
}

BOOL DUIAPI IsPlugin(HPLUGIN hPlugin)
{
	return PluginsManager::IsPlugin(DuiHandle<PluginData>(hPlugin));
}

/*
 *	CallNextPlugin ��һ������Ҫ��API��������ʱ�ı�������ִ�д���
 *	���ִ��˳��Ĭ���ǰ���ע��˳��ķ��򣬼���ע��Ĳ����ִ�У���ע��Ĳ����ִ��
 *	��ĳЩ���������£�һ�����ϣ���õ�������ִ�еĲ���ص��Ľ����Ȼ����ݽ������һ��������ʱ����ͨ�� CallNextPlugin �ı�ִ�д���
 *	����A����Ļص������е��ô� API�������ú��� B/C... ����Ļص����̣�Ȼ��ѽ�����ظ� A �����A ���������֮���ٴӻص��з���
 *	���ͬʱ��A �ص����֮�󣬱��ü���ִ�� B/C... �Ļص�������Ϊ B/C... �Ѿ���ִ�й����������ظ����� B/C... �Ļص���
 */
BOOL DUIAPI CallNextPlugin(const CallContext* cc, char* params)
{
	PluginCallContext* ppcc = (PluginCallContext*)cc;
	if (ppcc==NULL || ppcc->curPlugin==NULL)
		return FALSE;

	BOOL bHandled = FALSE;
	PluginsList* plug = (PluginsList*)ppcc->curPlugin;
	//if (plug->Next()) // ����Ҫ����������� Next �ǿգ���ʾ����Ĭ��ʵ��
	{
		ppcc->curPlugin = plug->Next();
		bHandled = PluginsManager::_callPluginsChain(*ppcc, params);
		ppcc->curPlugin = plug;
	}

	return bHandled;
}

BOOL DUIAPI CallDefault(const CallContext* cc, char* params)
{
	PluginCallContext* ppcc = (PluginCallContext*)cc;
	if (ppcc==NULL || ppcc->curPlugin==NULL || ppcc->defPluginFinished)
		return FALSE;

	BOOL bHandled = FALSE;

	LPVOID oldPlug = ppcc->curPlugin;

	ppcc->curPlugin = NULL; // �ÿռ��ɵ���Ĭ��ʵ��
	bHandled = PluginsManager::_callPluginsChain(*ppcc, params);
	
	ppcc->curPlugin = oldPlug;

	return bHandled;
}

//////////////////////////////////////////////////////////////////////////
PluginCallContext::PluginCallContext( /*DWORD _opcode,*/ BOOL _stopOnTrue/*=FALSE*/, HDE _hde/*=NULL*/, HWND _hwnd/*=NULL*/ )
	: unused(0)
	, stopOnTrue(_stopOnTrue)
	, lastPlugin(NULL)
	, curPlugin(NULL)
	, defPluginFinished(FALSE)
	, defProc(FALSE)
	, handled(FALSE)
{
	cbSize = sizeof(CallContext);
	opcode = -1;
	hde = _hde;
	hwnd = _hwnd;
	output = NULL;
}

PluginCallContext& PluginCallContext::Call( DWORD _opcode, ... )
{
	opcode = _opcode;
	if (opcode==-1) return *this;

	if (hwnd==NULL && hde)
	{
		DuiNode* n = DuiNode::FromHandle(hde);
		hwnd = n->m_pLayoutMgr->GetPaintWindow();
	}

	va_list params;
	va_start(params, _opcode);

	// �������в��
	PluginsList* chain = NULL;
	chain->BuildPluginsChain(&chain);
	curPlugin = chain;

	handled = PluginsManager::_callPluginsChain(*this, params);

	if (chain)
	{
		delete[] chain;
	}

	va_end(params);

	return *this;
}

PluginCallContext& PluginCallContext::CallOne( PluginData* plug, DWORD _opcode, ... )
{
	if (plug==NULL) return *this;;
	opcode = _opcode;
	if (opcode==-1) return *this;

	if (hwnd==NULL && hde)
	{
		hwnd = DuiHandle<DuiNode>(hde)->m_pLayoutMgr->GetPaintWindow();
	}

	va_list params;
	va_start(params, _opcode);

	// �������в��
	PluginsList chain;
	chain.plugin = plug;
	chain.finished = FALSE;
	curPlugin = &chain;

	PluginsManager::_callPluginsChain(*this, params, TRUE);

	va_end(params);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//PluginsManager::PluginsManager(void)
//{
//}
//
//PluginsManager::~PluginsManager(void)
//{
//}
//
//PluginsManager& PluginsManager::instance()
//{
//	static PluginsManager mgr;
//	return mgr;
//}

PluginData* PluginsManager::RegisterPlugin( fnPluginCallback cb, LPVOID data, LPVOID reserved )
{
	if (reserved) return NULL;
	if (cb==NULL) return NULL;

	CSLocker locker(g_cs);
	for (int i=0; i<g_plugins.GetSize(); i++)
	{
		if (g_plugins[i]->cb==cb && g_plugins[i]->data==data)
			return g_plugins[i];
	}

	PluginData* pd = NEW PluginData;
	if (pd==NULL) return NULL;
	pd->cb = cb;
	pd->data = data;

	// ������汾���Ƿ�ʹ����ȫ��ͬ�� OPCODE �汾
	DWORD dwVer = 0;
	PluginCallContext().Output(&dwVer).CallOne(pd, 0);
	//CallOnePlugin(pd, PluginCallContext(0).Output(&dwVer));
	if (dwVer != OPCODE_VERSION)
	{
		delete pd;
		return NULL;
	}

	g_plugins.Add(pd);
	return pd;
}

BOOL PluginsManager::UnregisterPlugin( PluginData* pd )
{
	if (pd==NULL) return FALSE;

	CSLocker locker(g_cs);
	int index = g_plugins.Find(pd);
	if (-1 == index)
		return FALSE;

	delete pd;
	g_plugins.RemoveAt(index);
	return TRUE;
}

BOOL PluginsManager::IsPlugin( PluginData* pd )
{
	if (pd==NULL) return FALSE;

	CSLocker locker(g_cs);
	int index = g_plugins.Find(pd);
	return index >= 0;
}

/*
 *	���ò����
 */
//BOOL PluginsManager::CallPlugins( PluginCallContext& pcc, ... )
//{
//	va_list params;
//	va_start(params, pcc);
//
//	// �������в��
//	BOOL bHandled = FALSE;
//	PluginsList* chain = NULL;
//	chain->BuildPluginsChain(&chain);
//	pcc.curPlugin = chain;
//
//	bHandled = _callPluginsChain(pcc, params);
//
//	if (chain)
//	{
//		delete[] chain;
//	}
//
//	va_end(params);
//
//	return bHandled;
//}
//
///*
// *	����ĳ�����������������Ƿ��Ѵ���
// */
//void PluginsManager::CallOnePlugin( PluginData* plug, PluginCallContext& pcc, ... )
//{
//	if (plug==NULL) return;
//
//	va_list params;
//	va_start(params, pcc);
//
//	// �������в��
//	PluginsList chain;
//	chain.plugin = plug;
//	chain.finished = FALSE;
//	pcc.curPlugin = &chain;
//
//	_callPluginsChain(pcc, params, TRUE);
//
//	va_end(params);
//}

/*
 *	pcc.curPlugin �Ѿ���Ч
 */
BOOL PluginsManager::_callPluginsChain( PluginCallContext& pcc, char* params, BOOL noDefault/*=FALSE*/ )
{
	BOOL bHandled = FALSE;

	PluginsList* plug = (PluginsList*)pcc.curPlugin;
	if (plug==NULL) // ����Ĭ��ʵ��
	{
		if (!noDefault && !pcc.defPluginFinished)
		{
			// ���������Ĭ�ϻص�������øûص����������ϵͳĬ��ʵ��
			if (pcc.defProc)
			{
				bHandled = TRUE; // ����Ĭ�ϻص�������Ϊ�Ѵ���
				switch (pcc.opcode)
				{
#define DoPreArg(...) __VA_ARGS__
#define PreArg(type,name) type* _##name = (type *)((params += X86SIZE(type)) - X86SIZE(type));
#define DoPreArg2(...) __VA_ARGS__
#define PreArg2(type,name) , type
#define Arg2(type,name) *_##name
#define __op_calldef(rettype, op, prearg, prearg2, ...) \
				case OpCode_##op: \
				{ \
					prearg; \
					rettype ret = ((rettype (/*CALLBACK*/ *)(CallContext* prearg2))pcc.defProc)((CallContext*)&pcc, __VA_ARGS__); \
					if (pcc.output!=NULL && bHandled) *((rettype*)pcc.output) = ret; \
					break; \
				}

					__foreach_op(__op_calldef, DoPreArg, PreArg, DoPreArg2, PreArg2, Arg2)

#undef __op_calldef
#undef DoPreArg
#undef PreArg
#undef DoPreArg2
#undef PreArg2
#undef Arg2
				}
			}
			else
			{
				bHandled = g_defPlugin.cb(g_defPlugin.data, &pcc, params);
			}

			pcc.defPluginFinished = TRUE;

			if (bHandled && pcc.stopOnTrue)
				return (pcc.lastPlugin = &g_defPlugin), TRUE;
			return bHandled;
		}
		return FALSE;
	}

	if (!plug->finished)
	{
		// ���ûص�
		bHandled = plug->plugin->cb(plug->plugin->data, &pcc, params);

		plug->finished = TRUE;

		if (bHandled && pcc.stopOnTrue)
			return (pcc.lastPlugin = plug->plugin), TRUE;
	}

	// ������һ���ص�
	pcc.curPlugin = plug->Next();
	//if (pcc.curPlugin) // ����ΪNULL����ʾ����ϵͳĬ��ʵ��
		return _callPluginsChain(pcc, params);
	//return bHandled;
}

/*
 *	���´�����һ�������Ĳ��ʵ�֣����ܾ��ǰ����пؼ����ü���Բ�Ǿ��Ρ�
 *	��δ�����Է�����REDUI��Ӧ�ó�������DLL�У�������ͬ��
 *	
 *	ʵ��һ�����ֻ��Ҫ�����򵥵Ĳ��裺
 *		1. ����һ���࣬�� ReduiPlugin<> ����
 *		2. ʵ��ע����˵�����κ�һ��������������������е� GetControlClipRgn������һ��Բ�Ǿ�������
 *		3. Ϊ�๹��һ��ʵ��
 */
//class CMyPlugin : public ReduiPlugin<CMyPlugin>
//{
//public:
//	HRGN GetControlClipRgn(HDE hCtrl, HDC hdc, RECT rcClip)
//	{
//		return ::CreateRoundRectRgn(...);
//	}
//};
//
//CMyPlugin myPlugin;