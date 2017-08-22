#include "stdafx.h"
#include "DuiStyleParser.h"

//////////////////////////////////////////////////////////////////////////
// ������ɫ��  �ο�������ɫ���ɷ��� http://www.lioil.net/lbs/article.asp?id=111

#define __foreach_named_color(V) \
	V(LightPink, ǳ�ۺ�, FFB6C1, 255,182,193) \
	V(Pink, �ۺ�, FFC0CB, 255,192,203) \
	V(Crimson, �ɺ� (���), DC143C, 220,20,60) \
	V(LavenderBlush, ���Ϻ�, FFF0F5, 255,240,245) \
	V(PaleVioletRed, ����������, DB7093, 219,112,147) \
	V(HotPink, ����ķۺ�, FF69B4, 255,105,180) \
	V(DeepPink, ��ۺ�, FF1493, 255,20,147) \
	V(MediumVioletRed, ����������, C71585, 199,21,133) \
	V(Orchid, ������, DA70D6, 218,112,214) \
	V(Thistle, ��, D8BFD8, 216,191,216) \
	V(Plum, ������, DDA0DD, 221,160,221) \
	V(Violet, ������, EE82EE, 238,130,238) \
	V(Magenta, ��� (Ʒ�� õ���), FF00FF, 255,0,255) \
	V(Fuchsia, ��������(�Ϻ�ɫ), FF00FF, 255,0,255) \
	V(DarkMagenta, �����, 8B008B, 139,0,139) \
	V(Purple, ��ɫ, 800080, 128,0,128) \
	V(MediumOrchid, ��������, BA55D3, 186,85,211) \
	V(DarkViolet, ��������, 9400D3, 148,0,211) \
	V(DarkOrchid, ��������, 9932CC, 153,50,204) \
	V(Indigo, ���� (����ɫ), 4B0082, 75,0,130) \
	V(BlueViolet, ��������, 8A2BE2, 138,43,226) \
	V(MediumPurple, ����ɫ, 9370DB, 147,112,219) \
	V(MediumSlateBlue, �а�����, 7B68EE, 123,104,238) \
	V(SlateBlue, ������, 6A5ACD, 106,90,205) \
	V(DarkSlateBlue, ��������, 483D8B, 72,61,139) \
	V(Lavender, Ѭ�²ݵ���, E6E6FA, 230,230,250) \
	V(GhostWhite, �����, F8F8FF, 248,248,255) \
	V(Blue, ����, 0000FF, 0,0,255) \
	V(MediumBlue, ����ɫ, 0000CD, 0,0,205) \
	V(MidnightBlue, ��ҹ��, 191970, 25,25,112) \
	V(DarkBlue, ����ɫ, 00008B, 0,0,139) \
	V(Navy, ������, 000080, 0,0,128) \
	V(RoyalBlue, �ʼ��� (����), 4169E1, 65,105,225) \
	V(CornflowerBlue, ʸ������, 6495ED, 100,149,237) \
	V(LightSteelBlue, ������, B0C4DE, 176,196,222) \
	V(LightSlateGray, ��ʯ���, 778899, 119,136,153) \
	V(SlateGray, ʯ���, 708090, 112,128,144) \
	V(DodgerBlue, ������, 1E90FF, 30,144,255) \
	V(AliceBlue, ����˿��, F0F8FF, 240,248,255) \
	V(SteelBlue, ���� (����), 4682B4, 70,130,180) \
	V(LightSkyBlue, ������ɫ, 87CEFA, 135,206,250) \
	V(SkyBlue, ����ɫ, 87CEEB, 135,206,235) \
	V(DeepSkyBlue, ������, 00BFFF, 0,191,255) \
	V(LightBlue, ����, ADD8E6, 173,216,230) \
	V(PowderBlue, ��ҩ��, B0E0E6, 176,224,230) \
	V(CadetBlue, ������, 5F9EA0, 95,158,160) \
	V(Azure, ε��ɫ, F0FFFF, 240,255,255) \
	V(LightCyan, ����ɫ, E0FFFF, 224,255,255) \
	V(PaleTurquoise, ���̱�ʯ, AFEEEE, 175,238,238) \
	V(Cyan, ��ɫ, 00FFFF, 0,255,255) \
	V(Aqua, ˮɫ, 00FFFF, 0,255,255) \
	V(DarkTurquoise, ���̱�ʯ, 00CED1, 0,206,209) \
	V(DarkSlateGray, ��ʯ���, 2F4F4F, 47,79,79) \
	V(DarkCyan, ����ɫ, 008B8B, 0,139,139) \
	V(Teal, ˮѼɫ, 008080, 0,128,128) \
	V(MediumTurquoise, ���̱�ʯ, 48D1CC, 72,209,204) \
	V(LightSeaGreen, ǳ������, 20B2AA, 32,178,170) \
	V(Turquoise, �̱�ʯ, 40E0D0, 64,224,208) \
	V(Aquamarine, ��ʯ����, 7FFFD4, 127,255,212) \
	V(MediumAquamarine, �б�ʯ����, 66CDAA, 102,205,170) \
	V(MediumSpringGreen, �д���ɫ, 00FA9A, 0,250,154) \
	V(MintCream, ��������, F5FFFA, 245,255,250) \
	V(SpringGreen, ����ɫ, 00FF7F, 0,255,127) \
	V(MediumSeaGreen, �к�����, 3CB371, 60,179,113) \
	V(SeaGreen, ������, 2E8B57, 46,139,87) \
	V(Honeydew, �۹�ɫ, F0FFF0, 240,255,240) \
	V(LightGreen, ����ɫ, 90EE90, 144,238,144) \
	V(PaleGreen, ����ɫ, 98FB98, 152,251,152) \
	V(DarkSeaGreen, ��������, 8FBC8F, 143,188,143) \
	V(LimeGreen, ��������, 32CD32, 50,205,50) \
	V(Lime, ������, 00FF00, 0,255,0) \
	V(ForestGreen, ɭ����, 228B22, 34,139,34) \
	V(Green, ����, 008000, 0,128,0) \
	V(DarkGreen, ����ɫ, 006400, 0,100,0) \
	V(Chartreuse, ���ؾ��� (����ɫ), 7FFF00, 127,255,0) \
	V(LawnGreen, ��ƺ��, 7CFC00, 124,252,0) \
	V(GreenYellow, �̻�ɫ, ADFF2F, 173,255,47) \
	V(DarkOliveGreen, �������, 556B2F, 85,107,47) \
	V(YellowGreen, ����ɫ, 9ACD32, 154,205,50) \
	V(OliveDrab, ��魺�ɫ, 6B8E23, 107,142,35) \
	V(Beige, ��ɫ(����ɫ), F5F5DC, 245,245,220) \
	V(LightGoldenrodYellow, ���ջ�, FAFAD2, 250,250,210) \
	V(Ivory, ����, FFFFF0, 255,255,240) \
	V(LightYellow, ǳ��ɫ, FFFFE0, 255,255,224) \
	V(Yellow, ����, FFFF00, 255,255,0) \
	V(Olive, ���, 808000, 128,128,0) \
	V(DarkKhaki, �ߴ��, BDB76B, 189,183,107) \
	V(LemonChiffon, ���ʳ�, FFFACD, 255,250,205) \
	V(PaleGoldenrod, �Ҿջ�, EEE8AA, 238,232,170) \
	V(Khaki, ��ߴ��, F0E68C, 240,230,140) \
	V(Gold, ��ɫ, FFD700, 255,215,0) \
	V(Cornsilk, ����˿ɫ, FFF8DC, 255,248,220) \
	V(Goldenrod, ��ջ�, DAA520, 218,165,32) \
	V(DarkGoldenrod, ����ջ�, B8860B, 184,134,11) \
	V(FloralWhite, ���İ�ɫ, FFFAF0, 255,250,240) \
	V(OldLace, ����˿, FDF5E6, 253,245,230) \
	V(Wheat, С��ɫ, F5DEB3, 245,222,179) \
	V(Moccasin, ¹Ƥѥ, FFE4B5, 255,228,181) \
	V(Orange, ��ɫ, FFA500, 255,165,0) \
	V(PapayaWhip, ��ľ��, FFEFD5, 255,239,213) \
	V(BlanchedAlmond, ���׵�����ɫ, FFEBCD, 255,235,205) \
	V(NavajoWhite, ������, FFDEAD, 255,222,173) \
	V(AntiqueWhite, �Ŷ���, FAEBD7, 250,235,215) \
	V(Tan, ��ɫ, D2B48C, 210,180,140) \
	V(BurlyWood, Ӳľɫ, DEB887, 222,184,135) \
	V(Bisque, ������, FFE4C4, 255,228,196) \
	V(DarkOrange, ���ɫ, FF8C00, 255,140,0) \
	V(Linen, ���鲼, FAF0E6, 250,240,230) \
	V(Peru, ��³, CD853F, 205,133,63) \
	V(PeachPuff, ����ɫ, FFDAB9, 255,218,185) \
	V(SandyBrown, ɳ��ɫ, F4A460, 244,164,96) \
	V(Chocolate, �ɿ���, D2691E, 210,105,30) \
	V(SaddleBrown, ����ɫ, 8B4513, 139,69,19) \
	V(Seashell, ������, FFF5EE, 255,245,238) \
	V(Sienna, ������ɫ, A0522D, 160,82,45) \
	V(LightSalmon, ǳ������ɫ, FFA07A, 255,160,122) \
	V(Coral, ɺ��, FF7F50, 255,127,80) \
	V(OrangeRed, �Ⱥ�ɫ, FF4500, 255,69,0) \
	V(DarkSalmon, ������(����)ɫ, E9967A, 233,150,122) \
	V(Tomato, ���Ѻ�, FF6347, 255,99,71) \
	V(MistyRose, ����õ��, FFE4E1, 255,228,225) \
	V(Salmon, ����(����)ɫ, FA8072, 250,128,114) \
	V(Snow, ѩ, FFFAFA, 255,250,250) \
	V(LightCoral, ��ɺ��ɫ, F08080, 240,128,128) \
	V(RosyBrown, õ����ɫ, BC8F8F, 188,143,143) \
	V(IndianRed, ӡ�Ⱥ�, CD5C5C, 205,92,92) \
	V(Red, ����, FF0000, 255,0,0) \
	V(Brown, ��ɫ, A52A2A, 165,42,42) \
	V(FireBrick, �ͻ�ש, B22222, 178,34,34) \
	V(DarkRed, ���ɫ, 8B0000, 139,0,0) \
	V(Maroon, ��ɫ, 800000, 128,0,0) \
	V(White, ����, FFFFFF, 255,255,255) \
	V(WhiteSmoke, ����, F5F5F5, 245,245,245) \
	V(Gainsboro, ��˹���޻�ɫ, DCDCDC, 220,220,220) \
	V(LightGrey, ǳ��ɫ, D3D3D3, 211,211,211) \
	V(Silver, ����ɫ, C0C0C0, 192,192,192) \
	V(DarkGray, ���ɫ, A9A9A9, 169,169,169) \
	V(Gray, ��ɫ, 808080, 128,128,128) \
	V(DimGray, �����Ļ�ɫ, 696969, 105,105,105) \
	V(Black, ����, 000000, 0,0,0)

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//
void EraseSplash(LPCOLESTR szData, LPOLESTR szDst)
{
	if (szData==NULL || szDst==NULL) return;

	while (*szData != 0)
	{
		if (*szData == L'\\')
		{
			szData++;
			if (*szData == 0)
			{
				*szDst++ = L'\\';
				break;
			}

			*szDst = *szData++;
			switch (*szDst)
			{
			case L'0': *szDst++ = L'\0'; break;
			case L't': *szDst++ = L'\t'; break;
			case L'r': *szDst++ = L'\r'; break;
			case L'n': *szDst++ = L'\n'; break;
			case L'a': *szDst++ = L'\a'; break;
			case L'b': *szDst++ = L'\b'; break;
			default: szDst++;
			}
		}
		else
			*szDst++ = *szData++;
	}
	*szDst = 0;
}

