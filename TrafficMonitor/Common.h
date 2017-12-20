#pragma once

//����ĳһ�����ʷ����
struct HistoryTraffic
{
	int year;
	int month;
	int day;
	unsigned kBytes;	//����ʹ�õ���������KBΪ��λ��

	//�Ƚ�����HistoryTraffic��������ڣ����a��ʱ�����b���򷵻�true
	static bool DateGreater(const HistoryTraffic& a, const HistoryTraffic& b)
	{
		if (a.year != b.year)
			return a.year > b.year;
		else if (a.month != b.month)
			return a.month > b.month;
		else if (a.day != b.day)
			return a.day > b.day;
		else
			return false;
	}

	//�ж�����HistoryTraffic����������Ƿ����
	static bool DateEqual(const HistoryTraffic& a, const HistoryTraffic& b)
	{
		return a.year == b.year && a.month == b.month && a.day == b.day;
	}
};

class CCommon
{
public:
	CCommon();
	~CCommon();
	//��const char*�ַ���ת���ɿ��ַ��ַ���
	static wstring StrToUnicode(const char* str);

	static string UnicodeToStr(const wchar_t* wstr);

	//��һ��int��������д��ini�ļ�������ɹ��򷵻�true
	static bool WritePrivateProfileIntW(const wchar_t * AppName, const wchar_t * KeyName, int value, const wchar_t * Path);

	//���������ڴ�Сת������KB��MB��GBΪ��λ���ַ���
	static CString DataSizeToString(unsigned int size);

	static CString KBytesToString(unsigned int kb_size);

	//��������FILETIME�ṹ��ʱ���
	static __int64 CompareFileTime2(FILETIME time1, FILETIME time2);

	//��һ����־��Ϣstr_textд�뵽file_path�ļ���
	static void WriteLog(const char* str_text, LPCTSTR file_path);

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

	static wstring GetExePath();

	//��ָ��λ�û����ı�
	static void DrawWindowText(CDC* pDC, CRect rect, LPCTSTR lpszString, COLORREF color, COLORREF back_color);

	//Ϊһ��Static�ؼ����ָ������ɫ
	static void FillStaticColor(CStatic& static_ctr, COLORREF color);

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

	//�ж������Ƿ�տ������ڸտ���3�����ڷ���true�����򷵻�false
	static bool WhenStart();

	//��ʾ�����ʾ
	static CString GetMouseTipsInfo(__int64 today_traffic, int cpu_usage, int memory_usage, int used_memory, int total_memory, bool show_cpu_memory);

};

