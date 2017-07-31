// TaskBarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TaskBarDlg.h"
#include "afxdialogex.h"


// CTaskBarDlg �Ի���

IMPLEMENT_DYNAMIC(CTaskBarDlg, CDialogEx)

CTaskBarDlg::CTaskBarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TASK_BAR_DIALOG, pParent)
{

}

CTaskBarDlg::~CTaskBarDlg()
{
}

void CTaskBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_UP1, m_disp_up);
	//DDX_Control(pDX, IDC_STATIC_DOWN1, m_disp_down);
	//DDX_Control(pDX, IDC_STATIC3, m_disp_cpu);
	//DDX_Control(pDX, IDC_STATIC4, m_disp_memory);
}


BEGIN_MESSAGE_MAP(CTaskBarDlg, CDialogEx)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SET_BACK_COLOR, &CTaskBarDlg::OnSetBackgroundColor)
	ON_COMMAND(ID_SET_TEXT_COLOR, &CTaskBarDlg::OnSetTextColor)
	ON_WM_INITMENU()
	ON_COMMAND(ID_SET_FONT2, &CTaskBarDlg::OnSetFont)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CTaskBarDlg ��Ϣ�������


void CTaskBarDlg::ShowInfo()
{
	if (this->m_hWnd == NULL || m_pDC == nullptr) return;
	CString str;
	CString in_speed = CCommon::DataSizeToString(theApp.m_in_speed);
	CString out_speed = CCommon::DataSizeToString(theApp.m_out_speed);
	
	//���û����DC
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);
	int draw_width = (m_show_cpu_memory ? m_window_width : m_window_width_s);
	MemBitmap.CreateCompatibleBitmap(m_pDC, draw_width, m_rect.Height());
	MemDC.SelectObject(&MemBitmap);
	//��ͼ
	CRect tmp{ m_rect };
	tmp.MoveToXY(0, 0);
	MemDC.FillSolidRect(tmp, m_back_color);		//��䱳��ɫ
	MemDC.SelectObject(&m_font);
	//�����ϴ��ٶ�
	tmp.bottom = m_window_height / 2;
	tmp.right = tmp.left + m_window_width_s;
	if (!m_swap_up_down)
		str.Format(_T("��:%s/s"), out_speed.GetString());
	else
		str.Format(_T("��:%s/s"), in_speed.GetString());
	CCommon::DrawWindowText(&MemDC, tmp, str, m_text_color, m_back_color);
	//���������ٶ�
	tmp.MoveToY(tmp.bottom);
	if (!m_swap_up_down)
		str.Format(_T("��:%s/s"), in_speed.GetString());
	else
		str.Format(_T("��:%s/s"), out_speed.GetString());
	CCommon::DrawWindowText(&MemDC, tmp, str, m_text_color, m_back_color);
	if (m_show_cpu_memory)
	{
		//����CPU������
		if (!m_taskbar_on_side)
		{
			tmp.MoveToXY(m_window_width_s, 0);
			tmp.right = tmp.left + (m_window_width - m_window_width_s);
		}
		else
		{
			tmp.MoveToY(m_window_height);
			tmp.right = tmp.left + (m_window_width - m_window_width_s);
		}
		str.Format(_T("CPU:%d%%"), theApp.m_cpu_usage);
		CCommon::DrawWindowText(&MemDC, tmp, str, m_text_color, m_back_color);
		//�����ڴ�������
		tmp.MoveToY(tmp.bottom);
		str.Format(_T("�ڴ�:%d%%"), theApp.m_memory_usage);
		CCommon::DrawWindowText(&MemDC, tmp, str, m_text_color, m_back_color);
	}
	//��������DC�е�ͼ�񿽱�����Ļ����ʾ
	m_pDC->BitBlt(0,0, draw_width, m_rect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();



	//if (!m_swap_up_down)
	//{
	//	str.Format(_T("��:%s/s"), out_speed.GetString());
	//	m_disp_up.SetWindowTextEx(str);
	//	str.Format(_T("��:%s/s"), in_speed.GetString());
	//	m_disp_down.SetWindowTextEx(str);
	//}
	//else
	//{
	//	str.Format(_T("��:%s/s"), in_speed.GetString());
	//	m_disp_up.SetWindowTextEx(str);
	//	str.Format(_T("��:%s/s"), out_speed.GetString());
	//	m_disp_down.SetWindowTextEx(str);
	//}
	//if (m_show_cpu_memory)
	//{
	//	str.Format(_T("CPU:%d%%"), theApp.m_cpu_usage);
	//	m_disp_cpu.SetWindowTextEx(str);
	//	str.Format(_T("�ڴ�:%d%%"), theApp.m_memory_usage);
	//	m_disp_memory.SetWindowTextEx(str);
	//}
	//else
	//{
	//	m_disp_cpu.SetWindowText(_T(""));
	//	m_disp_memory.SetWindowText(_T(""));
	//}
}


