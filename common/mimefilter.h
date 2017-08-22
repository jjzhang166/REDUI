#pragma once

#ifndef __MIMEFILTER_H__
#define __MIMEFILTER_H__

#include <WinInet.h>
#include "compress.h"

#include <atlctl.h>
#include <atlstr.h>

typedef void (CALLBACK* fnOnDataAvailable)(LPVOID, LPSTREAM);

class ATL_NO_VTABLE CDownload
{
public:
	typedef CComSingleThreadModel _ThreadModel; // CBindStatusCallback ��Ҫ�������
	// ����İ󶨱�־��Ĭ�ϱ�־λ�������� BINDF_PULLDATA�����û�еĻ���OnDataAvailable ���ᱻ���õ�
	typedef CBindStatusCallback<CDownload, BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE | BINDF_PULLDATA> _BindStatusCallback;

	CComPtr<IStream> m_spStream;
	fnOnDataAvailable m_pfnDataAvailable;
	LPVOID m_callbackData;
	CDownload(fnOnDataAvailable pfn=NULL, LPVOID callbackData=NULL) : m_pfnDataAvailable(pfn), m_callbackData(callbackData) {}
	~CDownload() { m_pfnDataAvailable=NULL; m_callbackData=NULL; }

	template<typename T>
	void OnData(T* , BYTE* pBytes, DWORD cBytes)
	{
		ATLASSERT(m_spStream.p);
		if (pBytes)
		{
			ULONG cbWrited = 0;
			m_spStream->Write((const void*)pBytes, cBytes, &cbWrited);
		}
		else
		{
			LARGE_INTEGER li;
			li.QuadPart = 0;
			m_spStream->Seek(li, STREAM_SEEK_SET, NULL); // ָ�븴λ���������ȡ

			// AsyncCallback
			if (m_pfnDataAvailable)
			{
				m_pfnDataAvailable(m_callbackData, m_spStream.p);
				m_spStream = NULL;
			}
		}
	}

	// �첽������Ҫ�ⲿ����CDownloadʵ����Ȼ����ô� Download ����������ʵ��ʱ�贫��ص�����
	HRESULT Download(LPCOLESTR url)
	{
		if (m_spStream) m_spStream = NULL;

		HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &m_spStream.p);
		if (FAILED(hr)) return hr;
		return CBindStatusCallback<CDownload>::Download(this, &CDownload::OnData, (BSTR)url);
	}

	static HRESULT Download(LPCOLESTR url, IStream** ppStream)
	{
		if (ppStream==NULL) return E_POINTER;

		CDownload dl;
		HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &dl.m_spStream);
		if (FAILED(hr)) return hr;

		hr = _BindStatusCallback::Download(&dl, &CDownload::OnData, (BSTR)url);
		if (SUCCEEDED(hr) && dl.m_spStream.p)
			return dl.m_spStream.QueryInterface(ppStream);
		return hr;
	}

	static HRESULT LoadUrlToStream( LPCOLESTR lpszUrl, IStream** ppStream, HINSTANCE hMod/*=NULL*/ )
	{
		if (lpszUrl==NULL || *lpszUrl==0 /*|| ppStream==NULL*/)
			return E_POINTER;
		if (ppStream)
			*ppStream = NULL;

		HRESULT hr;

		// �����п��ܵ�url��Ϸ���һ��������У�һ��һ������
		CSimpleArray<CStringW> urls;
		if (::PathIsURLW(lpszUrl)) urls.Add(lpszUrl);
		else
		{
			OLECHAR mod_path[MAX_PATH+32] = L"res://";
			LPCOLESTR file_base = mod_path + lstrlenW(mod_path), res_base = mod_path;
			::GetModuleFileNameW(hMod, (LPWSTR)file_base, MAX_PATH);
			CStringW strPreFile=L"./", strPreRes=L"/";

			WCHAR url[INTERNET_MAX_URL_LENGTH] = L"";
			DWORD dwSize = INTERNET_MAX_URL_LENGTH;
			// �ȳ����ⲿ�ļ���Ȼ������Դ
			if (SUCCEEDED(hr=UrlCombineW(file_base, lpszUrl, url, &dwSize, 0))) urls.Add(url);
			if (SUCCEEDED(hr=UrlCombineW(file_base, strPreFile+lpszUrl, url, &dwSize, 0))) urls.Add(url);
			if (SUCCEEDED(hr=UrlCombineW(res_base, lpszUrl, url, &dwSize, 0))) urls.Add(url);
			if (SUCCEEDED(hr=UrlCombineW(res_base, strPreRes+lpszUrl, url, &dwSize, 0))) urls.Add(url);
		}

		for (int i=0; i<urls.GetSize(); i++)
		{
			//hr = URLOpenBlockingStreamW(NULL, urls[i], ppStream, 0, NULL);
			hr = CDownload::Download(urls[i], ppStream);
			if (SUCCEEDED(hr)) return hr;

			//// // ��û������ IBindStatusCallback ʱ��BindToStorage ���ܷ��� INET_E_DATA_NOT_AVAILABLE����Ҫ���ڼ����� mimefilter ������·���
			//// ���Բ��� ATL::CBindStatusCallback ����������
			//CComPtr<IMoniker> spMoniker;
			//hr = ::CreateURLMoniker(NULL, urls[i], &spMoniker);
			//if (FAILED(hr)) continue;

			//CComPtr<IBindCtx> spBindCtx;
			//hr = ::CreateBindCtx(0, &spBindCtx);
			//if (FAILED(hr)) continue;
			////BIND_OPTS opt = {sizeof(BIND_OPTS)};
			////spBindCtx->GetBindOptions(&opt);
			////opt.grfMode = STGM_READ;
			////hr = spBindCtx->SetBindOptions(&opt);

			//hr = spMoniker->BindToStorage(spBindCtx, NULL, IID_IStream, (void**)ppStream);
			//if (SUCCEEDED(hr)) return hr;
		}

		return hr;
	}

	static void StreamToBSTR(IStream* pStream, CComBSTR& bstrRet)
	{
		if (pStream==NULL) return;

		STATSTG ss;
		pStream->Stat(&ss, STATFLAG_NONAME);
		LPBYTE pBuf = new BYTE[(ULONG)ss.cbSize.QuadPart+1];
		if (pBuf)
		{
			ULONG ulRead = 0;
			pStream->Read(pBuf, (ULONG)ss.cbSize.QuadPart, &ulRead);
			pBuf[ulRead] = 0;

			if (::IsTextUnicode(pBuf, ulRead, NULL))
				bstrRet = (LPCOLESTR)pBuf;
			else
			{
				LPBYTE pBuf2 = pBuf;
				// ����Ƿ�UTF-8���룬����ͨ��BOM��⣬UTF-8��BOMֵ�� EF BB BF
				int nSize = 0;
				if (ulRead>=3 && pBuf2[0]==0xEF && pBuf2[1]==0xBB && pBuf2[2]==0xBF) // is utf-8
				{
					pBuf2 += 3;
					nSize = ulRead - 3;
					nSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)pBuf2, -1, NULL, 0);
				}
				else
				{
					nSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)pBuf2, -1/*bufSize*/, NULL, 0);
					if (nSize==0 && GetLastError()==ERROR_NO_UNICODE_TRANSLATION) // �����������ANSI��
					{
						bstrRet = (LPCSTR)pBuf2;
						nSize = 0;
					}
				}

				if (nSize>0) // utf-8
				{
					LPWSTR uniBuf = new WCHAR[nSize];
					if (uniBuf)
					{
						::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pBuf2, -1, uniBuf, nSize);
						bstrRet = uniBuf;
						delete[] uniBuf;
					}
				}
			}

			delete[] pBuf;
		}
	}
};

