// TaskbarColorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TaskbarColorDlg.h"
#include "afxdialogex.h"
#include "CMFCColorDialogEx.h"


// CTaskbarColorDlg �Ի���

IMPLEMENT_DYNAMIC(CTaskbarColorDlg, CBaseDialog)

CTaskbarColorDlg::CTaskbarColorDlg(const std::map<DisplayItem, TaskbarItemColor>& colors, CWnd* pParent /*=NULL*/)
	: CBaseDialog(IDD_TASKBAR_COLOR_DIALOG, pParent), m_colors(colors)
{
}

CTaskbarColorDlg::~CTaskbarColorDlg()
{
}

CString CTaskbarColorDlg::GetDialogName() const
{
    return _T("TaskbarColorDlg");
}

void CTaskbarColorDlg::DoDataExchange(CDataExchange* pDX)
{
    CBaseDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list_ctrl);
}


BEGIN_MESSAGE_MAP(CTaskbarColorDlg, CBaseDialog)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CTaskbarColorDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CTaskbarColorDlg ��Ϣ�������


BOOL CTaskbarColorDlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

    SetIcon(theApp.GetMenuIcon(IDI_TASKBAR_WINDOW), FALSE);		// ����Сͼ��

    //��ʼ���б�ؼ�
    CRect rect;
    m_list_ctrl.GetClientRect(rect);
    m_list_ctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
    int width0 = rect.Width() /2;
    int width1 = (rect.Width() - width0 - theApp.DPI(20) - 1) / 2;
    int width2 = rect.Width() - width0 - width1 - theApp.DPI(20) - 1;
    m_list_ctrl.InsertColumn(0, CCommon::LoadText(IDS_ITEM), LVCFMT_LEFT, width0);
    m_list_ctrl.InsertColumn(1, CCommon::LoadText(IDS_COLOR_LABEL), LVCFMT_LEFT, width1);
    m_list_ctrl.InsertColumn(1, CCommon::LoadText(IDS_COLOR_VALUE), LVCFMT_LEFT, width2);
    m_list_ctrl.SetDrawItemRangMargin(theApp.DPI(2));

    //���б��в�����
    for (auto iter = m_colors.begin(); iter != m_colors.end(); ++iter)
    {
        CString item_name;
        switch (iter->first)
        {
        case TDI_UP:
            item_name = CCommon::LoadText(IDS_UPLOAD);
            break;
        case TDI_DOWN:
            item_name = CCommon::LoadText(IDS_DOWNLOAD);
            break;
        case TDI_CPU:
            item_name = _T("CPU");
            break;
        case TDI_MEMORY:
            item_name = CCommon::LoadText(IDS_MEMORY);
            break;
        case TDI_GPU_USAGE:
            item_name = CCommon::LoadText(IDS_GPU_DISP);
            break;
#ifndef WITHOUT_TEMPERATURE
        case TDI_CPU_TEMP:
            item_name = CCommon::LoadText(IDS_CPU_TEMPERATURE);
            break;
        case TDI_GPU_TEMP:
            item_name = CCommon::LoadText(IDS_GPU_TEMPERATURE);
            break;
        case TDI_HDD_TEMP:
            item_name = CCommon::LoadText(IDS_HDD_TEMPERATURE);
            break;
        case TDI_MAIN_BOARD_TEMP:
            item_name = CCommon::LoadText(IDS_MAINBOARD_TEMPERATURE);
            break;
#endif
        default:
            break;
        }
        if (!item_name.IsEmpty())
        {
            int index = m_list_ctrl.GetItemCount();
            m_list_ctrl.InsertItem(index, item_name);
            m_list_ctrl.SetItemColor(index, 1, m_colors[iter->first].label);
            m_list_ctrl.SetItemColor(index, 2, m_colors[iter->first].value);
        }
    }

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CTaskbarColorDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int index = pNMItemActivate->iItem;
    int col = pNMItemActivate->iSubItem;
    if (col == 1 || col == 2)
    {
        COLORREF color = m_list_ctrl.GetItemColor(index, col);
        CMFCColorDialogEx colorDlg(color, 0, this);
        if (colorDlg.DoModal() == IDOK)
        {
            color = colorDlg.GetColor();
            m_list_ctrl.SetItemColor(index, col, color);
        }
    }

    *pResult = 0;
}
