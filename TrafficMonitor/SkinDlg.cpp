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
	DDX_Control(pDX, IDC_SKIN_COURSE_STATIC, m_skin_course);
	DDX_Control(pDX, IDC_SKIN_DOWNLOAD_STATIC, m_skin_download);
	DDX_Control(pDX, IDC_PREVIEW_GROUP_STATIC, m_preview_static);
	DDX_Control(pDX, IDC_NOTIFY_STATIC, m_notify_static);
}

void CSkinDlg::LoadSkinLayout(const wstring& cfg_path, LayoutData& layout_data)
{
	//��ini�ļ���ȡƤ�����֣�������DPI��������
	layout_data.text_height = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("text_height"), 20, cfg_path.c_str()));
	layout_data.no_text = (GetPrivateProfileInt(_T("layout"), _T("no_text"), 0, cfg_path.c_str()) != 0);

	layout_data.width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("width_l"), 220, cfg_path.c_str()));
	layout_data.height_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("height_l"), 43, cfg_path.c_str()));
	layout_data.up_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_x_l"), 6, cfg_path.c_str()));
	layout_data.up_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_y_l"), 2, cfg_path.c_str()));
	layout_data.up_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_width_l"), 108, cfg_path.c_str()));
	layout_data.up_align_l = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("up_align_l"), 0, cfg_path.c_str()));
	layout_data.down_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_x_l"), 114, cfg_path.c_str()));
	layout_data.down_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_y_l"), 2, cfg_path.c_str()));
	layout_data.down_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_width_l"), 110, cfg_path.c_str()));
	layout_data.down_align_l = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("down_align_l"), 0, cfg_path.c_str()));
	layout_data.cpu_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_x_l"), 6, cfg_path.c_str()));
	layout_data.cpu_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_y_l"), 21, cfg_path.c_str()));
	layout_data.cpu_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_width_l"), 108, cfg_path.c_str()));
	layout_data.cpu_align_l = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("cpu_align_l"), 0, cfg_path.c_str()));
	layout_data.memory_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_x_l"), 114, cfg_path.c_str()));
	layout_data.memory_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_y_l"), 21, cfg_path.c_str()));
	layout_data.memory_width_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_width_l"), 110, cfg_path.c_str()));
	layout_data.memory_align_l = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("memory_align_l"), 0, cfg_path.c_str()));
	layout_data.show_up_l = (GetPrivateProfileInt(_T("layout"), _T("show_up_l"), 1, cfg_path.c_str()) != 0);
	layout_data.show_down_l = (GetPrivateProfileInt(_T("layout"), _T("show_down_l"), 1, cfg_path.c_str()) != 0);
	layout_data.show_cpu_l = (GetPrivateProfileInt(_T("layout"), _T("show_cpu_l"), 1, cfg_path.c_str()) != 0);
	layout_data.show_memory_l = (GetPrivateProfileInt(_T("layout"), _T("show_memory_l"), 1, cfg_path.c_str()) != 0);
	layout_data.preview_x_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("preview_x_l"), 0, cfg_path.c_str()));
	layout_data.preview_y_l = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("preview_y_l"), 47, cfg_path.c_str()));

	layout_data.width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("width_s"), 220, cfg_path.c_str()));
	layout_data.height_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("height_s"), 28, cfg_path.c_str()));
	layout_data.up_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_x_s"), 6, cfg_path.c_str()));
	layout_data.up_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_y_s"), 4, cfg_path.c_str()));
	layout_data.up_width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("up_width_s"), 108, cfg_path.c_str()));
	layout_data.up_align_s = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("up_align_s"), 0, cfg_path.c_str()));
	layout_data.down_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_x_s"), 114, cfg_path.c_str()));
	layout_data.down_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_y_s"), 4, cfg_path.c_str()));
	layout_data.down_width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("down_width_s"), 110, cfg_path.c_str()));
	layout_data.down_align_s = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("down_align_s"), 0, cfg_path.c_str()));
	layout_data.cpu_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_x_s"), 0, cfg_path.c_str()));
	layout_data.cpu_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_y_s"), 0, cfg_path.c_str()));
	layout_data.cpu_width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("cpu_width_s"), 0, cfg_path.c_str()));
	layout_data.cpu_align_s = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("cpu_align_s"), 0, cfg_path.c_str()));
	layout_data.memory_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_x_s"), 0, cfg_path.c_str()));
	layout_data.memory_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_y_s"), 0, cfg_path.c_str()));
	layout_data.memory_width_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("memory_width_s"), 0, cfg_path.c_str()));
	layout_data.memory_align_s = static_cast<Alignment>(GetPrivateProfileInt(_T("layout"), _T("memory_align_s"), 0, cfg_path.c_str()));
	layout_data.show_up_s = (GetPrivateProfileInt(_T("layout"), _T("show_up_s"), 1, cfg_path.c_str()) != 0);
	layout_data.show_down_s = (GetPrivateProfileInt(_T("layout"), _T("show_down_s"), 1, cfg_path.c_str()) != 0);
	layout_data.show_cpu_s = (GetPrivateProfileInt(_T("layout"), _T("show_cpu_s"), 0, cfg_path.c_str()) != 0);
	layout_data.show_memory_s = (GetPrivateProfileInt(_T("layout"), _T("show_memory_s"), 0, cfg_path.c_str()) != 0);
	layout_data.preview_x_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("preview_x_s"), 0, cfg_path.c_str()));
	layout_data.preview_y_s = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("preview_y_s"), 0, cfg_path.c_str()));
}

