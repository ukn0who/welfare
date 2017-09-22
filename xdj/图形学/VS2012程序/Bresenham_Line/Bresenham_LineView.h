// Bresenham_LineView.h : CBresenham_LineView ��Ľӿ�
//


#pragma once


class CBresenham_LineView : public CView
{
protected: // �������л�����
	CBresenham_LineView();
	DECLARE_DYNCREATE(CBresenham_LineView)

// ����
public:
	CBresenham_LineDoc* GetDocument() const;

// ����
public:
	 void Bresenham_Line(int x0, int y0, int x1, int y1);

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CBresenham_LineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Bresenham_LineView.cpp �ĵ��԰汾
inline CBresenham_LineDoc* CBresenham_LineView::GetDocument() const
   { return reinterpret_cast<CBresenham_LineDoc*>(m_pDocument); }
#endif

