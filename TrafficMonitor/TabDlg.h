//��������Tab��ǩ�е��ӶԻ�����
#pragma once
class CTabDlg : public CDialogEx
{
public:
	CTabDlg(UINT nIDTemplate, CWnd *pParent = NULL);
	~CTabDlg();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
protected:
	CWnd* m_pParent;
};

