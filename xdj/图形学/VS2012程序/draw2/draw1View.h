// draw1View.h : Cdraw1View 类的接口
//


#pragma once


class Cdraw1View : public CView
{
protected: // 仅从序列化创建
	Cdraw1View();
	DECLARE_DYNCREATE(Cdraw1View)

// 属性
public:
	Cdraw1Doc* GetDocument() const;
	typedef struct{
	           int x,y;
               }Vertex;
typedef Vertex Edge[2];
typedef Vertex VertexArray[50];

// 操作
public:

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cdraw1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // draw1View.cpp 的调试版本
inline Cdraw1Doc* Cdraw1View::GetDocument() const
   { return reinterpret_cast<Cdraw1Doc*>(m_pDocument); }
#endif

