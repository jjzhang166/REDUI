#ifndef __DUIINLINE_H__
#define __DUIINLINE_H__

#pragma once

#include "DuiManager.h"

class CDuiInlineControlBase : public ControlExtension,
		public ISinkOnPrepareDC,
		public ISinkOnUpdateInlineRegion
{
	DECLARE_CLASS_NAME(CDuiInlineControlBase)
	DECLARE_CLASS_CAST(CDuiInlineControlBase, ControlExtension, ISinkOnPrepareDC, ISinkOnUpdateInlineRegion)
	DECLARE_BASE_CLASS_STYLE("display:inline")

	// ControlExtension
public:
	DuiNode* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);
	virtual BOOL OnPrepareDC(HANDLE, HDC) { return FALSE; }
	virtual void OnUpdateInlineRegion(HANDLE);
};

//////////////////////////////////////////////////////////////////////////
// InlineText ������������Ϣ�������ؼ�����ͬʱstyleҲʹ�ø��ؼ���

class CDuiInlineText : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiInlineText)
	DECLARE_CLASS_CAST(CDuiInlineText, CDuiInlineControlBase)
	DECLARE_BASE_CLASS_STYLE("overflow:hidden")

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
	//virtual RECT GetPos(DUI_RECTTYPE rt=DUIRT_CONTENT) { return m_rcItem; }
	virtual void SetAttribute(HDE hde, LPCWSTR szName, VARIANT* value);
	virtual void GetAttribute(HDE hde, LPCWSTR szName, VARIANT* value);
	virtual DuiStyleVariant* GetStyleAttribute(HDE hde, DuiStyleAttributeType sat, DuiStyleVariantType svt=SVT_EMPTY, DWORD dwMatchMask=0);
};

THIS_IS_CONTROL_EXTENSION(CDuiInlineText, InlineText)


//////////////////////////////////////////////////////////////////////////
// Anchor

class CDuiAnchor : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiAnchor)
	DECLARE_CONTROL_FLAGS(DUIFLAG_SETCURSOR|DUIFLAG_TABSTOP)
	DECLARE_CLASS_CAST(CDuiAnchor, CDuiInlineControlBase)

	BEGIN_CLASS_STYLE_MAP("color:#0000ff; cursor:hand; font-style:underline")
		STATE_STYLE(DUISTATE_HOT, "color:#ff0000")
	END_CLASS_STYLE_MAP()

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
	BOOL Activate(HDE hde);
};

THIS_IS_CONTROL_EXTENSION3(CDuiAnchor, Anchor, a, Link)

//////////////////////////////////////////////////////////////////////////
// Font  <font size=4 face="xxx" color="#xxx"></font>

class CDuiFont : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiFont)
	DECLARE_CLASS_CAST(CDuiFont, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiFont, Font, f)


//////////////////////////////////////////////////////////////////////////
// Bold  <b>...</b>

class CDuiBold : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiBold)
	DECLARE_CLASS_CAST(CDuiBold, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION3(CDuiBold, Bold, b, strong)

//////////////////////////////////////////////////////////////////////////
// Italic <i>...</i>

class CDuiItalic : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiItalic)
	DECLARE_CLASS_CAST(CDuiItalic, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiItalic, Italic, i)


//////////////////////////////////////////////////////////////////////////
// Underline <u>...</u>

class CDuiUnderline : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiUnderline)
	DECLARE_CLASS_CAST(CDuiUnderline, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiUnderline, Underline, u)


//////////////////////////////////////////////////////////////////////////
// Strike <s>...</s> ɾ���� StrikeOut | Strike-through

class CDuiStrike : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiStrike)
	DECLARE_CLASS_CAST(CDuiStrike, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiStrike, Strike, s)


//////////////////////////////////////////////////////////////////////////
// Big <big>...</big> �ȵ�ǰ������������

