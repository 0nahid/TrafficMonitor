#include "stdafx.h"
#include "Common.h"


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

wstring CCommon::StrToUnicode(const char* str)
{
	wstring result;
	int size;
	size = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	if (size <= 0) return wstring();
	wchar_t* str_unicode = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, str, -1, str_unicode, size);
	result.assign(str_unicode);
	delete[] str_unicode;
	return result;
}

string CCommon::UnicodeToStr(const wchar_t * wstr)
{
	string result;
	int size{ 0 };
	size = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	if (size <= 0) return string();
	char* str = new char[size + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, size, NULL, NULL);
	result.assign(str);
	delete[] str;
	return result;
}

bool CCommon::WritePrivateProfileIntW(const wchar_t * AppName, const wchar_t * KeyName, int value, const wchar_t * Path)
{
	wchar_t buff[11];
	_itow_s(value, buff, 10);
	return (WritePrivateProfileStringW(AppName, KeyName, buff, Path) != FALSE);
}

CString CCommon::DataSizeToString(unsigned int size)
{
	CString str;
	if (size < 1024 * 10)					//10KB������KBΪ��λ������2λС��
		str.Format(_T("%.2fKB"), size / 1024.0f);
	else if (size < 1024 * 1024)			//1MB������KBΪ��λ������1λС��
		str.Format(_T("%.1fKB"), size / 1024.0f);
	else if (size < 1024 * 1024 * 1024)		//1GB������MBΪ��λ������2λС��
		str.Format(_T("%.2fMB"), size / 1024.0f / 1024.0f);
	else
		str.Format(_T("%.2fGB"), size / 1024.0f / 1024.0f / 1024.0f);
	return str;
}

CString CCommon::KBytesToString(unsigned int kb_size)
{
	CString k_bytes_str;
	if (kb_size < 1024)
		k_bytes_str.Format(_T("%dKB"), kb_size);
	else if (kb_size < 1024 * 1024)
		k_bytes_str.Format(_T("%.2fMB"), kb_size / 1024.0);
	else
		k_bytes_str.Format(_T("%.2fGB"), kb_size / 1024.0 / 1024.0);
	return k_bytes_str;
}

__int64 CCommon::CompareFileTime2(FILETIME time1, FILETIME time2)
{
	__int64 a = static_cast<__int64>(time1.dwHighDateTime) << 32 | time1.dwLowDateTime;
	__int64 b = static_cast<__int64>(time2.dwHighDateTime) << 32 | time2.dwLowDateTime;
	return b - a;
}

void CCommon::WriteLog(const char* str_text, LPCTSTR file_path)
{
	SYSTEMTIME cur_time;
	GetLocalTime(&cur_time);
	ofstream file{ file_path, std::ios::app };	//��׷�ӵķ�ʽ����־�ļ�
	file << cur_time.wYear << "/" << cur_time.wMonth << "/" << cur_time.wDay << " ";
	file << cur_time.wHour << ":" << cur_time.wMinute << ":" << cur_time.wSecond << "." << cur_time.wMilliseconds << ": ";
	file << str_text << std::endl;
}