BOOL SplitStringToArray(LPCOLESTR lpszData, CStrArray& aStrings, LPCOLESTR lpszTokens/*=NULL*/, BOOL bRemoveQuoto/*=TRUE*/)
{
	if (lpszData == NULL) return FALSE;

	if (lpszTokens == NULL)
		lpszTokens = L" \t\r\n";

	aStrings.RemoveAll();

	CStdString strData; // = lpszData;
	EraseSplash(lpszData, strData.GetBuffer(lstrlenW(lpszData)));
	strData.ReleaseBuffer();
	int nStart = 0;
	for (CStdString str=strData.Tokenize(lpszTokens, nStart); nStart>=0; str=strData.Tokenize(lpszTokens, nStart))
	{
		// ��������ת���
		CStdString str2;
		EraseSplash(str, str2.GetBuffer(str.GetLength()));
		str2.ReleaseBuffer();
		str2.Trim();
		if (bRemoveQuoto)
		{
			// �������Ű����Ĵ������ִ��ڲ�������ֿո񡢵ȺŻ���һ������
			OLECHAR cQuote = str2[0];
			if (cQuote==L'\'' || cQuote==L'\"') // ������
			{
				// Ѱ�ҵڶ�����Ӧ������
				nStart -= str.GetLength() - 1;
				int nEnd = strData.Find(cQuote, nStart--);
				//while (nEnd>nStart && strData[nEnd-1]==L'\\' && (nEnd-nStart<=1 || strData[nEnd-2]!=L'\\')) // ??? ȷ������ת���
				//	nEnd = strData.Find(cQuote, nEnd+1);
				if (nEnd < 0) // û�ж�Ӧ����
					return FALSE;
				str2 = strData.Mid(nStart, nEnd-nStart);
				nStart = nEnd + 1;
			}
		}
		aStrings.Add(str2);
	}
	return TRUE;
}

HRESULT ObjectInitFromString(IDispatch* pDisp, LPCOLESTR szInit)
{
	if (pDisp==NULL || szInit==NULL) return E_FAIL;

	CComPtr<IDispatch> disp = pDisp;
	CStrArray strs;
	if (SplitStringToArray(szInit, strs, L";"))
	{
		for (int i=0; i<strs.GetSize(); i++)
		{
			CStrArray pairs;
			if (SplitStringToArray(strs[i], pairs, L":=") && pairs.GetSize()==2)
			{
				CComVariant v = pairs[1];
				disp.PutPropertyByName(pairs[0], &v);
			}
		}
		return S_OK;
	}
	return E_FAIL;
}

BOOL ParseBoolString(LPCOLESTR lpszData, BOOL bDef/*=FALSE*/)
{
	if (lpszData==NULL) return bDef;
	if (lstrcmpiW(lpszData, L"true")==0 ||
		lstrcmpiW(lpszData, L"yes")==0 ||
		lstrcmpiW(lpszData, L"1")==0)
		return TRUE;
	else if (lstrcmpiW(lpszData, L"false")==0 ||
		lstrcmpiW(lpszData, L"no")==0 ||
		lstrcmpiW(lpszData, L"0")==0)
		return FALSE;
	return bDef;
}

