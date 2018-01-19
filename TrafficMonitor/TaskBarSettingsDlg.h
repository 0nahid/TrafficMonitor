#pragma once


// CTaskBarSettingsDlg �Ի���

class CTaskBarSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskBarSettingsDlg)

public:
	CTaskBarSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskBarSettingsDlg();

	//ѡ����������
	//CString m_font_name;
	//int m_font_size;
	//COLORREF m_text_color;
	//COLORREF m_back_color;
	//wstring m_up_string;		//Ĭ��Ϊ���ϴ�: ��
	//wstring m_down_string;		//Ĭ��Ϊ������: ��
	//wstring m_cpu_string;		//Ĭ��Ϊ��CPU: ��
	//wstring m_memory_string;	//Ĭ��Ϊ���ڴ�: ��
	//bool m_swap_up_down;		//�Ƿ񽻻��ϴ������ص�λ��
	TaskBarSettingData m_data;

	void DrawStaticColor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASKBAR_SETTINGS_DIALOG };
#endif

protected:
	CStatic m_text_color_static;
	CStatic m_back_color_static;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSetFontButton1();
	afx_msg void OnBnClickedSetColorButton2();
	afx_msg void OnBnClickedSetColorButton3();
	afx_msg void OnEnChangeUploadEdit1();
	afx_msg void OnEnChangeDownloadEdit1();
	afx_msg void OnEnChangeCpuEdit1();
	afx_msg void OnEnChangeMemoryEdit1();
	afx_msg void OnBnClickedSetDefaultButton1();
	afx_msg void OnBnClickedSwitchUpDownCheck1();
};
