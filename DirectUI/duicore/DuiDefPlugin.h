#ifndef DuiDefPlugin_h__
#define DuiDefPlugin_h__

#include "DuiPluginsManager.h"

class DefPlugin : public ReduiPlugin<DefPlugin>
{
	int __NoAutoRegister; // ռλ����������ֹ�Զ�ע����

public:
	DefPlugin();
	~DefPlugin();

	LPCWSTR GetNormalName(LPCWSTR szAlias, LPCWSTR szNameType);
	int Test(int n1, int n2, int n3);
	IVisual* QueryVisual(LPCWSTR szVisualName);
	BOOL PaintBorder(HDE hde, HDC hdc, RECT rcBorder);
	BOOL PaintFocus(HDE hde, HDC hdc, RECT rcFocus, HRGN hrgn);
	BOOL PaintBackground(HDE hde, HDC hdc, RECT rcBkgnd);
	BOOL PaintForeground(HDE hde, HDC hdc, RECT rcFrgnd);

	ILayout* QueryLayout(LPCWSTR szLayoutName);
	BOOL OnUpdateLayout(HDE hde);
};

#endif // DuiDefPlugin_h__