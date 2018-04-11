// GeneralSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "GeneralSettingsDlg.h"
#include "afxdialogex.h"


// CGeneralSettingsDlg dialog

IMPLEMENT_DYNAMIC(CGeneralSettingsDlg, CTabDlg)

CGeneralSettingsDlg::CGeneralSettingsDlg(CWnd* pParent /*=NULL*/)
	: CTabDlg(IDD_GENERAL_SETTINGS_DIALOG, pParent)
{

}

CGeneralSettingsDlg::~CGeneralSettingsDlg()
{
}

void CGeneralSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CTabDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGeneralSettingsDlg, CTabDlg)
	ON_BN_CLICKED(IDC_CHECK_NOW_BUTTON, &CGeneralSettingsDlg::OnBnClickedCheckNowButton)
	ON_BN_CLICKED(IDC_CHECK_UPDATE_CHECK, &CGeneralSettingsDlg::OnBnClickedCheckUpdateCheck)
	ON_BN_CLICKED(IDC_AUTO_RUN_CHECK, &CGeneralSettingsDlg::OnBnClickedAutoRunCheck)
	ON_BN_CLICKED(IDC_ALLOW_SKIN_FONT_CHECK, &CGeneralSettingsDlg::OnBnClickedAllowSkinFontCheck)
	ON_BN_CLICKED(IDC_ALLOW_SKIN_DISP_STR_CHECK, &CGeneralSettingsDlg::OnBnClickedAllowSkinDispStrCheck)
END_MESSAGE_MAP()


// CGeneralSettingsDlg ��Ϣ�������


BOOL CGeneralSettingsDlg::OnInitDialog()
{
	CTabDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	((CButton*)GetDlgItem(IDC_CHECK_UPDATE_CHECK))->SetCheck(m_data.check_update_when_start);
	((CButton*)GetDlgItem(IDC_ALLOW_SKIN_FONT_CHECK))->SetCheck(m_data.allow_skin_cover_font);
	((CButton*)GetDlgItem(IDC_ALLOW_SKIN_DISP_STR_CHECK))->SetCheck(m_data.allow_skin_cover_text);

	//��鿪ʼ�˵��ġ�������Ŀ¼����û�г���Ŀ�ݷ�ʽ������������ÿ�����������Ȼ��ɾ����ݷ�ʽ
	wstring start_up_path = CCommon::GetStartUpPath();
	bool shortcut_exist = CCommon::FileExist((start_up_path + L"\\TrafficMonitor.lnk").c_str());
	if (shortcut_exist)
	{
		theApp.SetAutoRun(true);
		m_data.auto_run = true;
		DeleteFile((start_up_path + L"\\TrafficMonitor.lnk").c_str());
	}
	else
	{
		m_data.auto_run = theApp.GetAutoRun();
	}
	((CButton*)GetDlgItem(IDC_AUTO_RUN_CHECK))->SetCheck(m_data.auto_run);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGeneralSettingsDlg::OnBnClickedCheckNowButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTrafficMonitorApp::CheckUpdate(true);
}


void CGeneralSettingsDlg::OnBnClickedCheckUpdateCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.check_update_when_start = (((CButton*)GetDlgItem(IDC_CHECK_UPDATE_CHECK))->GetCheck() != 0);
}


void CGeneralSettingsDlg::OnBnClickedAutoRunCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.auto_run = (((CButton*)GetDlgItem(IDC_AUTO_RUN_CHECK))->GetCheck() != 0);
	m_auto_run_modified = true;
}


void CGeneralSettingsDlg::OnBnClickedAllowSkinFontCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.allow_skin_cover_font = (((CButton*)GetDlgItem(IDC_ALLOW_SKIN_FONT_CHECK))->GetCheck() != 0);
}


void CGeneralSettingsDlg::OnBnClickedAllowSkinDispStrCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_data.allow_skin_cover_text = (((CButton*)GetDlgItem(IDC_ALLOW_SKIN_DISP_STR_CHECK))->GetCheck() != 0);
}
