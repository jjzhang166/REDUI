#ifndef __DIRECTUI_H__
#define __DIRECTUI_H__

#pragma once

#include <atlcomcli.h>

#ifndef __DUIPLUGIN_H__
#include "../DuiPlugin.h"
#endif

//////////////////////////////////////////////////////////////////////////
//
//class CDuiLayoutModeBase;
class CDuiScrollbarBase;
//class CDuiVisualBase;
struct ControlExtensionEntry;
//struct DuiLayoutModeFactroyEntry;
//struct DuiVisualFactroyEntry;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Don't remove or edit this block ��Ҫɾ�����޸���������
#pragma section("DirectUI$__a", read, shared)
#pragma section("DirectUI$__b", read, shared)
#pragma section("DirectUI$__c", read, shared)
extern "C"
{
	__declspec(selectany) __declspec(allocate("DirectUI$__a")) ControlExtensionEntry* __pctrlextEntryFirst = NULL;
	__declspec(selectany) __declspec(allocate("DirectUI$__c")) ControlExtensionEntry* __pctrlextEntryLast = NULL;
}

#pragma comment(linker, "/merge:DirectUI=.rdata")
// Don't remove or edit this block ��Ҫɾ�����޸���������
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// �������ߺ�
namespace __dui_base
{
#define __for_each_number(v, ...) \
	v(0, __VA_ARGS__) \
	v(1, __VA_ARGS__) \
	v(2, __VA_ARGS__) \
	v(3, __VA_ARGS__) \
	v(4, __VA_ARGS__) \
	v(5, __VA_ARGS__) \
	v(6, __VA_ARGS__) \
	v(7, __VA_ARGS__) \
	v(8, __VA_ARGS__) \
	v(9, __VA_ARGS__) \
	v(10, __VA_ARGS__) \
	v(11, __VA_ARGS__) \
	v(12, __VA_ARGS__) \
	v(13, __VA_ARGS__) \
	v(14, __VA_ARGS__) \
	v(15, __VA_ARGS__)

	// ��ֵ��1�ĳ���
#define __cntdec_0 0
#define __cntdec_1 0
#define __cntdec_2 1
#define __cntdec_3 2
#define __cntdec_4 3
#define __cntdec_5 4
#define __cntdec_6 5
#define __cntdec_7 6
#define __cntdec_8 7
#define __cntdec_9 8
#define __cntdec_10 9
#define __cntdec_11 10
#define __cntdec_12 11
#define __cntdec_13 12
#define __cntdec_14 13
#define __cntdec_15 14

#define __cntdec(n) __cntdec_##n

	// ������������
#define __connect2(x, y) x##y
#define __connect(x, y) __connect2(x, y)

	// �ѷ��ű���ַ���
#define __to_string2(x) #x
#define __to_string(x) __to_string2(x)