bool CTaskBarDlg::AdjustWindowPos()
{
	//CRect rect = m_rcMin;
	//rect.right = rect.left + m_min_bar_width;
	//::MoveWindow(m_hMin, 0, 0, rect.Width(), rect.Height(), TRUE);
	if (this->m_hWnd == NULL)
		return false;
	CRect rcMin;
	::GetWindowRect(m_hMin, rcMin);	//�����С�����ڵ�����
	if (rcMin.Width() >= rcMin.Height())		//����������Ŀ�ȴ��ڸ߶ȣ��������������涥����ײ�ʱ
	{
		//���ô��ڴ�С
		m_rect.right = m_rect.left + (m_show_cpu_memory ? m_window_width : m_window_width_s);
		m_rect.bottom = m_rect.top + m_window_height;
		if (rcMin.Width() != m_min_bar_width)	//�����С�����ڵĿ�ȸı��ˣ������������������ڵ�λ��
		{
			m_rcMin = rcMin;
			m_min_bar_width = m_rcMin.Width() - m_rect.Width();	//������С�����ڿ��
			::MoveWindow(m_hMin, 0, 0, m_rcMin.Width() - m_rect.Width(), m_rcMin.Height(), TRUE);	//������С�����ڵ�λ��
			::MoveWindow(this->m_hWnd, m_rcMin.Width() - m_rect.Width() + 2, (m_rcMin.Height() - m_rect.Height()) / 2, \
				m_rect.Width(), m_rect.Height(), TRUE);		//�������������ڵ�λ��

			CRect rect;
			GetWindowRect(rect);	//��ȡ��ǰ���ڵľ���λ��
			//�������û�б��ɹ�Ƕ�뵽�������������ƶ����˻�����Ļ���Ͻǵľ���λ�ã����������ڵ�λ��
			if (rect.left == m_rcMin.Width() - m_rect.Width() + 2 && rect.top == (m_rcMin.Height() - m_rect.Height()) / 2)
			{
				rect.MoveToXY(rect.left + m_rcBar.left, rect.top + m_rcBar.top);
				this->MoveWindow(rect);
			}
		}
		m_taskbar_on_side = false;
	}
	else		//������������Ļ�������Ҳ�ʱ
	{
		//���ô��ڴ�С
		m_rect.right = m_rect.left + m_window_width_s;
		m_rect.bottom = m_rect.top + (m_show_cpu_memory ? (2 * m_window_height) : m_window_height);
		if (rcMin.Height() != m_min_bar_height)	//�����С�����ڵĸ߶ȸı��ˣ������������������ڵ�λ��
		{
			m_rcMin = rcMin;
			m_min_bar_height = m_rcMin.Height() - m_rect.Height();	//������С�����ڸ߶�
			::MoveWindow(m_hMin, 0, 0, m_rcMin.Width(), m_rcMin.Height() - m_rect.Height(), TRUE);	//������С�����ڵ�λ��
			int left_pos = (m_rcMin.Width() - m_window_width_s) / 2;
			if (left_pos < 0) left_pos = 0;
			::MoveWindow(this->m_hWnd, left_pos, m_rcMin.Height() - m_rect.Height() + 2, \
				m_rect.Width(), m_rect.Height(), TRUE);		//�������������ڵ�λ��

			CRect rect;
			GetWindowRect(rect);	//��ȡ��ǰ���ڵľ���λ��
			//�������û�б��ɹ�Ƕ�뵽�������������ƶ����˻�����Ļ���Ͻǵľ���λ�ã����������ڵ�λ��
			if (rect.left == left_pos && rect.top == m_rcMin.Height() - m_rect.Height() + 2)
			{
				rect.MoveToXY(rect.left + m_rcBar.left, rect.top + m_rcBar.top);
				this->MoveWindow(rect);
			}
		}
		m_taskbar_on_side = true;
	}
	if (m_connot_insert_to_task_bar && ::GetForegroundWindow() == m_hTaskbar)	//�ڴ����޷�Ƕ��������ʱ������������������������ϣ����ô����ö�
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);			//�����ö�
	}
	return true;
}


