// Bresenham_LineView.h : CBresenham_LineView 类的接口
//


#pragma once


class CBresenham_LineView : public CView
{
protected: // 仅从序列化创建
	CBresenham_LineView();
	DECLARE_DYNCREATE(CBresenham_LineView)

// 属性
public:
	CBresenham_LineDoc* GetDocument() const;

// 操作
public:
	 void Bresenham_Line(int x0, int y0, int x1, int y1);

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
	virtual ~CBresenham_LineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Bresenham_LineView.cpp 的调试版本
inline CBresenham_LineDoc* CBresenham_LineView::GetDocument() const
   { return reinterpret_cast<CBresenham_LineDoc*>(m_pDocument); }
#endif