class CResModule
{
	HMODULE hMod;
	BOOL bFree;
public:
	CResModule(LPCWSTR file) : bFree(FALSE)
	{
		hMod = ::GetModuleHandleW(file);
		DWORD err = 0, err2=0;
		if (hMod == NULL)
		{
			err = GetLastError();
			hMod = ::LoadLibraryExW(file, NULL, LOAD_LIBRARY_AS_DATAFILE);
			bFree = TRUE;
		}
		if (hMod==NULL)
		{
#ifdef _DEBUG
			err2 = GetLastError();
			ATLTRACE("\nERR:%d, %d", err, err2);
			OutputDebugStringW(L" ģ�鲻����:");
			OutputDebugStringW(file);
#endif // _DEBUG
			WCHAR path[MAX_PATH] = L"";
			GetModuleFileNameW(NULL, path, MAX_PATH);
			if (lstrcmpiW(path, file) == 0)
			{
				hMod = ::GetModuleHandleW(NULL);
				bFree = FALSE;
#ifdef _DEBUG
				OutputDebugStringW(L" - ��ǰ�� DLL �ж�ȡ EXE ģ�顣");
#endif // _DEBUG
			}
		}
	}
	~CResModule()
	{
		if (bFree && hMod)
			::FreeLibrary(hMod);
		hMod = NULL;
	}

	operator HMODULE() { return hMod; }
};

static LPCSTR LoadHtmlRes(HMODULE hMod, LPCWSTR id, ULONG* pulSize=NULL, LPCWSTR type=NULL)
{
	if (type==NULL) type = MAKEINTRESOURCEW(23);
	HRSRC hResource = ::FindResourceW( hMod, id, type );
	if( hResource == NULL )
	{
		return( NULL );
	}

	HGLOBAL hGlobal = ::LoadResource( hMod, hResource );
	if( hGlobal == NULL )
	{
		return( NULL );
	}

	if (pulSize)
		*pulSize = ::SizeofResource(hMod, hResource);
	return (LPCSTR)::LockResource(hGlobal);
}

