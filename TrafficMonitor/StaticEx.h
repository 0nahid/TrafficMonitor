//CStatic��������࣬����ʵ������Static�ؼ�������ɫ��
//�Լ���������˴��ڱ���ͼƬʱ�ؼ������ص������⡣
#pragma once
#include "afxwin.h"
#define WM_LINK_CLICKED (WM_USER + 1002)
class CStaticEx :
	public CStatic
{
public:
	CStaticEx();
	CStaticEx(bool is_hyperlink);		//���캯���������ļ��ؼ��ı��Ƿ�Ϊ������
	~CStaticEx();

	void SetWindowTextEx(LPCTSTR lpszString);	//Ϊ�ؼ���������ɫ���ı�����Ҫ���SetTextColorʹ�ã�
	void SetTextColor(COLORREF textColor);		//���ÿؼ��ı���ɫ
	CString GetString() const;			//��ȡ�ؼ��ı�
	void SetURL(CString strURL);		//���ó�����
	CString GetURL() const;			//��ȡ�������ַ���

	void SetLinkEnable(bool enable) { m_linkEnable = enable; }

	void SetFillColor(COLORREF fill_color);		//����Ҫ���ı���ɫ

protected:
	COLORREF m_TextColor;	//�ؼ�������ɫ
	CString m_text;			//�ؼ��ϵ��ı�

	bool m_isHyperLink{ false };	//���Ҫ���ؼ���Ϊ�����ӣ���Ϊtrue
	bool m_linkEnable{ true };		//���Ϊtrue�������򿪳����ӣ������򸸴��ڷ���һ�������Ϣ
	bool m_bHot{ false };			//�����ָ������ʱ����Ϊtrue
	CString m_strURL;				//�������ַ���

	bool m_fill_color_enable{ false };		//�Ƿ�Ϊ�ؼ������ɫ
	COLORREF m_fill_color{};

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

