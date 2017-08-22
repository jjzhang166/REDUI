#ifndef __DUIPLUGIN_H__
#define __DUIPLUGIN_H__

#if (_MSC_VER < 1400) || !defined(_M_IX86)
	#error opcode.h requires Visual C++ 2005 and above, and MUST be compiled in X86 architecture.
#endif // _MSC_VER >= 1400

#include "DirectUIWindow.h"
#include "opcode.h"

typedef HANDLE HPLUGIN;

#define X86SIZE(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define Arg(type,name) ( *(type *)((params += X86SIZE(type)) - X86SIZE(type)) )

#define DuiVoid int

//////////////////////////////////////////////////////////////////////////
// ��չ�ӿ�
class IExtension
{
public:
	virtual void Use(HANDLE hSource) = 0; // hSource ��ʾ��ʼʹ�ô˲����Դ
	virtual void Unuse(HANDLE hSource) = 0; // hSource ��ʾ����ʹ�ô˲����Դ
	virtual void* CastToClass(LPCWSTR szName) = 0; // ��չʵ��Ӧ���ṩCAST���������͵Ļ���
};

//////////////////////////////////////////////////////////////////////////
// ��չ����
class IExtensionContainer
{
public:
	virtual void AttachExtension(IExtension* pExt) = 0;
	virtual void DetachExtension(IExtension* pExt) = 0;
};

//////////////////////////////////////////////////////////////////////////
// API for plugins

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

IExtensionContainer* DUIAPI DuiGetExtensionContainer(HDE hde);

#ifdef __cplusplus
}
#endif /* __cplusplus */

//////////////////////////////////////////////////////////////////////////
// �ؼ���չ��ר������չ�ؼ���ÿ��ʵ����ͨ����չ�������ӵ��ؼ���
//class IControlExtension : public IExtension
//{
//	static LPCOLESTR __MyName() { return MakeIntName(100); }
//public:
//	// �ؼ���չ��Ӧ�����������ؼ����
//	virtual void SetOwner(HDE hde) = 0;
//	virtual HDE GetOwner() = 0;
//};

//////////////////////////////////////////////////////////////////////////
// ��۽ӿڡ����ͨ��ʵ����۽ӿڣ�����߿�ͱ����Ļ��ơ�
// ��۽ӿڶ�Ӧ��ʽ���е�visual��ʽ�����ͨ����ѯ������������ƻ�ô˽ӿ�
// IVisual ������չ�ӿ�

class IVisual
{
public:
	virtual RECT GetAdjustRect(HDE hde) const = 0;
	// ���µĻ��ƺ��������Ҫ����Ĭ�ϻ��ƣ�Ӧ��ֱ�ӷ���FALSE
	virtual BOOL OnPaintBorder(HDE hde, HDC hdc, RECT rcBorder) = 0;
	virtual BOOL OnPaintFocus(HDE hde, HDC hdc, RECT rcFocus, HRGN hrgn) = 0;
	virtual BOOL OnPaintBackground(HDE hde, HDC hdc, RECT rcBkgnd) = 0;
	virtual BOOL OnPaintForeground(HDE hde, HDC hdc, RECT rcFrgnd) = 0;
};

//////////////////////////////////////////////////////////////////////////
// ���ֽӿڡ����ͨ��ʵ�ֲ��ֽӿڣ�ʵ�ֶ��ӿؼ��Ĳ����Ű�
// ���ֽӿڶ�Ӧ��ʽ���е� layout ��ʽ�����ͨ�����Ʋ�ѯ�����ô˽ӿ�
class ILayout : public IExtension
{
public:
	virtual BOOL OnUpdateLayout(HDE hde) = 0;
};

/*
 *	CallContext �ṹ��ʾ��ǰ�����ĵ��������ģ����Ӧ������ȷ�ϴ��������Ƿ��Լ���ע������ע��Ӧ���������� FALSE
 */
struct CallContext
{
	DWORD cbSize;	// sizeof(CallContext)���ṹ���С
	DWORD opcode;	// �����룬����Ҫִ�еĲ������ͣ�����ֵ�� OpCode_ Ϊǰ׺��ֵ
	LPVOID output;	// ����ֵ�ڴ��ָ�룬���ڴ��ɵ����ߴ�������ֵ����Ϊ NULL����ʾ�����߲����ķ���ֵ
	HWND hwnd;		// ��ǰ���ڲ����Ĵ��ھ����NULL ��ʾ��ǰ����δ��������
	HDE hde;		// ��ǰ���ڲ����Ŀؼ�Ԫ�ؾ����NULL ��ʾ��ǰ����δ�����ؼ�
};

