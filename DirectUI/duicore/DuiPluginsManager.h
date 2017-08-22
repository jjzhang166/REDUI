#ifndef DuiPluginsManager_h__
#define DuiPluginsManager_h__

#pragma once

#include "../DuiPlugin.h"

template<typename T>
class DuiHandle
{
public:
	HANDLE _h;
	T* _p;

	DuiHandle(HANDLE h) : _h(h), _p(NULL)
	{
		if (_h)
			__if_exists(T::unused) { _p = (T*)(((char*)_h) - offsetof(T,unused)); }
			__if_not_exists(T::unused) { _p = ((T*)(((char*)_h) + 4)) - 1; }
	}
	DuiHandle(T* p) : _p(p), _h(NULL)
	{
		if (_p)
			__if_exists(T::unused) { _h = (HANDLE)(((char*)_p) + offsetof(T,unused)); }
			__if_not_exists(T::unused) { _h = (HANDLE)(((char*)(_p + 1)) - 4); }
	}

	operator HANDLE() { return _h; }
	operator T* () { return _p; }
	T* operator ->() { return _p; }
};

/*
 *	�������
 */
struct PluginData
{
	fnPluginCallback cb;
	LPVOID data;
};

/*
 *	�������������
 */
typedef void (/*__cdecl*/ * fnDefPluginProc)();
struct PluginCallContext : public CallContext
{
public:
	BOOL stopOnTrue; // �Ƿ��ڷ���TRUE��ֹͣ��һ��������ã�Ĭ��FALSE�����������в��
	PluginData* lastPlugin; // ��� stopOnTrue == TRUE����ô���ﱣ����󷵻�TRUE�Ĳ��
	LPVOID curPlugin; // ������е�ǰ���ڵ��õĲ��
	BOOL defPluginFinished; // ϵͳĬ��ʵ���Ƿ��ѵ���
	fnDefPluginProc defProc; // Ĭ�ϻص������ʵ���˴˻ص�������������ϵͳĬ��ʵ�֣�����Ĭ�ϻص����ܷ���VOID����һ������Ϊ CallContext*����������Ϊ��������
	BOOL handled; // �����Ƿ��ѱ�����

	DWORD unused; // ����ֶβ���ʹ��

	PluginCallContext(/*DWORD _opcode, */BOOL _stopOnTrue=FALSE, HDE _hde=NULL, HWND _hwnd=NULL);

	// ���ò���
	PluginCallContext& Output(LPVOID pOutput) // ���÷���ֵ������ָ��
	{ output = pOutput; return *this; }
	PluginCallContext& StopOnTrue(BOOL bStopOnTrue) // �����Ƿ������� TRUE ��ֹͣ���ú������
	{ stopOnTrue=bStopOnTrue; return *this; }
	template<typename tProc> PluginCallContext& DefProc(tProc proc) // ����Ĭ�ϻص�������ȡ��ϵͳĬ��ʵ��
	{ defProc = (fnDefPluginProc)proc; return *this; }
	PluginCallContext& SetHde(HDE _hde) // ���ÿؼ����
	{ hde = _hde; return *this; }
	PluginCallContext& SetHwnd(HWND _hwnd) // ���ô��ھ��
	{ hwnd = _hwnd; return *this; }

	PluginCallContext& Call(DWORD _opcode, ...); // ���ò����
	PluginCallContext& CallOne(PluginData* plug, DWORD _opcode, ...); // ����һ������Ĳ���ص�

	operator BOOL() { return handled; }
	BOOL IsHandled() const { return handled; }

	template<typename T>
	T GetOutput() { return output ? *((T*)output) : T(0); }
};

/*
 *	���������
 */
class PluginsManager
{
	friend BOOL DUIAPI CallNextPlugin(const CallContext* cc, char* params);
	friend BOOL DUIAPI CallDefault(const CallContext* cc, char* params);
	friend PluginCallContext;
private:
	//PluginsManager(void);
	//~PluginsManager(void);

public:
	//static PluginsManager& instance();

	static PluginData* RegisterPlugin(fnPluginCallback cb, LPVOID data, LPVOID reserved);
	static BOOL UnregisterPlugin(PluginData* pd);
	static BOOL IsPlugin(PluginData* pd);

	//static BOOL CallPlugins(PluginCallContext& pcc, ...);
	//static void CallOnePlugin(PluginData* plug, PluginCallContext& pcc, ...);

protected:
	static BOOL _callPluginsChain(PluginCallContext& pcc, char* params, BOOL noDefault=FALSE);
};

#endif // DuiPluginsManager_h__
