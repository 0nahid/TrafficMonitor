#pragma once
#include"Common.h"
#include "afxcmn.h"
#include "AdapterCommon.h"

// CNetworkInfoDlg �Ի���

class CNetworkInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetworkInfoDlg)

public:
	CNetworkInfoDlg(vector<NetWorkConection>& adapters, MIB_IFROW* pIfRow, int connection_selected, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetworkInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETWORK_INFO_DIALOG };
#endif

	//unsigned int m_in_bytes;		//��ǰ�鿴�����������������ѽ����ֽ���
	//unsigned int m_out_bytes;		//��ǰ�鿴�����������������ѷ����ֽ���

	SYSTEMTIME m_start_time;		//����������ʱ��

protected:

	//MIB_IFROW m_network_info;		//��ǰ�鿴������������Ϣ
	//wstring m_ip_address{ L"-.-.-.-" };		//IP��ַ
	//wstring m_subnet_mask{ L"-.-.-.-" };	//��������
	//wstring m_default_gateway{ L"-.-.-.-" };	//Ĭ������
	
	vector<NetWorkConection>& m_connections;
	MIB_IFROW* m_pIfRow;
	int m_connection_selected;

	CListCtrl m_info_list;
	CMenu m_menu;
	CString m_selected_string;
	CSize m_min_size;

	CWinThread* m_pGetIPThread;			//��ȡ����IP���߳�

	//void GetIPAddress();	//��ȡIP��ַ
	void ShowInfo();

	//��ȡ����IP���̺߳���
	static UINT GetInternetIPThreadFunc(LPVOID lpParam);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCopyText();
	afx_msg void OnNMRClickInfoList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnBnClickedPreviousButton();
	afx_msg void OnBnClickedNextButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
