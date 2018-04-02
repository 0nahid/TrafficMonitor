//��װ�Ļ�ͼ��
#pragma once
class CDrawCommon
{
public:

	//����ģʽ
	enum class StretchMode
	{
		STRETCH,		//���죬��ı����
		FILL,			//��䣬���ı��������ü�����
		FIT			//��Ӧ������ı���������ü�
	};

	CDrawCommon();
	~CDrawCommon();

	void Create(CDC* pDC, CWnd* pMainWnd);
	void SetFont(CFont* pfont);		//���û����ı�������
	void SetDC(CDC* pDC);		//���û�ͼ��DC
	CDC* GetDC() { return m_pDC; }

	void DrawWindowText(CRect rect, LPCTSTR lpszString, COLORREF color, bool center);	//��ָ���ľ��������ڻ����ı�

	void SetDrawRect(CRect rect);		//���û�ͼ��������

	//����һ��λͼ
	//��ע�⣺��stretch_mode����ΪStretchMode::FILL����䣩ʱ�������û�ͼ�����������֮����Ҫ��������ͼ�Σ�
	//��Ҫ�������û�ͼ�������򣬷���ͼƬ���������޷����ƣ�
	void DrawBitmap(CBitmap& bitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(UINT bitmap_id, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(HBITMAP hbitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);

	//��ͼƬ���쵽ָ���ߴ�(https://blog.csdn.net/sichuanpb/article/details/22986877)
	static void BitmapStretch(CImage *pImage, CImage *ResultImage, CSize size);

	void FillRect(CRect rect, COLORREF color);		//�ô�ɫ������

private:
	CDC* m_pDC{};		//���ڻ�ͼ��CDC���ָ��
	CWnd* m_pMainWnd{};	//��ͼ���ڵľ��
	CFont* m_pfont{};
};