void CTaskBarDlg::SaveConfig()
{
	CCommon::WritePrivateProfileIntW(L"task_bar", L"task_bar_back_color", m_back_color, theApp.m_config_path.c_str());
	CCommon::WritePrivateProfileIntW(L"task_bar", L"task_bar_text_color", m_text_color, theApp.m_config_path.c_str());
	CCommon::WritePrivateProfileIntW(L"task_bar", L"tack_bar_show_cpu_memory", m_show_cpu_memory, theApp.m_config_path.c_str());
	WritePrivateProfileString(_T("task_bar"), _T("tack_bar_font_name"), m_font_name, theApp.m_config_path.c_str());
	CCommon::WritePrivateProfileIntW(L"task_bar", L"tack_bar_font_size", m_font_size, theApp.m_config_path.c_str());
}

void CTaskBarDlg::LoadConfig()
{
	m_back_color = GetPrivateProfileInt(_T("task_bar"), _T("task_bar_back_color"), 0, theApp.m_config_path.c_str());
	m_text_color = GetPrivateProfileInt(_T("task_bar"), _T("task_bar_text_color"), 0x00ffffffU, theApp.m_config_path.c_str());
	m_show_cpu_memory = (GetPrivateProfileInt(_T("task_bar"), _T("tack_bar_show_cpu_memory"), 1, theApp.m_config_path.c_str()) != 0);
	m_swap_up_down = (GetPrivateProfileInt(_T("config"), _T("swap_up_down"), 0, theApp.m_config_path.c_str()) != 0);
	GetPrivateProfileString(_T("task_bar"), _T("tack_bar_font_name"), _T("΢���ź�"), m_font_name.GetBuffer(32), 32, theApp.m_config_path.c_str());
	m_font_size = GetPrivateProfileInt(_T("task_bar"), _T("tack_bar_font_size"), 9, theApp.m_config_path.c_str());
}