static DWORD ResAutoUnzip(LPCSTR szSrc, DWORD dwSrcSize, LPBYTE szDst=NULL, DWORD dwBufSize=0)
{
	if (szSrc==NULL || dwSrcSize==0) return 0;
	if (szDst==NULL && dwBufSize>0) return 0;
	if (dwSrcSize>=14 && szSrc[0]=='R' && szSrc[1]=='P' && szSrc[2]=='T' && szSrc[3]=='Z' && szSrc[4]=='I' && szSrc[5]=='P')
	{
		DWORD dwSize = *((LPDWORD)(szSrc+6));
		if (dwBufSize==0) return dwSize;
		if (dwSize>dwBufSize) return (DWORD)-1;

		DWORD dwZipSize = *((LPDWORD)(szSrc+10));
		//ATLASSERT(dwZipSize == dwSrcSize-14);
		ULONG ulUnzipSize = CWMLZSS::Unzip((LPBYTE)szSrc+14, dwZipSize, szDst);
		ATLASSERT(ulUnzipSize==dwSize);
		if (dwBufSize>dwSize)
			szDst[dwSize] = 0;
		return dwSize;
	}
	else // memcpy only
	{
		if (dwBufSize==0) return dwSrcSize;
		if (dwSrcSize>dwBufSize) return (DWORD)-1;
		memcpy_s(szDst, dwBufSize, szSrc, dwSrcSize);
		if (dwBufSize>dwSrcSize)
			szDst[dwSrcSize] = 0;
		return dwSrcSize;
	}
}

static void LoadResourceFromModule(HMODULE hMod, LPCWSTR id, CComBSTR& bstrRet, LPCWSTR type=NULL)
{
	ULONG ulSize = 0;
	LPCSTR p = LoadHtmlRes(hMod, id, &ulSize, type);
	DWORD bufSize = ResAutoUnzip(p, ulSize);
	LPBYTE pBuf = new BYTE[bufSize+1];
	ResAutoUnzip(p, ulSize, pBuf, bufSize+1);

	if (::IsTextUnicode(pBuf, bufSize, NULL))
		bstrRet = (LPCOLESTR)pBuf;
	else
	{
		LPBYTE pBuf2 = pBuf;
		// ����Ƿ�UTF-8���룬����ͨ��BOM��⣬UTF-8��BOMֵ�� EF BB BF
		int nSize = 0;
		if (bufSize>=3 && pBuf2[0]==0xEF && pBuf2[1]==0xBB && pBuf2[2]==0xBF) // is utf-8
		{
			pBuf2 += 3;
			nSize = bufSize - 3;
			nSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)pBuf2, -1/*bufSize*/, NULL, 0);
		}
		else
		{
			nSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)pBuf2, -1/*bufSize*/, NULL, 0);
			if (nSize==0 && GetLastError()==ERROR_NO_UNICODE_TRANSLATION) // �����������ANSI��
			{
				bstrRet = (LPCSTR)pBuf2;
				nSize = 0;
			}
		}

		if (nSize>0) // utf-8
		{
			LPWSTR uniBuf = new WCHAR[nSize];
			if (uniBuf)
			{
				::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pBuf2, -1, uniBuf, nSize);
				bstrRet = uniBuf;
				delete[] uniBuf;
			}
		}
	}

	delete[] pBuf;
}

class UserSchemas
{
	struct  
	{
		WCHAR origname[16]; // raptor
		WCHAR name[16]; // raptor:
		int len; // ÿ��SCHEMA���ĳ��ȣ��������� strlen("raptor:")==7
		WCHAR deffile[MAX_PATH]; // Ĭ���ļ��� c:\\abc\\def.exe
		WCHAR defext[16]; // Ĭ���ļ���չ .htm(����С����)
		WCHAR deftype[16]; // Ĭ����Դ���ڵ���Դ��

		WCHAR defdir[MAX_PATH]; // Ĭ���ļ�����·��
	} schemas[16]; // ���ɵǼ� 16 ���Զ���Э��
	long cnt;

	UserSchemas() { memset(this, 0, sizeof(UserSchemas)); AddSchema(L"raptor",NULL,L"htm",L"htm"); }

	long GetSchemaIndex(LPCWSTR url)
	{
		if (url==NULL) return -1;
		int len = lstrlenW(url);

		for (long i=0; i<cnt; i++)
		{
			if (len>=schemas[i].len && memcmp(url, schemas[i].name, schemas[i].len*sizeof(WCHAR))==0)
				return i;
		}
		return -1;
	}

public:
	static UserSchemas& instance()
	{
		static UserSchemas us;
		return us;
	}

	static void RegisterFilters(IClassFactory* pcf, BOOL bReg=TRUE)
	{
		CComPtr<IInternetSession> session;
		CoInternetGetSession(0, &session, 0);
		UserSchemas& us = instance();
		for (long i=0; i<us.cnt; i++)
		{
			if (bReg) session->RegisterNameSpace(pcf, CLSID_NULL, us.schemas[i].origname, 0, NULL, 0);
			else session->UnregisterNameSpace(pcf, us.schemas[i].origname);
		}
	}

