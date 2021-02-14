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
	m_cpu_his.RemoveAll();
	m_memory_his.RemoveAll();
}

void CTaskBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTaskBarDlg, CDialogEx)
	ON_WM_RBUTTONUP()
	ON_WM_INITMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTaskBarDlg ��Ϣ�������


void CTaskBarDlg::ShowInfo(CDC* pDC)
{
	if (this->GetSafeHwnd() == NULL || pDC == nullptr || !IsWindow(this->GetSafeHwnd())) return;

	if (m_rect.IsRectEmpty() || m_rect.IsRectNull()) return;

	//���û����DC
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC, m_window_width, m_window_height);
	MemDC.SelectObject(&MemBitmap);
	//��ͼ
    CRect draw_rect{ m_rect };      //��ͼ�ľ�������
    draw_rect.MoveToXY(0, 0);
	MemDC.FillSolidRect(draw_rect, theApp.m_taskbar_data.back_color);		//��䱳��ɫ
	CDrawCommon draw;
	draw.Create(&MemDC, nullptr);
	draw.SetFont(&m_font);
	draw.SetBackColor(theApp.m_taskbar_data.back_color);

    //��������ֵ�λ��
    int index = 0;
    CRect item_rect{};
    int item_count = CCommon::CountOneBits(theApp.m_cfg_data.m_tbar_display_item);  //Ҫ��ʾ����Ŀ����
    auto last_iter = m_item_widths.begin();
    for (auto iter = m_item_widths.begin(); iter != m_item_widths.end(); ++iter)
    {
        if (theApp.m_cfg_data.m_tbar_display_item & iter->first)    //���������Ҫ��ʾ�����Ż���
        {
            //�����������涥����ײ�
            if (IsTasksbarOnTopOrBottom())
            {
                if (theApp.m_taskbar_data.horizontal_arrange)   //ˮƽ����
                {
                    if (index > 0)
                        item_rect.MoveToX(item_rect.right + theApp.DPI(4));
                    item_rect.right = item_rect.left + iter->second.TotalWidth();
                    item_rect.bottom = item_rect.top + m_window_height;
                    DrawDisplayItem(draw, iter->first, item_rect, iter->second.label_width);
                }
                else        //��ˮƽ����ʱ��ÿ����һ����ʾ
                {
                    //��indexΪ����ʱͬʱ����������Ŀ
                    if (index % 2 == 1)
                    {
                        CRect item_rect_up;     //����һ����Ŀ�ľ�������
                        if (index > 0)
                            item_rect_up.MoveToXY(item_rect.right + theApp.DPI(4), 0);
                        item_rect.left = item_rect_up.left;
                        item_rect.top = (m_window_height - TASKBAR_WND_HEIGHT / 2);
                        //ȷ�����ڴ�С
                        item_rect_up.bottom = item_rect.top - 1;
                        item_rect.bottom = m_window_height;
                        int width = max(iter->second.TotalWidth(), last_iter->second.TotalWidth());
                        item_rect.right = item_rect.left + width;
                        item_rect_up.right = item_rect_up.left + width;
                        int label_width = max(iter->second.label_width, last_iter->second.label_width);
                        //������Ϣ
                        DrawDisplayItem(draw, last_iter->first, item_rect_up, label_width);
                        DrawDisplayItem(draw, iter->first, item_rect, label_width);
                    }
                    //Ҫ���Ƶ���ĿΪ����ʱ�������һ��
                    else if (item_count % 2 == 1 && index == item_count - 1)
                    {
                        item_rect.MoveToXY(item_rect.right + theApp.DPI(4), 0);
                        item_rect.bottom = TASKBAR_WND_HEIGHT / 2;
                        item_rect.right = item_rect.left + iter->second.TotalWidth();
                        DrawDisplayItem(draw, iter->first, item_rect, iter->second.label_width);
                    }
                }
            }
            //����������������
            else
            {
                if (index > 0)
                    item_rect.MoveToXY(0, item_rect.bottom + theApp.DPI(2));
                item_rect.bottom = item_rect.top + TASKBAR_WND_HEIGHT / 2;
                item_rect.right = item_rect.left + min(m_window_width, m_rcMin.Width() - theApp.DPI(2));
                DrawDisplayItem(draw, iter->first, item_rect, iter->second.label_width);
            }

            index++;
            last_iter = iter;
        }
    }

	//��������DC�е�ͼ�񿽱�����Ļ����ʾ
	pDC->BitBlt(0,0, m_window_width, m_window_height, &MemDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CTaskBarDlg::DrawDisplayItem(CDrawCommon& drawer, TaskbarDisplayItem type, CRect rect, int label_width)
{
    //����Ҫ���Ƶ��ı���ɫ
    COLORREF label_color{};
    COLORREF text_color{};
    if (theApp.m_taskbar_data.specify_each_item_color)
    {
        switch (type)
        {
        case TDI_UP:
            label_color = theApp.m_taskbar_data.text_colors[0];
            text_color = theApp.m_taskbar_data.text_colors[1];
            break;
        case TDI_DOWN:
            label_color = theApp.m_taskbar_data.text_colors[2];
            text_color = theApp.m_taskbar_data.text_colors[3];
            break;
        case TDI_CPU:
            label_color = theApp.m_taskbar_data.text_colors[4];
            text_color = theApp.m_taskbar_data.text_colors[5];
            break;
        case TDI_MEMORY:
            label_color = theApp.m_taskbar_data.text_colors[6];
            text_color = theApp.m_taskbar_data.text_colors[7];
            break;
        default:
            label_color = theApp.m_taskbar_data.text_colors[0];
            text_color = theApp.m_taskbar_data.text_colors[1];
            break;
        }
    }
    else
    {
        label_color = theApp.m_taskbar_data.text_colors[0];
        text_color = theApp.m_taskbar_data.text_colors[0];
    }
    
    //���ñ�ǩ����ֵ�ľ�������
    CRect rect_label{ rect };
    rect_label.right = rect_label.left + label_width;
    CRect rect_value{ rect };
    rect_value.left = rect_label.right;

    // ����״̬��
    if (type == TDI_CPU || type == TDI_MEMORY)
    {
        if (theApp.m_taskbar_data.cm_graph_type)
        {
            if (type == TDI_CPU)
            {
                AddHisToList(m_cpu_his, theApp.m_cpu_usage);
                TryDrawGraph(drawer, rect, m_cpu_his);
            }
            else
            {
                AddHisToList(m_memory_his, theApp.m_memory_usage);
                TryDrawGraph(drawer, rect, m_memory_his);
            }
        }
        else
        {
            int usage = (type == TDI_CPU ? theApp.m_cpu_usage : theApp.m_memory_usage);
            TryDrawStatusBar(drawer, rect, usage);
        }
    }

    //���Ʊ�ǩ
    wstring str_label = theApp.m_taskbar_data.disp_str.Get(type);
    if (theApp.m_taskbar_data.swap_up_down)
    {
        if (type == TDI_UP)
            str_label = theApp.m_taskbar_data.disp_str.Get(TDI_DOWN);
        else if (type == TDI_DOWN)
            str_label = theApp.m_taskbar_data.disp_str.Get(TDI_UP);
    }
    drawer.DrawWindowText(rect, str_label.c_str(), label_color);

    //������ֵ
    CString str_value;
    Alignment value_alignment{ theApp.m_taskbar_data.value_right_align ? Alignment::RIGHT : Alignment::LEFT };		//��ֵ�Ķ��뷽ʽ
    //�����ϴ��������ٶ�
    if (type == TDI_UP || type == TDI_DOWN)
    {
        CString format_str;
        if (theApp.m_taskbar_data.hide_unit && theApp.m_taskbar_data.speed_unit != SpeedUnit::AUTO)
            format_str = _T("%s");
        else
            format_str = _T("%s/s");
        CString str_in_speed = CCommon::DataSizeToString(theApp.m_in_speed, theApp.m_taskbar_data);
        CString str_out_speed = CCommon::DataSizeToString(theApp.m_out_speed, theApp.m_taskbar_data);
        if (theApp.m_taskbar_data.swap_up_down)
            std::swap(str_in_speed, str_out_speed);
        if (type == TDI_UP)
        {
            str_value.Format(format_str, str_out_speed.GetString());
        }
        else
        {
            str_value.Format(format_str, str_in_speed.GetString());
        }
    }

    //����CPU���ڴ�������
    else if (type == TDI_CPU || type == TDI_MEMORY)
    {
        int usage = (type == TDI_CPU ? theApp.m_cpu_usage : theApp.m_memory_usage);
        CString format_str;
        if (theApp.m_taskbar_data.hide_percent)
            format_str = _T("%d");
        else if (theApp.m_taskbar_data.separate_value_unit_with_space)
            format_str = _T("%d %%");
        else
            format_str = _T("%d%%");
        str_value.Format(format_str, usage);
    }

    //�����¶�
    else if (type == TDI_CPU_TEMP || type == TDI_GPU_TEMP || type == TDI_HDD_TEMP || type == TDI_MAIN_BOARD_TEMP)
    {
        int temperature{};
        switch (type)
        {
        case TDI_CPU_TEMP:
            temperature = theApp.m_cpu_temperature;
            break;
        case TDI_GPU_TEMP:
            temperature = theApp.m_gpu_temperature;
            break;
        case TDI_HDD_TEMP:
            temperature = theApp.m_hdd_temperature;
            break;
        case TDI_MAIN_BOARD_TEMP:
            temperature = theApp.m_main_board_temperature;
            break;
        default:
            break;
        }
        CString format_str;
        if (theApp.m_taskbar_data.separate_value_unit_with_space)
            format_str = _T("%d ��");
        else
            format_str = _T("%d��");
        str_value.Format(format_str, temperature);
    }

    drawer.DrawWindowText(rect_value, str_value, text_color, value_alignment);
}

void CTaskBarDlg::TryDrawStatusBar(CDrawCommon& drawer, const CRect& rect_bar, int usage_percent)
{
	if (!theApp.m_taskbar_data.show_status_bar)
	{
		return;
	}

	CSize fill_size = CSize(rect_bar.Width() * usage_percent / 100, rect_bar.Height());
	CRect rect_fill(rect_bar.TopLeft(), fill_size);
	drawer.DrawRectOutLine(rect_bar, theApp.m_taskbar_data.status_bar_color, 1, true);
	drawer.FillRect(rect_fill, theApp.m_taskbar_data.status_bar_color);
}

bool CTaskBarDlg::AdjustWindowPos()
{
	if (this->GetSafeHwnd() == NULL || !IsWindow(this->GetSafeHwnd()))
		return false;
	CRect rcMin, rcBar;
	::GetWindowRect(m_hMin, rcMin);	//�����С�����ڵ�����
	::GetWindowRect(m_hBar, rcBar);	//��ö�������������
	static bool last_taskbar_on_top_or_bottom;
	CheckTaskbarOnTopOrBottom();
	if (m_taskbar_on_top_or_bottom != last_taskbar_on_top_or_bottom)
	{
		CalculateWindowSize();
		last_taskbar_on_top_or_bottom = m_taskbar_on_top_or_bottom;
	}

	if (m_taskbar_on_top_or_bottom)		//�������������涥����ײ�ʱ
	{
		//���ô��ڴ�С
		m_rect.right = m_rect.left + m_window_width;
		m_rect.bottom = m_rect.top + m_window_height;
		if (rcMin.Width() != m_min_bar_width)	//�����С�����ڵĿ�ȸı��ˣ������������������ڵ�λ��
		{
			m_left_space = rcMin.left - rcBar.left;
			m_rcMin = rcMin;
			m_min_bar_width = m_rcMin.Width() - m_rect.Width();	//������С�����ڿ��
			if (!theApp.m_taskbar_data.tbar_wnd_on_left)
			{
				::MoveWindow(m_hMin, m_left_space, 0, m_rcMin.Width() - m_rect.Width(), m_rcMin.Height(), TRUE);	//������С�����ڵ�λ��
				m_rect.MoveToX(m_left_space + m_rcMin.Width() - m_rect.Width() + 2);
			}
			else
			{
				::MoveWindow(m_hMin, m_left_space + m_rect.Width(), 0, m_rcMin.Width() - m_rect.Width(), m_rcMin.Height(), TRUE);
				m_rect.MoveToX(m_left_space);
			}
			m_rect.MoveToY((rcBar.Height() - m_rect.Height()) / 2);
			if (theApp.m_taskbar_data.horizontal_arrange && theApp.m_win_version.IsWindows7())
				m_rect.MoveToY(m_rect.top + theApp.DPI(1));
			MoveWindow(m_rect);
		}
	}
	else		//������������Ļ�������Ҳ�ʱ
	{
		//���ô��ڴ�С
		if (rcMin.Height() != m_min_bar_height)	//�����С�����ڵĸ߶ȸı��ˣ������������������ڵ�λ��
		{
			m_top_space = rcMin.top - rcBar.top;
			m_rcMin = rcMin;
			m_min_bar_height = m_rcMin.Height() - m_rect.Height();	//������С�����ڸ߶�
			if (!theApp.m_taskbar_data.tbar_wnd_on_left)
			{
				::MoveWindow(m_hMin, 0, m_top_space, m_rcMin.Width(), m_rcMin.Height() - m_rect.Height(), TRUE);	//������С�����ڵ�λ��
				m_rect.MoveToY(m_top_space + m_rcMin.Height() - m_rect.Height() + 2);
			}
			else
			{
				::MoveWindow(m_hMin, 0, m_top_space + m_rect.Height(), m_rcMin.Width(), m_rcMin.Height() - m_rect.Height(), TRUE);	//������С�����ڵ�λ��
				m_rect.MoveToY(m_top_space);
			}
			m_rect.MoveToX((m_rcMin.Width() - m_window_width) / 2);
			if (m_rect.left < theApp.DPI(2))
				m_rect.MoveToX(theApp.DPI(2));
			MoveWindow(m_rect);
		}
	}

	CRect rect{ m_rect };
	//�������û�б��ɹ�Ƕ�뵽�������������ƶ����˻�����Ļ���Ͻǵľ���λ�ã����������ڵ�λ��
	if (m_connot_insert_to_task_bar)
	{
		rect.MoveToXY(rect.left + rcBar.left, rect.top + rcBar.top);
		this->MoveWindow(rect);
	}

	if (m_connot_insert_to_task_bar && ::GetForegroundWindow() == m_hTaskbar)	//�ڴ����޷�Ƕ��������ʱ������������������������ϣ����ô����ö�
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);			//�����ö�
	}
	return true;
}