class CDuiBig : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiBig)
	DECLARE_CLASS_CAST(CDuiBig, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION(CDuiBig, Big)


//////////////////////////////////////////////////////////////////////////
// Small <small>...</small> �ȵ�ǰ�����С������

class CDuiSmall : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiSmall)
	DECLARE_CLASS_CAST(CDuiSmall, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION(CDuiSmall, Small)


//////////////////////////////////////////////////////////////////////////
// WhiteSpace  <w width=20 /> ����һ��20���ؿ�Ŀհף�Ĭ��12����

class CDuiWhiteSpace : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiWhiteSpace)
	DECLARE_CLASS_CAST(CDuiWhiteSpace, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiWhiteSpace, WhiteSpace, w)


//////////////////////////////////////////////////////////////////////////
// Paragraph  <p lineSpace="5" indent="10">...</p>
//		lineSpace; // �м�࣬Ĭ��5
//		indent; // ��������������, 0-100�� Ĭ��0

class CDuiParagraph : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiParagraph)
	DECLARE_CLASS_CAST(CDuiParagraph, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiParagraph, Paragraph, p)


//////////////////////////////////////////////////////////////////////////
// LineBreak  <br />

class CDuiLineBreak : public CDuiInlineControlBase
{
	DECLARE_CONTROL_EXTENSION(CDuiLineBreak)
	DECLARE_CLASS_CAST(CDuiLineBreak, CDuiInlineControlBase)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
	virtual void OnUpdateInlineRegion(HANDLE) {} // Do nothing
};

THIS_IS_CONTROL_EXTENSION2(CDuiLineBreak, LineBreak, br)


//////////////////////////////////////////////////////////////////////////
// HorizontalLine  <hr width="20" color="#8f8f8f" /> ��һ��20���س���ˮƽ��
//		width; // �ߵĳ��ȣ������0����ֱ�ӻ������ұߣ�Ĭ����0
//		color; // ������ɫ��Ĭ�ϻ�ɫ

class CDuiHorizontalLine : public CDuiInlineControlBase
			, public ISinkOnReposInlineRect
{
	DECLARE_CONTROL_EXTENSION(CDuiHorizontalLine)
	DECLARE_CLASS_CAST(CDuiHorizontalLine, CDuiInlineControlBase, ISinkOnReposInlineRect)

public:
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
	virtual void OnReposInlineRect(HANDLE, int index, long cx, InDrawData* pidd);
};

THIS_IS_CONTROL_EXTENSION2(CDuiHorizontalLine, HorizontalLine, hr)


//////////////////////////////////////////////////////////////////////////
// Img  <img src="bmp1" width="20" height="20" />
//		width;	// ������Ϊ0������Ĭ��ͼƬ���
//		height;	// ����߶�Ϊ0������Ĭ��ͼƬ�߶�
//		src;	// ָʾͼƬ��Դ��ID

class CDuiImg : public CDuiInlineControlBase
	, public CDuiConnectorCallback
	//, public SINK_CLASS(OnUpdate3DSurface)
{
	DECLARE_CONTROL_EXTENSION(CDuiImg)
	DECLARE_CLASS_CAST(CDuiImg, CDuiInlineControlBase/*, SINK_CLASS(OnUpdate3DSurface)*/)
	DECLARE_BASE_CLASS_STYLE("min-width:0;min-height:0;")

public:
	~CDuiImg();
	virtual void OnPaintContent(HDE hde, HDC hdc, RECT rcPaint, BOOL bDraw, InDrawData* pidd);
	virtual void SetAttribute(HDE hde, LPCWSTR szName, VARIANT* value);

	// CDuiConnectorCallback method
	virtual BOOL OnHit(LPVOID pKey, LPVOID pVal, DWORD flag);

	// SINK_CLASS(OnCreate3DSurface) method
	//virtual void OnUpdate3DSurface(HANDLE, RECT rc);

protected:
	void __updateSize();
};

THIS_IS_CONTROL_EXTENSION(CDuiImg, Img)


#endif // __DUIINLINE_H__