/*
 *	����ص�����
 */
typedef BOOL (__cdecl * fnPluginCallback)(LPVOID data, const CallContext* cc, char* params);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 *	ע����ж�ز�� API
 */
HPLUGIN DUIAPI RegisterPlugin(fnPluginCallback cb, LPVOID data, LPVOID reserved);
BOOL DUIAPI UnregisterPlugin(HPLUGIN hPlugin);
BOOL DUIAPI IsPlugin(HPLUGIN hPlugin);

// ����APIֻ�����ڻص�ִ�й����У����������ı�����Ч
// CallNextPlugin �������ú�����δ���õĲ���ص�
// CallDefault ��������ϵͳĬ��ʵ�֣�������ֱ��Խ��ʣ��Ĳ����
BOOL DUIAPI CallNextPlugin(const CallContext* cc, char* params);
BOOL DUIAPI CallDefault(const CallContext* cc, char* params);

#ifdef __cplusplus
}



//////////////////////////////////////////////////////////////////////////
// ��������࣬�����ڲ�����VC2005�ϱ���


//////////////////////////////////////////////////////////////////////////
// ����ģ���� ReduiPlugin�����ʵ���߿�ѡ��Ӵ���̳У���ѡ����ʵ�����蹦�ܶ�Ӧ�ĳ�Ա����
// ��ʵ�ֵĲ��������μ� opcode.h �ļ��п�ʼ���ֵ�ע��
// �����дҪ��ѭ����ԭ��
//		* ���ҹ�����������
//		* �����������ǰ���������� RegisterPlugin ע���Լ���ReduiPlugin ���ڹ��캯������ɡ�
//		* �������ֹǰ������ UnregisterPlugin ж���Լ���ReduiPlugin ����������������ɡ�
//		* �������ʵ�� fnPluginCallback �ص����������ǲ�����ܵ��õ�Ψһ��ڡ�ReduiPlugin ��ʵ���� Call �ص��������ڲ�ʵ�ֵ��õ��ɷ���
//		* ���ʵ�ֵĻص�����˵����
//			- ����������
//				CallContext* cc�����������ģ���������ʱ�ĵ�ǰ���ڡ��ؼ�Ԫ�ء������롣����κ�һ�����ݲ����ϲ��������Ŀ�꣬��Ӧ�÷��� FALSE��
//				char* params�����ò������ϣ�����ͳһ�ĵ���Լ������ͬ�������Ӧ��ͬ�Ĳ������͡�
//				LPVOID output������ֵ������ָ�룬��ͬ��������Ҫ��ͬ�ķ���ֵ���ͣ��������ṩ�������������ֵ��NULL����ʾ�ò�������Ҫ����ֵ
//			- ����ֵ BOOL��TRUE ��ʾ����Ѵ���ò�����FALSE ��ʾ���δ����򲻹�ע�ò���
// 
template<class t>
class ReduiPlugin
{
public:
	HPLUGIN m_hPlugin;

protected:
	typedef ReduiPlugin<t> thisClass;

	// ������Ҫ���ص��Ƿ��Ѵ������Ϣ����������
	BOOL m_bHandled;
	void SetHandled(BOOL bHandled)
	{
		m_bHandled = bHandled;
	}

	// Ԥ�����������ģ�������������ϣ�Ӧ�÷��� FALSE�������ٽ������ɷ�����������
	BOOL IsCallValid(const CallContext* cc)
	{
		switch (cc->opcode)
		{
#define __call_valid(ret, op, ...) __if_exists(t::op) { case OpCode_##op: }

			__foreach_op(__call_valid,,,,,)

#undef __call_valid
		case 0:
			return TRUE;
		}
		return FALSE;
	}

	// �ص�������������������� CallNextPlugin/CallDefault �ȸı��������ô���� API ʱ��Ҫ��Щ����
	struct
	{
		const CallContext* _cc;
		char* _params;
	} m_cache;

public:
	ReduiPlugin() : m_hPlugin(NULL), m_bHandled(FALSE)
	{
		__if_not_exists(t::__NoAutoRegister)
		{
			m_hPlugin = ::RegisterPlugin((fnPluginCallback)&thisClass::_PluginEntry, (t*)this, NULL);
		}
	}
	virtual ~ReduiPlugin()
	{
		__if_not_exists(t::__NoAutoRegister)
		{
			::UnregisterPlugin(m_hPlugin);
		}
	}