	bool AddSchema(LPCWSTR szSchema, LPCWSTR deffile=NULL, LPCWSTR defext=NULL, LPCWSTR deftype=NULL)
	{
		if (szSchema==NULL || *szSchema==0 || cnt>16) return false;
		lstrcpynW(schemas[cnt].origname, szSchema, 16);
		lstrcpynW(schemas[cnt].name, szSchema, 15);
		lstrcatW(schemas[cnt].name, L":"); // �������ð�ţ����� raptor:
		schemas[cnt].len = lstrlenW(schemas[cnt].name);

		if (deffile) lstrcpynW(schemas[cnt].deffile, deffile, MAX_PATH);
		else /*deffile==NULL*/ ::GetModuleFileNameW(NULL, schemas[cnt].deffile, MAX_PATH);

		lstrcpyW(schemas[cnt].defdir, schemas[cnt].deffile);
		LPWSTR p = schemas[cnt].defdir + lstrlenW(schemas[cnt].defdir);
		while (p>=schemas[cnt].defdir && *p!=L'\\') p--;
		if (p>=schemas[cnt].defdir && *p==L'\\') *p = 0;
		
		if (defext && *defext!=0) { *schemas[cnt].defext=L'.'; lstrcpynW(schemas[cnt].defext+1, *defext==L'.'?defext+1:defext, 15); }
		if (deftype) lstrcpynW(schemas[cnt].deftype, deftype, 16);
		cnt++;
		return true;
	}

	//long GetCount() const { return cnt; }
	//LPCWSTR GetSchema(long i) { return (i>=0 && i<cnt) ? schema[i] : NULL; }
	static BOOL ParseUserUrl(LPCWSTR url, LPWSTR file=NULL, LPWSTR type=NULL, LPWSTR name=NULL)
	{
		if (url==NULL) return FALSE;
		int len = lstrlenW(url);

		/*
		 *	url - �����URL����
			file - ������������Ŀ���ļ�·�������統ǰEXE�ļ���·������ѡ
			type - ������������Ŀ���ļ�����Դ�ļ������ͣ�����"js"�����δ��ֵ����ʾĬ����HTML���ͣ���Դ�飩�����nameҲ�ǿգ���ʾֱ�ӷ���Ŀ���ļ���������Դ
			name - ��������������Դ�ļ������ƣ�����"start.htm"�����ֵ�ǿգ���ʾֱ�ӷ���Ŀ���ļ���������Դ����ʱtype��ֵ����
		 */

		if (len>=6 && (memcmp(url,L"res://", 6*sizeof(WCHAR))==0)) // res://file/[type/]name
		{
			//// ����Э������
			//if (schema) lstrcpyW(schema, L"res");

			// �����ҵ��ļ�·��
			LPWSTR pStart = (LPWSTR)(url+6);
			LPWSTR pEnd = pStart;
			while (*pEnd!=L'/' && *pEnd!=0) pEnd++;
			if (*pEnd != 0)
			{
				if (file) lstrcpynW(file, pStart, pEnd-pStart+1);

				// ��������Դ����
				pStart = pEnd + 1;
				pEnd = pStart;
				while (*pEnd!=L'/' && *pEnd!=0) pEnd++;
				if (*pEnd != 0) // ������
				{
					if (type) lstrcpynW(type, pStart, pEnd-pStart+1);
					pStart = pEnd + 1;
				}
				else // Ĭ�� HTM ����
					if (type) lstrcpyW(type, L"htm");

				// ��������Դ��
				if (name) lstrcpyW(name, pStart);
			}
			return TRUE;
		}
		else if (len>=7 && (memcmp(url, L"file://", 7*sizeof(WCHAR))==0)) // file://[/]file
		{
			LPCWSTR pStart = url+7;
			// �п���fileЭ�������3��б�� file:///
			if (*pStart==L'/') pStart++;
			if (file)
			{
				lstrcpyW(file, pStart);
				// fileЭ���п��ܰѷ�б������б�ܱ�ʾ����Ҫ�滻�ɷ�б��
				LPWSTR p = file;
				while (*p!=0)
				{
					if (*p == L'/') *p = L'\\';
					p++;
				}
			}

			// fileЭ��û��type��name
			if (type) *type=0;
			if (name) *name=0;
			return TRUE;
		}

		UserSchemas& us = UserSchemas::instance();
		long i = us.GetSchemaIndex(url);
		if (i<0) return FALSE;

		// �Զ���Э����������漸�֣�ÿ�ֿ��������֣�һ����Ѱ���ļ���һ����Ѱ����Դ���������ļ������û���ļ�������Դ
		////// {schema:}[type/]name[.ext]
		/*
		 *	raptor:abc			--> �ļ���{deffiledir}\abc{defext}		��Դ��{deffile}/abc{defext}
			raptor:abc.ext		--> �ļ���{deffiledir}\abc.ext			��Դ��{deffile}/abc.ext
			raptor:hh/abc		--> �ļ���{deffiledir}\hh\abc{defext}	��Դ��{deffile}/hh/abc{defext}
			raptor:hh/abc.ext	--> �ļ���{deffiledir}\hh\abc.ext		��Դ��{deffile}/hh/abc.ext
		 */
		WCHAR _file[MAX_PATH] = L""; 
		WCHAR _type[16] = L"";
		WCHAR _name[32] = L"";

		LPCWSTR /*pPath=NULL,*/ pType=NULL, pExt=NULL, pName=NULL;
		int /*nPath=0,*/ nType=0, nExt=0, nName=0;

		LPCWSTR pStart = (LPCWSTR)(url+us.schemas[i].len); // pStart ָ��ʼ
		LPCWSTR pEnd = pStart + lstrlenW(pStart);		// pEnd ָ���β
		// ����������λ��
		LPCWSTR p = pEnd;
		while (p>=pStart && *p!=L'/' && *p!=L'.') p--;
		if (p<pStart) // raptor:abc
		{
			pName = pStart; nName = pEnd - pStart;
		}
		else if (*p == L'/') // raptor:hh/abc
		{
			pName = p+1; nName = pEnd - pName;
			pType = pStart; nType = p - pType;
		}
		else // *p==L'.'
		{
			pExt = p; nExt = pEnd - pExt;
			while (p>=pStart && *p!=L'/') p--;
			if (p<pStart) // raptor:abc.ext
			{
				pName = pStart; nName = pExt - pName;
			}
			else // *p==L'/',  raptor:hh/abc.ext
			{
				pName = p + 1; nName = pExt - pName;
				pType = pStart; nType = p - pType;
			}
		}

#define Str_CatN(dst, src, n) lstrcpynW((dst) + lstrlenW(dst), src, (n)+1)

		// ���ڿ�ʼ�����ļ�������Դ
		lstrcpyW(_file, us.schemas[i].defdir); lstrcatW(_file, L"\\"); // c:\\dir\\ 
		if (pType && nType>0) // c:\\dir\\hh\\ 
		{
			Str_CatN(_file, pType, nType);
			Str_CatN(_file, L"\\", 1);
		}
		Str_CatN(_file, pName, nName);
		if (pExt) Str_CatN(_file, pExt, nExt);
		else lstrcatW(_file, us.schemas[i].defext);
		// ̽���ļ��Ƿ����
		DWORD dwAttr = ::GetFileAttributesW(_file);
		if (dwAttr!=INVALID_FILE_ATTRIBUTES && (dwAttr&FILE_ATTRIBUTE_DIRECTORY)==0)
		{
			if (file) lstrcpyW(file, _file);
			if (type) *type = 0;
			if (name) *name = 0;
			return TRUE;
		}

		// ��������Դ
		if (file) lstrcpyW(file, us.schemas[i].deffile);
		if (type)
		{
			if (pType) lstrcpynW(type, pType, nType+1);
			else if (*us.schemas[i].deftype!=0) lstrcpyW(type, us.schemas[i].deftype);
			else *type = 0;
		}
		if (name)
		{
			lstrcpynW(name, pName, nName+1);
			if (pExt) Str_CatN(name, pExt, nExt);
			else lstrcatW(name, us.schemas[i].defext);
		}
		return TRUE;

#undef Str_CatN
	}
};

