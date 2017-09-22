// DisplaySquareBezierView.h : CDisplaySquareBezierView 类的接口
//


#pragma once


class CDisplaySquareBezierView : public CView
{
protected: // 仅从序列化创建
	CDisplaySquareBezierView();
	DECLARE_DYNCREATE(CDisplaySquareBezierView)

// 属性
public:
	CDisplaySquareBezierDoc* GetDocument() const;

// 操作
public:
	 void DisplaySquareBezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int m) ;
void MidPointLine(int x0, int y0, int x1, int y1);


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
	virtual ~CDisplaySquareBezierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DisplaySquareBezierView.cpp 的调试版本
inline CDisplaySquareBezierDoc* CDisplaySquareBezierView::GetDocument() const
   { return reinterpret_cast<CDisplaySquareBezierDoc*>(m_pDocument); }
#endif