BOOL ParseStateString(LPCOLESTR lpszState, DWORD& state)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), DUISTATE_##x},
	static const struct {LPCOLESTR name; int len_of_name; DWORD state;} __mapitem_entry[] = {
		MAP_ITEM(FOCUSED)		MAP_ITEM(SELECTED)		MAP_ITEM(DISABLED)		MAP_ITEM(HOT)
		MAP_ITEM(PUSHED)		MAP_ITEM(CHECKED)		MAP_ITEM(READONLY)		MAP_ITEM(CAPTURED)
		MAP_ITEM(HIDDEN)		MAP_ITEM(HOVER)			MAP_ITEM(EXPANDED)
	};
#undef MAP_ITEM

	int len = lstrlenW(lpszState);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (__mapitem_entry[i].len_of_name==len && lstrcmpiW(lpszState,__mapitem_entry[i].name)==0)
			return state|=__mapitem_entry[i].state, TRUE;
	}

	return FALSE;
}

DWORD TryLoadStateFromString(LPCOLESTR lpszValue)
{
	if (lpszValue==NULL || *lpszValue==0) return 0;

	DWORD state = 0;
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs)) return 0;

	for (int i=0; i<strs.GetSize(); i++)
	{
		if (!ParseStateString(strs[i], state))
			return 0;
	}
	return state;
}

BOOL ParseOverflowString(LPCOLESTR lpszValue, LONG& l)
{
	if (lstrcmpiW(lpszValue, L"auto") == 0) return l=OVERFLOW_AUTO, TRUE;
	if (lstrcmpiW(lpszValue, L"hidden") == 0) return l=OVERFLOW_HIDDEN, TRUE;
	if (lstrcmpiW(lpszValue, L"scroll") == 0) return l=OVERFLOW_SCROLL, TRUE;
	return FALSE;
}

BOOL ParseDisplayString(LPCOLESTR lpszValue, LONG& l)
{
	if (lstrcmpiW(lpszValue, L"none") == 0) return l=DUIDISPLAY_NONE, TRUE;
	if (lstrcmpiW(lpszValue, L"inline") == 0) return l=DUIDISPLAY_INLINE, TRUE;
	if (lstrcmpiW(lpszValue, L"block") == 0) return l=DUIDISPLAY_BLOCK, TRUE;
	if (lstrcmpiW(lpszValue, L"inlineblock") == 0) return l=DUIDISPLAY_INLINEBLOCK, TRUE;
	return FALSE;
}

BOOL ParsePositionString(LPCOLESTR lpszValue, LONG& l)
{
	if (lstrcmpiW(lpszValue, L"relative") == 0) return l=DUIPOS_RELATIVE, TRUE;
	if (lstrcmpiW(lpszValue, L"absolute") == 0) return l=DUIPOS_ABSOLUTE, TRUE;
	if (lstrcmpiW(lpszValue, L"fixed") == 0) return l=DUIPOS_FIXED, TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//

static BOOL TryTranslateToSysColorIndex(LPCOLESTR lpszData, int& idx)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), COLOR_##x},
	static const struct {LPCOLESTR name; int len_of_name; int index;} __mapitem_entry[] = {
		MAP_ITEM(SCROLLBAR)		MAP_ITEM(BACKGROUND)		MAP_ITEM(ACTIVECAPTION)		MAP_ITEM(INACTIVECAPTION)
		MAP_ITEM(MENU)		MAP_ITEM(WINDOW)		MAP_ITEM(WINDOWFRAME)		MAP_ITEM(MENUTEXT)
		MAP_ITEM(WINDOWTEXT)		MAP_ITEM(CAPTIONTEXT)		MAP_ITEM(ACTIVEBORDER)		MAP_ITEM(INACTIVEBORDER)
		MAP_ITEM(APPWORKSPACE)		MAP_ITEM(HIGHLIGHT)		MAP_ITEM(HIGHLIGHTTEXT)		MAP_ITEM(BTNFACE)
		MAP_ITEM(BTNSHADOW)		MAP_ITEM(GRAYTEXT)		MAP_ITEM(BTNTEXT)		MAP_ITEM(INACTIVECAPTIONTEXT)
		MAP_ITEM(BTNHIGHLIGHT)		MAP_ITEM(3DDKSHADOW)		MAP_ITEM(3DLIGHT)		MAP_ITEM(INFOTEXT)
		MAP_ITEM(INFOBK)		MAP_ITEM(HOTLIGHT)		MAP_ITEM(GRADIENTACTIVECAPTION)		MAP_ITEM(GRADIENTINACTIVECAPTION)
		MAP_ITEM(MENUHILIGHT)		MAP_ITEM(MENUBAR)		MAP_ITEM(DESKTOP)		MAP_ITEM(3DFACE)
		MAP_ITEM(3DSHADOW)		MAP_ITEM(3DHIGHLIGHT)		MAP_ITEM(3DHILIGHT)		MAP_ITEM(BTNHILIGHT)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (__mapitem_entry[i].len_of_name==len && lstrcmpiW(lpszData,__mapitem_entry[i].name)==0)
			return idx=__mapitem_entry[i].index, TRUE;
	}

	return FALSE;
}

static BOOL TryTranslateToNamedColor(LPCOLESTR lpszData, COLORREF& clr)
{
#define named_color(ename, cname, hex, r, g, b) {L#ename, lstrlenW(L#ename), L#cname, lstrlenW(L#cname), RGB(r,g,b)},
	static const struct {LPCOLESTR ename; int ename_len; LPCOLESTR cname; int cname_len; COLORREF _clr;} __mapitem_entry[] = {
		__foreach_named_color(named_color)
	};
#undef named_color

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	// Ϊ��������ܣ�����Ӣ������û������������
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if ((__mapitem_entry[i].ename_len==len && lstrcmpiW(lpszData,__mapitem_entry[i].ename)==0))
			return clr=__mapitem_entry[i]._clr/*|0xff000000*/, TRUE;
	}

	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if ((__mapitem_entry[i].cname_len==len && lstrcmpiW(lpszData,__mapitem_entry[i].cname)==0))
			return clr=__mapitem_entry[i]._clr/*|0xff000000*/, TRUE;
	}

	return FALSE;
}

BOOL TryLoad_BOOL_FromString(LPCOLESTR lpszData, BOOL& b)
{
	if (lpszData == NULL) return FALSE;
	b = ParseBoolString(lpszData);
	return TRUE;
}

BOOL TryLoad_long_FromString(LPCOLESTR lpszData, long& l)
{
	if (lpszData == NULL) return FALSE;

	//long _l = _wtol(lpszData);
	LPOLESTR pEnd = NULL;
	long _l = wcstol(lpszData, &pEnd, 10);
	//int err = errno; // why always 0?
	if (pEnd && *pEnd!=0)
	//if (_l==0 && (err==ERANGE || err==EINVAL))
		return FALSE;
	return l=_l, TRUE;
}

BOOL TryLoad_double_FromString(LPCOLESTR lpszData, double& d)
{
	if (lpszData == NULL) return FALSE;

	LPOLESTR pEnd = NULL;
	double _d = wcstod(lpszData, &pEnd);
	if (*pEnd==L'%' && *(pEnd+1)==0)
		return d=_d/100, TRUE;
	else if (*pEnd==0)
		return d=_d, TRUE;

	return FALSE;
}

BOOL TryLoad_float_FromString(LPCOLESTR lpszData, float& f)
{
	double d;
	if (TryLoad_double_FromString(lpszData, d)) return (f=(float)d, TRUE);
	return FALSE;
}