static HRESULT GetResourceStream(LPCWSTR url, CComVariant& varRet) // VT_UNKNOWN(IStream)
{
	HRESULT hr = E_FAIL;
	varRet.Clear();
	if (url==NULL) return E_INVALIDARG;
	int len = lstrlenW(url);

	WCHAR file[MAX_PATH] = L"";
	WCHAR type[16] = L"";
	WCHAR name[32] = L"";
	LPWSTR newtype = type;
	if (UserSchemas::ParseUserUrl(url, file, type, name))
	{
		if (*type==0 && *name==0) // ������Դ�����ļ�
			return S_FALSE;

		if (lstrcmpiW(newtype, L"htm") == 0)
			newtype = NULL;

		HMODULE hMod = ::LoadLibraryExW(file, NULL, LOAD_LIBRARY_AS_DATAFILE);
		if (hMod)
		{
			ULONG ulSize = 0;
			LPCSTR p = LoadHtmlRes(hMod, name, &ulSize, newtype);
			DWORD newSize = ResAutoUnzip(p, ulSize);
			HGLOBAL hGlobal = GlobalAlloc(GHND, newSize);
			if (hGlobal)
			{
				LPBYTE pBuf = (LPBYTE)GlobalLock(hGlobal);
				ResAutoUnzip(p, ulSize, pBuf, newSize);
				GlobalUnlock(hGlobal);

				CComPtr<IStream> spStream;
				CreateStreamOnHGlobal(hGlobal, TRUE, &spStream);
				varRet = (IUnknown*)spStream;
				hr = S_OK;
			}
			::FreeLibrary(hMod);
		}
	}
	return hr;
}

static HRESULT GetResourceText(LPCWSTR url, CComBSTR& bstrRet) // VT_BSTR
{
	bstrRet.Empty();
	if (url==NULL) return E_INVALIDARG;
	int len = lstrlenW(url);

	WCHAR file[MAX_PATH] = L"";
	WCHAR type[16] = L"";
	WCHAR name[32] = L"";
	LPWSTR newtype = type;
	if (UserSchemas::ParseUserUrl(url, file, type, name))
	{
		if (*type==0 && *name==0) // ������Դ�����ļ�
			return S_FALSE;

		if (lstrcmpiW(newtype, L"htm") == 0)
			newtype = NULL;

		CResModule mod(file);
		if (mod)
			LoadResourceFromModule(mod, name, bstrRet, newtype);
	}
// 	else
// 	{
// 		HINTERNET hinet = ::InternetOpenW(L"WebFlow", INTERNET_OPEN_TYPE_PRECONFIG,  NULL, NULL, 0);
// 		if (hinet)
// 		{
// 			WCHAR szHead[] = L"Accept: */*\r\n\r\n";
// 			HINTERNET hFile = ::InternetOpenUrlW(hinet, url, szHead, lstrlenW(szHead), INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE, NULL);
// 			if (hFile)
// 			{
// 				DWORD dwContentLen = 1024*1024;
// 				BYTE* pBuf = new BYTE[dwContentLen+1];
// 				if (pBuf)
// 				{
// 					DWORD dwRead = 0;
// 					if (InternetReadFile(hFile, pBuf, dwContentLen, &dwRead))
// 					{
// 						pBuf[dwRead] = 0;
// 						varRet = (LPCSTR)pBuf;
// 					}
// 					delete[] pBuf;
// 				}
// 				InternetCloseHandle(hFile);
// 			}
// 			InternetCloseHandle(hinet);
// 		}
// 	}
	return S_OK;
}

