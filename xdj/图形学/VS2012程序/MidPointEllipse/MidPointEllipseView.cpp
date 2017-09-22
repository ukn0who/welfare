// MidPointEllipseView.cpp : CMidPointEllipseView 类的实现
//

#include "stdafx.h"
#include <cmath>
#include "MidPointEllipse.h"

#include "MidPointEllipseDoc.h"
#include "MidPointEllipseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidPointEllipseView

IMPLEMENT_DYNCREATE(CMidPointEllipseView, CView)

BEGIN_MESSAGE_MAP(CMidPointEllipseView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMidPointEllipseView 构造/析构

CMidPointEllipseView::CMidPointEllipseView()
{
	// TODO: 在此处添加构造代码

}

CMidPointEllipseView::~CMidPointEllipseView()
{
}

BOOL CMidPointEllipseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CMidPointEllipseView 绘制

void CMidPointEllipseView::OnDraw(CDC* /*pDC*/)
{
	CMidPointEllipseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	MidPointEllipse(30,60,100,100);
	MidPointEllipse(60,30,100,100);

	MidPointEllipse(30,30,300,100);
	MidPointEllipse(30,30,330,130);
	MidPointEllipse(30,30,360,100);
	MidPointEllipse(30,30,330,70);
	//MidPointEllipse(30,30,330,200);
}


// CMidPointEllipseView 打印

BOOL CMidPointEllipseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMidPointEllipseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CMidPointEllipseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CMidPointEllipseView 诊断

#ifdef _DEBUG
void CMidPointEllipseView::AssertValid() const
{
	CView::AssertValid();
}

void CMidPointEllipseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMidPointEllipseDoc* CMidPointEllipseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidPointEllipseDoc)));
	return (CMidPointEllipseDoc*)m_pDocument;
}
#endif //_DEBUG


// CMidPointEllipseView 消息处理程序
void CMidPointEllipseView::MidPointEllipse(int a, int b,int x0,int y0)
{
	int x,y,d,xP,yP,sa,sb,color=0;
	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;y = b;d = 4*(sb - sa*b) + sa;
	EllipsePoints(x,y,x0,y0);
	while(x <= xP)
	{
		if(d <= 0)
			d += 4*sb*(2*x + 3);
		else
		{
			d += 4*sb*(2*x + 3) - 8*sa*(y - 1);
			y --;
		}
		x ++;
        EllipsePoints(x,y,x0,y0);
	}
	x = a;y = 0;d = 4*(sa - sb*a) + sb;
	EllipsePoints(x,y,x0,y0);
	while(y <= yP)
	{
		if(d <= 0)
			d += 4*sa*(2*y + 3);
		else
		{
			d += 4*sa*(2*y + 3) - 8*sb*(x - 1);
			x --;
		}
		y ++;
        EllipsePoints(x,y,x0,y0);
	}
}
void CMidPointEllipseView::EllipsePoints(int x, int y,int x0,int y0)
{
  int  color=0; 
	CDC* pDC = GetDC();
	pDC->SetPixel(x+x0,y+y0,color);
	pDC->SetPixel(-x+x0,y+y0,color);
	pDC->SetPixel(-x+x0,-y+y0,color);
	pDC->SetPixel(x+x0,-y+y0,color);
}