BOOL CTaskBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��������������ͼ��
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);

	LoadConfig();

	this->GetWindowRect(m_rect);
	m_window_width = m_rect.Width();
	m_window_width_s = static_cast<int>(m_rect.Width()*0.566f + 0.5f);
	m_window_height = m_rect.Height();
	if (!m_show_cpu_memory)
	{
		m_rect.right = m_rect.left + m_window_width_s;
	}

	m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);		//Ѱ��������Shell_TrayWnd�Ĵ��ھ��
	m_hBar = ::FindWindowEx(m_hTaskbar, 0, L"ReBarWindow32", NULL);	//Ѱ�Ҷ��������ľ��
	m_hMin = ::FindWindowEx(m_hBar, 0, L"MSTaskSwWClass", NULL);	//Ѱ����С�����ڵľ��

	::GetWindowRect(m_hMin, m_rcMin);	//�����С�����ڵ�����
	::GetWindowRect(m_hBar, m_rcBar);	//��ö�������������

	if (m_rcMin.Width() >= m_rcMin.Height())		//����������Ŀ�ȴ��ڸ߶ȣ��������������涥����ײ�ʱ
	{
		m_min_bar_width = m_rcMin.Width() - m_rect.Width();	//������С�����ڿ��

		//ͨ����MoveWindow�������ı�С�����ڵĿ��
		::MoveWindow(m_hMin, 0, 0, m_rcMin.Width() - m_rect.Width(), m_rcMin.Height(), TRUE);

		::SetParent(this->m_hWnd, m_hBar);	//�ѳ��򴰿����ó����������Ӵ���

		//�������򴰿ڵĴ�С��λ��
		//ע�����ѵ�ǰ��������Ϊ���������Ӵ��ں�MoveWindow�����ƶ���λ���ǻ��������������λ�ã�
		//��ĳЩ����£��类��ȫ�����ֹʱ�������޷�Ƕ�������������ڻ��ƶ���������Ļ���Ͻǵľ���λ�á�
		::MoveWindow(this->m_hWnd, m_rcMin.Width() - m_rect.Width() + 2, (m_rcBar.Height() - m_rect.Height()) / 2, \
			m_rect.Width(), m_rect.Height(), TRUE);

		CRect rect;
		GetWindowRect(rect);	//��ȡ��ǰ���ڵľ���λ��
		//�������û�б��ɹ�Ƕ�뵽�������������ƶ����˻�����Ļ���Ͻǵľ���λ�ã����������ڵ�λ��
		if (rect.left == m_rcMin.Width() - m_rect.Width() + 2 && rect.top == (m_rcBar.Height() - m_rect.Height()) / 2)
		{
			rect.MoveToXY(rect.left + m_rcBar.left, rect.top + m_rcBar.top);
			this->MoveWindow(rect);
			m_connot_insert_to_task_bar = true;
			MessageBox(_T("���棺����û�гɹ�Ƕ���������������ѱ���ȫ�����ֹ��"), NULL, MB_ICONWARNING);
		}
		m_taskbar_on_side = false;
	}
	else	//�������������������Ҳ�ʱ
	{
		int left_pos = (m_rcMin.Width() - m_window_width_s) / 2;
		if (left_pos < 0) left_pos = 0;
		if (m_show_cpu_memory)	//��CPU���ڴ������ʷŵ����ٵ�����
		{
			//m_disp_cpu.SetWindowPos(&CWnd::wndTop, 0, m_rect.Height(), 0, 0, SWP_NOSIZE);
			//m_disp_memory.SetWindowPos(&CWnd::wndTop, 0, m_rect.Height() * 3 / 2, 0, 0, SWP_NOSIZE);
			m_rect.right = m_rect.left + m_window_width_s;
			m_rect.bottom = m_rect.top + m_rect.Height() * 2;
		}
		m_min_bar_height = m_rcMin.Height() - m_rect.Height();	//������С�����ڸ߶�

		//ͨ����MoveWindow�������ı�С�����ڵĸ߶�
		::MoveWindow(m_hMin, 0, 0, m_rcMin.Width(), m_rcMin.Height() - m_rect.Height(), TRUE);

		::SetParent(this->m_hWnd, m_hBar);	//�ѳ��򴰿����ó����������Ӵ���

		//�������򴰿ڵĴ�С��λ��
		//ע�����ѵ�ǰ��������Ϊ���������Ӵ��ں�MoveWindow�����ƶ���λ���ǻ��������������λ�ã�
		//��ĳЩ����£��类��ȫ�����ֹʱ�������޷�Ƕ�������������ڻ��ƶ���������Ļ���Ͻǵľ���λ�á�
		::MoveWindow(this->m_hWnd, left_pos, m_rcMin.Height() - m_rect.Height() + 2, \
			m_rect.Width(), m_rect.Height(), TRUE);

		CRect rect;
		GetWindowRect(rect);	//��ȡ��ǰ���ڵľ���λ��
		//�������û�б��ɹ�Ƕ�뵽�������������ƶ����˻�����Ļ���Ͻǵľ���λ�ã����������ڵ�λ��
		if (rect.left == left_pos && rect.top == m_rcMin.Height() - m_rect.Height() + 2)
		{
			rect.MoveToXY(rect.left + m_rcBar.left, rect.top + m_rcBar.top);
			this->MoveWindow(rect);
			m_connot_insert_to_task_bar = true;
			MessageBox(_T("���棺����û�гɹ�Ƕ���������������ѱ���ȫ�����ֹ��"), NULL, MB_ICONWARNING);
		}
		m_taskbar_on_side = true;
	}

	m_menu.LoadMenu(IDR_TASK_BAR_MENU);

	SetBackgroundColor(m_back_color);


	//��������
	m_font.CreatePointFont(m_font_size * 10, m_font_name);

	m_tool_tips.Create(this, TTS_ALWAYSTIP);
	m_tool_tips.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		//������ʾ��Ϣ�����ö�

	m_pDC = GetDC();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTaskBarDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	SaveConfig();
	DestroyWindow();
	//����رյ�ʱ�򣬰���С�����ڵ�width�ָ���ȥ
	::MoveWindow(m_hMin, 0, 0, m_rcMin.Width(), m_rcMin.Height(), TRUE);

	//CDialogEx::OnCancel();
}


void CTaskBarDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CPoint point1;	//����һ������ȷ�����λ�õ�λ��  
	GetCursorPos(&point1);	//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����  
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, this); //��ָ��λ����ʾ�����˵�
	CDialogEx::OnRButtonUp(nFlags, point1);
}