BOOL CCommon::CreateFileShortcut(LPCTSTR lpszLnkFileDir, LPCTSTR lpszFileName, LPCTSTR lpszLnkFileName, LPCTSTR lpszWorkDir, WORD wHotkey, LPCTSTR lpszDescription, int iShowCmd)
{
	if (lpszLnkFileDir == NULL)
		return FALSE;

	HRESULT hr;
	IShellLink     *pLink;  //IShellLink����ָ��
	IPersistFile   *ppf; //IPersisFil����ָ��

						 //����IShellLink����
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
	if (FAILED(hr))
		return FALSE;

	//��IShellLink�����л�ȡIPersistFile�ӿ�
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr))
	{
		pLink->Release();
		return FALSE;
	}

	TCHAR file_path[MAX_PATH];
	GetModuleFileName(NULL, file_path, MAX_PATH);

	//Ŀ��
	if (lpszFileName == NULL)
		pLink->SetPath(file_path);
	else
		pLink->SetPath(lpszFileName);

	//����Ŀ¼
	if (lpszWorkDir != NULL)
	{
		pLink->SetWorkingDirectory(lpszWorkDir);
	}
	else
	{
		//���ù���Ŀ¼Ϊ��ݷ�ʽĿ������λ��
		TCHAR workDirBuf[MAX_PATH];
		if (lpszFileName == NULL)
			wcscpy_s(workDirBuf, file_path);
		else
			wcscpy_s(workDirBuf, lpszFileName);
		LPTSTR pstr = wcsrchr(workDirBuf, _T('\\'));
		*pstr = _T('\0');
		pLink->SetWorkingDirectory(workDirBuf);
	}

	//��ݼ�
	if (wHotkey != 0)
		pLink->SetHotkey(wHotkey);

	//��ע
	if (lpszDescription != NULL)
		pLink->SetDescription(lpszDescription);

	//��ʾ��ʽ
	pLink->SetShowCmd(iShowCmd);


	//��ݷ�ʽ��·�� + ����
	wchar_t szBuffer[MAX_PATH];
	if (lpszLnkFileName != NULL) //ָ���˿�ݷ�ʽ������
		swprintf_s(szBuffer, L"%s\\%s", lpszLnkFileDir, lpszLnkFileName);
	else
	{
		//û��ָ�����ƣ��ʹ�ȡָ���ļ����ļ�����Ϊ��ݷ�ʽ���ơ�
		const wchar_t *pstr;
		if (lpszFileName != NULL)
			pstr = wcsrchr(lpszFileName, L'\\');
		else
			pstr = wcsrchr(file_path, L'\\');

		if (pstr == NULL)
		{
			ppf->Release();
			pLink->Release();
			return FALSE;
		}
		//ע���׺��Ҫ��.exe��Ϊ.lnk
		swprintf_s(szBuffer, L"%s\\%s", lpszLnkFileDir, pstr);
		int nLen = wcslen(szBuffer);
		szBuffer[nLen - 3] = L'l';
		szBuffer[nLen - 2] = L'n';
		szBuffer[nLen - 1] = L'k';
	}
	//�����ݷ�ʽ��ָ��Ŀ¼��
	//WCHAR  wsz[MAX_PATH];  //����Unicode�ַ���
	//MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, wsz, MAX_PATH);

	hr = ppf->Save(szBuffer, TRUE);

	ppf->Release();
	pLink->Release();
	return SUCCEEDED(hr);
}

wstring CCommon::GetStartUpPath()
{
	LPITEMIDLIST ppidl;
	TCHAR pszStartUpPath[MAX_PATH];
	if (SHGetSpecialFolderLocation(NULL, CSIDL_STARTUP, &ppidl) == S_OK)
	{
		SHGetPathFromIDList(ppidl, pszStartUpPath);
		//wcscat_s(pszStartUpPath, MAX_PATH, L"\\Startup");
		CoTaskMemFree(ppidl);
	}
	return wstring(pszStartUpPath);
}

void CCommon::GetFiles(const wchar_t* path, vector<wstring>& files)
{
	//�ļ���� 
	int hFile = 0;
	//�ļ���Ϣ����Unicode����ʹ��_wfinddata_t�����ֽ��ַ���ʹ��_finddata_t��
	_wfinddata_t fileinfo;
	wstring file_name;
	if ((hFile = _wfindfirst(wstring(path).append(L"\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			file_name.assign(fileinfo.name);
			if (file_name != L"." && file_name != L"..")
				files.push_back(wstring(path) + L"\\" + file_name);  //���ļ�������(����"."��"..")
		} while (_wfindnext(hFile, &fileinfo) == 0);
	}
	_findclose(hFile);
}

bool CCommon::FileExist(LPCTSTR file_name)
{
	_wfinddata_t fileinfo;
	return (_wfindfirst(file_name, &fileinfo) != -1);
}

SYSTEMTIME CCommon::CompareSystemTime(SYSTEMTIME a, SYSTEMTIME b)
{
	SYSTEMTIME result{};
	short hour = a.wHour - b.wHour;
	short minute = a.wMinute - b.wMinute;
	short second = a.wSecond - b.wSecond;

	if (second < 0)
	{
		second += 60;
		minute--;
	}

	if (minute < 0)
	{
		minute += 60;
		hour--;
	}

	if (hour < 0)
	{
		hour += 24;
	}
	result.wHour = hour;
	result.wMinute = minute;
	result.wSecond = second;
	return result;
}

wstring CCommon::GetExePath()
{
	wchar_t path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	size_t index;
	wstring current_path{ path };
	index = current_path.find_last_of(L'\\');
	current_path = current_path.substr(0, index + 1);
	return current_path;
}

void CCommon::DrawWindowText(CDC * pDC, CRect rect, LPCTSTR lpszString, COLORREF color, COLORREF back_color)
{
	pDC->SetTextColor(color);
	//m_pDC->SetBkMode(TRANSPARENT);
	//�ñ���ɫ����������
	pDC->FillSolidRect(rect, back_color);
	pDC->DrawText(lpszString, rect, DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);

}

