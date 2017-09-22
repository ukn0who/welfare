// MidPointEllipseView.h : CMidPointEllipseView ��Ľӿ�
//


#pragma once


class CMidPointEllipseView : public CView
{
protected: // �������л�����
	CMidPointEllipseView();
	DECLARE_DYNCREATE(CMidPointEllipseView)

// ����
public:
	CMidPointEllipseDoc* GetDocument() const;

// ����
public:
	void MidPointEllipse(int a, int b,int x0,int y0);
    void EllipsePoints(int x, int y,int x0,int y0);


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
	virtual ~CMidPointEllipseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MidPointEllipseView.cpp �ĵ��԰汾
inline CMidPointEllipseDoc* CMidPointEllipseView::GetDocument() const
   { return reinterpret_cast<CMidPointEllipseDoc*>(m_pDocument); }
#endif

