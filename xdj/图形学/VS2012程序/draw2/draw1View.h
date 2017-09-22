// draw1View.h : Cdraw1View ��Ľӿ�
//


#pragma once


class Cdraw1View : public CView
{
protected: // �������л�����
	Cdraw1View();
	DECLARE_DYNCREATE(Cdraw1View)

// ����
public:
	Cdraw1Doc* GetDocument() const;
	typedef struct{
	           int x,y;
               }Vertex;
typedef Vertex Edge[2];
typedef Vertex VertexArray[50];

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
	virtual ~Cdraw1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void MidPointLine(int x0, int x1, int y0, int y1, int color);
	void EllipsePoints(int x, int y, int color);
	void MidPointEllipse(int a, int b, int color);
	void Intersect(Vertex * s, Vertex * p, Edge clipBoundary, Vertex * I);
	bool Inside(Vertex * testVertex, Edge clipBoundary);
	void Output(Vertex * newVertex, int * outLength, VertexArray outVertexArray);
	void SutherlandHodgmanEllipseClip(int inLength, VertexArray inVertexArray, int * outLength, VertexArray outVertexArray, Edge clipBoundary);
	//VertexArray outVertexArray;
};

#ifndef _DEBUG  // draw1View.cpp �ĵ��԰汾
inline Cdraw1Doc* Cdraw1View::GetDocument() const
   { return reinterpret_cast<Cdraw1Doc*>(m_pDocument); }
#endif