void CSkinDlg::ShowPreview()
{
	//���벼������
	wstring cfg_path{ theApp.m_skin_path + m_skins[m_skin_selected] + L"\\skin.ini" };
	LoadSkinLayout(cfg_path, m_skin_data.layout);
	//���뱳��ͼ
	LoadBackImage((theApp.m_skin_path + m_skins[m_skin_selected]).c_str(), true);
	LoadBackImage((theApp.m_skin_path + m_skins[m_skin_selected]).c_str(), false);
	//��ȡ��ǰƤ����������ɫ
	m_skin_data.text_color = GetPrivateProfileInt(_T("skin"), _T("text_color"), 0, cfg_path.c_str());
	//��ȡ��ǰƤ��������
	m_skin_data.font_name = CCommon::GetIniStringW(L"skin", L"font_name", L"", cfg_path.c_str());
	m_skin_data.font_size = GetPrivateProfileInt(_T("skin"), _T("font_size"), 0, cfg_path.c_str());
	m_view->IniFont();
	//��ȡƤ������
#define BUFF_SIZE 64
	wchar_t buff[BUFF_SIZE];
	GetPrivateProfileString(_T("skin"), _T("skin_author"), _T("unknow"), buff, BUFF_SIZE, cfg_path.c_str());
	SetDlgItemText(IDC_SKIN_INFO, (wstring(L"Ƥ�����ߣ�") + buff).c_str());
	//��ȡ��ʾ�ı�
	m_skin_data.disp_str.up = CCommon::GetIniStringW(_T("skin"), _T("up_string"), NONE_STR, cfg_path.c_str());
	m_skin_data.disp_str.down = CCommon::GetIniStringW(_T("skin"), _T("down_string"), NONE_STR, cfg_path.c_str());
	m_skin_data.disp_str.cpu = CCommon::GetIniStringW(_T("skin"), _T("cpu_string"), NONE_STR, cfg_path.c_str());
	m_skin_data.disp_str.memory = CCommon::GetIniStringW(_T("skin"), _T("memory_string"), NONE_STR, cfg_path.c_str());
	//��ȡԤ������С
	m_skin_data.layout.preview_width = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("preview_width"), 238, cfg_path.c_str()));
	m_skin_data.layout.preview_height = theApp.DPI(GetPrivateProfileInt(_T("layout"), _T("preview_height"), 105, cfg_path.c_str()));
	m_view->SetSize(m_skin_data.layout.preview_width, m_skin_data.layout.preview_height);
	//ˢ��Ԥ��ͼ
	m_view->Invalidate();
	//������ʾ��Ϣ
	bool cover_font_setting{ !m_skin_data.font_name.empty() || (m_skin_data.font_size >= MIN_FONT_SIZE && m_skin_data.font_size <= MAX_FONT_SIZE) };
	bool cover_str_setting{ !m_skin_data.disp_str.IsInvalid() };
	if (cover_font_setting && cover_str_setting)
		m_notify_static.SetWindowTextEx(_T("ע�⣺��Ƥ���Ḳ���������ú���ʾ�ı����á�"));
	else if(cover_font_setting)
		m_notify_static.SetWindowTextEx(_T("ע�⣺��Ƥ���Ḳ���������á�"));
	else if(cover_str_setting)
		m_notify_static.SetWindowTextEx(_T("ע�⣺��Ƥ���Ḳ����ʾ�ı����á�"));
	else
		m_notify_static.SetWindowTextEx(_T(""));
}


