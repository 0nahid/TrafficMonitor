// SkinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "SkinDlg.h"
#include "afxdialogex.h"


// CSkinDlg �Ի���

IMPLEMENT_DYNAMIC(CSkinDlg, CDialogEx)

CSkinDlg::CSkinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SKIN_DIALOG, pParent)
{

}

CSkinDlg::~CSkinDlg()
{
}

void CSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_select_box);
	DDX_Control(pDX, IDC_STATIC_SKIN_S, m_skin_preview_s);
	DDX_Control(pDX, IDC_STATIC_SKIN_L, m_skin_preview_l);
	//  DDX_Control(pDX, IDC_STATIC_TEXT1, m_preview_text_s);
	//  DDX_Control(pDX, IDC_STATIC_TEXT2, m_preview_text_l);
}


void CSkinDlg::ShowPreview()
{
	//��ʾС�ߴ��Ԥ��ͼ
	m_skin_preview_s.SetWindowPos(&CWnd::wndTop, 0, 0, m_skin_width, m_skin_height_s, SWP_NOMOVE);	//���Ŀؼ��Ŀ�͸�
	m_image = (HBITMAP)LoadImage(NULL, (theApp.m_skin_path + m_skins[m_skin_selected]+ L"\\background.bmp").c_str(), IMAGE_BITMAP, m_skin_width, m_skin_height_s, LR_LOADFROMFILE);
	m_skin_preview_s.SetPicture(m_image);		//ΪCStatic�ؼ�����ͼƬ
	//��ʾ��ߴ��Ԥ��ͼ
	m_skin_preview_l.SetWindowPos(&CWnd::wndTop, 0, 0, m_skin_width, m_skin_height_l, SWP_NOMOVE);
	m_image = (HBITMAP)LoadImage(NULL, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\background_l.bmp").c_str(), IMAGE_BITMAP, m_skin_width, m_skin_height_l, LR_LOADFROMFILE);
	m_skin_preview_l.SetPicture(m_image);
	//��ȡ��ǰƤ����������ɫ
	m_text_color =  GetPrivateProfileInt(_T("skin"), _T("text_color"), 0, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini").c_str());
	//��ȡƤ������
#define BUFF_SIZE 64
	wchar_t buff[BUFF_SIZE];
	GetPrivateProfileString(_T("skin"), _T("skin_author"), _T("unknow"), buff, BUFF_SIZE, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini").c_str());
	SetDlgItemText(IDC_SKIN_INFO, (wstring(L"Ƥ�����ߣ�") + buff).c_str());
	//��ȡ��ʾ�ı�
	m_disp_str.up = CCommon::GetIniStringW(_T("skin"), _T("up_string"), NONE_STR, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini").c_str());
	m_disp_str.down = CCommon::GetIniStringW(_T("skin"), _T("down_string"), NONE_STR, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini").c_str());
	m_disp_str.cpu = CCommon::GetIniStringW(_T("skin"), _T("cpu_string"), NONE_STR, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini").c_str());
	m_disp_str.memory = CCommon::GetIniStringW(_T("skin"), _T("memory_string"), NONE_STR, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini").c_str());
}


void CSkinDlg::SetPreviewText(CDC* pDC, bool l_preview)
{
	pDC->SetTextColor(m_text_color);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(this->GetFont());
	CRect rect;
	rect.right = m_skin_width;
	if (l_preview)
		rect.bottom = m_skin_height_l;
	else
		rect.bottom = m_skin_height_s;
	rect.left += 10;
	DrawThemeParentBackground(m_hWnd, pDC->GetSafeHdc(), &rect);	//�ػ�ؼ������Խ�������ص�������
	pDC->DrawText(_T("ʾ���ı�1234ABCD"), rect, DT_VCENTER | DT_SINGLELINE);
	ReleaseDC(pDC);
}


BEGIN_MESSAGE_MAP(CSkinDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSkinDlg::OnCbnSelchangeCombo1)
	//ON_WM_TIMER()
	ON_MESSAGE(WM_CONTROL_REPAINT, &CSkinDlg::OnControlRepaint)
END_MESSAGE_MAP()


// CSkinDlg ��Ϣ�������

BOOL CSkinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ��ѡ���
	for (const auto& skin_path : m_skins)
	{
		wstring skin_name;
		size_t index = skin_path.find_last_of(L'\\');
		skin_name = skin_path.substr(index + 1);
		m_select_box.AddString(skin_name.c_str());
	}
	m_select_box.SetCurSel(m_skin_selected);
	//��ʾԤ��ͼƬ
	ShowPreview();

	//SetTimer(2345, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CSkinDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_skin_selected = m_select_box.GetCurSel();
	ShowPreview();
	//��ʾʾ���ı�
	SetPreviewText(m_skin_preview_s.GetDC(), false);
	SetPreviewText(m_skin_preview_l.GetDC(), true);
}


//void CSkinDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	SetPreviewText(m_skin_preview_s);
//	SetPreviewText(m_skin_preview_l);
//	KillTimer(2345);		//��ʱ����Ӧһ�κ�ͽ�������
//
//	CDialogEx::OnTimer(nIDEvent);
//}


afx_msg LRESULT CSkinDlg::OnControlRepaint(WPARAM wParam, LPARAM lParam)
{
	//�����յ�Ԥ��ͼ�ؼ����ػ���Ϣʱ���ػ�Ԥ���ı�
	CWnd* pControl = (CWnd*)wParam;
	CDC* pDC = (CDC*)lParam;
	if (pControl == &m_skin_preview_s)
		SetPreviewText(pDC, false);
	if (pControl == &m_skin_preview_l)
		SetPreviewText(pDC, true);
	return 0;
}
