/*
CStatic��������࣬��ʵ�����¼��ֹ���
1����������ɫ���ı��ؼ���
����SetTextColor�����ı���ɫ��
����Ҫ��ʱ�����SetWindowTextEx���ÿؼ��ı�

2�����������ӣ�
����ʱ�����캯��������Ϊtrue��
����SetURL�������ó����ӣ�
����SetLinkEnable�������õ���ؼ����Ǵ򿪳����ӻ�����Ӧ����
�������SetLinkEnable(false)�������ؼ�����򸸴��ڷ���һ��WM_LINK_CLICKED��Ϣ��
��ͨ��WPARAM���ݿؼ���ָ��

���Ϲ��ܲ���ͬʱʹ��
*/
#pragma once
#include "afxwin.h"
#include "CommonData.h"
#define WM_LINK_CLICKED (WM_USER + 1002)
class CStaticEx :
	public CStatic
{
public:
	CStaticEx();
	CStaticEx(bool is_hyperlink);		//���캯���������ļ��ؼ��ı��Ƿ�Ϊ������
	~CStaticEx();

	//��Static�ؼ�������������ɫ���ı�ʱ
public:
	void SetWindowTextEx(LPCTSTR lpszString, Alignment align = Alignment::LEFT);	//Ϊ�ؼ���������ɫ���ı�����Ҫ���SetTextColorʹ�ã�
	void SetTextColor(COLORREF textColor);		//���ÿؼ��ı���ɫ
	void SetBackColor(COLORREF back_color);		//���ÿؼ�������ɫ
	CString GetString() const;			//��ȡ�ؼ��ı�

protected:
	bool m_color_text{ false };
	COLORREF m_text_color;	//�ؼ�������ɫ
	COLORREF m_back_color;
	CString m_text;			//�ؼ��ϵ��ı�
	Alignment m_align{};		//�ı��Ķ��뷽ʽ
	bool m_draw_background_color{ false };	//�Ƿ���ҪΪ�ؼ���䱳����ɫ

	//��Static�ؼ�����������ʱ
public:
	void SetURL(CString strURL);		//���ó�����
	CString GetURL() const;			//��ȡ�������ַ���
	void SetLinkEnable(bool enable) { m_linkEnable = enable; }
protected:
	bool m_isHyperLink{ false };	//���Ҫ���ؼ���Ϊ�����ӣ���Ϊtrue
	bool m_linkEnable{ true };		//���Ϊtrue�������򿪳����ӣ������򸸴��ڷ���һ�������Ϣ
	bool m_bHot{ false };			//�����ָ������ʱ����Ϊtrue
	CString m_strURL;				//�������ַ���

protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void PreSubclassWindow();
};