BOOL TryLoad_COLORREF_FromString(LPCOLESTR lpszData, COLORREF& clr)
{
	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	if (len>1 && len<=9 && lpszData[0]==L'#') // #a #ab #abc #080808 #aa080808
	{
		COLORREF c = (COLORREF)wcstoul(lpszData+1, NULL, 16); // bbggrraa
		clr = RGB(GetBValue(c), GetGValue(c), GetRValue(c));
		if (len>=8) clr |= (c&0xff000000);
		//else clr |= 0xff000000;
		return TRUE;
	}

	if (len==11 && lstrcmpiW(lpszData,L"transparent")==0)
		return clr=CLR_INVALID, TRUE;

	// try system color
	int idx;
	if (TryTranslateToSysColorIndex(lpszData, idx))
		return clr=::GetSysColor(idx)/*|0xff000000*/, TRUE;

	if (TryTranslateToNamedColor(lpszData, clr)) return TRUE;

	return FALSE;
}

#ifndef NO3D
BOOL TryLoad_D3DCOLORVALUE_FromString(LPCOLESTR lpszData, D3DCOLORVALUE& clr)
{
	if (lpszData == NULL) return FALSE;

	COLORREF clrref;
	if (TryLoad_COLORREF_FromString(lpszData, clrref))
		return clr=COLOR(clrref), TRUE;

	// try float color. such as "r,g,b,a" or "r,g,b"
	CStrArray strs;
	if (SplitStringToArray(lpszData, strs, L", \t\r\n") && strs.GetSize()>=3)
	{
		float r,g,b,a=1.f;
		if (TryLoad_float_FromString(strs[0], r) &&
			TryLoad_float_FromString(strs[1], g) &&
			TryLoad_float_FromString(strs[2], b) &&
			(strs.GetSize()<4 || TryLoad_float_FromString(strs[3], a)))
		{
			clr.r = r;
			clr.g = g;
			clr.b = b;
			clr.a = a;
			return TRUE;
		}
	}

	return FALSE;
}
#endif // NO3D

BOOL TryLoad_floatptr_FromString(LPCOLESTR lpszData, float* v, int num)
{
	if (lpszData==NULL || v==NULL || num<=0 || num>256) return FALSE;

	// format "x,y,z"
	CStrArray strs;
	if (SplitStringToArray(lpszData, strs, L", \t\r\n") && strs.GetSize()>=num)
	{
		float* vTmp = new float[num];
		BOOL bRet = TRUE;
		for (int i=0; i<num; i++)
		{
			if (!(bRet = TryLoad_float_FromString(strs[i], vTmp[i]))) break;
		}
		if (bRet)
		{
			for (int i=0; i<num; i++) v[i] = vTmp[i];
		}
		delete[] vTmp;
		return bRet;
	}

	return FALSE;
}

BOOL TryLoadFontFaceFromString(LPCOLESTR lpszData, LOGFONTW& lf, LONG& mask)
{
	if (lpszData == NULL) return FALSE;

	class EnumFontHelper
	{
	public:
		static BOOL CALLBACK EnumProc(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, BOOL* pb) { return *pb=TRUE, TRUE; }
	};
	BOOL b = FALSE;
	HDC hdc = ::GetDC(NULL);
	::EnumFontFamilies(hdc, lpszData, (FONTENUMPROC)EnumFontHelper::EnumProc, (LPARAM)&b);
	::ReleaseDC(NULL, hdc);

	if (b)
		mask|=SVT_FONT_MASK_FAMILY, lstrcpyW(lf.lfFaceName, lpszData);
	return b;
}

BOOL TryLoadFontStyleFromString(LPCOLESTR lpszData, LOGFONTW& lf, LONG& mask)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), FW_##x},
	static const struct {LPCOLESTR name; int len_of_name; long weight;} __mapitem_entry[] = {
		MAP_ITEM(THIN)	MAP_ITEM(EXTRALIGHT)	MAP_ITEM(ULTRALIGHT)	MAP_ITEM(LIGHT) MAP_ITEM(NORMAL)
		MAP_ITEM(REGULAR)	MAP_ITEM(MEDIUM)	MAP_ITEM(SEMIBOLD)	MAP_ITEM(DEMIBOLD) MAP_ITEM(BOLD)
		MAP_ITEM(EXTRABOLD)	MAP_ITEM(ULTRABOLD)	MAP_ITEM(HEAVY)	MAP_ITEM(BLACK)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	if (len==6 && lstrcmpiW(lpszData, L"italic") == 0) return mask|=SVT_FONT_MASK_STYLE, lf.lfItalic=TRUE, TRUE;
	if (len==9 && lstrcmpiW(lpszData, L"underline") == 0) return mask|=SVT_FONT_MASK_STYLE, lf.lfUnderline=TRUE, TRUE;
	if (len==9 && lstrcmpiW(lpszData, L"strikeout") == 0) return mask|=SVT_FONT_MASK_STYLE, lf.lfStrikeOut=TRUE, TRUE;

	if ((len==6 && lstrcmpiW(lpszData, L"normal")==0)) // normal �� regular ��Ȼ��һ�����������︳�����⺬�壬���ڰ������������Ը�λ
		mask|=SVT_FONT_MASK_STYLE, lf.lfItalic = lf.lfUnderline = lf.lfStrikeOut = FALSE;
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return mask|=SVT_FONT_MASK_STYLE, lf.lfWeight=__mapitem_entry[i].weight, TRUE;
	}

	return FALSE;
}

BOOL TryLoadFontSizeFromString(LPCOLESTR lpszData, LOGFONTW& lf, LONG& mask)
{
	if (lpszData == NULL) return FALSE;

	if (!TryLoad_long_FromString(lpszData, lf.lfHeight))
		return FALSE;
	return mask|=SVT_FONT_MASK_SIZE, lf.lfWidth=0, TRUE;
}

static BOOL TryLoadPenStyleFromString(LPCOLESTR lpszData, LOGPEN& lp, LONG& mask)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), PS_##x},
	static const struct {LPCOLESTR name; int len_of_name; UINT style;} __mapitem_entry[] = {
		MAP_ITEM(SOLID)	MAP_ITEM(DASH)	MAP_ITEM(DOT)	MAP_ITEM(DASHDOT)
		MAP_ITEM(DASHDOTDOT)	MAP_ITEM(NULL)	MAP_ITEM(INSIDEFRAME)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return mask|=SVT_PEN_MASK_STYLE, lp.lopnStyle=__mapitem_entry[i].style, TRUE;
	}
	return FALSE;
}

static BOOL TryLoadTextStyleFromString(LPCOLESTR lpszData, LONG& l)
{
#define DT_MIDDLE DT_VCENTER
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), DT_##x},
	static const struct {LPCOLESTR name; int len_of_name; UINT style;} __mapitem_entry[] = {
		MAP_ITEM(TOP)	MAP_ITEM(LEFT)	MAP_ITEM(CENTER)	MAP_ITEM(RIGHT)
		MAP_ITEM(VCENTER)	MAP_ITEM(BOTTOM)	MAP_ITEM(WORDBREAK)	MAP_ITEM(SINGLELINE)
		MAP_ITEM(EXPANDTABS)	MAP_ITEM(NOCLIP)	MAP_ITEM(EXTERNALLEADING)	MAP_ITEM(NOPREFIX)
		MAP_ITEM(INTERNAL)	MAP_ITEM(EDITCONTROL)	MAP_ITEM(PATH_ELLIPSIS)	MAP_ITEM(END_ELLIPSIS)
		MAP_ITEM(MODIFYSTRING)	MAP_ITEM(RTLREADING)	MAP_ITEM(WORD_ELLIPSIS)	MAP_ITEM(NOFULLWIDTHCHARBREAK)
		MAP_ITEM(HIDEPREFIX)	MAP_ITEM(PREFIXONLY)	MAP_ITEM(MIDDLE)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return l|=__mapitem_entry[i].style, TRUE;
	}
	return FALSE;
}

