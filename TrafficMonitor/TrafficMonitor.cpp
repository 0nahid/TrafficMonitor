
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

//void CTrafficMonitorApp::_OnOptions(int tab)
//{
//	COptionsDlg optionsDlg(tab);
//	//��ѡ���������ݴ��ݸ�ѡ�����öԻ���
//	optionsDlg.m_tab1_dlg.m_font_name = theApp.m_font_name;
//	optionsDlg.m_tab1_dlg.m_font_size = theApp.m_font_size;
//	optionsDlg.m_tab1_dlg.m_text_color = theApp.m_text_color;
//	optionsDlg.m_tab1_dlg.m_up_string = theApp.m_up_string;
//	optionsDlg.m_tab1_dlg.m_down_string = theApp.m_down_string;
//	optionsDlg.m_tab1_dlg.m_cpu_string = theApp.m_cpu_string;
//	optionsDlg.m_tab1_dlg.m_memory_string = theApp.m_memory_string;
//	optionsDlg.m_tab1_dlg.m_swap_up_down = theApp.m_swap_up_down;
//
//	optionsDlg.m_tab2_dlg.m_font_name = theApp.m_tbar_font_name;
//	optionsDlg.m_tab2_dlg.m_font_size = theApp.m_tbar_font_size;
//	optionsDlg.m_tab2_dlg.m_text_color = theApp.m_tbar_text_color;
//	optionsDlg.m_tab2_dlg.m_back_color = theApp.m_tbar_back_color;
//	optionsDlg.m_tab2_dlg.m_up_string = theApp.m_tbar_up_string;
//	optionsDlg.m_tab2_dlg.m_down_string = theApp.m_tbar_down_string;
//	optionsDlg.m_tab2_dlg.m_cpu_string = theApp.m_tbar_cpu_string;
//	optionsDlg.m_tab2_dlg.m_memory_string = theApp.m_tbar_memory_string;
//	optionsDlg.m_tab2_dlg.m_swap_up_down = theApp.m_tbar_swap_up_down;
//
//	if (optionsDlg.DoModal() == IDOK)
//	{
//		theApp.m_font_name = optionsDlg.m_tab1_dlg.m_font_name;
//		theApp.m_font_size = optionsDlg.m_tab1_dlg.m_font_size;
//		theApp.m_text_color = optionsDlg.m_tab1_dlg.m_text_color;
//		theApp.m_up_string = optionsDlg.m_tab1_dlg.m_up_string;
//		theApp.m_down_string = optionsDlg.m_tab1_dlg.m_down_string;
//		theApp.m_cpu_string = optionsDlg.m_tab1_dlg.m_cpu_string;
//		theApp.m_memory_string = optionsDlg.m_tab1_dlg.m_memory_string;
//		theApp.m_swap_up_down = optionsDlg.m_tab1_dlg.m_swap_up_down;
//
//		theApp.m_tbar_font_name = optionsDlg.m_tab2_dlg.m_font_name;
//		theApp.m_tbar_font_size = optionsDlg.m_tab2_dlg.m_font_size;
//		theApp.m_tbar_text_color = optionsDlg.m_tab2_dlg.m_text_color;
//		theApp.m_tbar_back_color = optionsDlg.m_tab2_dlg.m_back_color;
//		theApp.m_tbar_up_string = optionsDlg.m_tab2_dlg.m_up_string;
//		theApp.m_tbar_down_string = optionsDlg.m_tab2_dlg.m_down_string;
//		theApp.m_tbar_cpu_string = optionsDlg.m_tab2_dlg.m_cpu_string;
//		theApp.m_tbar_memory_string = optionsDlg.m_tab2_dlg.m_memory_string;
//		theApp.m_tbar_swap_up_down = optionsDlg.m_tab2_dlg.m_swap_up_down;
//	}
//}


// Ψһ��һ�� CTrafficMonitorApp ����

CTrafficMonitorApp theApp;


// CTrafficMonitorApp ��ʼ��

BOOL CTrafficMonitorApp::InitInstance()
{
#ifndef _DEBUG
	wstring cmd_line{ m_lpCmdLine };
	bool is_restart{ cmd_line.find(L"RestartByRestartManager") != wstring::npos };		//��������в����к����ַ�����RestartByRestartManager����˵�������Ǳ�Windows����������
	if (is_restart && CCommon::WhenStart())		//����ڿ���ʱ����������������ֱ���˳�����
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
			if (!is_restart)
				AfxMessageBox(_T("�Ѿ���һ�������������С�"));
			return FALSE;
		}
	}
#endif

	//���������ļ���·��
	wstring exe_path{ CCommon::GetExePath() };
	m_config_path = exe_path + L"config.ini";
	m_history_traffic_path = exe_path + L"history_traffic.dat";
	m_log_path = exe_path + L"error.log";
	m_skin_path = exe_path + L"skins";

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