	operator HPLUGIN () { return m_hPlugin; }

	BOOL IsPlugin()
	{
		return ::IsPlugin(m_hPlugin);
	}

	const CallContext* GetCallContext() const
	{
		return m_cache._cc;
	}

	LPVOID GetOutputPtr() const
	{
		return m_cache._cc.output;
	}

	/*
	 *	CallNextPlugin ���ڸı�������ִ��˳���ڵ�ǰ����Ļص������У���ִ�к�������Ļص���
	 *	���ַ�ʽ���Ի�ú����ص��Ľ�����پ����Լ����ִ��
	 */
	BOOL CallNextPlugin()
	{
		return ::CallNextPlugin(m_cache._cc, m_cache._params);
	}

	/*
	 *	����������£�ϵͳĬ��ʵ���ڲ������������ĩ�˱����ã�CallDefault ��ʹϵͳĬ��ʵ����ǰִ�У�Ȼ�󷵻ؼ���ִ�е�������
	 *	�����������ÿ�����������ϵͳĬ��ʵ�֣���౻ִ��һ�Σ����˳�򱻴��ң�ִ�й��Ĳ���ص��������ٴ�ִ��
	 */
	BOOL CallDefault()
	{
		return ::CallDefault(m_cache._cc, m_cache._params);
	}

protected:
	/*
	 *	_PluginEntry �ǲ���ӿڵ�Ψһ������ڣ���ʵ�ֽ��򻯲��������
	 */
	static BOOL __cdecl _PluginEntry(LPVOID data, const CallContext* cc, char* params)
	{
		_assert(data && cc);
		t* pThis = (t*)data;

		/*
		 *	����������Ա� CallNextPlugin ��ȡ
		 */
		pThis->m_cache._cc = cc;
		pThis->m_cache._params = params;

		/*
		 *	�����������ģ�����ע�Ĳ���������
		 */
		pThis->SetHandled(FALSE); // �����Ч��ʱ��Ĭ������Ϊ������
		if (!pThis->IsCallValid(cc))
			return FALSE;

		/*
		 *	ת��ʵ�ʵ���
		 */
		pThis->SetHandled(TRUE); // ʵ�ʵ���ʱ��Ĭ������Ϊ�Ѵ���

		/*
		 *	��������Ҫ�Զ��崦����̣�Ӧ������������ʵ�����º�����
		 *	
				 BOOL PluginProc(const CallContext* cc, char* params);
		 *	
		 *	��ʵ����������ڲ���Ҫ�Լ������������Ӧ�÷��� FALSE��������ִ��Ĭ�ϵĵ����ɷ�����
		 */
		__if_exists(t::PluginProc)
		{
			if (pThis->PluginProc(cc, params))
				return TRUE;
		}

		return pThis->thisClass::_CallDispatch(cc, params);
	}

private:
	BOOL _CallDispatch(const CallContext* cc, char* params)
	{
		t* pThis = (t*)this;
		switch (cc->opcode)
		{
#define DoPreArg(...) __VA_ARGS__
#define PreArg(type,name) type* _##name = (type *)((params += X86SIZE(type)) - X86SIZE(type));
#define DoPreArg2(...)
#define PreArg2(type,name)
#define Arg2(type,name) *_##name
#define __op_dispatch(retype, op, prearg, prearg2, ...) \
	__if_exists(t::op) { \
		case OpCode_##op: \
		{ \
			prearg; \
			retype ret = pThis->op(__VA_ARGS__); \
			if (cc->output!=NULL && m_bHandled) *((retype*)cc->output) = ret; \
			break; \
		} \
	}

		__foreach_op(__op_dispatch, DoPreArg, PreArg, DoPreArg2, PreArg2, Arg2)

#undef __op_dispatch
#undef DoPreArg
#undef PreArg
#undef DoPreArg2
#undef PreArg2
#undef Arg2

		case 0: if (cc->output) *((DWORD*)cc->output) = OPCODE_VERSION; break; // 0 ��ʾ��ȡOPCODE�汾��
		default: SetHandled(FALSE);
		}
		return m_bHandled;
	}
};


#endif // __cplusplus

#endif // __DUIPLUGIN_H__