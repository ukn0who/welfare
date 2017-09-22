// drawmatView.h : CdrawmatView ��Ľӿ�
//


#pragma once


class CdrawmatView : public CView
{
protected: // �������л�����
	CdrawmatView();
	DECLARE_DYNCREATE(CdrawmatView)

// ����
public:
	CdrawmatDoc* GetDocument() const;

// ����
public:
void drawmat(char *mat,int matsize,int x,int y,int color) ;
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
	virtual ~CdrawmatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // drawmatView.cpp �ĵ��԰汾
inline CdrawmatDoc* CdrawmatView::GetDocument() const
   { return reinterpret_cast<CdrawmatDoc*>(m_pDocument); }
#endif

