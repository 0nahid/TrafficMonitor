#pragma once
#include "MainWndSettingsDlg.h"
#include "TaskBarSettingsDlg.h"
#include "afxcmn.h"

// COptionsDlg �Ի���

#define TIMER_ID1 1120
#define TIMER_ID2 1121

class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(int tab = 0, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptionsDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONS_DIALOG };
#endif

	CMainWndSettingsDlg m_tab1_dlg;
	CTaskBarSettingsDlg m_tab2_dlg;

protected:
	CTabCtrl m_tab;
	int m_tab_selected;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
