#pragma once
#include "afxwin.h"


// CDonateDlg �Ի���

class CDonateDlg : public CDialog
{
	DECLARE_DYNAMIC(CDonateDlg)

public:
	CDonateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDonateDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DONATE_DIALOG };
#endif

protected:
	CStatic m_donate_pic;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