static BOOL TryLoadFlagFromString(LPCOLESTR lpszData, LONG& l)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), DUIFLAG_##x},
	static const struct {LPCOLESTR name; int len_of_name; UINT flag;} __mapitem_entry[] = {
		MAP_ITEM(TABSTOP)	MAP_ITEM(WANTRETURN)	MAP_ITEM(SETCURSOR)	MAP_ITEM(SELECTABLE)
		MAP_ITEM(EXPANDABLE)	MAP_ITEM(NOFOCUSFRAME)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return l|=__mapitem_entry[i].flag, TRUE;
	}
	return FALSE;
}

static BOOL TryLoadStretchFromString(LPCOLESTR lpszData, LONG& l)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), DUISTRETCH_##x},
	static const struct {LPCOLESTR name; int len_of_name; LONG mode;} __mapitem_entry[] = {
		MAP_ITEM(NO_MOVE_X)	MAP_ITEM(NO_MOVE_Y)	MAP_ITEM(NO_SIZE_X)	MAP_ITEM(NO_SIZE_Y)
		MAP_ITEM(NO_MOVE)		MAP_ITEM(NO_SIZE)
		//MAP_ITEM(NEWGROUP)	MAP_ITEM(NEWLINE)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return l |= __mapitem_entry[i].mode, TRUE;
	}
	return FALSE;
}

static BOOL TryLoadCursorFromString(LPCOLESTR lpszData, HCURSOR& cs)
{
#define IDC_DEFAULT IDC_ARROW
#define IDC_MOVE IDC_SIZEALL
#define IDC_TEXT IDC_IBEAM
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), IDC_##x},
	static const struct {LPCOLESTR name; int len_of_name; LPCTSTR cursor;} __mapitem_entry[] = {
		MAP_ITEM(ARROW)	MAP_ITEM(IBEAM)	MAP_ITEM(WAIT)	MAP_ITEM(CROSS)
		MAP_ITEM(UPARROW)	MAP_ITEM(SIZENWSE)	MAP_ITEM(SIZENESW)	MAP_ITEM(SIZEWE)
		MAP_ITEM(SIZENS)	MAP_ITEM(SIZEALL)	MAP_ITEM(NO)	MAP_ITEM(HAND)
		MAP_ITEM(HELP)	MAP_ITEM(APPSTARTING)	MAP_ITEM(DEFAULT)	MAP_ITEM(MOVE)
		MAP_ITEM(TEXT)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return cs=LoadCursor(NULL,__mapitem_entry[i].cursor), TRUE;
	}
	return FALSE;
}

static BOOL TryLoadHitTestFromString(LPCOLESTR lpszData, LONG& l)
{
#define MAP_ITEM(x) {OLESTR(#x), lstrlenW(L#x), HT##x},
	static const struct {LPCOLESTR name; int len_of_name; LONG ht;} __mapitem_entry[] = {
		MAP_ITEM(ERROR)	MAP_ITEM(TRANSPARENT)	MAP_ITEM(NOWHERE)	MAP_ITEM(CLIENT)
		MAP_ITEM(CAPTION)	MAP_ITEM(SYSMENU)	MAP_ITEM(GROWBOX)	MAP_ITEM(SIZE)
		MAP_ITEM(MENU)	MAP_ITEM(HSCROLL)	MAP_ITEM(VSCROLL)	MAP_ITEM(MINBUTTON)
		MAP_ITEM(MAXBUTTON)	MAP_ITEM(LEFT)	MAP_ITEM(RIGHT)	MAP_ITEM(TOP)
		MAP_ITEM(TOPLEFT)	MAP_ITEM(TOPRIGHT)	MAP_ITEM(BOTTOM)	MAP_ITEM(BOTTOMLEFT)
		MAP_ITEM(BOTTOMRIGHT)	MAP_ITEM(BORDER)	MAP_ITEM(REDUCE)	MAP_ITEM(ZOOM)
		MAP_ITEM(OBJECT)	MAP_ITEM(CLOSE)	MAP_ITEM(HELP)
	};
#undef MAP_ITEM

	if (lpszData == NULL) return FALSE;

	int len = lstrlenW(lpszData);
	for (int i=0; i<sizeof(__mapitem_entry)/sizeof(__mapitem_entry[0]); i++)
	{
		if (len==__mapitem_entry[i].len_of_name && lstrcmpiW(lpszData, __mapitem_entry[i].name)==0)
			return l=__mapitem_entry[i].ht, TRUE;
	}
	return FALSE;
}

/*
 *	color format:
		colorname
		[themename ]colortype
		#080808
		transparent
 */
static COLORREF StyleParseColor(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs))
		return CLR_INVALID;

	for (int i=0; i<strs.GetSize(); i++)
	{
		COLORREF clr;
		if (TryLoad_COLORREF_FromString(strs[i], clr))
			return clr;
	}

	return CLR_INVALID;
}

/*
 *	font format:
		[themename ]fonttype
		font-family(string) font-size(number) font-style(italic|bold|underline)  // such as: 'Times New Roman' 12 italic bold
 */
static BOOL StyleParseFont(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, LOGFONTW& lf, LONG& mask)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs))
		return FALSE;

	for (int i=0; i<strs.GetSize(); i++)
	{
		if (TryLoadFontFaceFromString(strs[i], lf, mask))
			continue;

		if (TryLoadFontStyleFromString(strs[i], lf, mask))
			continue;

		if (TryLoadFontSizeFromString(strs[i], lf, mask))
			continue;

		// unknown string
		return FALSE;
	}

	return TRUE;
}

/*
 *	pen format:
		width style color
 */
static BOOL StyleParsePen(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, LOGPEN& lp, LONG& mask)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs))
		return FALSE;

	for (int i=0; i<strs.GetSize(); i++)
	{
		if (TryLoad_long_FromString(strs[i], lp.lopnWidth.x))
			{mask|=SVT_PEN_MASK_WIDTH; continue;}

		if (TryLoadPenStyleFromString(strs[i], lp, mask))
			continue;

		if (TryLoad_COLORREF_FromString(strs[i], lp.lopnColor))
			{lp.lopnColor&=0x00ffffff, mask|=SVT_PEN_MASK_COLOR; continue;}

		// unknown string
		return FALSE;
	}

	return TRUE;
}

/*
 *	rect format(px):
		left[ top[ right[ bottom]]]
 */
BOOL StyleParseRect(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, RECT& rc, BOOL bNeedFull/*=FALSE*/)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs, L", \t\r\n"))
		return FALSE;

	int num = strs.GetSize();
	if (num==0)
		return FALSE;

	if (!TryLoad_long_FromString(strs[0], rc.left))
		return FALSE;
	if (num==1 && !bNeedFull)
		return rc.bottom=rc.right=rc.top=rc.left, TRUE;

	if (!TryLoad_long_FromString(strs[1], rc.top))
		return FALSE;
	if (num==2 && !bNeedFull)
		return rc.right=rc.left, rc.bottom=rc.top, TRUE;

	if (!TryLoad_long_FromString(strs[2], rc.right))
		return FALSE;
	if (num==3 && !bNeedFull)
		return rc.bottom=rc.top, TRUE;

	return TryLoad_long_FromString(strs[3], rc.bottom);
}

