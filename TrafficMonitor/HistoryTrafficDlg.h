#pragma once
#include "afxcmn.h"
#include "Common.h"

// CHistoryTrafficDlg �Ի���

class CHistoryTrafficDlg : public CDialog
{
	DECLARE_DYNAMIC(CHistoryTrafficDlg)

public:
	CHistoryTrafficDlg(deque<HistoryTraffic>& history_traffics, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHistoryTrafficDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY_TRAFFIC_DIALOG };
#endif

protected:
	CListCtrl m_history_list;
	deque<HistoryTraffic>& m_history_traffics;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