void CTaskBarDlg::ApplyWindowTransparentColor()
{
#ifndef COMPILE_FOR_WINXP
	if (theApp.m_taskbar_data.transparent_color != 0 && theApp.m_taksbar_transparent_color_enable)
	{
		SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(theApp.m_taskbar_data.transparent_color, 0, LWA_COLORKEY);
	}
	else
	{
		SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
	}
#endif // !COMPILE_FOR_WINXP
}


void CTaskBarDlg::CheckTaskbarOnTopOrBottom()
{
	CRect rect;
	CRect rcMin;
	CRect rcBar;
	if (m_hTaskbar != 0)
	{
		::GetWindowRect(m_hMin, rcMin);	//�����С�����ڵ�����
		::GetWindowRect(m_hBar, rcBar);	//��ö�������������
		if(m_left_space==0)
			m_left_space = rcMin.left - rcBar.left;
		if(m_top_space==0)
			m_top_space = rcMin.top - rcBar.top;

		::GetWindowRect(m_hTaskbar, rect);			//��ȡ�������ľ�������
		m_taskbar_on_top_or_bottom = (rect.Width()>=rect.Height());		//����������Ŀ�ȴ��ڸ߶ȣ�����������Ļ�Ķ�����ײ�
	}
	else
	{
        m_taskbar_on_top_or_bottom = true;
	}
}

