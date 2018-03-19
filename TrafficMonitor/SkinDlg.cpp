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

void CSkinDlg::GetSkinLayout(const wstring& cfg_path, LayoutData& layout_data)
{
	//��ini�ļ���ȡƤ�����֣�������DPI��������
	layout_data.text_height = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("text_height"), 20, cfg_path.c_str()));
	layout_data.width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("width_l"), 220, cfg_path.c_str()));
	layout_data.height_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("height_l"), 43, cfg_path.c_str()));
	layout_data.up_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_x_l"), 6, cfg_path.c_str()));
	layout_data.up_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_y_l"), 2, cfg_path.c_str()));
	layout_data.up_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_width_l"), 108, cfg_path.c_str()));
	layout_data.down_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_x_l"), 114, cfg_path.c_str()));
	layout_data.down_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_y_l"), 2, cfg_path.c_str()));
	layout_data.down_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_width_l"), 110, cfg_path.c_str()));
	layout_data.cpu_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_x_l"), 6, cfg_path.c_str()));
	layout_data.cpu_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_y_l"), 22, cfg_path.c_str()));
	layout_data.cpu_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_width_l"), 108, cfg_path.c_str()));
	layout_data.memory_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_x_l"), 114, cfg_path.c_str()));
	layout_data.memory_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_y_l"), 22, cfg_path.c_str()));
	layout_data.memory_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_width_l"), 110, cfg_path.c_str()));

	layout_data.width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("width_s"), 220, cfg_path.c_str()));
	layout_data.height_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("height_s"), 28, cfg_path.c_str()));
	layout_data.up_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_x_s"), 6, cfg_path.c_str()));
	layout_data.up_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_y_s"), 4, cfg_path.c_str()));
	layout_data.up_width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_width_s"), 108, cfg_path.c_str()));
	layout_data.down_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_x_s"), 114, cfg_path.c_str()));
	layout_data.down_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_y_s"), 4, cfg_path.c_str()));
	layout_data.down_width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_width_s"), 110, cfg_path.c_str()));

}

void CSkinDlg::ShowPreview()
{
	//���벼������
	wstring cfg_path{ theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini" };
	GetSkinLayout(cfg_path, m_layout_data);
	//��ʾС�ߴ��Ԥ��ͼ
	m_skin_preview_s.SetWindowPos(&CWnd::wndTop, 0, 0, m_layout_data.width_s, m_layout_data.height_s, SWP_NOMOVE);	//���Ŀؼ��Ŀ�͸�
	m_image = (HBITMAP)LoadImage(NULL, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\background.bmp").c_str(), IMAGE_BITMAP, m_layout_data.width_s, m_layout_data.height_s, LR_LOADFROMFILE);
	m_skin_preview_s.SetPicture(m_image);		//ΪCStatic�ؼ�����ͼƬ
	//��ʾ��ߴ��Ԥ��ͼ
	m_skin_preview_l.SetWindowPos(&CWnd::wndTop, 0, 0, m_layout_data.width_l, m_layout_data.height_l, SWP_NOMOVE);
	m_image = (HBITMAP)LoadImage(NULL, (theApp.m_skin_path + m_skins[m_skin_selected] + L"\\background_l.bmp").c_str(), IMAGE_BITMAP, m_layout_data.width_l, m_layout_data.height_l, LR_LOADFROMFILE);
	m_skin_preview_l.SetPicture(m_image);
	//��ȡ��ǰƤ����������ɫ
	m_text_color = GetPrivateProfileInt(_T("skin"), _T("text_color"), 0, cfg_path.c_str());
	//��ȡƤ������
#define BUFF_SIZE 64
	wchar_t buff[BUFF_SIZE];
	GetPrivateProfileString(_T("skin"), _T("skin_author"), _T("unknow"), buff, BUFF_SIZE, cfg_path.c_str());
	SetDlgItemText(IDC_SKIN_INFO, (wstring(L"Ƥ�����ߣ�") + buff).c_str());
	//��ȡ��ʾ�ı�
	m_disp_str.up = CCommon::GetIniStringW(_T("skin"), _T("up_string"), NONE_STR, cfg_path.c_str());
	m_disp_str.down = CCommon::GetIniStringW(_T("skin"), _T("down_string"), NONE_STR, cfg_path.c_str());
	m_disp_str.cpu = CCommon::GetIniStringW(_T("skin"), _T("cpu_string"), NONE_STR, cfg_path.c_str());
	m_disp_str.memory = CCommon::GetIniStringW(_T("skin"), _T("memory_string"), NONE_STR, cfg_path.c_str());
}


void CSkinDlg::SetPreviewText(CDC* pDC, bool l_preview)
{
	pDC->SetTextColor(m_text_color);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(this->GetFont());
	CRect rect;
	if (l_preview)
	{
		rect.right = m_layout_data.width_l;
		rect.bottom = m_layout_data.height_l;
	}
	else
	{
		rect.right = m_layout_data.width_s;
		rect.bottom = m_layout_data.height_s;
	}
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
