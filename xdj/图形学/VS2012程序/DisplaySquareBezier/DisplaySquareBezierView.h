// DisplaySquareBezierView.h : CDisplaySquareBezierView ��Ľӿ�
//


#pragma once


class CDisplaySquareBezierView : public CView
{
protected: // �������л�����
	CDisplaySquareBezierView();
	DECLARE_DYNCREATE(CDisplaySquareBezierView)

// ����
public:
	CDisplaySquareBezierDoc* GetDocument() const;

// ����
public:
	 void DisplaySquareBezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int m) ;
void MidPointLine(int x0, int y0, int x1, int y1);


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
	virtual ~CDisplaySquareBezierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DisplaySquareBezierView.cpp �ĵ��԰汾
inline CDisplaySquareBezierDoc* CDisplaySquareBezierView::GetDocument() const
   { return reinterpret_cast<CDisplaySquareBezierDoc*>(m_pDocument); }
#endif