CString CTaskBarDlg::GetMouseTipsInfo()
{
	CString tip_info;
	CString temp;
	temp.Format(_T("%s: %s (%s: %s/%s: %s)"), CCommon::LoadText(IDS_TRAFFIC_USED_TODAY),
		CCommon::KBytesToString(static_cast<unsigned int>((theApp.m_today_up_traffic + theApp.m_today_down_traffic) / 1024)),
		CCommon::LoadText(IDS_UPLOAD), CCommon::KBytesToString(static_cast<unsigned int>(theApp.m_today_up_traffic / 1024)),
		CCommon::LoadText(IDS_DOWNLOAD), CCommon::KBytesToString(static_cast<unsigned int>(theApp.m_today_down_traffic / 1024))
	);
	tip_info += temp;
	if (!IsShowUp())
	{
		temp.Format(_T("\r\n%s: %s/s"), CCommon::LoadText(IDS_UPLOAD),
			CCommon::DataSizeToString(theApp.m_out_speed, theApp.m_main_wnd_data));
		tip_info += temp;
	}
	if (!IsShowDown())
	{
		temp.Format(_T("\r\n%s: %s/s"), CCommon::LoadText(IDS_DOWNLOAD),
			CCommon::DataSizeToString(theApp.m_in_speed, theApp.m_main_wnd_data));
		tip_info += temp;
	}
	if (!IsShowCpu())
	{
		temp.Format(_T("\r\n%s: %d%%"), CCommon::LoadText(IDS_CPU_USAGE), theApp.m_cpu_usage);
		tip_info += temp;
	}
	if (!IsShowCpuMemory())
	{
		temp.Format(_T("\r\n%s: %s/%s"),
			CCommon::LoadText(IDS_MEMORY_USAGE),
			CCommon::KBytesToString(theApp.m_used_memory), CCommon::KBytesToString(theApp.m_total_memory));
	}
	if (!IsShowMemory())
	{
		temp.Format(_T("\r\n%s: %s/%s (%d%%)"), CCommon::LoadText(IDS_MEMORY_USAGE),
			CCommon::KBytesToString(theApp.m_used_memory),
			CCommon::KBytesToString(theApp.m_total_memory), theApp.m_memory_usage);
		tip_info += temp;
	}
	else
	{
		temp.Format(_T("\r\n%s: %s/%s"), CCommon::LoadText(IDS_MEMORY_USAGE),
			CCommon::KBytesToString(theApp.m_used_memory),
			CCommon::KBytesToString(theApp.m_total_memory));
		tip_info += temp;
	}
	return tip_info;
}

