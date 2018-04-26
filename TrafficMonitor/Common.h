#pragma once
#include "CommonData.h"

class CCommon
{
public:
	CCommon();
	~CCommon();
	//��const char*�ַ���ת���ɿ��ַ��ַ���
	static wstring StrToUnicode(const char* str, bool utf8 = false);

	static string UnicodeToStr(const wchar_t* wstr);

	/*�������ݵĴ�Сת������KB��MB��GBΪ��λ���ַ���
	size�����ݵĴ�С����λΪ�ֽ�
	short_mode���Ƿ�ʹ�þ���ģʽ����СС����λ������λ����ʾ��B����
	speed_unit�����ݵĵ�λ���������Զ���KB��MB
	hide_unit���Ƿ����ص�λ
	����ֵ��ת������ַ���
	*/
	static CString DataSizeToString(unsigned int size, bool short_mode = false, SpeedUnit unit = SpeedUnit::AUTO, bool hide_unit = false);

	static CString KBytesToString(unsigned int kb_size);

	//��������FILETIME�ṹ��ʱ���
	static __int64 CompareFileTime2(FILETIME time1, FILETIME time2);

	//��һ����־��Ϣstr_textд�뵽file_path�ļ���
	static void WriteLog(const char* str_text, LPCTSTR file_path);
	static void WriteLog(const wchar_t* str_text, LPCTSTR file_path);

	/*
	�������ܣ���ָ���ļ���ָ����Ŀ¼�´������ݷ�ʽ
	����������
	lpszLnkFileDir  ָ��Ŀ¼������ΪNULL��
	lpszFileName    ָ���ļ���ΪNULL��ʾ��ǰ���̵�EXE�ļ���
	lpszLnkFileName ��ݷ�ʽ���ƣ�ΪNULL��ʾEXE�ļ�����
	wHotkey         Ϊ0��ʾ�����ÿ�ݼ�
	pszDescription  ��ע
	iShowCmd        ���з�ʽ��Ĭ��Ϊ���洰��
	*/
	static BOOL CreateFileShortcut(LPCTSTR lpszLnkFileDir, LPCTSTR lpszFileName = NULL, LPCTSTR lpszLnkFileName = NULL, LPCTSTR lpszWorkDir = NULL, WORD wHotkey = 0, LPCTSTR lpszDescription = NULL, int iShowCmd = SW_SHOWNORMAL);

	//��ȡ��ʼ�˵������г����еġ�������Ŀ¼��·��
	static wstring GetStartUpPath();

	//��ȡpath·���µ��ļ����ļ��У������ļ����ļ������Ʊ�����files�����С�
	static void GetFiles(const wchar_t* path, vector<wstring>& files);

	//�ж�һ���ļ��Ƿ����
	static bool FileExist(LPCTSTR file_name);

	//��������SYSTEMTIME�ṹʱ��Ĳa-b��ֻ����ʱ���֡��룩
	static SYSTEMTIME CompareSystemTime(SYSTEMTIME a, SYSTEMTIME b);

	//��ȡ��ǰ�����·��
	static wstring GetExePath();

	//��ȡsystem32�ļ��е�·��
	static wstring GetSystemPath();

	//��ָ��λ�û����ı�
	static void DrawWindowText(CDC* pDC, CRect rect, LPCTSTR lpszString, COLORREF color, COLORREF back_color);

	//���û�ͼ�ļ�������
	static void SetDrawArea(CDC* pDC, CRect rect);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	* �������ƣ�IsForegroundFullscreen
	* ����˵�����жϵ�ǰ�������û�������ǰ̨�����Ƿ���ȫ���ġ�
	* ����˵������
	* ����˵����true���ǡ�
	false����
	* �̰߳�ȫ����
	* ����������IsForegroundFullscreen ()����ʾ�жϵ�ǰ�������û�������ǰ̨�����Ƿ���ȫ���ġ�
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	static bool IsForegroundFullscreen();

	//��һ���ַ������浽������
	static bool CopyStringToClipboard(const wstring& str);

	//��ȡWindows�汾
	static void GetWindowsVersion(int& major_version, int& minor_version, int& build_number);

	//�жϵ�ǰWindows�汾�Ƿ�ΪWin10�＾�����߸��»���µİ汾
	static bool IsWindows10FallCreatorOrLater();

	//��ȡURL������
	static bool GetURL(const wstring& url, wstring& result);

	//��ȡ����IP
	static wstring GetInternetIp();

	static void SetRect(CRect& rect, int x, int y, int width, int height);

	//����Դ�ļ������ַ��������У�front_str��back_strΪ�����ַ���ʱ��Ҫ��ǰ��������ӵ��ַ���
	static CString LoadText(UINT id, LPCTSTR back_str = nullptr);
	static CString LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str = nullptr);

	static CString IntToString(int n);

	//ɾ���������ƺ����Bold��Light���ַ�������������Щ�ַ������������ϸ
	static void NormalizeFont(LOGFONT& font);

	//��ȫ���ַ������ƺ���
	static void WStringCopy(wchar_t* str_dest, int dest_size, const wchar_t* str_source, int source_size = INT_MAX);
};

