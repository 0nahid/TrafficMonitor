//һ��������ʾͼƬ�ľ�̬�ؼ�
//�����ڶԻ����OnInitDialog()�����е���SetPicture()����
#pragma once
class CPictureStatic : public CStatic
{
public:
	CPictureStatic();
	~CPictureStatic();

	void SetPicture(UINT pic_id);

protected:
	CDC m_memDC;
	CBitmap m_bitmap;
	CRect m_rect;
	BITMAP m_bm;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