void CTaskBarDlg::SetTextFont()
{
	//���m_font�Ѿ�������һ��������Դ�������ͷ���
	if (m_font.m_hObject)
	{
		m_font.DeleteObject();
	}
	//�����µ�����
	m_font.CreateFont(
		FONTSIZE_TO_LFHEIGHT(theApp.m_taskbar_data.font.size), // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		(theApp.m_taskbar_data.font.bold ? FW_BOLD : FW_NORMAL), // nWeight
		theApp.m_taskbar_data.font.italic, // bItalic
		theApp.m_taskbar_data.font.underline, // bUnderline
		theApp.m_taskbar_data.font.strike_out, // cStrikeOut
		DEFAULT_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		theApp.m_taskbar_data.font.name);
}

void CTaskBarDlg::ApplySettings()
{
	SetTextFont();
	CalculateWindowSize();
}

void CTaskBarDlg::CalculateWindowSize()
{
	bool horizontal_arrange = theApp.m_taskbar_data.horizontal_arrange && m_taskbar_on_top_or_bottom;
    int item_count = CCommon::CountOneBits(theApp.m_cfg_data.m_tbar_display_item);
    m_item_widths.clear();

    m_pDC->SelectObject(&m_font);
	//�����ǩ���
    const auto& item_map = theApp.m_taskbar_data.disp_str.GetAllItems();
    for (auto iter = item_map.begin(); iter != item_map.end(); ++iter)
    {
        m_item_widths[iter->first].label_width = m_pDC->GetTextExtent(iter->second.c_str()).cx;
    }

    //������ֵ���ֿ��

    //������ʾ�ϴ����ز�������Ҫ�Ŀ��
	CString sample_str;
    int value_width{};
	wstring digits(theApp.m_taskbar_data.digits_number, L'8');		//��������λ������ָ�������ġ�8��
	bool hide_unit{ theApp.m_taskbar_data.hide_unit && theApp.m_taskbar_data.speed_unit != SpeedUnit::AUTO };
	if (theApp.m_taskbar_data.speed_short_mode)
	{
		if (hide_unit)
			sample_str.Format(_T("%s."), digits.c_str());
		else
			sample_str.Format(_T("%s.M/s"), digits.c_str());
	}
	else
	{
		if (hide_unit)
			sample_str.Format(_T("%s.8"), digits.c_str());
		else
			sample_str.Format(_T("%s.8MB/s"), digits.c_str());
	}
	if (!hide_unit && theApp.m_taskbar_data.separate_value_unit_with_space)
		sample_str += _T(' ');
	if(theApp.m_taskbar_data.speed_short_mode && !theApp.m_taskbar_data.unit_byte && !theApp.m_taskbar_data.hide_unit)
		sample_str += _T('b');
    value_width = m_pDC->GetTextExtent(sample_str).cx;		//����ʹ�õ�ǰ������ʾ�ı���Ҫ�Ŀ��ֵ
	m_item_widths[TDI_UP].value_width = value_width;
    m_item_widths[TDI_DOWN].value_width = value_width;

	//������ʾCPU���ڴ沿������Ҫ�Ŀ��
    CString str;
    if (theApp.m_taskbar_data.hide_percent)
	{
		str = _T("100");
	}
	else if (theApp.m_taskbar_data.separate_value_unit_with_space)
	{
        str = _T("100 %");
	}
	else
	{
        str = _T("100%");
	}
    value_width = m_pDC->GetTextExtent(str).cx;
    m_item_widths[TDI_CPU].value_width = value_width;
    m_item_widths[TDI_MEMORY].value_width = value_width;

    //�����¶���ʾ�Ŀ��
    if (theApp.m_taskbar_data.separate_value_unit_with_space)
        str = _T("99 ��");
    else
        str = _T("99��");
    value_width = m_pDC->GetTextExtent(str).cx;
    m_item_widths[TDI_CPU_TEMP].value_width = value_width;
    m_item_widths[TDI_GPU_TEMP].value_width = value_width;
    m_item_widths[TDI_HDD_TEMP].value_width = value_width;
    m_item_widths[TDI_MAIN_BOARD_TEMP].value_width = value_width;

    //���㴰���ܿ��
    if (IsTasksbarOnTopOrBottom())  //������������Ķ�����ײ�ʱ
    {
        m_window_width = 0;
        if (theApp.m_taskbar_data.horizontal_arrange)   //ˮƽ����ʱ
        {
            for (auto iter = m_item_widths.begin(); iter != m_item_widths.end(); ++iter)
            {
                if (theApp.m_cfg_data.m_tbar_display_item & iter->first)
                    m_window_width += iter->second.TotalWidth();
            }
            m_window_width += theApp.DPI(4) * (m_item_widths.size()/* - 1*/);   //����ÿ����ǩ��Ŀ�϶
        }
        else        //��ˮƽ����ʱ��ÿ����һ������
        {
            int index = 0;
            int width0;
            for (auto iter = m_item_widths.begin(); iter != m_item_widths.end(); ++iter)
            {
                if (theApp.m_cfg_data.m_tbar_display_item & iter->first)
                {
                    if (index % 2 == 0)
                    {
                        width0 = iter->second.TotalWidth();
                    }
                    else
                    {
                        m_window_width += max(width0, iter->second.TotalWidth());
                    }
                    if (item_count % 2 == 1 && index == item_count - 1) //��Ŀ��Ϊ����ʱ�������һ���Ŀ��
                    {
                        m_window_width += iter->second.TotalWidth();
                    }

                    index++;
                }
            }
            m_window_width += theApp.DPI(4) * ((m_item_widths.size() - 1) / 2 + 1);   //����ÿ����ǩ��Ŀ�϶
        }
    }
    else        //����������������ʱ
    {
        m_window_width = 0;
        //���б�ǩ�����Ŀ�ȼ�Ϊ���ڿ��
        for (auto iter = m_item_widths.begin(); iter != m_item_widths.end(); ++iter)
        {
            if (theApp.m_cfg_data.m_tbar_display_item & iter->first)
            {
                if (m_window_width < iter->second.TotalWidth())
                    m_window_width = iter->second.TotalWidth();
            }
        }
    }

    //���㴰�ڸ߶�
    if (IsTasksbarOnTopOrBottom())
    {
        if (!horizontal_arrange)
            m_window_height = TASKBAR_WND_HEIGHT;
        else
            m_window_height = TASKBAR_WND_HEIGHT * 3 / 4;
    }
    else
    {
        m_window_height = 0;
        for (auto iter = m_item_widths.begin(); iter != m_item_widths.end(); ++iter)
        {
            if (theApp.m_cfg_data.m_tbar_display_item & iter->first)
                m_window_height += (TASKBAR_WND_HEIGHT / 2);
        }
        m_window_height += (theApp.DPI(2) * (m_item_widths.size() - 1));   //����ÿ����ǩ��Ŀ�϶
    }
    m_rect.right = m_rect.left + m_window_width;
	m_rect.bottom = m_rect.top + m_window_height;

}

