// MidPointEllipseView.h : CMidPointEllipseView 类的接口
//


#pragma once


class CMidPointEllipseView : public CView
{
protected: // 仅从序列化创建
	CMidPointEllipseView();
	DECLARE_DYNCREATE(CMidPointEllipseView)

// 属性
public:
	CMidPointEllipseDoc* GetDocument() const;

// 操作
public:
	void MidPointEllipse(int a, int b,int x0,int y0);
    void EllipsePoints(int x, int y,int x0,int y0);


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
	virtual ~CMidPointEllipseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MidPointEllipseView.cpp 的调试版本
inline CMidPointEllipseDoc* CMidPointEllipseView::GetDocument() const
   { return reinterpret_cast<CMidPointEllipseDoc*>(m_pDocument); }
#endif

