// Draw4View.h : CDraw4View 类的接口
//


#pragma once


class CDraw4View : public CView
{
protected: // 仅从序列化创建
	CDraw4View();
	DECLARE_DYNCREATE(CDraw4View)

// 属性
public:
	CDraw4Doc* GetDocument() const;
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
	virtual ~CDraw4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Draw01(int a, int b);
	void Draw02(int a, int b);
	void Draw03(int a, int b);
	void Draw04(int a, int b);
	void Draw05(int a, int b);
	void Draw06(int a, int b);
	void Draw07(int a, int b);
	void Draw08(int a, int b);
	void Draw09(int a, int b);
	void Draw10(int a, int b);
	void Draw11(int a, int b);
	void Draw12(int a, int b);
	void Draw14(int a, int b);
	void Draw13(int x0, int x1, int y0, int y1);
	void DisplaySquareBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int m);
	void DisplaySquareBezier2(int x0, int y0, int x1, int y1, int x2, int y2,int m);
	void DisplaySquareBezier3(int x0, int y0, int x1, int y1, int x2, int y2,int m);
	void DisplaySquareBezier4(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int m);
	void LineDDA1(int x0, int y0, int x1, int y1);
	void LineDDA2(int x0, int y0, int x1, int y1);
	void LineDDA3(int x0, int y0, int x1, int y1);
	void LineDDA4(int x0, int y0, int x1, int y1);
	void drawmat(char *mat,int matsize,int x,int y,int color);
	void Scan(CPoint point, int oldColor, int newColor);
	void ScanNext(int oldColor, int newColor);
	void Fill(CPoint point, int oldColor, int newColor);
    void SutherlandHodgmanEllipseClip(int inLength, VertexArray inVertexArray,int * outLength, VertexArray outVertexArray, Edge clipBoundary);
	void Output(Vertex * newVertex, int * outLength, VertexArray outVertexArray);
	bool Inside(Vertex * testVertex, Edge clipBoundary);
	void Intersect(Vertex * s, Vertex * p, Edge clipBoundary, Vertex * I);


};

#ifndef _DEBUG  // Draw4View.cpp 的调试版本
inline CDraw4Doc* CDraw4View::GetDocument() const
   { return reinterpret_cast<CDraw4Doc*>(m_pDocument); }
#endif

