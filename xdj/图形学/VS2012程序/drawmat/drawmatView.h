// drawmatView.h : CdrawmatView 类的接口
//


#pragma once


class CdrawmatView : public CView
{
protected: // 仅从序列化创建
	CdrawmatView();
	DECLARE_DYNCREATE(CdrawmatView)

// 属性
public:
	CdrawmatDoc* GetDocument() const;

// 操作
public:
void drawmat(char *mat,int matsize,int x,int y,int color) ;
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
	virtual ~CdrawmatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // drawmatView.cpp 的调试版本
inline CdrawmatDoc* CdrawmatView::GetDocument() const
   { return reinterpret_cast<CdrawmatDoc*>(m_pDocument); }
#endif

