#pragma once
#include "afxwin.h"
#include"StaticEx.h"

// CSkinDlg �Ի���

class CSkinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSkinDlg)

public:
	CSkinDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSkinDlg();

	vector<wstring> m_skins;		//Ƥ���ļ���·��
	int m_skin_selected;			//ѡ���Ƥ��
	int m_skin_width;		//Ԥ��ͼ���
	int m_skin_height_s;	//Ԥ��ͼ�߶ȣ�С��
	int m_skin_height_l;	//Ԥ��ͼ�߶ȣ���

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SKIN_DIALOG };
#endif

	COLORREF GetTextColor() const
	{
		return m_text_color;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	COLORREF m_text_color;			//��ǰƤ�����ı���ɫ
	CComboBox m_select_box;			//ѡ���
	CStatic m_skin_preview_s;		//��ʾ��Ԥ��ͼ�Ŀؼ�
	CStatic m_skin_preview_l;		//��ʾСԤ��ͼ�Ŀؼ�
	HBITMAP m_image;				//ͼƬ���
	//wstring m_skin_author;			//Ƥ������

	void ShowPreview();		//��ʾƤ��Ԥ��
	void SetPreviewText(CStatic& static_preview);	//����Ԥ������

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
