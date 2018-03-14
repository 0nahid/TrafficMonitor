#include "stdafx.h"
#include "PictureStatic.h"


CPictureStatic::CPictureStatic()
{
}


CPictureStatic::~CPictureStatic()
{
	m_memDC.DeleteDC();
}

void CPictureStatic::SetPicture(UINT pic_id)
{
	m_bitmap.LoadBitmap(pic_id);		//����λͼ
	CDC* pDC = GetDC();
	//��ȡͼ��ʵ�ʴ�С
	GetObject(m_bitmap, sizeof(BITMAP), &m_bm);
	m_memDC.CreateCompatibleDC(pDC);
	m_memDC.SelectObject(&m_bitmap);
	//��ȡ�ؼ���С
	GetClientRect(m_rect);

}

BEGIN_MESSAGE_MAP(CPictureStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CPictureStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
	if (m_bitmap.m_hObject != NULL)
	{
		// �������б���ͼƬʧ��
		dc.SetStretchBltMode(HALFTONE);
		dc.SetBrushOrg(0, 0);
		//���ƽ��ڴ�DC�е�ͼ��
		dc.StretchBlt(0, 0, m_rect.Width(), m_rect.Height(), &m_memDC, 0, 0, m_bm.bmWidth, m_bm.bmHeight, SRCCOPY);
	}
}
