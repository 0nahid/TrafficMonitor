
// TrafficMonitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TrafficMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrafficMonitorApp

BEGIN_MESSAGE_MAP(CTrafficMonitorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTrafficMonitorApp ����

CTrafficMonitorApp::CTrafficMonitorApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

void CTrafficMonitorApp::LoadConfig()
{
	CIniHelper ini;
	ini.SetPath(theApp.m_config_path);
	//m_no_multistart_warning_time = GetPrivateProfileInt(_T("other"), _T("no_multistart_warning_time"), 300000, m_config_path.c_str());
	m_no_multistart_warning = ini.GetBool(_T("other"), _T("no_multistart_warning"), false);
	m_notify_interval = ini.GetInt(_T("other"), _T("notify_interval"), 60);
	m_general_data.check_update_when_start = ini.GetBool(_T("general"), _T("check_update_when_start"), true);
	m_general_data.allow_skin_cover_font = ini.GetBool(_T("general"), _T("allow_skin_cover_font"), true);
	m_general_data.allow_skin_cover_text = ini.GetBool(_T("general"), _T("allow_skin_cover_text"), true);
	m_general_data.language = static_cast<Language>(ini.GetInt(_T("general"), _T("language"), 0));
}

void CTrafficMonitorApp::SaveConfig()
{
	CIniHelper ini;
	ini.SetPath(theApp.m_config_path);
	//CCommon::WritePrivateProfileIntW(_T("other"), _T("no_multistart_warning_time"), m_no_multistart_warning_time);
	ini.WriteBool(_T("other"), _T("no_multistart_warning"), m_no_multistart_warning);
	ini.WriteInt(_T("other"), _T("notify_interval"), m_notify_interval);
	ini.WriteBool(_T("general"), _T("check_update_when_start"), m_general_data.check_update_when_start);
	ini.WriteBool(_T("general"), _T("allow_skin_cover_font"), m_general_data.allow_skin_cover_font);
	ini.WriteBool(_T("general"), _T("allow_skin_cover_text"), m_general_data.allow_skin_cover_text);
	ini.WriteInt(_T("general"), _T("language"), static_cast<int>(m_general_data.language));
}

int CTrafficMonitorApp::DPI(int pixel)
{
	return m_dpi * pixel / 96;
}

void CTrafficMonitorApp::DPI(CRect & rect)
{
	rect.left = DPI(rect.left);
	rect.right = DPI(rect.right);
	rect.top = DPI(rect.top);
	rect.bottom = DPI(rect.bottom);
}

void CTrafficMonitorApp::GetDPI(CWnd* pWnd)
{
	CWindowDC dc(pWnd);
	HDC hDC = dc.GetSafeHdc();
	m_dpi = GetDeviceCaps(hDC, LOGPIXELSY);
}

void CTrafficMonitorApp::CheckUpdate(bool message)
{
	CWaitCursor wait_cursor;
	wstring version_info;
	if (!CCommon::GetURL(L"https://raw.githubusercontent.com/zhongyang219/TrafficMonitor/master/version.info", version_info))		//��ȡ�汾��Ϣ
	{
		if(message)
			AfxMessageBox(CCommon::LoadText(IDS_CHECK_UPDATE_FAILD), MB_OK | MB_ICONWARNING);
		return;
	}

	size_t index, index1, index2, index3, index4, index5;
	index = version_info.find(L"<version>");
	index1 = version_info.find(L"</version>");
	index2 = version_info.find(L"<link>");
	index3 = version_info.find(L"</link>");
	index4 = version_info.find(L"<contents>");
	index5 = version_info.find(L"</contents>");
	wstring version;		//����汾
	wstring link;			//��������
	wstring contents;		//��������
	version = version_info.substr(index + 9, index1 - index - 9);
	link = version_info.substr(index2 + 6, index3 - index2 - 6);
	contents = version_info.substr(index4 + 10, index5 - index4 - 10);
	CString contents_str = contents.c_str();
	contents_str.Replace(L"\\n", L"\r\n");
	if (index == wstring::npos || index1 == wstring::npos || index2 == wstring::npos || index3 == wstring::npos || version.empty() || link.empty())
	{
		if (message)
			AfxMessageBox(CCommon::LoadText(IDS_CHECK_UPDATE_ERROR), MB_OK | MB_ICONWARNING);
		return;
	}
	if (version > VERSION)		//����������ϵİ汾���ڱ��ذ汾
	{
		CString info;
		if (contents.empty())
			info.Format(CCommon::LoadText(IDS_UPDATE_AVLIABLE), version.c_str());
		else
			info.Format(CCommon::LoadText(IDS_UPDATE_AVLIABLE2), version.c_str(), contents_str);
			
		if (AfxMessageBox(info, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			ShellExecute(NULL, _T("open"), link.c_str(), NULL, NULL, SW_SHOW);		//ת����������
		}
	}
	else
	{
		if(message)
			AfxMessageBox(CCommon::LoadText(IDS_ALREADY_UPDATED), MB_OK | MB_ICONINFORMATION);
	}
}

UINT CTrafficMonitorApp::CheckUpdateThreadFunc(LPVOID lpParam)
{
	CCommon::SetThreadLanguage(theApp.m_general_data.language);		//�����߳�����
	CheckUpdate(false);		//������
	return 0;
}

void CTrafficMonitorApp::SetAutoRun(bool auto_run)
{
	CRegKey key;
	wstring module_path;
	if (m_module_path.find(L' ') != wstring::npos)
	{
		//���·�����пո�����Ҫ�ڳ���·��ǰ�����˫����
		module_path = L'\"';
		module_path += m_module_path;
		module_path += L'\"';
	}
	else
	{
		module_path = m_module_path;
	}
	//��ע�����
	if (key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run")) != ERROR_SUCCESS)
	{
		AfxMessageBox(CCommon::LoadText(IDS_AUTORUN_FAILED_NO_KEY), MB_OK | MB_ICONWARNING);
		return;
	}
	if (auto_run)		//д��ע�����
	{
		if (key.SetStringValue(_T("TrafficMonitor"), module_path.c_str()) != ERROR_SUCCESS)
		{
			AfxMessageBox(CCommon::LoadText(IDS_AUTORUN_FAILED_NO_ACCESS), MB_OK | MB_ICONWARNING);
			return;
		}
	}
	else		//ɾ��ע�����
	{
		//ɾ��ǰ�ȼ��ע������Ƿ���ڣ���������ڣ���ֱ�ӷ���
		wchar_t buff[256];
		ULONG size{ 256 };
		if (key.QueryStringValue(_T("TrafficMonitor"), buff, &size) != ERROR_SUCCESS)
			return;
		if (key.DeleteValue(_T("TrafficMonitor")) != ERROR_SUCCESS)
		{
			AfxMessageBox(CCommon::LoadText(IDS_AUTORUN_DELETE_FAILED), MB_OK | MB_ICONWARNING);
			return;
		}
	}
}

bool CTrafficMonitorApp::GetAutoRun()
{
	CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run")) != ERROR_SUCCESS)
	{
		return false;
	}
	wchar_t buff[256];
	ULONG size{ 256 };
	if (key.QueryStringValue(_T("TrafficMonitor"), buff, &size) != ERROR_SUCCESS)
	{
		return false;
	}
	//ֻҪ�ҵ���"TrafficMonitor"��������򷵻�true
	return true;
}


// Ψһ��һ�� CTrafficMonitorApp ����

CTrafficMonitorApp theApp;


// CTrafficMonitorApp ��ʼ��

BOOL CTrafficMonitorApp::InitInstance()
{
	//���������ļ���·��
#ifdef _DEBUG
	m_config_path = L".\\config.ini";
	m_history_traffic_path = L".\\history_traffic.dat";
	m_log_path = L".\\error.log";
	m_skin_path = L".\\skins";
#else
	wstring exe_path = CCommon::GetExePath();
	m_config_path = exe_path + L"config.ini";
	m_history_traffic_path = exe_path + L"history_traffic.dat";
	m_log_path = exe_path + L"error.log";
	m_skin_path = exe_path + L"skins";
#endif

	wchar_t path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	m_module_path = path;

	m_system_path = CCommon::GetSystemPath();

	m_is_windows10_fall_creator = CCommon::IsWindows10FallCreatorOrLater();

	//��ini�ļ���������
	LoadConfig();

	//��ʼ����������
	CCommon::SetThreadLanguage(m_general_data.language);

#ifndef _DEBUG
	wstring cmd_line{ m_lpCmdLine };
	bool is_restart{ cmd_line.find(L"RestartByRestartManager") != wstring::npos };		//��������в����к����ַ�����RestartByRestartManager����˵�������Ǳ�Windows����������
	//bool when_start{ CCommon::WhenStart(m_no_multistart_warning_time) };
	if (is_restart && m_is_windows10_fall_creator)		//��ǰWindows�汾���＾�����߸���ʱ���������������������ֱ���˳�����
	{
		//AfxMessageBox(_T("������Ϣ�������ѱ�Windows����������������������"));
		return FALSE;
	}

	//����Ƿ�����ʵ����������
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, _T("FirstName"));
	if (hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			//char buff[128];
			//string cmd_line_str{ CCommon::UnicodeToStr(cmd_line.c_str()) };
			//sprintf_s(buff, "when_start=%d, m_no_multistart_warning=%d, cmd_line=%s", when_start, m_no_multistart_warning, cmd_line_str.c_str());
			//CCommon::WriteLog(buff, _T(".\\start.log"));
			if (!m_no_multistart_warning)
			{
				AfxMessageBox(CCommon::LoadText(IDS_AN_INSTANCE_RUNNING));
			}
			return FALSE;
		}
	}
#endif

	SaveConfig();

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//����ʱ������
	if (m_general_data.check_update_when_start)
	{
		m_pUpdateThread = AfxBeginThread(CheckUpdateThreadFunc, NULL);
	}

	CTrafficMonitorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

