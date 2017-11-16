#pragma once


// CMainWndSettingsDlg �Ի���

class CMainWndSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainWndSettingsDlg)

public:
	CMainWndSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainWndSettingsDlg();

	//ѡ����������
	CString m_font_name;
	int m_font_size;
	COLORREF m_text_color;
	wstring m_up_string;		//Ĭ��Ϊ���ϴ�: ��
	wstring m_down_string;		//Ĭ��Ϊ������: ��
	wstring m_cpu_string;		//Ĭ��Ϊ��CPU: ��
	wstring m_memory_string;	//Ĭ��Ϊ���ڴ�: ��
	bool m_swap_up_down;		//�Ƿ񽻻��ϴ������ص�λ��
	bool m_hide_main_wnd_when_fullscreen;		//�г���ȫ������ʱ����������

	void DrawStaticColor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_WND_SETTINGS_DIALOG };
#endif

protected:
	CStatic m_color_static;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeUploadEdit();
	afx_msg void OnEnChangeDownloadEdit();
	afx_msg void OnEnChangeCpuEdit();
	afx_msg void OnEnChangeMemoryEdit();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnStnClickedTextColorStatic();
	afx_msg void OnBnClickedSetColorButton1();
	afx_msg void OnBnClickedSetDefaultButton();
	afx_msg void OnBnClickedSetFontButton();
	afx_msg void OnBnClickedSwitchUpDownCheck();
	afx_msg void OnBnClickedFullscreenHideCheck();
};