//// if nBufSize==0 or lpBuf==0, return needed size only(include termination null)
//static int GetResourceText(LPCWSTR url, LPWSTR lpBuf, int nBufSize)
//{
//	if (url==NULL) return 0;
//	int len = lstrlenW(url);
//
//	WCHAR file[MAX_PATH] = L"";
//	WCHAR type[16] = L"";
//	WCHAR name[32] = L"";
//	LPWSTR newtype = type;
//	if (UserSchemas::ParseUserUrl(url, file, type, name))
//	{
//		if (*type==0 && *name==0) // ������Դ�����ļ�
//			return 0;
//
//		if (lstrcmpiW(newtype, L"htm") == 0)
//			newtype = NULL;
//
//		int nSize = 0;
//		HMODULE hMod = ::LoadLibraryExW(file, NULL, LOAD_LIBRARY_AS_DATAFILE);
//		if (hMod)
//		{
//			ULONG ulSize = 0;
//			LPCSTR p = LoadHtmlRes(hMod, name, &ulSize, newtype);
//			DWORD bufSize = ResAutoUnzip(p, ulSize);
//			LPBYTE pBuf = new BYTE[bufSize+1];
//			ResAutoUnzip(p, ulSize, pBuf, bufSize+1);
//			::FreeLibrary(hMod);
//
//			if (::IsTextUnicode(pBuf, bufSize, NULL))
//			{
//				nSize = bufSize+1;
//				if (lpBuf && nBufSize>=nSize)
//					lstrcpyW(lpBuf, (LPCWSTR)pBuf);
//			}
//			else
//			{
//				LPBYTE pBuf2 = pBuf;
//				// ����Ƿ�UTF-8���룬����ͨ��BOM��⣬UTF-8��BOMֵ�� EF BB BF
//				if (bufSize>=3 && pBuf2[0]==0xEF && pBuf2[1]==0xBB && pBuf2[2]==0xBF) // is utf-8
//				{
//					pBuf2 += 3;
//					nSize = bufSize - 3;
//					nSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)pBuf2, -1/*bufSize*/, NULL, 0);
//				}
//				else
//				{
//					nSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)pBuf2, -1/*bufSize*/, NULL, 0);
//					if (nSize==0 && GetLastError()==ERROR_NO_UNICODE_TRANSLATION) // �����������ANSI��
//					{
//						nSize = ::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pBuf2, -1, NULL, 0);
//						if (lpBuf && nBufSize>=nSize)
//						{
//							nSize = ::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pBuf2, -1, lpBuf, nBufSize);
//						}
//						delete[] pBuf;
//						return nSize;
//					}
//				}
//
//				if (nSize>0 && lpBuf && nBufSize>=nSize) // utf-8
//				{
//					nSize = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pBuf2, -1, lpBuf, nBufSize);
//				}
//			}
//
//			delete[] pBuf;
//		}
//
//		return nSize;
//	}
//	return 0;
//}

class CMimeFilter : public IInternetProtocol
{
private:
	ULONG m_ulRef;
	LPBYTE m_pBuf;

public:
	CMimeFilter() : /*m_hInternetSession(NULL), m_hHttpSession(NULL),*/m_pBuf(NULL), m_pos(0), m_size(0), m_content(NULL), m_ulRef(1)
	{
	}
	~CMimeFilter() { Clear(); }
	void Clear()
	{
		if (m_pBuf)
		{
			delete[] m_pBuf;
			m_pBuf = NULL;
		}
	};