void CSkinDlg::LoadBackImage(const wstring & path, bool small_image)
{
	if (small_image)
	{
		m_background_s.Destroy();
		m_background_s.Load((path + BACKGROUND_IMAGE_S).c_str());
	}
	else
	{
		m_background_l.Destroy();
		m_background_l.Load((path + BACKGROUND_IMAGE_L).c_str());
	}
}

CRect CSkinDlg::CalculateViewRect()
{
	CRect rect;
	m_preview_static.GetWindowRect(rect);		//��ȡ��Ԥ���� group box ��λ��
	ScreenToClient(&rect);
	CRect scroll_view_rect{ rect };
	scroll_view_rect.DeflateRect(theApp.DPI(12), theApp.DPI(40));
	scroll_view_rect.top = rect.top + theApp.DPI(28);
	return scroll_view_rect;
}


BEGIN_MESSAGE_MAP(CSkinDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSkinDlg::OnCbnSelchangeCombo1)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CSkinDlg ��Ϣ�������

BOOL CSkinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(AfxGetApp()->LoadIcon(IDI_NOFITY_ICON3), FALSE);		// ����Сͼ��
	//��ʼ��ѡ���
	for (const auto& skin_path : m_skins)
	{
		wstring skin_name;
		size_t index = skin_path.find_last_of(L'\\');
		skin_name = skin_path.substr(index + 1);
		m_select_box.AddString(skin_name.c_str());
	}
	m_select_box.SetCurSel(m_skin_selected);
	m_select_box.SetMinVisibleItems(9);
	//��ʼ��Ԥ����ͼ
	m_view = (CSkinPreviewView*)RUNTIME_CLASS(CSkinPreviewView)->CreateObject();
	m_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, CalculateViewRect(), this, 3000);
	m_view->InitialUpdate();
	m_view->SetSkinData(&m_skin_data);
	m_view->SetBackImage(&m_background_s, &m_background_l);
	m_view->SetFont(m_pFont);
	m_view->IniFont();
	m_view->ShowWindow(SW_SHOW);

	//������ʾ��Ϣ
	m_notify_static.SetTextColor(RGB(252, 128, 45));
	m_notify_static.SetBackColor(GetSysColor(COLOR_BTNFACE));
	m_notify_static.SetWindowTextEx(_T(""));

	//��ʾԤ��ͼƬ
	ShowPreview();

	//��ȡ���ڳ�ʼʱ�Ĵ�С
	CRect rect;
	GetWindowRect(rect);
	m_min_size = rect.Size();

	//���ó�����
	m_skin_course.SetURL(_T("https://github.com/zhongyang219/TrafficMonitor/blob/master/Ƥ�������̳�.md"));
	m_skin_download.SetURL(_T("https://github.com/zhongyang219/TrafficMonitorSkin/blob/master/Ƥ������.md"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CSkinDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_skin_selected = m_select_box.GetCurSel();
	ShowPreview();
}


void CSkinDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(m_preview_static.m_hWnd!=NULL && nType!= SIZE_MINIMIZED)
		m_view->MoveWindow(CalculateViewRect());
}


void CSkinDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ƴ�����С��С
	lpMMI->ptMinTrackSize.x = m_min_size.cx;		//������С���
	lpMMI->ptMinTrackSize.y = m_min_size.cy;		//������С�߶�

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