	// ���ɲ�ͬ������˳�����
#define __repeat_0(m, ...)
#define __repeat_1(m, ...)	__repeat_0(m, __VA_ARGS__)  m(1, __VA_ARGS__)
#define __repeat_2(m, ...)	__repeat_1(m, __VA_ARGS__)  m(2, __VA_ARGS__)
#define __repeat_3(m, ...)	__repeat_2(m, __VA_ARGS__)  m(3, __VA_ARGS__)
#define __repeat_4(m, ...)	__repeat_3(m, __VA_ARGS__)  m(4, __VA_ARGS__)
#define __repeat_5(m, ...)	__repeat_4(m, __VA_ARGS__)  m(5, __VA_ARGS__)
#define __repeat_6(m, ...)	__repeat_5(m, __VA_ARGS__)  m(6, __VA_ARGS__)
#define __repeat_7(m, ...)	__repeat_6(m, __VA_ARGS__)  m(7, __VA_ARGS__)
#define __repeat_8(m, ...)	__repeat_7(m, __VA_ARGS__)  m(8, __VA_ARGS__)
#define __repeat_9(m, ...)	__repeat_8(m, __VA_ARGS__)  m(9, __VA_ARGS__)
#define __repeat_10(m, ...) __repeat_9(m, __VA_ARGS__)  m(10, __VA_ARGS__)
#define __repeat_11(m, ...) __repeat_10(m, __VA_ARGS__)  m(11, __VA_ARGS__)
#define __repeat_12(m, ...) __repeat_11(m, __VA_ARGS__)  m(12, __VA_ARGS__)
#define __repeat_13(m, ...) __repeat_12(m, __VA_ARGS__)  m(13, __VA_ARGS__)
#define __repeat_14(m, ...) __repeat_13(m, __VA_ARGS__)  m(14, __VA_ARGS__)
#define __repeat_15(m, ...) __repeat_14(m, __VA_ARGS__)  m(15, __VA_ARGS__)

#define __last_repeat_0(m, ...)
#define __last_repeat_1(m, ...)	m(1, __VA_ARGS__)
#define __last_repeat_2(m, ...)	m(2, __VA_ARGS__)
#define __last_repeat_3(m, ...)	m(3, __VA_ARGS__)
#define __last_repeat_4(m, ...)	m(4, __VA_ARGS__)
#define __last_repeat_5(m, ...)	m(5, __VA_ARGS__)
#define __last_repeat_6(m, ...)	m(6, __VA_ARGS__)
#define __last_repeat_7(m, ...)	m(7, __VA_ARGS__)
#define __last_repeat_8(m, ...)	m(8, __VA_ARGS__)
#define __last_repeat_9(m, ...)	m(9, __VA_ARGS__)
#define __last_repeat_10(m, ...) m(10, __VA_ARGS__)
#define __last_repeat_11(m, ...)  m(11, __VA_ARGS__)
#define __last_repeat_12(m, ...)  m(12, __VA_ARGS__)
#define __last_repeat_13(m, ...)  m(13, __VA_ARGS__)
#define __last_repeat_14(m, ...)  m(14, __VA_ARGS__)
#define __last_repeat_15(m, ...)  m(15, __VA_ARGS__)

#define __repeat(n, m_begin, m_end, ...) __connect(__repeat_, __cntdec(n))(m_begin, __VA_ARGS__) __connect(__last_repeat_, n)(m_end, __VA_ARGS__)

// CastHelper
#define __tparam16(n,...) typename T##n=int,
#define __tparam16_end(n,...) typename T##n=int
#define __basecast(n, ...) \
	__if_exists(T##n::CastToClass) { if (!p) p = pExt->T##n::CastToClass(name); } \
	__if_exists(T##n::__HasName) { if (!p && (T##n::__HasName(name))) return (T##n *)pExt; } \
	__if_exists(T##n::__MyName) { if (!p && (name==T##n::__MyName() || (!isInt && (HIWORD(T##n::__MyName())!=0) && lstrcmpiW(name,T##n::__MyName())==0))) return (T##n *)pExt; }

template<class T, __repeat(15, __tparam16, __tparam16_end)>
class __CastHelperT
{
public:
	static LPVOID Cast2Class(T* pExt, LPCOLESTR name)
	{
		if (name==NULL) return NULL;
		BOOL isInt = (HIWORD(name)==0);
		__if_exists(T::__HasName) { if (T::__HasName(name)) return pExt; }
		__if_exists(T::__MyName) { if (name==(T::__MyName()) || (!isInt && (HIWORD(T::__MyName())!=0) && lstrcmpiW(name, T::__MyName())==0)) return pExt; }
		LPVOID p = NULL;
		__repeat(15, __basecast, __basecast)
		return p;
	}
};
} // end namespace __dui_base

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//


// ����ĺ궨�����ڿؼ�������������
typedef IExtension* (CALLBACK* fnCreateControlExtension)();
typedef void (CALLBACK* fnRegisterClassStyle)(HWND, LPCOLESTR);

typedef struct ControlExtensionEntry
{
	LPCOLESTR szName, szAlias, szAlias2;
	int lenName, lenAlias, lenAlias2;
	fnCreateControlExtension pfnCreateControlExtension;
	fnRegisterClassStyle pfnRegisterClassStyle;
} ControlExtensionEntry;

// �ڲ�����ʽ����: 100 - 499
enum
{
	InternalIntName__First = 100,
	InternalIntName_ControlExtension = 100,
	InternalIntName_CDuiInlineControlBase,
	InternalIntName_CDuiInlineText,
	InternalIntName_CDuiAnchor,
	InternalIntName_CDuiBig,
	InternalIntName_CDuiBold,
	InternalIntName_CDuiFont,
	InternalIntName_CDuiHorizontalLine,
	InternalIntName_CDuiImg,
	InternalIntName_CDuiItalic,
	InternalIntName_CDuiLineBreak,
	InternalIntName_CDuiParagraph,
	InternalIntName_CDuiUnderline,
	InternalIntName_CDuiWhiteSpace,
	InternalIntName_CDuiSmall,
	InternalIntName_CDuiStrike,

	InternalIntName_CDuiButton,
	InternalIntName_CDuiOption,
	InternalIntName_CDuiCheckBox,
	InternalIntName_CDuiGroupBox,

	InternalIntName_CDuiWindowControl,
	InternalIntName_CDuiAxSite,
	InternalIntName_CDuiActiveX,
	InternalIntName_CDuiXcp,

	InternalIntName_CDuiOnChildWidthChanged,
	InternalIntName_CDuiCustomOrg,

	InternalIntName_CDuiLayout,
	InternalIntName_CDuiLayoutDialog,
	InternalIntName_CDuiLayoutHorizontal,
	InternalIntName_CDuiLayoutHorzSplitter,
	InternalIntName_CDuiLayoutPage,
	InternalIntName_CDuiLayoutSplitter,
	InternalIntName_CDuiLayoutTile,
	InternalIntName_CDuiLayoutVertical,
	InternalIntName_CDuiLayoutVertSplitter,
	InternalIntName_CDuiLayoutModeCoverFlow,

	InternalIntName_CDuiEditable,
	InternalIntName_CDuiEdit,
	InternalIntName_CDuiRichEdit,

	InternalIntName_CDuiController,
	InternalIntName_CDuiControllerListBase,
	InternalIntName_CDuiControllerList,
	InternalIntName_CDuiControllerListMulti,
	InternalIntName_CDuiList,
	InternalIntName_CDuiListFooter,
	InternalIntName_CDuiListHeader,
	InternalIntName_CDuiControllerListItemBase,

	InternalIntName_DuiLayout,
	InternalIntName_LayoutSplitter,
	InternalIntName_DefLayout,

	InternalIntName_LayoutVertical,
	InternalIntName_LayoutHorizontal,
	InternalIntName_LayoutTile,
	InternalIntName_LayoutDialog,
	InternalIntName_LayoutVerticalSplitter,
	InternalIntName_LayoutHorizontalSplitter,
	InternalIntName_LayoutPage,

	//InternalIntName_,
	//InternalIntName_,
	//InternalIntName_,
	//InternalIntName_,

	InternalIntName__Last = 499
};

// ͨ����չ�๤�ߺ�
#define DECLARE_CLASS_NAME(class, ...) public: static LPCWSTR __MyName() { return __if_exists(InternalIntName_##class){MakeIntName(InternalIntName_##class)} __if_not_exists(InternalIntName_##class){ L#class __pragma(message(#class " has no INT name.")) }; }
#define DECLARE_CLASS_NAME2(class, name) public: static LPCWSTR __MyName() { return L#name; }
#define DECLARE_CLASS_NAME_INT(n, ...) public: static LPCWSTR __MyName() { return MakeIntName(n); }	// �����ͽӿ�Ӧ��ʹ������ʽ���ƣ���ֱ���� == �ж������Ƿ���ͬ
//#define DECLARE_GET_CLASS_NAME(class) virtual LPCOLESTR GetName() const { return CLASS_NAME(class); }
//#define DECLARE_MODULE_HANDLE() virtual HINSTANCE GetModuleHandle() const { return _AtlBaseModule.GetModuleInstance(); }
#define DECLARE_DELETE_THIS(class) \
	virtual void Use(HANDLE h) \
	{ \
		__if_exists(class::__Use) { __Use(h); } \
		__if_exists(class::OnConnect) { OnConnect(); } \
	} \
	virtual void Unuse(HANDLE h) \
	{ \
		__if_exists(class::__Unuse) { __Unuse(h); } \
		__if_exists(class::OnDisconnect) { OnDisconnect(); } \
		delete this; \
	}

#define DECLARE_NO_DELETE_THIS(class) \
	virtual void Use(HANDLE h) \
	{ \
		__if_exists(class::__Use) { __Use(h); } \
		__if_exists(class::OnConnect) { OnConnect(); } \
	} \
	virtual void Unuse(HANDLE h) \
	{ \
		__if_exists(class::__Unuse) { __Unuse(h); } \
		__if_exists(class::OnDisconnect) { OnDisconnect(); } \
	}

#define DECLARE_HAS_NAME(class, factory, maptype) \
	public: static BOOL __HasName(LPCOLESTR name) \
	{ \
		extern factory maptype##class; \
		factory* f = &maptype##class; \
		if (name==NULL || *name==0) return FALSE; \
		BOOL isInt = (HIWORD(name)==0); \
		if (f->szName==name || (f->szAlias==name) || (f->szAlias2==name)) return TRUE; \
		if (!isInt && ((lstrcmpiW(f->szName,name)==0) || (f->szAlias && lstrcmpiW(f->szAlias,name)==0) || (f->szAlias2 && lstrcmpiW(f->szAlias2,name)==0))) return TRUE; \
		return FALSE; \
	}
#define CLASS_NAME(class) class::__MyName()
//#define CLASS_NAME_BASE(class) class::__MyName()

#define DECLARE_EXTENSION(class) \
public: \
	DECLARE_CLASS_NAME(class) \
	/*DECLARE_GET_CLASS_NAME(class)*/ \
	DECLARE_DELETE_THIS(class)

#define DECLARE_EXTENSION2(class, name) \
public: \
	DECLARE_CLASS_NAME2(class, name) \
	/*DECLARE_GET_CLASS_NAME(class)*/ \
	DECLARE_DELETE_THIS(class)

// �ؼ���չʵ�������������к�
#define DECLARE_CONTROL_EXTENSION(class) \
public: \
	DECLARE_EXTENSION(class) \
	/*DECLARE_EXTENSION2(class, control_name)*/ \
	/*__if_exists(__ctrlext_##class) {DECLARE_HAS_NAME(class, ControlExtensionEntry, __ctrlext_)}*/ \
	static IExtension* CALLBACK CreateMyself() { return NEW class; }

// ÿ���ؼ�ʵ����Ӧ�����ඨ���ⲿ��������
#define THIS_IS_CONTROL_EXTENSION_BASE(class, name, alias1, alias2) \
	__declspec(selectany) ControlExtensionEntry __ctrlext_##class = {name, alias1, alias2, lstrlenW(name), alias1?lstrlenW(alias1):0, alias2?lstrlenW(alias2):0, \
			class::CreateMyself, \
			__if_exists(class::__RegisterMyClassStyle){class::__RegisterMyClassStyle} __if_not_exists(class::__RegisterMyClassStyle){NULL}}; \
	extern "C" __declspec(allocate("DirectUI$__b")) __declspec(selectany) ControlExtensionEntry* const __pctrlext_##class = &__ctrlext_##class; \
	__pragma(comment(linker, "/include:___pctrlext_" #class));

#define THIS_IS_CONTROL_EXTENSION(class, name) THIS_IS_CONTROL_EXTENSION_BASE(class, L#name, NULL, NULL)
#define THIS_IS_CONTROL_EXTENSION2(class, name, alias) THIS_IS_CONTROL_EXTENSION_BASE(class, L#name, L#alias, NULL)
#define THIS_IS_CONTROL_EXTENSION3(class, name, alias, alias2) THIS_IS_CONTROL_EXTENSION_BASE(class, L#name, L#alias, L#alias2)


// ͨ���ؼ�ʵ������г�ʼ����STYLE�����������������ӳ�ʼ����񴮣���������ʹ��UNICODE������NULL
#define BEGIN_CLASS_STYLE_MAP( default_class_style) \
public: \
	static void CALLBACK __RegisterMyClassStyle(HWND hwnd, LPCOLESTR lpszName=NULL) \
	{ \
		/*if (lpszName==NULL) lpszName = class::__MyName();*/ \
		if (lpszName==NULL || *lpszName==0) return; \
		static const struct {DWORD _state; LPCOLESTR _style;} __stylesEntry[] = { \
			{0, L##default_class_style},

#define STATE_STYLE(state, style) {state, L##style},

#define END_CLASS_STYLE_MAP() \
		}; \
		__super::__RegisterMyClassStyle(hwnd, lpszName); \
		for (int i=0; i<sizeof(__stylesEntry)/sizeof(__stylesEntry[0]); i++) \
			::ParseStyle(hwnd, lpszName, __stylesEntry[i]._state, __stylesEntry[i]._style); \
	}

#define DECLARE_BASE_CLASS_STYLE(default_class_style) \
	BEGIN_CLASS_STYLE_MAP(default_class_style) \
	END_CLASS_STYLE_MAP()

#define DECLARE_CONTROL_FLAGS(x) public: virtual UINT OnGetControlFlags(HANDLE) {return x;}

// CastToClass (class cast)
#define DECLARE_BASE_CLASS_CAST(class, ...) \
public: \
	DECLARE_CLASS_NAME(class) \
	DECLARE_CLASS_CAST(class, __VA_ARGS__)

	//virtual LPVOID CastToClass(LPCOLESTR szName=NULL) \
	//{ \
	//	if (szName==CLASS_NAME(class) || lstrcmpiW(szName, CLASS_NAME(class))==0) return (class*)this; \
	//	__if_exists(class::CastToExt) { LPVOID p=class::CastToExt(szName); if (p) return p; } \
	//	return NULL; \
	//}

#define DECLARE_CLASS_CAST(class, ...) \
public: \
	virtual void* CastToClass(LPCWSTR szName) \
	{ \
		return __dui_base::__CastHelperT<class, __VA_ARGS__>::Cast2Class(this, szName); \
	}

//#define DECLARE_CLASS_CAST2(class, base_class, base_class2) DECLARE_CLASS_CAST(class, base_class, base_class2)

#define CLASS_CAST(ctrl, class) static_cast<class*>((ctrl)->CastToClass(CLASS_NAME(class)))


//////////////////////////////////////////////////////////////////////////
// ����ģʽʵ����ʹ������ĺ�
//typedef CDuiLayoutModeBase* (CALLBACK* fnCreateLayoutMode)(CDuiControlExtensionBase*);
//
//typedef struct DuiLayoutModeFactroyEntry 
//{
//	LPCOLESTR szName, szAlias, szAlias2;
//	int lenName, lenAlias, lenAlias2;
//	fnCreateLayoutMode pfnCreateLayoutMode;
//} DuiLayoutModeFactroyEntry;
//
//#define DECLARE_LAYOUT_MODE(class, mode) \
//public: \
//	DECLARE_EXTENSION2(class, mode) \
//	DECLARE_HAS_NAME(class, DuiLayoutModeFactroyEntry, __modeMap_) \
//	static CDuiLayoutModeBase* CALLBACK CreateMyself(CDuiControlExtensionBase* owner) { CDuiLayoutModeBase* p=NEW class; return p?(p->SetOwner(owner), p):NULL; }
//
//#define IMPLEMENT_LAYOUT_MODE_BASE(class, alias1, alias2) \
//	__declspec(selectany) DuiLayoutModeFactroyEntry __modeMap_##class = {CLASS_NAME(class), alias1, alias2, lstrlenW(CLASS_NAME(class)), alias1?lstrlenW(alias1):0, alias2?lstrlenW(alias2):0, class::CreateMyself}; \
//	extern "C" __declspec(allocate("DirectUI$__e")) __declspec(selectany) DuiLayoutModeFactroyEntry* const __pmodeMap_##class = &__modeMap_##class; \
//	__pragma(comment(linker, "/include:___pmodeMap_" #class));
//
//#define IMPLEMENT_LAYOUT_MODE(class) IMPLEMENT_LAYOUT_MODE_BASE(class, NULL, NULL)
//#define IMPLEMENT_LAYOUT_MODE2(class, alias) IMPLEMENT_LAYOUT_MODE_BASE(class, L#alias, NULL)
//#define IMPLEMENT_LAYOUT_MODE3(class, alias, alias2) IMPLEMENT_LAYOUT_MODE_BASE(class, L#alias, L#alias2)


//////////////////////////////////////////////////////////////////////////
// �Ӿ� ʵ����ʹ������ĺ�
//typedef CDuiVisualBase* (CALLBACK* fnCreateVisual)(CDuiControlExtensionBase*);
//
//struct DuiVisualFactroyEntry
//{
//	LPCOLESTR szName;
//	int lenName;
//	fnCreateVisual pfnCreateVisual;
//};
//
//#define DECLARE_VISUAL(class, name) \
//public: \
//	DECLARE_EXTENSION2(class, name) \
//	static CDuiVisualBase* CALLBACK CreateMyself(CDuiControlExtensionBase* owner) { CDuiVisualBase* p=NEW class; return p?(p->SetOwner(owner), p):NULL; }
//
//#define IMPLEMENT_VISUAL(class) \
//	__declspec(selectany) DuiVisualFactroyEntry __visualMap_##class = {CLASS_NAME(class), lstrlenW(CLASS_NAME(class)), class::CreateMyself}; \
//	extern "C" __declspec(allocate("DirectUI$__h")) __declspec(selectany) DuiVisualFactroyEntry* const __pvisualMap_##class = &__visualMap_##class; \
//	__pragma(comment(linker, "/include:___pvisualMap_" #class));


//////////////////////////////////////////////////////////////////////////
// ע�⣺ʹ��Сд��ĸ��������;

typedef enum
{
	DUIET__FIRST = 0,	DUIET__INVALID = DUIET__FIRST,
	DUIET_mousemove,	DUIET_MOUSEBEGIN = DUIET_mousemove,
	DUIET_mouseleave,	DUIET_mouseout = DUIET_mouseleave,
	DUIET_mouseenter,	DUIET_mouseover = DUIET_mouseenter,
	DUIET_mousehover,
	DUIET_buttondown,
	DUIET_buttonup,
	DUIET_click,
	DUIET_dblclick,
	DUIET_contextmenu,
	DUIET_vscroll,
	DUIET_hscroll,
	DUIET_scrollwheel,	DUIET_MOUSEEND = DUIET_scrollwheel,
	DUIET_keydown,		DUIET_KEYBEGIN = DUIET_keydown,
	DUIET_keyup,
	DUIET_char,
	DUIET_syskey,		DUIET_KEYEND = DUIET_syskey,
	DUIET_killfocus,	DUIET_blur = DUIET_killfocus,
	DUIET_setfocus,		DUIET_focus = DUIET_setfocus,
	DUIET_size,
	//DUIET_setcursor,
	DUIET_measureitem,
	DUIET_drawitem,
	DUIET_timer,
	DUIET_notify,
	DUIET_command,
	DUIET_load,
	DUIET_unload,
	DUIET_propertychange,
	DUIET__LAST,

} DUI_EVENTTYPE;

#define event_type_to_name(type) (LPCOLESTR)(type)

typedef enum
{
	DUIRT_CONTENT	= 0,
	DUIRT_PADDING,
	DUIRT_INSIDEBORDER,	// �Ӿ���ʽ����ռ�ݱ߽��PADDING֮��Ŀռ䣬�˱�־������䱳�������õ�
	DUIRT_BORDER,
	DUIRT_MARGIN,
	DUIRT_TOTAL = DUIRT_MARGIN,
} DUI_RECTTYPE;

typedef enum
{
	DUIPOS_DEFAULT	= 0,
	DUIPOS_STATIC	= DUIPOS_DEFAULT,	// Ĭ�϶�λģʽ���ɲ�����ʽ����λ��
	DUIPOS_RELATIVE,					// ���λ�ã�������ʽ�����ο�λ�ã�left/top����ƫ��������Ԫ��
	DUIPOS_ABSOLUTE,					// ����λ�ã�����ھ߱�POSITION��ʽ�ĸ�Ԫ�ػ��Ԫ�أ�left/top/bottom/right/width/height����λ�ã�������Ԫ��
	DUIPOS_FIXED,						// �̶�λ�ã�����ڴ��ڿͻ����������κβ�����ʽ��Ӱ�죬left/top/bottom/right/width/height����λ�ã�������Ԫ��
} DUI_POSITION;

//////////////////////////////////////////////////////////////////////////
//

// Flags for GetControlFlags()
#define DUIFLAG_TABSTOP			0x00000001
#define DUIFLAG_WANTRETURN		0x00000002
#define DUIFLAG_SETCURSOR		0x00000004
#define DUIFLAG_SELECTABLE		0x00000008
#define DUIFLAG_EXPANDABLE		0x00000010
#define DUIFLAG_NOFOCUSFRAME	0x00000020
#define DUIFLAG_NOCHILDREN		0x00000040 // ��Щ�ؼ������ⲿ���ݣ����������ӿؼ����������������ӿؼ��������ƻ���Ӧ�¼������ܷ����ӿؼ��������ԡ��˱�־�ݲ�֧��XML������

// Flags for FindControl()
#define DUIFIND_ALL           0x00000000
#define DUIFIND_VISIBLE       0x00000001
#define DUIFIND_ENABLED       0x00000002
#define DUIFIND_HITTEST       0x00000004
#define DUIFIND_ME_FIRST      0x80000000

// Flags for GetStyleAttribute MATCH MASK
#define DUISTYLEMATCH_NAME		0x00000001
#define DUISTYLEMATCH_ID		0x00000002
#define DUISTYLEMATCH_STATE		0x00000004
#define DUISTYLEMATCH_PARENT	0x00000008
#define DUISTYLEMATCH_NAME_ID	(DUISTYLEMATCH_NAME | DUISTYLEMATCH_ID)
#define DUISTYLEMATCH_ALL		(DUISTYLEMATCH_NAME | DUISTYLEMATCH_ID | DUISTYLEMATCH_STATE | DUISTYLEMATCH_PARENT)

// Flags for overflow
typedef enum
{
	OVERFLOW_AUTO		= 0,	// default
	OVERFLOW_HIDDEN,
	OVERFLOW_SCROLL
} DuiOverflowType;

// Flags for display
#define DUIDISPLAY_NONE		0x00000001	// �ݲ�֧�֣���Ϊ��DUISTATE��ͻ
#define DUIDISPLAY_INLINE	0x00000002	// default, HRGN is valid
#define DUIDISPLAY_BLOCK	0x00000004	// RECT is valid
#define DUIDISPLAY_INLINEBLOCK (DUIDISPLAY_INLINE | DUIDISPLAY_BLOCK) // RECT is valid


//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
// style attributes
//typedef enum
//{
//	SAT__UNKNOWN = 0,
//	SAT_COLOR,				// color(COLOR)
//	SAT_FONT,				// font(FONT)
//	SAT_TEXT_STYLE,			// text-style(LONG)
//	SAT_CURSOR,				// cursor(CURSOR)
//	SAT_LINE_DISTANCE,		// line-distance(LONG)
//
//	SAT__NO_PARENT,			// >>>> ���µ����ݱ�ʾ���Բ����ԴӸ�Ԫ���м̳�
//
//	SAT_BACKGROUND,			// background(COLOR | ICON | BITMAP | EXTERNAL)
//	SAT_FOREGROUND,			// foreground(COLOR | ICON | BITMAP | EXTERNAL)
//	SAT_FLAG,				// flag(LONG) DUIFLAG_TABSTOP|WANTRETURN
//	SAT_HITTEST_AS,			// hittest_as(LONG) // return while WM_NCHITTEST
//
//	SAT_MARGIN,				// margin(RECT)
//	SAT_PADDING,			// padding(RECT)
//	SAT_BORDER,				// border(PEN)
//
//	SAT_WIDTH,				// width(LONG/PERCENT/AUTO)
//	SAT_HEIGHT,				// height(LONG/PERCENT/AUTO)
//	SAT_MINWIDTH,			// min-width(LONG/PERCENT)
//	SAT_MINHEIGHT,			// min-height(LONG/PERCENT)
//
//	// left/top/right/bottom/width/height����position��ʽ������ʱ���ձ��ο�����ĸ��������ƫ��ֵ������left������ߣ�top�����ϱߣ�right�����ұ�,bottom���յױ�
//	// ����ʹ��auto��Ϊֵ��ǰ��������������ֵ����������� left:10;width:50;right:auto; ��ʾright = left + width
//	SAT_LEFT,				// left(LONG/PERCENT/AUTO)
//	SAT_TOP,				// top(LONG/PERCENT/AUTO)
//	SAT_RIGHT,				// right(LONG/PERCENT/AUTO)
//	SAT_BOTTOM,				// bottom(LONG/PERCENT/AUTO)
//	SAT_POSITION,			// position(LONG), static(default)/relative/absolute/fixed
//	SAT_ZINDEX,				// z-index(LONG), default:0
//
//	SAT_STRETCH,			// stretch mode(LONG) when parent control's layout mode is dialog
//	SAT_DIALOG_ITEM_POS,	// dailog item rect(RECT) when parent control's layout mode is dialog
//	SAT_COLUMNS,			// columns(LONG) when parent control's layout mode is tile
//
//	SAT_OVERFLOW,			// overflow(LONG) // auto(default) hidden scroll
//	SAT_OVERFLOW_INCLUDE_OFFSET,	// overflow-include-offset(BOOL) // false(default)
//	SAT_DISPLAY,			// display(LONG) // inline(default) inlineblock block none
//	SAT_LAYOUT,				// layout(STRING) // horizontal vertical tile dialog inline(default) // only for block/inlineblock
//	SAT_VISUAL,				// visual(STRING) // button checkbox ...
//	SAT_FILTER,				// filter(STRING) // wipe ...
//	SAT_CLIP,				// clip(STRING) // roundrect custom...
//} DuiStyleAttributeType;
//
//// Style variant type
//typedef enum
//{
//	SVT_EMPTY = 0,
//	SVT_BOOL = 0x00000001<<0,			// true|yes|1, false|no|0
//	SVT_LONG = 0x00000001<<1,			// 123
//	SVT_DOUBLE = 0x00000001<<2,			// 123.456
//	SVT_PERCENT = 0x00000001<<3,		// 40%
//	SVT_STRING = 0x00000001<<4,			// "abcd"
//	SVT_EXPRESSION = 0x00000001<<5,		// "abc()"
//	SVT_COLOR = 0x00000001<<6,			// [ThemeName ]ColorType, #080808
//	SVT_PEN = 0x00000001<<7,			// {ThemeName ]ColorType
//	SVT_FONT = 0x00000001<<8,			// [ThemeName ]FontType
//	SVT_BRUSH = 0x00000001<<9,
//	SVT_ICON = 0x00000001<<10,
//	SVT_BITMAP = 0x00000001<<11,
//	SVT_CURSOR = 0x00000001<<12,
//	SVT_RECT = 0x00000001<<13,			// left top right bottom
//	SVT_SIZE = 0x00000001<<14,			// cx cy
//	SVT_POINT = 0x00000001<<15,			// x y
//	SVT_EXTERNAL = 0x00000001<<16,		// external extension, such as GDI+::Image
//
//	// auto value
//	SVT_AUTO = 0x00000001<<31,			// auto is a "value", it has no real value.
//
//	// font mask
//	SVT_FONT_MASK_FAMILY	= 0x01000000,
//	SVT_FONT_MASK_SIZE		= 0x02000000,
//	SVT_FONT_MASK_STYLE		= 0x04000000,
//	SVT_FONT_MASK_ALL		= (SVT_FONT_MASK_FAMILY | SVT_FONT_MASK_SIZE | SVT_FONT_MASK_STYLE),
//	// pen mask
//	SVT_PEN_MASK_WIDTH		= 0x01000000,
//	SVT_PEN_MASK_STYLE		= 0x02000000,
//	SVT_PEN_MASK_COLOR		= 0x04000000,
//	SVT_PEN_MASK_ALL		= (SVT_PEN_MASK_WIDTH | SVT_PEN_MASK_STYLE | SVT_PEN_MASK_COLOR),
//	// all mask
//	SVT_MASK_ALL			= 0x00FFFFFF,
//} DuiStyleVariantType;
//
//// Style variant
//typedef struct tagDuiStyleVariant
//{
//	DuiStyleAttributeType sat;
//	DuiStyleVariantType svt;
//
//	union
//	{
//		BOOL boolVal;		// svt == SVT_BOOL
//		LONG longVal;		// svt == SVT_LONG
//		DOUBLE doubleVal;	// svt == SVT_DOUBLE or svt == SVT_PERCENT
//		LPCOLESTR strVal;	// svt == SVT_STRING or svt == SVT_EXPRESSION
//		COLORREF colorVal;	// svt == SVT_COLOR
//		LPLOGPEN penVal;		// svt == SVT_PEN
//		LPLOGFONTW fontVal;		// svt == SVT_FONT
//		HBRUSH brushVal;	// svt == SVT_BRUSH
//		HICON iconVal;		// svt == SVT_ICON or svt == SVT_CURSOR
//		HBITMAP bitmapVal;	// svt == SVT_BITMAP
//		//HCURSOR cursorVal;	// svt == SVT_CURSOR
//		LPRECT rectVal;		// svt == SVT_RECT
//		LPSIZE sizeVal;		// svt == SVT_SIZE
//		LPPOINT pointVal;	// svt == SVT_POINT
//		LPVOID extVal;		// svt == SVT_EXTERNAL
//	};
//} DuiStyleVariant;
//
//// style variant API
//DuiStyleVariant* WINAPI StyleVariantCreate();
//BOOL WINAPI StyleVariantInit(DuiStyleVariant* pVar);
//BOOL WINAPI StyleVariantClear(DuiStyleVariant* pVar);
//
//BOOL WINAPI StyleVariantIsEmpty(DuiStyleVariant* pVar);
//HPEN WINAPI StyleVariantGetPen(DuiStyleVariant* pVar, LPLOGPEN pRefPen);
//void WINAPI StyleVariantSetPen(DuiStyleVariant* pVal, LPLOGPEN pRefPen, LONG mask);
//HFONT WINAPI StyleVariantGetFont(DuiStyleVariant* pVar, LPLOGFONTW pRefFont);
//void WINAPI StyleVariantSetFont(DuiStyleVariant* pVar, LPLOGFONTW pRefFont, LONG mask);
//BOOL WINAPI StyleVariantGetLogBrush(DuiStyleVariant* pVar, LPLOGBRUSH pLogBrush);
//BOOL WINAPI StyleVariantGetBitmap(DuiStyleVariant* pVar, LPBITMAP pBitmap);
//LPVOID WINAPI StyleVariantGetExternal(DuiStyleVariant* pVar);
//
//
////////////////////////////////////////////////////////////////////////////
////
//
//// Structure for notifications from the system
//// to the control implementation.
//typedef struct tagDuiEvent
//{
//	LPCOLESTR Name; // HIWORD(Name)==0 is DUI_EVENTTYPE, HIWORD(Name)!=0 is event name string
//	HDE pSender;
//	DWORD dwTimestamp;
//	POINT ptMouse;
//	OLECHAR chKey;
//	WORD wKeyState;
//	LPCOLESTR pPropertyName;
//	WPARAM wParam; // ����¼����Կؼ��ڲ����������ֵ���ܰ��� DISPPARAMS* ��Ϊ�ص������Ĳ���
//	LPARAM lParam;
//	BOOL cancelBubble;
//	BOOL returnValue; // TRUE-stop continue, default is FALSE
//} DuiEvent;
//
////////////////////////////////////////////////////////////////////////////
//typedef struct
//{
//	HDE owner; // rc �� pt �ǹ������˿ؼ��ͻ�����
//	RECT rc;
//	POINT pt;				// ��ǰ��������
//	LONG cyCurLine;			// ��ǰ�е����ָ߶�
//	LONG cyMinHeight;		// ��ǰ�е���С�߶� >= ���ָ߶�
//	LONG cyTotalHeight;		// �ܸ߶�
//	LONG lLineIndent;		// ����
//	LONG lLineDistance;		// �м�࣬����ʱ�߶�Ӧ���� cyMinHeight + lLineDistance
//	UINT uTextStyle;		// �ı���ʽ
//
//	LPVOID pvReserved;
//} InDrawData;
//

//////////////////////////////////////////////////////////////////////////
// �¼���Ӧ���װ��
// �¼���Ӧ��ͨ��������ʵ�֣���������չ��ʵ�֣���ͨ��IExtension::CastToClass()���
// �¼���Ӧ�ӿ��ǹ����ģ�Ϊ������ַ����Ƚ����ܣ���������ʽ��������Χ�� 500-999
// ��չ�ӿڲ�ͬ�ڲ����ͨ���Ƕ�ʵ���ӿڣ����������ֻ��Ҫһ��ȫ��ʵ�����ɡ�Ϊ��ʹ���Ҳ��ʵ����չ������չ�������һ������Ϊһ�����������ǰ������

//#define SINK_CLASS(sinkname) ISink##sinkname
//
//#define DEFINE_SINK(sinkname, ...) \
//class SINK_CLASS(sinkname) \
//{ \
//	DECLARE_CLASS_NAME_INT(IntName_##sinkname) \
//public: virtual void sinkname( HANDLE h, __VA_ARGS__ ) = 0; \
//};
//
//#define DEFINE_SINK_TYPE(type, sinkname, ...) \
//class SINK_CLASS(sinkname) \
//{ \
//	DECLARE_CLASS_NAME_INT(IntName_##sinkname) \
//public: virtual type sinkname( HANDLE h, __VA_ARGS__ ) = 0; \
//};
//
//#define DEFINE_SINK_BOOL(sinkname, ...) DEFINE_SINK_TYPE(BOOL, sinkname, __VA_ARGS__)
//
//enum SinkName
//{
//	IntName_IsMyEvent = 500,
//	IntName_OnGetControlFlags,
//	IntName_OnAddChildNode,
//	IntName_OnStyleChanged,
//	IntName_OnStateChanged,
//	IntName_OnChildStateChanged,
//	IntName_OnAttributeChanged,
//	IntName_OnChildAttributeChanged,
//	IntName_OnAttributeRemoved,
//	IntName_OnChildAttributeRemoved,
//	IntName_OnChildAdded,
//	IntName_OnChildRemoved,
//	IntName_OnUpdateLayout,
//	IntName_OnPrepareDC,
//	IntName_OnScroll,
//	IntName_OnGetContentSize,
//	IntName_OnUpdate3DSurface,
//	IntName_OnUpdateInlineRegion,
//	IntName_OnReposInlineRect,
//	
//	IntName__Last = 999
//};
//
//// �¼������¼�
//DEFINE_SINK_BOOL(IsMyEvent, DuiEvent& event); // ����¼�����������TRUE�����򷵻�FALSE
////class CDuiSinkIsMyEvent : public CDuiSinkBase
////{
////	DECLARE_CLASS_NAME_INT(500)
////public:
////	virtual BOOL IsMyEvent(HANDLE h, DuiEvent& event) = 0; // ����¼�����������TRUE�����򷵻�FALSE
////};
//
//// �ؼ���־��ȡ�¼�
//DEFINE_SINK_TYPE(UINT, OnGetControlFlags); // ��ȡ�ؼ��Ŀ��Ʊ�־λ
//
//// ���ĳ��XML�ӽڵ��Ǹ��ؼ�ĳҪ�ص�ר���ӽڵ㣬ʵ�ִ˷�����Ҫ��Ӧ�÷���TRUE�������ٽ������ӿؼ�
//DEFINE_SINK_BOOL(OnAddChildNode, HANDLE hChild); // ���ؼ������ӽڵ��ǿؼ������ڲ���Դ
//
//// �ؼ�״̬�ı��¼�
//DEFINE_SINK(OnStateChanged, DWORD dwStateMask ); // �ؼ�״̬�����˸ı�
//
//// �ؼ���ʽ���Ըı��¼�
//DEFINE_SINK(OnStyleChanged, DuiStyleVariant* newval); // �ؼ�˽����ʽ���Է����˸ı䣬�ı��ֵ�ڲ�����
//
//// �ӿؼ�״̬�ı��¼�
//DEFINE_SINK_BOOL(OnChildStateChanged, HDE pChild, DWORD dwStateMask); // �ӿؼ���״̬�����˸ı�
//
//// �ؼ����Ըı��¼�
//DEFINE_SINK(OnAttributeChanged, LPCOLESTR szAttr); // �ؼ����Է����˸ı�
//
//// �ӿؼ����Ըı��¼�
//DEFINE_SINK(OnChildAttributeChanged, HDE pChild, LPCOLESTR szAttr); // �ӿؼ������Է����˸ı�
//
//// �ؼ�������ɾ���¼�
//DEFINE_SINK(OnAttributeRemoved, LPCOLESTR szAttr); // �ؼ�������ɾ��
//
//// �ӿؼ�������ɾ���¼�
//DEFINE_SINK(OnChildAttributeRemoved, HDE pChild, LPCOLESTR szAttr); // �ӿؼ�������ɾ��
//
//// �ӿؼ������¼�
//DEFINE_SINK(OnChildAdded, HDE pChild); // �ӿؼ��Ѿ������
//
//// �ӿؼ�ɾ���¼�
//DEFINE_SINK(OnChildRemoved, HDE pChild); // �ӿؼ�������ɾ��
//
//// ���ָ����¼�
//DEFINE_SINK_BOOL(OnUpdateLayout); // ��Ҫ�����Լ����ݵĲ��֣��������������TRUE�����򷵻�FALSE
//
////// �ӿؼ���С�ı��¼�
////DEFINE_SINK_BOOL(OnChildSizeChanged, CDuiControlExtensionBase* pChild); // �ӿؼ���С��Ҫ����
//
//// ׼���豸�����Ļ���
//DEFINE_SINK_BOOL(OnPrepareDC, HDC hdc); // �ؼ��Լ��������׼��HDC�ĳ�ʼ���ã�����Ѵ�����TRUE�� ���򷵻�FALSE
//
//// �ؼ�������λ�øı��¼�
//DEFINE_SINK(OnScroll, HDE pScroll, BOOL bVert=TRUE); // �ؼ�����λ�÷����˸ı䣬����¼��ᷢ�� pScroll �ؼ����������ӿؼ�
//
//// ����ؼ��Լ����ṩ���ݴ�С�Ĺ��㣬ʵ������¼�
//DEFINE_SINK(OnGetContentSize, SIZE& sz);
//
//// �ؼ��ṩ�Լ��Ĵ���/����3D���溯��
//DEFINE_SINK(OnUpdate3DSurface, RECT rc);
//
//// �����ؼ������Լ�������;���
//DEFINE_SINK(OnUpdateInlineRegion)
//
//// �����ؼ��Ե�ǰ�����µ���ƫ�ƺʹ�С��index��ʾ������ε�������cx��ʾˮƽƫ��ֵ���߶ȵ����ο�idd.cyMinHeight
//DEFINE_SINK(OnReposInlineRect, int index, long cx, InDrawData& idd)

//////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
// CDuiControllerBase �ǿ��������ࡣ�������������п��ƹ����ӿؼ���״̬����Ϊ������LIST/TREE/TABPAGEʹ�ò�ͬ�ķ�ʽ�����ӿؼ�״̬

//class CDuiControllerBase : public IControlExtension
//{
//	DECLARE_BASE_CLASS_CAST(CDuiControllerBase)
//public:
//	//virtual CDuiControlExtensionBase* GetOwner() const = 0;
//
//	virtual BOOL GetShortcut(CDuiControlExtensionBase* child, OLECHAR* pRet) { return FALSE; }
//	virtual BOOL SetShortcut(CDuiControlExtensionBase* child, OLECHAR ch) { return FALSE; }
//
//	virtual BOOL SetFocus(CDuiControlExtensionBase* child) { return FALSE; }
//
//	virtual BOOL GetState(CDuiControlExtensionBase* child, DWORD* pRet) { return FALSE; }
//	virtual BOOL SetState(CDuiControlExtensionBase* child, DWORD dwNewState, DWORD* pRet) { return FALSE; }
//	virtual BOOL ModifyState(CDuiControlExtensionBase* child, DWORD dwAdded, DWORD dwRemoved) { return FALSE; }
//	virtual BOOL HasState(CDuiControlExtensionBase* child, DWORD dwState, BOOL* pRet) { return FALSE; }
//
//	virtual BOOL Activate(CDuiControlExtensionBase* child, BOOL* pRet) { return FALSE; }
//	virtual BOOL IsVisible(CDuiControlExtensionBase* child, BOOL bRealResult, BOOL* pRet) { return FALSE; }
//	virtual BOOL IsEnabled(CDuiControlExtensionBase* child, BOOL bRealResult, BOOL* pRet) { return FALSE; }
//	virtual BOOL IsFocused(CDuiControlExtensionBase* child, BOOL* pRet) { return FALSE; }
//	virtual BOOL SetVisible(CDuiControlExtensionBase* child, BOOL bVisible) { return FALSE; }
//	virtual BOOL SetEnabled(CDuiControlExtensionBase* child, BOOL bEnable) { return FALSE; }
//
//	virtual BOOL GetPos(CDuiControlExtensionBase* child, DUI_RECTTYPE rt, RECT* pRet) { return FALSE; }
//	virtual BOOL SetPos(CDuiControlExtensionBase* child, RECT rc) { return FALSE; }
//
//	virtual BOOL EstimateSize(CDuiControlExtensionBase* child, SIZE szAvailable, SIZE* pRet) { return FALSE; }
//	virtual BOOL OnPaintContent(CDuiControlExtensionBase* child, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData& idd) { return FALSE; }
//};


//////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////
// CDuiOnChildWidthChanged �����û���κγ�Ա��Ψһ�����þ������ĳ���ؼ�ϣ������ֱ���ӿؼ���ȱ仯��֪ͨ����Ӧ����CASTʱ����һ����Ч��ָ��

class CDuiOnChildWidthChanged
{
	DECLARE_BASE_CLASS_CAST(CDuiOnChildWidthChanged)
};

//////////////////////////////////////////////////////////////////////////
//

typedef HDE (CALLBACK* FINDCONTROLPROC)(HDE, LPVOID);

typedef void (CALLBACK* EVENTCALLBACK)(HDE, DuiEvent&);


//////////////////////////////////////////////////////////////////////////
// ���������ࡣÿ����������һ�����������ԡ��ݲ���չ

class CDuiScrollbarBase
{
public:
	virtual HDE GetOwner() const = 0;
	virtual BOOL SetScrollRange(int nRange, BOOL bRedraw=FALSE) = 0; // ����TRUE��ʾ��ʾ״̬�����˱仯
	virtual int GetScrollPos() const = 0;
	virtual void SetScrollPos(int nPos, BOOL bRedraw=FALSE) = 0;
	//virtual int GetScrollPage() const = 0;
	virtual int GetScrollbarWidth() const = 0;
	virtual void ShowScrollbar(BOOL bShow) = 0;
	virtual void EnableScrollbar(BOOL bEnable) = 0;
	virtual BOOL IsValid() const = 0;

	virtual BOOL IsScrollEvent(DuiEvent& event) = 0; // ��������¼�Ӧ�÷���FALSE
};

//////////////////////////////////////////////////////////////////////////
// ����ģʽ���ࡣÿ��������ؼ�����һ������ģʽ

//class CDuiLayoutModeBase : public IControlExtension,
//						public CDuiSinkIsMyEvent,
//						public CDuiSinkOnUpdateLayout,
//						public CDuiSinkOnChildStateChanged
//{
//	DECLARE_BASE_CLASS_CAST(CDuiLayoutModeBase, CDuiSinkIsMyEvent, CDuiSinkOnUpdateLayout, CDuiSinkOnChildStateChanged)
//public:
//
//	//virtual BOOL OnUpdateLayout() = 0;
//	//virtual BOOL IsLayoutEvent(DuiEvent& event) = 0; // ��������¼�Ӧ�÷���FALSE
//	//virtual BOOL OnChildStateChanged(CDuiControlExtensionBase* pChild, DWORD dwStateMask) = 0;
//};

//////////////////////////////////////////////////////////////////////////
// ����Ӿ����ࡣ�ؼ�����ʹ���Ӿ���ʽ��������߿�ͱ����Ļ���

//class CDuiVisualBase : public CDuiExtension
//{
//	DECLARE_BASE_CLASS_CAST(CDuiVisualBase)
//public:
//	//virtual void DeleteThis() = 0; // delete this
//	virtual CDuiControlExtensionBase* GetOwner() const = 0;
//	virtual void SetOwner(CDuiControlExtensionBase* owner) = 0;
//
//	virtual RECT GetAdjustRect() const = 0;
//	// ���µĻ��ƺ��������Ҫ����Ĭ�ϻ��ƣ�Ӧ��ֱ�ӷ���FALSE
//	virtual BOOL OnPaintBorder(HDC hdc, RECT rcBorder) = 0;
//	virtual BOOL OnPaintBackground(HDC hdc, RECT rcBkgnd) = 0;
//	virtual BOOL OnPaintFocus(HDC hdc, RECT rcFocus) = 0;
//};

#endif // __DIRECTUI_H__