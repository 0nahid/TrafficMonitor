#pragma once
#include "Common.h"
#include "afxwin.h"
#include "StaticEx.h"

// CTaskBarDlg �Ի���

class CTaskBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskBarDlg)

public:
	CTaskBarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskBarDlg();

	//unsigned int m_in_speed{};		//�����ٶ�
	//unsigned int m_out_speed{};		//�ϴ��ٶ�
	//int m_cpu_usage{};		//CPU������
	//int m_memory_usage{};	//�ڴ�������
	//int m_used_memory{};	//���������ڴ棨��λΪKB��
	//int m_total_memory{};	//�����ڴ���������λΪKB��

	//__int64 m_today_traffic{};	//������ʹ�õ�����

	CToolTipCtrl m_tool_tips;
	//int m_tip_type{};	//����ָʾҪ��ʾ����ʾ�����ͣ�0������ʾ��ʾ��1����ʾ��������������2���ڴ���������

	bool m_show_cpu_memory;	//��ʾCPU���ڴ�������
	//bool m_hide_main_window;	//����������
	//bool m_position_corrected{ false };	//�������λ�ñ�����������Ϊtrue

	void ShowInfo();		//����Ϣ��ʾ���ؼ���
	bool AdjustWindowPos();	//���ô������������е�λ��
	//void ShowCpuMemory();	//�л���ʾCPU���ڴ�������ʱ�Ĵ���

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_BAR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HWND m_hTaskbar;	//���������ھ��
	HWND m_hBar;		//���������ڶ��������ľ��
	HWND m_hMin;		//��С�����ڵľ��
	CRect m_rcBar;		//���������ڵľ�������
	CRect m_rcMin;		//��С�����ڵľ�������
	CRect m_rect;		//��ǰ���ڵľ�������
	int m_window_width;		//���ڿ��
	int m_window_width_s;	//����ʾCPU���ڴ�������ʱ�Ĵ��ڿ��

	int m_min_bar_width;	//��С��������С��Ⱥ�Ŀ��
	int m_min_bar_height;	//��С��������С�߶Ⱥ�ĸ߶ȣ���������������Ļ�����Ҳ�ʱ��

	bool m_connot_insert_to_task_bar{ false };	//��������޷�Ƕ������������Ϊtrue

	CStaticEx m_disp_up;	//��ʾ�ϴ��ٶȵ�Static�ؼ�
	CStaticEx m_disp_down;	//��ʾ�����ٶȵ�Static�ؼ�
	CStaticEx m_disp_cpu;	//��ʾCPU�����ʵ�Static�ؼ�
	CStaticEx m_disp_memory;	//��ʾ�ڴ������ʵ�Static�ؼ�

	CMenu m_menu;	//�Ҽ��˵�

	COLORREF m_back_color{ RGB(0,0,0) };	//������ɫ
	COLORREF m_text_color{ RGB(255,255,255) };	//������ɫ
	CFont m_font;			//����
	CString m_font_name;	//��������
	int m_font_size;		//�����С

	bool m_swap_up_down{ false };		//�����ϴ���������ʾ��λ��

	void SaveConfig();		//�������õ�ini�ļ�
	void LoadConfig();		//��ini�ļ���������

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetBackgroundColor();
	afx_msg void OnSetTextColor();
	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSetFont();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
