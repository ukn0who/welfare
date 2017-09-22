// BezierFillView.h : CBezierFillView 类的接口
//


#pragma once


class CBezierFillView : public CView
{
protected: // 仅从序列化创建
	CBezierFillView();
	DECLARE_DYNCREATE(CBezierFillView)

// 属性
public:
	CBezierFillDoc* GetDocument() const;

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
	virtual ~CBezierFillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Scan(CPoint point, int oldColor,int newColor);
	void ScanNext(int oldColor, int newColor);
	void Fill(CPoint point, int oldColor, int newColor);
	void DisplaySquareBezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int m) ;
    void MidPointLine(int x0, int y0, int x1, int y1);
};

#ifndef _DEBUG  // BezierFillView.cpp 的调试版本
inline CBezierFillDoc* CBezierFillView::GetDocument() const
   { return reinterpret_cast<CBezierFillDoc*>(m_pDocument); }
#endif

