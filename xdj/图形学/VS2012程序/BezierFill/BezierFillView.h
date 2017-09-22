// BezierFillView.h : CBezierFillView ��Ľӿ�
//


#pragma once


class CBezierFillView : public CView
{
protected: // �������л�����
	CBezierFillView();
	DECLARE_DYNCREATE(CBezierFillView)

// ����
public:
	CBezierFillDoc* GetDocument() const;

// ����
public:

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
	virtual ~CBezierFillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Scan(CPoint point, int oldColor,int newColor);
	void ScanNext(int oldColor, int newColor);
	void Fill(CPoint point, int oldColor, int newColor);
	void DisplaySquareBezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int m) ;
    void MidPointLine(int x0, int y0, int x1, int y1);
};

#ifndef _DEBUG  // BezierFillView.cpp �ĵ��԰汾
inline CBezierFillDoc* CBezierFillView::GetDocument() const
   { return reinterpret_cast<CBezierFillDoc*>(m_pDocument); }
#endif

