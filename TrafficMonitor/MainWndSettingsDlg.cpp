// MainWndSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "MainWndSettingsDlg.h"
#include "afxdialogex.h"


// CMainWndSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CMainWndSettingsDlg, CDialogEx)

CMainWndSettingsDlg::CMainWndSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_WND_SETTINGS_DIALOG, pParent)
{

}

CMainWndSettingsDlg::~CMainWndSettingsDlg()
{
}

void CMainWndSettingsDlg::DrawStaticColor()
{
	CCommon::FillStaticColor(m_color_static, m_text_color);
}

void CMainWndSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC, m_color_static);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainWndSettingsDlg, CDialogEx)
	ON_EN_CHANGE(IDC_UPLOAD_EDIT, &CMainWndSettingsDlg::OnEnChangeUploadEdit)
	ON_EN_CHANGE(IDC_DOWNLOAD_EDIT, &CMainWndSettingsDlg::OnEnChangeDownloadEdit)
	ON_EN_CHANGE(IDC_CPU_EDIT, &CMainWndSettingsDlg::OnEnChangeCpuEdit)
	ON_EN_CHANGE(IDC_MEMORY_EDIT, &CMainWndSettingsDlg::OnEnChangeMemoryEdit)
	//ON_WM_TIMER()
	//ON_STN_CLICKED(IDC_TEXT_COLOR_STATIC, &CMainWndSettingsDlg::OnStnClickedTextColorStatic)
	ON_BN_CLICKED(IDC_SET_COLOR_BUTTON1, &CMainWndSettingsDlg::OnBnClickedSetColorButton1)
	ON_BN_CLICKED(IDC_SET_DEFAULT_BUTTON, &CMainWndSettingsDlg::OnBnClickedSetDefaultButton)
	ON_BN_CLICKED(IDC_SET_FONT_BUTTON, &CMainWndSettingsDlg::OnBnClickedSetFontButton)
	ON_BN_CLICKED(IDC_SWITCH_UP_DOWN_CHECK, &CMainWndSettingsDlg::OnBnClickedSwitchUpDownCheck)
	ON_BN_CLICKED(IDC_FULLSCREEN_HIDE_CHECK, &CMainWndSettingsDlg::OnBnClickedFullscreenHideCheck)
END_MESSAGE_MAP()


// CMainWndSettingsDlg ��Ϣ�������


BOOL CMainWndSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(255, 255, 255));

	//��ʼ�����ؼ�״̬
	SetDlgItemText(IDC_FONT_NAME_EDIT, m_font_name);
	wchar_t buff[16];
	swprintf_s(buff, L"%d", m_font_size);
	SetDlgItemText(IDC_FONT_SIZE_EDIT, buff);

	SetDlgItemText(IDC_UPLOAD_EDIT, m_up_string.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT, m_down_string.c_str());
	SetDlgItemText(IDC_CPU_EDIT, m_cpu_string.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT, m_memory_string.c_str());

	((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->SetCheck(m_swap_up_down);
	((CButton*)GetDlgItem(IDC_FULLSCREEN_HIDE_CHECK))->SetCheck(m_hide_main_wnd_when_fullscreen);

	//SetTimer(11, 50, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMainWndSettingsDlg::OnEnChangeUploadEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_UPLOAD_EDIT, tmp);
	m_up_string = tmp;
}


void CMainWndSettingsDlg::OnEnChangeDownloadEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_DOWNLOAD_EDIT, tmp);
	m_down_string = tmp;
}


void CMainWndSettingsDlg::OnEnChangeCpuEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_CPU_EDIT, tmp);
	m_cpu_string = tmp;
}


void CMainWndSettingsDlg::OnEnChangeMemoryEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmp;
	GetDlgItemText(IDC_MEMORY_EDIT, tmp);
	m_memory_string = tmp;
}


//void CMainWndSettingsDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if (nIDEvent == 11)
//	{
//		CCommon::FillStaticColor(m_color_static, m_text_color);
//		KillTimer(11);
//	}
//	CDialogEx::OnTimer(nIDEvent);
//}


//void CMainWndSettingsDlg::OnStnClickedTextColorStatic()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CMainWndSettingsDlg::OnBnClickedSetColorButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog colorDlg(m_text_color, 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_text_color = colorDlg.GetColor();
		DrawStaticColor();
	}
}


void CMainWndSettingsDlg::OnBnClickedSetDefaultButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_up_string = L"�ϴ�: ";
	m_down_string = L"����: ";
	m_cpu_string = L"CPU: ";
	m_memory_string = L"�ڴ�: ";
	SetDlgItemText(IDC_UPLOAD_EDIT, m_up_string.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT, m_down_string.c_str());
	SetDlgItemText(IDC_CPU_EDIT, m_cpu_string.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT, m_memory_string.c_str());
}


void CMainWndSettingsDlg::OnBnClickedSetFontButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFont font;
	font.CreatePointFont(m_font_size * 10, m_font_name);
	LOGFONT lf{};             //LOGFONT����
	font.GetLogFont(&lf);
	CFontDialog fontDlg(&lf);	//��������Ի��򣬳�ʼѡ������Ϊ֮ǰ����
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���
	{
		//��ȡ������Ϣ
		m_font_name = fontDlg.GetFaceName();
		m_font_size = fontDlg.GetSize() / 10;
		//��������Ϣ��ʾ����
		SetDlgItemText(IDC_FONT_NAME_EDIT, m_font_name);
		wchar_t buff[16];
		swprintf_s(buff, L"%d", m_font_size);
		SetDlgItemText(IDC_FONT_SIZE_EDIT, buff);
	}
}


void CMainWndSettingsDlg::OnBnClickedSwitchUpDownCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_swap_up_down = (((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnBnClickedFullscreenHideCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_hide_main_wnd_when_fullscreen = (((CButton*)GetDlgItem(IDC_FULLSCREEN_HIDE_CHECK))->GetCheck() != 0);
}
