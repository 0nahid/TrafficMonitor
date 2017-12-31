#pragma once
#include "Common.h"
#include "afxwin.h"
//#include "StaticEx.h"

// CTaskBarDlg �Ի���

class CTaskBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskBarDlg)

public:
	CTaskBarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskBarDlg();

	CToolTipCtrl m_tool_tips;


	//��������ʾ��4����Ŀ��ǰ���ַ���
	//wstring m_up_string;		//Ĭ��Ϊ����:��
	//wstring m_down_string;		//Ĭ��Ϊ����:��
	//wstring m_cpu_string;		//Ĭ��Ϊ��CPU:��
	//wstring m_memory_string;		//Ĭ��Ϊ���ڴ�:��

	void ShowInfo();		//����Ϣ��ʾ���ؼ���
	bool AdjustWindowPos();	//���ô������������е�λ��

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
	int m_window_height;

	int m_min_bar_width;	//��С��������С��Ⱥ�Ŀ��
	int m_min_bar_height;	//��С��������С�߶Ⱥ�ĸ߶ȣ���������������Ļ�����Ҳ�ʱ��

	bool m_connot_insert_to_task_bar{ false };	//��������޷�Ƕ������������Ϊtrue
	bool m_taskbar_on_top_or_bottom{ true };		//�������������Ļ������ײ�����Ϊture

	CMenu m_menu;	//�Ҽ��˵�

	//COLORREF m_back_color{ RGB(0,0,0) };	//������ɫ
	//COLORREF m_text_color{ RGB(255,255,255) };	//������ɫ
	CFont m_font;			//����
	//CString m_font_name;	//��������
	//int m_font_size;		//�����С

	//bool m_swap_up_down{ false };		//�����ϴ���������ʾ��λ��

	CDC* m_pDC{};

	bool IsTaskbarOnTopOrBottom();		//�ж��������Ƿ�����Ļ�Ķ�����ײ���������򷵻�false���������������Ļ���࣬�򷵻�false

public:
	static void SaveConfig();		//�������õ�ini�ļ�
	static void LoadConfig();		//��ini�ļ���������

	void ApplySettings();
	void CalculateWindowWidth();		//���㴰����Ҫ�Ŀ��

	void SetToolTipsTopMost();			//���������ʾ�ö�
	void UpdateToolTips();

	bool GetCannotInsertToTaskBar() const { return m_connot_insert_to_task_bar; }

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnSetBackgroundColor();
	//afx_msg void OnSetTextColor();
	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnSetFont();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