void CTaskBarDlg::SetToolTipsTopMost()
{
	m_tool_tips.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void CTaskBarDlg::UpdateToolTips()
{
	if (theApp.m_taskbar_data.show_tool_tip)
	{
		CString tip_info;
		tip_info = GetMouseTipsInfo();
		m_tool_tips.UpdateTipText(tip_info, this);
	}
}

bool CTaskBarDlg::IsShowCpuMemory()
{
	return ((theApp.m_cfg_data.m_tbar_display_item & TDI_CPU) || (theApp.m_cfg_data.m_tbar_display_item & TDI_MEMORY));
}

bool CTaskBarDlg::IsShowNetSpeed()
{
	return ((theApp.m_cfg_data.m_tbar_display_item & TDI_UP) || (theApp.m_cfg_data.m_tbar_display_item & TDI_DOWN));
}

bool CTaskBarDlg::IsShowUp()
{
	return (theApp.m_cfg_data.m_tbar_display_item & TDI_UP);
}

bool CTaskBarDlg::IsShowDown()
{
	return (theApp.m_cfg_data.m_tbar_display_item & TDI_DOWN);
}

bool CTaskBarDlg::IsShowCpu()
{
	return (theApp.m_cfg_data.m_tbar_display_item & TDI_CPU);
}

bool CTaskBarDlg::IsShowMemory()
{
	return (theApp.m_cfg_data.m_tbar_display_item & TDI_MEMORY);
}

bool CTaskBarDlg::IsShowCpuTemperature()
{
    return (theApp.m_cfg_data.m_tbar_display_item & TDI_CPU_TEMP);
}

bool CTaskBarDlg::IsShowGpuTemperature()
{
    return (theApp.m_cfg_data.m_tbar_display_item & TDI_GPU_TEMP);
}

bool CTaskBarDlg::IsShowHddTemperature()
{
    return (theApp.m_cfg_data.m_tbar_display_item & TDI_HDD_TEMP);
}

bool CTaskBarDlg::IsShowMainboardTemperature()
{
    return (theApp.m_cfg_data.m_tbar_display_item & TDI_MAIN_BOARD_TEMP);
}

BOOL CTaskBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��������������ͼ��
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);

	m_pDC = GetDC();


	//��������
	SetTextFont();
	m_pDC->SelectObject(&m_font);


	m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);		//Ѱ��������Shell_TrayWnd�Ĵ��ھ��
	m_hBar = ::FindWindowEx(m_hTaskbar, 0, L"ReBarWindow32", NULL);	//Ѱ�Ҷ��������ľ��
	m_hMin = ::FindWindowEx(m_hBar, 0, L"MSTaskSwWClass", NULL);	//Ѱ����С�����ڵľ��

	//���ô���͸��ɫ
	ApplyWindowTransparentColor();

	::GetWindowRect(m_hMin, m_rcMin);	//�����С�����ڵ�����
	::GetWindowRect(m_hBar, m_rcBar);	//��ö�������������
	m_left_space = m_rcMin.left - m_rcBar.left;
	m_top_space = m_rcMin.top - m_rcBar.top;

	CheckTaskbarOnTopOrBottom();
	CalculateWindowSize();
	m_rect.SetRectEmpty();
	m_rect.bottom = m_window_height;
	m_rect.right = m_rect.left + m_window_width;

	if (m_taskbar_on_top_or_bottom)		//��������������涥����ײ�
	{
		m_min_bar_width = m_rcMin.Width() - m_rect.Width();	//������С�����ڿ��

		//ͨ����MoveWindow�������ı�С�����ڵĿ��
		if(!theApp.m_taskbar_data.tbar_wnd_on_left)
			::MoveWindow(m_hMin, m_left_space, 0, m_rcMin.Width() - m_rect.Width(), m_rcMin.Height(), TRUE);
		else
			::MoveWindow(m_hMin, m_left_space + m_rect.Width(), 0, m_rcMin.Width() - m_rect.Width(), m_rcMin.Height(), TRUE);

		m_connot_insert_to_task_bar = !(::SetParent(this->m_hWnd, m_hBar));	//�ѳ��򴰿����ó����������Ӵ���
		//m_connot_insert_to_task_bar = true;
		m_error_code = GetLastError();

		//�������򴰿ڵĴ�С��λ��
		if(!theApp.m_taskbar_data.tbar_wnd_on_left)
			m_rect.MoveToX(m_left_space + m_rcMin.Width() - m_rect.Width() + 2);
		else
			m_rect.MoveToX(m_left_space);
		m_rect.MoveToY((m_rcBar.Height() - m_rect.Height()) / 2);
		if (theApp.m_taskbar_data.horizontal_arrange && theApp.m_win_version.IsWindows7())		//ϵͳ��Win7����ˮƽ����ʱ������������λ�����µ���һ������
			m_rect.MoveToY(m_rect.top + theApp.DPI(1));
		//::MoveWindow(this->m_hWnd, wnd_x_pos, wnd_y_pos, m_rect.Width(), m_rect.Height(), TRUE);
		MoveWindow(m_rect);
	}
	else	//�������������������Ҳ�ʱ
	{
		//���ô��ڴ�С
		m_min_bar_height = m_rcMin.Height() - m_rect.Height();	//������С�����ڸ߶�

		//ͨ����MoveWindow�������ı�С�����ڵĸ߶�
		if (!theApp.m_taskbar_data.tbar_wnd_on_left)
			::MoveWindow(m_hMin, 0, m_top_space, m_rcMin.Width(), m_rcMin.Height() - m_rect.Height(), TRUE);
		else
			::MoveWindow(m_hMin, 0, m_top_space + m_rect.Height(), m_rcMin.Width(), m_rcMin.Height() - m_rect.Height(), TRUE);

		m_connot_insert_to_task_bar = (!::SetParent(this->m_hWnd, m_hBar));	//�ѳ��򴰿����ó����������Ӵ���
		//m_connot_insert_to_task_bar = true;
		m_error_code = GetLastError();

		//�������򴰿ڵĴ�С��λ��
		m_rect.MoveToX((m_rcMin.Width() - m_window_width) / 2);
		if (m_rect.left < theApp.DPI(2))
			m_rect.MoveToX(theApp.DPI(2));
		if (!theApp.m_taskbar_data.tbar_wnd_on_left)
			m_rect.MoveToY(m_top_space + m_rcMin.Height() - m_rect.Height() + 2);
		else
			m_rect.MoveToY(m_top_space);
		MoveWindow(m_rect);
	}
	CRect rect{ m_rect };
	//�������û�б��ɹ�Ƕ�뵽�������������ƶ����˻�����Ļ���Ͻǵľ���λ�ã����������ڵ�λ��
	if (m_connot_insert_to_task_bar)
	{
		rect.MoveToXY(rect.left + m_rcBar.left, rect.top + m_rcBar.top);
		this->MoveWindow(rect);
	}

	SetBackgroundColor(theApp.m_taskbar_data.back_color);

	//��ʼ�������ʾ
	m_tool_tips.Create(this, TTS_ALWAYSTIP);
	m_tool_tips.SetMaxTipWidth(600);
	m_tool_tips.AddTool(this, _T(""));
	SetToolTipsTopMost();		//������ʾ��Ϣ�����ö�

	//SetTimer(TASKBAR_TIMER, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTaskBarDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	//SaveConfig();
	DestroyWindow();
	//����رյ�ʱ�򣬰���С�����ڵ�width�ָ���ȥ
    CheckTaskbarOnTopOrBottom();
    if (m_taskbar_on_top_or_bottom)
		::MoveWindow(m_hMin, m_left_space, 0, m_rcMin.Width(), m_rcMin.Height(), TRUE);
	else

		::MoveWindow(m_hMin, 0, m_top_space, m_rcMin.Width(), m_rcMin.Height(), TRUE);

	//CDialogEx::OnCancel();
}


void CTaskBarDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CPoint point1;	//����һ������ȷ�����λ�õ�λ��  
	GetCursorPos(&point1);	//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����  
	theApp.m_taskbar_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, this); //��ָ��λ����ʾ�����˵�
	CDialogEx::OnRButtonUp(nFlags, point1);
}


void CTaskBarDlg::OnInitMenu(CMenu* pMenu)
{
	CDialogEx::OnInitMenu(pMenu);

	// TODO: �ڴ˴������Ϣ����������
	pMenu->CheckMenuItem(ID_SHOW_CPU_MEMORY2, MF_BYCOMMAND | (IsShowCpuMemory() ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_SHOW_NET_SPEED, MF_BYCOMMAND | ((IsShowNetSpeed() || !IsShowMemory()) ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_SHOW_MAIN_WND, MF_BYCOMMAND | (!theApp.m_cfg_data.m_hide_main_window ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_SHOW_NOTIFY_ICON, MF_BYCOMMAND | (theApp.m_cfg_data.m_show_notify_icon ? MF_CHECKED : MF_UNCHECKED));

    pMenu->CheckMenuItem(ID_SHOW_UP_SPEED, MF_BYCOMMAND | ((IsShowUp()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_DOWN_SPEED, MF_BYCOMMAND | ((IsShowDown()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_CPU_USAGE, MF_BYCOMMAND | ((IsShowCpu()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_MEMORY_USAGE, MF_BYCOMMAND | ((IsShowMemory()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_CPU_TEMPERATURE, MF_BYCOMMAND | ((IsShowCpuTemperature()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_GPU_TEMPERATURE, MF_BYCOMMAND | ((IsShowGpuTemperature()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_HDD_TEMPERATURE, MF_BYCOMMAND | ((IsShowHddTemperature()) ? MF_CHECKED : MF_UNCHECKED));
    pMenu->CheckMenuItem(ID_SHOW_MAIN_BOARD_TEMPERATURE, MF_BYCOMMAND | ((IsShowMainboardTemperature()) ? MF_CHECKED : MF_UNCHECKED));

	pMenu->EnableMenuItem(ID_SELECT_ALL_CONNECTION, MF_BYCOMMAND | (theApp.m_general_data.show_all_interface ? MF_GRAYED : MF_ENABLED));

	//pMenu->SetDefaultItem(ID_NETWORK_INFO);
	//����Ĭ�ϲ˵���
	switch (theApp.m_taskbar_data.double_click_action)
	{
	case DoubleClickAction::CONNECTION_INFO:
		pMenu->SetDefaultItem(ID_NETWORK_INFO);
		break;
	case DoubleClickAction::HISTORY_TRAFFIC:
		pMenu->SetDefaultItem(ID_TRAFFIC_HISTORY);
		break;
	case DoubleClickAction::SHOW_MORE_INFO:
		pMenu->SetDefaultItem(ID_SHOW_CPU_MEMORY2);
		break;
	case DoubleClickAction::OPTIONS:
		pMenu->SetDefaultItem(ID_OPTIONS2);
		break;
	default:
		pMenu->SetDefaultItem(-1);
		break;
	}
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_TASKBAR_MENU_POPED_UP, 0, 0);		//֪ͨ�����ڲ˵��ѵ���
}


BOOL CTaskBarDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//���ΰ��س�����ESC���˳�
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;

	if (theApp.m_taskbar_data.show_tool_tip && m_tool_tips.GetSafeHwnd() && (pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE))
	{
		m_tool_tips.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTaskBarDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnMouseMove(nFlags, point);
}


void CTaskBarDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (theApp.m_taskbar_data.double_click_action)
	{
	case DoubleClickAction::CONNECTION_INFO:
		SendMessage(WM_COMMAND,ID_NETWORK_INFO);		//˫���󵯳����������顱�Ի���
		break;
	case DoubleClickAction::HISTORY_TRAFFIC:
		SendMessage(WM_COMMAND, ID_TRAFFIC_HISTORY);		//˫���󵯳�����ʷ����ͳ�ơ��Ի���
		break;
	case DoubleClickAction::SHOW_MORE_INFO:
		PostMessage(WM_COMMAND, ID_SHOW_CPU_MEMORY2);		//�л���ʾCPU���ڴ�������
		break;
	case DoubleClickAction::OPTIONS:
		SendMessage(WM_COMMAND, ID_OPTIONS2);		//˫���󵯳���ѡ�����á��Ի���
		break;
	case DoubleClickAction::TASK_MANAGER:
        ShellExecuteW(NULL, _T("open"), (theApp.m_system_dir + L"\\Taskmgr.exe").c_str(), NULL, NULL, SW_NORMAL);		//�����������
        break;
    case DoubleClickAction::SEPCIFIC_APP:
		ShellExecuteW(NULL, _T("open"), (theApp.m_taskbar_data.double_click_exe).c_str(), NULL, NULL, SW_NORMAL);	//��ָ������Ĭ�����������
		break;
	default:
		break;
	}
	//CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CTaskBarDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if (nIDEvent == TASKBAR_TIMER)
	//{
	//	AdjustWindowPos();
	//	//ShowInfo();
	//	Invalidate(FALSE);
	//}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CTaskBarDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	UINT uMsg = LOWORD(wParam);
	if (uMsg == ID_SELECT_ALL_CONNECTION || uMsg == ID_SELETE_CONNECTION
		|| (uMsg > ID_SELECT_ALL_CONNECTION && uMsg <= ID_SELECT_ALL_CONNECTION + 98))
	{
		::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_COMMAND, wParam, lParam);	//�������ˡ�ѡ���������ӡ��Ӳ˵������Ϣת����������
		return TRUE;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}


void CTaskBarDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	ShowInfo(&dc);
}

void CTaskBarDlg::AddHisToList(CList<int,int> &list, int current_usage_percent)
{
	list.AddHead(current_usage_percent);
	//�ж��Ƿ񳬹���󳤶ȣ����������������β�������Ƴ�
	if (list.GetCount() > TASKBAR_GRAPH_MAX_LEN)
	{
		list.RemoveTail();
	}
}


void CTaskBarDlg::TryDrawGraph(CDrawCommon& drawer, const CRect &value_rect, CList<int,int> &list)
{
	if (!theApp.m_taskbar_data.show_status_bar)
	{
		return;
	}
	drawer.DrawRectOutLine(value_rect, theApp.m_taskbar_data.status_bar_color, 1, true);
	POSITION pos = list.GetHeadPosition();
	if (NULL != pos)
	{
		//�����ݲ���Ҫ����
		for (int i = 0; i < value_rect.Width(); i++)
		{
			//����������

			CPoint start_point = CPoint(value_rect.right - i, value_rect.bottom);
			int height = 0;

			for (int j = 0; j < TASKBAR_GRAPH_STEP; j++)
			{
				height = list.GetNext(pos)*value_rect.Height() / 100;
				if (NULL == pos) 
				{
					//û������ֱ�ӷ��ء�
					return;
				}

			}
			drawer.DrawLine(start_point, height, theApp.m_taskbar_data.status_bar_color);
		}
	}
}