	// IUnknown
	STDMETHOD_(ULONG, AddRef)() { return ++m_ulRef; }
	STDMETHOD_(ULONG, Release)()
	{
		m_ulRef--;
		if (m_ulRef==0)
		{
			ATLTRACE(_T("CMimeFilter is deleted!\n"));
			delete this;
		}
		return m_ulRef;
	}
	STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj)
	{
		if (!ppvObj)
			return E_POINTER;

		*ppvObj = NULL;
		if (iid==IID_IUnknown || iid==IID_IInternetProtocol)
			*ppvObj = (IInternetProtocol*)this;
		else if (iid == IID_IInternetProtocolRoot)
			*ppvObj = (IInternetProtocolRoot*)this;
		if (*ppvObj)
		{
			((LPUNKNOWN)(*ppvObj))->AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}

public:
	// IInternetProtocolRoot
	STDMETHOD (Start)(LPCWSTR szUrl, IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo, DWORD grfPI, DWORD dwReserved)
	{
		WCHAR file[MAX_PATH] = L"";
		WCHAR type[16] = L"";
		WCHAR name[32] = L"";
		LPWSTR newtype = type;
		if (UserSchemas::ParseUserUrl(szUrl, file, type, name))
		{
			ATLTRACE(_T("CMimeFilter::Start (%s)\n"), szUrl);

			do
			{
				m_pProtocolSink = pOIProtSink;
				m_pBindInfo = pOIBindInfo;
				if (*type==0 && *name==0) // ����һ���ļ�
				{
					HANDLE hFile = ::CreateFileW(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
					if (hFile == INVALID_HANDLE_VALUE)
						break;
					DWORD resSize = ::GetFileSize(hFile, NULL);
					if (resSize==INVALID_FILE_SIZE || resSize==0)
					{
						::CloseHandle(hFile);
						break;
					}

					BYTE* p = new BYTE[resSize];
					DWORD dwRead;
					::ReadFile(hFile, p, resSize, &dwRead, NULL);
					::CloseHandle(hFile);

					m_size = ResAutoUnzip((LPCSTR)p, resSize);
					Clear(), m_pBuf = new BYTE[m_size];
					ResAutoUnzip((LPCSTR)p, resSize, m_pBuf, m_size);
					m_content = m_pBuf;
					delete[] p;
				}
				else // ����һ����Դ
				{
					if (*newtype==0 || lstrcmpiW(newtype, L"htm") == 0)
						newtype = NULL;

					CResModule mod(file);
					//if (mod) // ����ļ�����EXE�������ص�ģ�������� NULL���������ﲻ�ܵ�������
					{
						LPWSTR mime = NULL;
						DWORD resSize = 0;
						LPCSTR p = LoadHtmlRes(mod, name, &resSize, newtype);
						m_size = ResAutoUnzip(p, resSize);
						Clear(), m_pBuf = new BYTE[m_size];
						ResAutoUnzip(p, resSize, m_pBuf, m_size);
						m_content = m_pBuf;

						if (m_size > resSize) // ��ѹ���������ṩ��Ч��MIME���ͣ�����ᱻmime sniffer�����ɶ���������
						{
							// �������ù̶���MIME���ͣ������� FindMimeFromData ���������ݽ��õ� application/octet-stream�����������ݣ�
							if (FAILED(FindMimeFromData(NULL, name, NULL, 0, NULL, 0, &mime, 0)))
							{
								static const WCHAR _mime[] = L"text/html";
								mime = (LPWSTR)CoTaskMemAlloc(sizeof(_mime));
								lstrcpyW(mime, _mime);
							}
						}

						if (mime ||
							//SUCCEEDED(FindMimeFromData(NULL, NULL, m_content, m_size, NULL, 0, &mime, 0)) ||
							SUCCEEDED(FindMimeFromData(NULL, szUrl, NULL, 0, NULL, 0, &mime, 0)))
						{
							m_pProtocolSink->ReportProgress(BINDSTATUS_MIMETYPEAVAILABLE, mime);
							CoTaskMemFree(mime);
						}
					}
				}
				m_pProtocolSink->ReportData(BSCF_FIRSTDATANOTIFICATION|BSCF_LASTDATANOTIFICATION|BSCF_DATAFULLYAVAILABLE, m_size, m_size);
				m_pProtocolSink->ReportResult(S_OK, 0, NULL);
				return S_OK;
			} while (FALSE);
		}

		return INET_E_USE_DEFAULT_PROTOCOLHANDLER;
	}

	STDMETHOD (Continue)(PROTOCOLDATA *pProtocolData) { return E_NOTIMPL; }
	STDMETHOD (Abort)(HRESULT hrReason, DWORD dwOptions) { return E_NOTIMPL; }
	STDMETHOD (Terminate)(DWORD dwOptions) { return S_OK; }
	STDMETHOD (Suspend)( void) {return E_NOTIMPL;}		// Not implemented
	STDMETHOD (Resume)( void) {return E_NOTIMPL;}		// Not implemented

	// IInternetProtocol based on IInternetProtocolRoot
	STDMETHOD (Read)(void *pv, ULONG cb, ULONG *pcbRead)
	{
		ATLTRACE(_T("CMimeFilter::Read (%d) length:%d, remain:%d\n"), cb, m_size, m_size-m_pos);

		LPSTR p = (LPSTR)m_content;
		if (p==NULL || m_size<=m_pos)
		{
			*pcbRead = 0;
			m_pProtocolSink->ReportResult(S_OK, 0, NULL);
			return S_FALSE;
		}

		p += m_pos;
		if (m_size-m_pos<cb)
		{
			*pcbRead = m_size-m_pos;
			memcpy_s(pv, cb, p, *pcbRead);
			m_pos += *pcbRead;
			m_pProtocolSink->ReportResult(S_OK, 0, NULL);
			return S_FALSE;
		}
		else
		{
			memcpy_s(pv, cb, p, cb);
			m_pos += cb;
			*pcbRead = cb;
			return S_OK;
		}
	}

	STDMETHOD (Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER __RPC_FAR *plibNewPosition) { return E_NOTIMPL; }
	STDMETHOD (LockRequest)(DWORD dwOptions) { return S_OK; }
	STDMETHOD (UnlockRequest)( void) { return S_OK; }

private:

	CComPtr<IInternetProtocolSink>	m_pProtocolSink;
	CComPtr<IInternetBindInfo>		m_pBindInfo;
	//HINTERNET						m_hInternetSession;
	//HINTERNET						m_hHttpSession;

	//_bstr_t m_content;
	LPBYTE m_content;
	ULONG m_size;
	ULONG m_pos;

	//static void __stdcall StatusCallback (HINTERNET, DWORD, DWORD, LPVOID, DWORD);

};

class CMimeFilterClassFactory : public IClassFactory,
	public IInternetProtocolInfo
{
public:
	void RegisterFilter()
	{
		CComPtr<IInternetSession> session;
		CoInternetGetSession(0, &session, 0);
		//session->RegisterNameSpace(this, CLSID_NULL, L"raptor", 0, NULL, 0);
		session->RegisterNameSpace(this, CLSID_NULL, L"res", 0, NULL, 0);
		UserSchemas::RegisterFilters(this, TRUE);
	}

	void UnregisterFilter()
	{
		CComPtr<IInternetSession> session;
		CoInternetGetSession(0, &session, 0);
		//session->UnregisterNameSpace(this, L"raptor");
		session->UnregisterNameSpace(this, L"res");
		UserSchemas::RegisterFilters(this, FALSE);
	}

	STDMETHOD_(ULONG, AddRef)() { return 1; }
	STDMETHOD_(ULONG, Release)() { return 1; }
	STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj)
	{
		if (!ppvObj)
			return E_POINTER;

		*ppvObj = NULL;;
		if (iid==IID_IUnknown || iid==IID_IClassFactory)
		{
			*ppvObj = (IClassFactory*)this;
			return S_OK;
		}
		else if (iid==IID_IInternetProtocolInfo)
		{
			*ppvObj = (IInternetProtocolInfo*)this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHOD (CreateInstance)(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
	{
		if (!ppvObject)
			return E_POINTER;

		*ppvObject = NULL;
		if (riid==IID_IUnknown || riid==IID_IInternetProtocol)
		{
			*ppvObject = new CMimeFilter;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHOD (LockServer)(BOOL fLock) { return S_OK; }

public:
	// IInternetProtocolInfo methods
	STDMETHOD (ParseUrl)(LPCWSTR pwzUrl, PARSEACTION ParseAction, DWORD dwParseFlags, LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved)
	{
		if(ParseAction == PARSE_SECURITY_URL) // �����ʵ�����������������ʽ��������ܾ����ʡ��Ĵ���
		{
			LPWSTR ptr;
			DWORD size;

			static const WCHAR wszRes[] = {L'r',L'e',L's',L':',L'/',L'/'};
			static const WCHAR wszRpt[] = {L'r',L'a',L'p',L't',L'o',L'r',L':'};

			if(lstrlenW(pwzUrl) <= 6 || (memcmp(pwzUrl, wszRes, sizeof(wszRes)) && memcmp(pwzUrl, wszRpt, sizeof(wszRpt))))
				return MK_E_SYNTAX;

			if (pwzUrl[1] == L'e') // res://
			{
				ptr = wcschr((LPWSTR)pwzUrl + 6, L'/');
				if(!ptr)
					return MK_E_SYNTAX;

				size = ptr-pwzUrl + 7 - 6;
				if (pcchResult) *pcchResult = size;
				if(size >= cchResult)
				{
					return S_FALSE;
				}

				memcpy(pwzResult, L"file://", 7*sizeof(WCHAR));
				memcpy(pwzResult + 7,
					pwzUrl + 6,
					(size-7)*sizeof(WCHAR));
				pwzResult[size] = 0;
			}
			else // raptor:
			{
				WCHAR path[MAX_PATH + 7] = L"file://";
				GetModuleFileNameW(NULL, path+7, MAX_PATH);
				size = (DWORD)lstrlenW(path);
				if (pcchResult) *pcchResult = size+1;
				if (size >= cchResult)
					return S_FALSE;
				lstrcpyW(pwzResult, path);
			}

			return S_OK;
		}
		else if(ParseAction == PARSE_DOMAIN)
		{
			return S_OK;
		}

		return INET_E_DEFAULT_ACTION;
	}

	STDMETHOD (CombineUrl)(LPCWSTR pwzBaseUrl, LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags, LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (CompareUrl)(LPCWSTR pwzUrl1, LPCWSTR pwzUrl2, DWORD dwCompareFlags)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (QueryInfo)(LPCWSTR pwzUrl, QUERYOPTION OueryOption, DWORD dwQueryFlags, LPVOID pBuffer, DWORD cbBuffer, DWORD *pcbBuf, DWORD dwReserved)
	{
		return E_NOTIMPL;
	}
};

#endif //__MIMEFILTER_H__