/*
 *	text-style format:
		left middle center ...
 */
BOOL StyleParseTextStyle(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, LONG& l)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs))
		return FALSE;

	for (int i=0; i<strs.GetSize(); i++)
	{
		TryLoadTextStyleFromString(strs[i], l);
		//if (!TryLoadTextStyleFromString(strs[i], l))
		//	return FALSE;
	}
	return TRUE;
}

/*
 *	flag format:
		tabstop wantreturn
 */
static BOOL StyleParseFlag(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, LONG& l)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs))
		return FALSE;

	for (int i=0; i<strs.GetSize(); i++)
	{
		if (!TryLoadFlagFromString(strs[i], l))
			return FALSE;
	}
	return TRUE;
}

/*
 *	stretch format:
		move_x move_y size_x size_y newgroup newline
 */
static BOOL StyleParseStretch(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, LONG& l)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs))
		return FALSE;

	for (int i=0; i<strs.GetSize(); i++)
	{
		if (!TryLoadStretchFromString(strs[i], l))
			return FALSE;
	}
	return TRUE;
}

/*
 *	image format
		image_id [normal|center|tile|strech]
 */
static BOOL StyleParseImage(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue, CDuiImageResource*& pRes, ExternalType& et)
{
	CStrArray strs;
	if (!SplitStringToArray(lpszValue, strs) || strs.GetSize()==0)
		return FALSE;

	pRes = pLayoutMgr->GetImageResource(strs[0]);
	if (pRes==NULL)
		return FALSE;

	et = ext_image_normal;
	if (strs.GetSize()>=2)
	{
		if (strs[1].CompareNoCase(L"center") == 0) et = ext_image_center;
		else if (strs[1].CompareNoCase(L"tile") == 0) et = ext_image_tile;
		else if (strs[1].CompareNoCase(L"stretch") == 0) et = ext_image_stretch;
		else if (strs[1].CompareNoCase(L"maxfit") == 0) et = ext_image_maxfit;
		else if (strs[1].CompareNoCase(L"squares") == 0) et = ext_image_squares;
	}
	return TRUE;
}

BOOL StyleToVariant(CDuiStyleVariant* sv, CComVariant& v)
{
	if (sv==NULL) return FALSE;
	switch (sv->svt)
	{
	case SVT_AUTO: v = (long)AutoValue; return TRUE;
	case SVT_LONG: v = sv->longVal; return TRUE;
	case SVT_PERCENT:
	case SVT_DOUBLE: v = (float)sv->doubleVal; return TRUE; // ����ֻ��עfloat������ת����float
	case SVT_BOOL: v = (bool)(sv->boolVal!=FALSE); return TRUE;
	case SVT_COLOR: // ��ɫֵ��ת���� COLOR ����
		{
			v.ClearToZero();
#ifndef NO3D
			COLOR* c = NULL;
			if (SUCCEEDED(COLOR::CreateInstance(&v.pdispVal, &c)))
			{
				v.vt = VT_DISPATCH;
				*c = sv->colorVal;
			}
#else
			v = (ULONG)sv->colorVal;
#endif
		}
		return TRUE;
	}
	return FALSE;
}

BOOL StyleToVariant(CDuiStyle* pStyle, DuiStyleAttributeType sat, CComVariant& v)
{
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(sat, FALSE);
	BOOL b = StyleToVariant(pRet, v);
	if (b && pRet->svt==SVT_COLOR)
	{
		gConnector.Disconnect(pRet, DISP_CAST(v.pdispVal,COLOR), cp_style_bind);
		gConnector.Connect(pRet, (DISP_CAST(v.pdispVal,COLOR)), cp_style_bind | sat, pStyle);
	}
	return b;
}

BOOL VariantToStyle(CDuiStyleVariant* sv, CComVariant& v)
{
	if (sv==NULL) return FALSE;
	// ��������������
	if (v.vt==VT_BOOL || v.vt==VT_R4 || v.vt==VT_R8 || v.vt==VT_I4 || v.vt==VT_DISPATCH)
	{
		DuiStyleAttributeType sat = sv->sat;
		StyleVariantClear(sv);
		sv->sat = sat;
		switch (v.vt)
		{
		case VT_BOOL: return *sv = (BOOL)(V_BOOL(&v)!=0), TRUE;
		case VT_R4: return *sv = (DOUBLE)V_R4(&v), TRUE;
		case VT_R8: return *sv = (DOUBLE)V_R8(&v), TRUE;
		case VT_I4: return (V_I4(&v)==AutoValue?sv->svt=SVT_AUTO:*sv = (long)V_I4(&v)), TRUE;
		case VT_DISPATCH: // VT_UI4:
#ifndef NO3D
			{
				COLOR* c = DISP_CAST(V_DISPATCH(&v), COLOR);
				if (c) return *sv = (COLORREF)*c, TRUE;
			}
#else
			return *sv = (COLORREF)V_UI4(&v), TRUE;
#endif
		}
	}
	return FALSE;
}

BOOL VariantToStyle(CDuiStyle* pStyle, DuiStyleAttributeType sat, CComVariant& v)
{
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(sat, TRUE);
	if (VariantToStyle(pRet, v)) return pStyle->FireChangeEvent(pRet), TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_STYLE_PARSER(Background)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return StyleToVariant(pStyle, SAT_BACKGROUND, v);
	if (v.vt!=VT_BSTR) return VariantToStyle(pStyle, SAT_BACKGROUND, v);
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BACKGROUND, TRUE);
	ATLASSERT(pRet);
	// try color
	COLORREF clr = StyleParseColor(pLayoutMgr, pStyle, v.bstrVal);
	if (clr != CLR_INVALID)
		return *pRet = clr, pStyle->FireChangeEvent(pRet), TRUE;
	// try bitmap or icon or image
	CDuiImageResource* pSrc=NULL;
	ExternalType et = ext_unknown;
	if (!StyleParseImage(pLayoutMgr, pStyle, v.bstrVal, pSrc, et))
		return FALSE;
	StyleVariantClear(pRet);
	pRet->sat = SAT_BACKGROUND;
	pRet->svt = SVT_EXTERNAL;
	pRet->__cache = (UINT_PTR)et;
	pRet->extVal = pSrc;
	pStyle->FireChangeEvent(pRet);
	return TRUE;
}

IMPLEMENT_STYLE_PARSER(Foreground)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return StyleToVariant(pStyle, SAT_FOREGROUND, v);
	if (v.vt!=VT_BSTR) return VariantToStyle(pStyle, SAT_FOREGROUND, v);
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FOREGROUND, TRUE);
	ATLASSERT(pRet);
	// try color
	COLORREF clr = StyleParseColor(pLayoutMgr, pStyle, v.bstrVal);
	if (clr != CLR_INVALID)
		return *pRet = clr, pStyle->FireChangeEvent(pRet), TRUE;
	// try bitmap or icon or image
	CDuiImageResource* pSrc=NULL;
	ExternalType et = ext_unknown;
	if (!StyleParseImage(pLayoutMgr, pStyle, v.bstrVal, pSrc, et))
		return FALSE;
	StyleVariantClear(pRet);
	pRet->sat = SAT_FOREGROUND;
	pRet->svt = SVT_EXTERNAL;
	pRet->__cache = (UINT_PTR)et;
	pRet->extVal = pSrc;
	pStyle->FireChangeEvent(pRet);
	return TRUE;
}