void CTaskBarDlg::OnSetBackgroundColor()
{
	// TODO: �ڴ���������������
	CColorDialog colorDlg(m_back_color, 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_back_color = colorDlg.GetColor();
		if (m_back_color == m_text_color)
			MessageBox(_T("���棺����ɫ��������ɫ��ͬ��"),NULL, MB_ICONWARNING);
		SetBackgroundColor(m_back_color);
		ShowInfo();
		SaveConfig();
	}
}

void CTaskBarDlg::OnSetTextColor()
{
	// TODO: �ڴ���������������
	CColorDialog colorDlg(m_text_color, 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_text_color = colorDlg.GetColor();
		if (m_back_color == m_text_color)
			MessageBox(_T("���棺������ɫ�ͱ���ɫ��ͬ��"), NULL, MB_ICONWARNING);
		//m_disp_cpu.SetTextColor(m_text_color);
		//m_disp_memory.SetTextColor(m_text_color);
		//m_disp_up.SetTextColor(m_text_color);
		//m_disp_down.SetTextColor(m_text_color);
		ShowInfo();
		SaveConfig();
	}
}


void CTaskBarDlg::OnInitMenu(CMenu* pMenu)
{
	CDialogEx::OnInitMenu(pMenu);

	// TODO: �ڴ˴������Ϣ����������
	pMenu->CheckMenuItem(ID_SHOW_CPU_MEMORY2, MF_BYCOMMAND | (m_show_cpu_memory ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_HIDE_MAIN_WND, MF_BYCOMMAND | (theApp.m_hide_main_window ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_SHOW_NOTIFY_ICON, MF_BYCOMMAND | (theApp.m_show_notify_icon ? MF_CHECKED : MF_UNCHECKED));

	pMenu->SetDefaultItem(ID_NETWORK_INFO);
}


BOOL CTaskBarDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//���ΰ��س�����ESC���˳�
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;

	if (m_tool_tips.GetSafeHwnd() && (pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE))
	{
		m_tool_tips.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTaskBarDlg::OnSetFont()
{
	// TODO: �ڴ���������������
	LOGFONT lf{};             //LOGFONT����
	m_font.GetLogFont(&lf);
	CFontDialog fontDlg(&lf);	//��������Ի��򣬳�ʼѡ������Ϊ֮ǰ����
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���
	{
		//���m_font�Ѿ�������һ��������Դ�������ͷ���
		if (m_font.m_hObject)
		{
			m_font.DeleteObject();
		}
		//ʹ��ѡ�������LOGFONT�����µ�����
		m_font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);
		//��ȡ������Ϣ
		m_font_name = fontDlg.m_cf.lpLogFont->lfFaceName;
		m_font_size = fontDlg.m_cf.iPointSize / 10;
		//ˢ�½�����Ϣ
		ShowInfo();
		//����������д�뵽ini�ļ�
		SaveConfig();
	}
}


void CTaskBarDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_tool_tips.SetMaxTipWidth(600);
	CString tip_info;
	if (m_show_cpu_memory)
	{
		tip_info.Format(_T("������ʹ��������%s\r\n�ڴ�ʹ�ã�%s/%s"), CCommon::KBytesToString(static_cast<unsigned int>(theApp.m_today_traffic / 1024)),
			CCommon::KBytesToString(theApp.m_used_memory), CCommon::KBytesToString(theApp.m_total_memory));
	}
	else
	{
		tip_info.Format(_T("������ʹ��������%s\r\nCPUʹ�ã�%d%%\r\n�ڴ�ʹ�ã�%s/%s (%d%%)"), CCommon::KBytesToString(static_cast<unsigned int>(theApp.m_today_traffic / 1024)),
			theApp.m_cpu_usage,
			CCommon::KBytesToString(theApp.m_used_memory), CCommon::KBytesToString(theApp.m_total_memory),
			theApp.m_memory_usage);
	}
	m_tool_tips.AddTool(this, tip_info);
	//m_tool_tips.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		//������ʾ��Ϣ�����ö�

	CDialogEx::OnMouseMove(nFlags, point);
}


void CTaskBarDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_COMMAND,ID_NETWORK_INFO);		//˫���󵯳����������顱�Ի���
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