IMPLEMENT_STYLE_PARSER(Color)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return StyleToVariant(pStyle, SAT_COLOR, v);
	if (v.vt!=VT_BSTR) return VariantToStyle(pStyle, SAT_COLOR, v);
	COLORREF clr = StyleParseColor(pLayoutMgr, pStyle, v.bstrVal);
	if (clr == CLR_INVALID)
		return FALSE;

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_COLOR, TRUE);
	ATLASSERT(pRet);
	return *pRet = clr, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Font)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FONT, TRUE);
	ATLASSERT(pRet);
	LONG mask = pRet->svt & SVT_FONT_MASK_ALL;

	LPLOGFONTW plf = FromStyleVariant(pRet, LPLOGFONTW);
	LOGFONTW lf;
	if (plf) lf = *plf;
	else ::GetObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONTW), &lf); // ȡĬ��THEME����

	if (!StyleParseFont(pLayoutMgr, pStyle, v.bstrVal, lf, mask))
		return FALSE;
	return pRet->SetFont(&lf, mask), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(FontFamily)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FONT, TRUE);
	ATLASSERT(pRet);
	LONG mask = pRet->svt & SVT_FONT_MASK_ALL;

	LPLOGFONTW plf = FromStyleVariant(pRet, LPLOGFONTW);
	LOGFONTW lf;
	if (plf) lf = *plf;
	else ::GetObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONTW), &lf); // ȡĬ��THEME����

	if (!TryLoadFontFaceFromString(v.bstrVal, lf, mask))
		return FALSE;

	return pRet->SetFont(&lf, mask), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(FontSize)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FONT, FALSE);
		if (pRet==NULL || (pRet->svt & SVT_FONT_MASK_SIZE)==0) return FALSE;
		LPLOGFONTW plf = FromStyleVariant(pRet, LPLOGFONTW);
		if (plf==NULL) return FALSE;
		v = (long)plf->lfHeight;
		return TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FONT, TRUE);
	ATLASSERT(pRet);
	LONG mask = pRet->svt & SVT_FONT_MASK_ALL;

	LPLOGFONTW plf = FromStyleVariant(pRet, LPLOGFONTW);
	LOGFONTW lf;
	if (plf) lf = *plf;
	else ::GetObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONTW), &lf); // ȡĬ��THEME����


	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		plf->lfHeight = (LONG)V_I4(&v);
		plf->lfWidth = 0;
	}
	else
	if (!TryLoadFontSizeFromString(v.bstrVal, lf, mask))
		return FALSE;

	return pRet->SetFont(&lf, mask), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(FontStyle)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FONT, TRUE);
	ATLASSERT(pRet);
	LONG mask = pRet->svt & SVT_FONT_MASK_ALL;

	LPLOGFONTW plf = FromStyleVariant(pRet, LPLOGFONTW);
	LOGFONTW lf;
	if (plf) lf = *plf;
	else ::GetObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONTW), &lf); // ȡĬ��THEME����

	CStrArray strs;
	if (!SplitStringToArray(v.bstrVal, strs))
		return FALSE;

	for (int i=0; i<strs.GetSize(); i++)
	{
		if (!TryLoadFontStyleFromString(strs[i], lf, mask))
			return FALSE;
	}

	return pRet->SetFont(&lf, mask), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_SIMPLE_STYLE_PARSER(LINE_DISTANCE, long);
//IMPLEMENT_STYLE_PARSER(LINE_DISTANCE)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
//{
//	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_LINE_DISTANCE, TRUE);
//	ATLASSERT(pRet);
//	LONG l;
//	if (!TryLoad_long_FromString(lpszValue, l))
//		return FALSE;
//	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
//}


IMPLEMENT_STYLE_PARSER(Margin)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	if (!StyleParseRect(pLayoutMgr, pStyle, v.bstrVal, rc))
		return FALSE;
	return *pRet=&rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(MarginLeft)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->left, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.left = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.left))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(MarginTop)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->top, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.top = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.top))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(MarginRight)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->right, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.right = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.right))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(MarginBottom)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->bottom, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MARGIN, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.bottom = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.bottom))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Padding)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, TRUE);
	ATLASSERT(pRet);
	RECT rc;
	if (!StyleParseRect(pLayoutMgr, pStyle, v.bstrVal, rc))
		return FALSE;
	return *pRet=&rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(PaddingLeft)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->left, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.left = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.left))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(PaddingTop)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->top, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.top = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.top))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(PaddingRight)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->right, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.right = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.right))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(PaddingBottom)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, FALSE);
		if (pRet==NULL) return FALSE;
		LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
		if (prc==NULL) return FALSE;
		return v=(long)prc->bottom, TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_PADDING, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	LPCRECT prc = FromStyleVariant(pRet, LPCRECT);
	if (prc) rc = *prc;

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		rc.bottom = (LONG)V_I4(&v);
	}
	else
	if (!TryLoad_long_FromString(v.bstrVal, rc.bottom))
		return FALSE;

	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Border)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BORDER, TRUE);
	ATLASSERT(pRet);
	LONG mask = (pRet->svt & SVT_PEN_MASK_ALL);
	LPLOGPEN plp = FromStyleVariant(pRet, LPLOGPEN);
	LOGPEN lp;
	if (plp) lp = *plp;
	else ::GetObject((HPEN)::GetStockObject(BLACK_PEN), sizeof(LOGPEN), &lp); // ȡĬ�ϻ���

	if (!StyleParsePen(pLayoutMgr, pStyle, v.bstrVal, lp, mask))
		return FALSE;

	return pRet->SetPen(&lp, mask), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(BorderWidth)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BORDER, FALSE);
		if (pRet==NULL || (pRet->svt & SVT_PEN_MASK_WIDTH)==0) return FALSE;
		LPLOGPEN plp = FromStyleVariant(pRet, LPLOGPEN);
		if (plp==NULL) return FALSE;
		v = (long)plp->lopnWidth.x;
		return TRUE;
	}

	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BORDER, TRUE);
	ATLASSERT(pRet);
	LONG mask = (pRet->svt & SVT_PEN_MASK_ALL);
	LPLOGPEN plp = FromStyleVariant(pRet, LPLOGPEN);
	LOGPEN lp;
	if (plp) lp = *plp;
	else ::GetObject((HPEN)::GetStockObject(BLACK_PEN), sizeof(LOGPEN), &lp); // ȡĬ�ϻ���

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_I4) return FALSE;
		lp.lopnWidth.x = (LONG)V_I4(&v);
	}
	else if (!TryLoad_long_FromString(v.bstrVal, lp.lopnWidth.x))
		return FALSE;

	return pRet->SetPen(&lp, mask|SVT_PEN_MASK_WIDTH), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(BorderStyle)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BORDER, TRUE);
	ATLASSERT(pRet);
	LONG mask = (pRet->svt & SVT_PEN_MASK_ALL);
	LPLOGPEN plp = FromStyleVariant(pRet, LPLOGPEN);
	LOGPEN lp;
	if (plp) lp = *plp;
	else ::GetObject((HPEN)::GetStockObject(BLACK_PEN), sizeof(LOGPEN), &lp); // ȡĬ�ϻ���

	if (!TryLoadPenStyleFromString(v.bstrVal, lp, mask))
		return FALSE;

	return pRet->SetPen(&lp, mask), pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(BorderColor)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead)
	{
		CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BORDER, FALSE);
		if (pRet==NULL || (pRet->svt & SVT_PEN_MASK_COLOR)==0) return FALSE;
		LPLOGPEN plp = FromStyleVariant(pRet, LPLOGPEN);
		if (plp==NULL) return FALSE;
		v = (ULONG)plp->lopnColor;
		return TRUE;
	}
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_BORDER, TRUE);
	ATLASSERT(pRet);
	LONG mask = (pRet->svt & SVT_PEN_MASK_ALL);
	LPLOGPEN plp = FromStyleVariant(pRet, LPLOGPEN);
	LOGPEN lp;
	if (plp) lp = *plp;
	else ::GetObject((HPEN)::GetStockObject(BLACK_PEN), sizeof(LOGPEN), &lp); // ȡĬ�ϻ���

	if (v.vt!=VT_BSTR)
	{
		if (v.vt!=VT_UI4) return FALSE;
		lp.lopnColor = (COLORREF)V_UI4(&v);
	}
	else
	{
		if (!TryLoad_COLORREF_FromString(v.bstrVal, lp.lopnColor))
			return FALSE;
		lp.lopnColor &= 0x00ffffff;
	}
	return pRet->SetPen(&lp, mask|SVT_PEN_MASK_COLOR), pStyle->FireChangeEvent(pRet), TRUE;
}

//IMPLEMENT_STYLE_PARSER(Width)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
//{
//	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_WIDTH, TRUE);
//	ATLASSERT(pRet);
//	LONG l;
//	if (TryLoad_long_FromString(lpszValue, l))
//		return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
//
//	double d;
//	if (TryLoad_double_FromString(lpszValue, d) && d>=0.0 && d<=1.0)
//		return *pRet = d, pRet->svt=SVT_PERCENT, pStyle->FireChangeEvent(pRet), TRUE;
//
//	return FALSE;
//}
//
//IMPLEMENT_STYLE_PARSER(Height)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
//{
//	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_HEIGHT, TRUE);
//	ATLASSERT(pRet);
//	LONG l;
//	if (TryLoad_long_FromString(lpszValue, l))
//		return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
//
//	double d;
//	if (TryLoad_double_FromString(lpszValue, d) && d>=0.0 && d<=1.0)
//		return *pRet = d, pRet->svt=SVT_PERCENT, pStyle->FireChangeEvent(pRet), TRUE;
//
//	return FALSE;
//}
//
//IMPLEMENT_STYLE_PARSER(MinWidth)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
//{
//	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MINWIDTH, TRUE);
//	ATLASSERT(pRet);
//	LONG l;
//	if (TryLoad_long_FromString(lpszValue, l))
//		return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
//
//	double d;
//	if (TryLoad_double_FromString(lpszValue, d) && d>=0.0 && d<=1.0)
//		return *pRet = d, pRet->svt=SVT_PERCENT, pStyle->FireChangeEvent(pRet), TRUE;
//
//	return FALSE;
//}
//
//IMPLEMENT_STYLE_PARSER(MinHeight)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
//{
//	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_MINHEIGHT, TRUE);
//	ATLASSERT(pRet);
//	LONG l;
//	if (TryLoad_long_FromString(lpszValue, l))
//		return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
//
//	double d;
//	if (TryLoad_double_FromString(lpszValue, d) && d>=0.0 && d<=1.0)
//		return *pRet = d, pRet->svt=SVT_PERCENT, pStyle->FireChangeEvent(pRet), TRUE;
//
//	return FALSE;
//}
//
//IMPLEMENT_STYLE_PARSER(Scroll)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, LPCOLESTR lpszValue)
//{
//	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_SCROLL, TRUE);
//	ATLASSERT(pRet);
//	*pRet = ParseBoolString(lpszValue);
//	return TRUE;
//}

IMPLEMENT_STYLE_PARSER(TextStyle)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_TEXT_STYLE, TRUE);
	ATLASSERT(pRet);
	LONG l = 0;
	if (!StyleParseTextStyle(pLayoutMgr, pStyle, v.bstrVal, l))
		return FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Cursor)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_CURSOR, TRUE);
	ATLASSERT(pRet);
	HCURSOR hCursor;
	CStdString str(v.bstrVal);
	str.Trim();
	if (!TryLoadCursorFromString(str, hCursor))
		return FALSE;
	pRet->svt = SVT_CURSOR;
	pRet->iconVal = hCursor;
	pStyle->FireChangeEvent(pRet);
	return TRUE;
}

IMPLEMENT_STYLE_PARSER(Flag)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FLAG, TRUE);
	ATLASSERT(pRet);
	LONG l = 0;
	if (!StyleParseFlag(pLayoutMgr, pStyle, v.bstrVal, l))
		return FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(HitTestAs)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_HITTEST_AS, TRUE);
	ATLASSERT(pRet);
	LONG l = HTNOWHERE;
	if (!TryLoadHitTestFromString(v.bstrVal, l))
		return FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Stretch)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_STRETCH, TRUE);
	ATLASSERT(pRet);
	LONG l = 0;
	if (!StyleParseStretch(pLayoutMgr, pStyle, v.bstrVal, l))
		return FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(DialogItemPos)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_DIALOG_ITEM_POS, TRUE);
	ATLASSERT(pRet);
	RECT rc = {0};
	if (!StyleParseRect(pLayoutMgr, pStyle, v.bstrVal, rc, TRUE))
		return FALSE;
	return *pRet = &rc, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_SIMPLE_STYLE_PARSER(COLUMNS, long);

IMPLEMENT_STYLE_PARSER(Overflow)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_OVERFLOW, TRUE);
	ATLASSERT(pRet);
	LONG l;
	if (!ParseOverflowString(v.bstrVal, l))
		return *pRet = (LONG)OVERFLOW_AUTO, FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Display)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_DISPLAY, TRUE);
	ATLASSERT(pRet);
	LONG l;
	if (!ParseDisplayString(v.bstrVal, l))
		return *pRet = (LONG)DUIDISPLAY_INLINE, FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Position)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_POSITION, TRUE);
	ATLASSERT(pRet);
	LONG l;
	if (!ParsePositionString(v.bstrVal, l))
		return *pRet = (LONG)DUIPOS_DEFAULT, FALSE;
	return *pRet = l, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Layout)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_LAYOUT, TRUE);
	ATLASSERT(pRet);
	return *pRet = (LPCOLESTR)v.bstrVal, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Visual)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_VISUAL, TRUE);
	ATLASSERT(pRet);
	return *pRet = (LPCOLESTR)v.bstrVal, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Filter)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_FILTER, TRUE);
	ATLASSERT(pRet);
	return *pRet = (LPCOLESTR)v.bstrVal, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_STYLE_PARSER(Clip)(CDuiLayoutManager* pLayoutMgr, CDuiStyle* pStyle, CComVariant& v, BOOL bRead/*=FALSE*/)
{
	if (bRead) return FALSE;
	if (v.vt!=VT_BSTR) return FALSE;
	CDuiStyleVariant* pRet = pStyle->GetPrivateAttribute(SAT_CLIP, TRUE);
	ATLASSERT(pRet);
	return *pRet = (LPCOLESTR)v.bstrVal, pStyle->FireChangeEvent(pRet), TRUE;
}

IMPLEMENT_SIMPLE_STYLE_PARSER(GLOWCOLOR, COLORREF);
IMPLEMENT_SIMPLE_STYLE_PARSER(GLOWTHICK, long);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(WIDTH);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(HEIGHT);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(MINWIDTH);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(MINHEIGHT);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(LEFT);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(TOP);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(RIGHT);
IMPLEMENT_AUTONUMBER_STYLE_PARSER(BOTTOM);
IMPLEMENT_SIMPLE_STYLE_PARSER(ZINDEX, long);
IMPLEMENT_SIMPLE_STYLE_PARSER(OVERFLOW_INCLUDE_OFFSET, BOOL);
