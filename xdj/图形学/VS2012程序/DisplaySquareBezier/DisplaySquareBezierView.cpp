// DisplaySquareBezierView.cpp : CDisplaySquareBezierView 类的实现
//

#include "stdafx.h"
#include "DisplaySquareBezier.h"

#include "DisplaySquareBezierDoc.h"
#include "DisplaySquareBezierView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDisplaySquareBezierView

IMPLEMENT_DYNCREATE(CDisplaySquareBezierView, CView)

BEGIN_MESSAGE_MAP(CDisplaySquareBezierView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDisplaySquareBezierView 构造/析构

CDisplaySquareBezierView::CDisplaySquareBezierView()
{
	// TODO: 在此处添加构造代码

}

CDisplaySquareBezierView::~CDisplaySquareBezierView()
{
}

BOOL CDisplaySquareBezierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CDisplaySquareBezierView 绘制

void CDisplaySquareBezierView::OnDraw(CDC* pDC)
{
	CDisplaySquareBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
DisplaySquareBezier(70/2,210/2,140/2,140/2,280/2,280/2,280/2,420/2,50);
DisplaySquareBezier(70/2,210/2,0,280/2,140/2,420/2,280/2,420/2,50);


}


// CDisplaySquareBezierView 打印

BOOL CDisplaySquareBezierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDisplaySquareBezierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CDisplaySquareBezierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CDisplaySquareBezierView 诊断

#ifdef _DEBUG
void CDisplaySquareBezierView::AssertValid() const
{
	CView::AssertValid();
}

void CDisplaySquareBezierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDisplaySquareBezierDoc* CDisplaySquareBezierView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDisplaySquareBezierDoc)));
	return (CDisplaySquareBezierDoc*)m_pDocument;
}
#endif //_DEBUG


// CDisplaySquareBezierView 消息处理程序
void CDisplaySquareBezierView::DisplaySquareBezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int m)
{//三次Bezier曲线
	float C[2][4],t,dx,Newx,Newy;
	int Vx,Vy,Nx,Ny,i,j;
	C[0][0]=x0;
	C[0][1]=-3*x0+3*x1;
	C[0][2]=3*x0-6*x1+3*x2;
	C[0][3]=-1*x0+3*x1-3*x2+x3;
     C[1][0]=y0;
	C[1][1]=-3*y0+3*y1;
	C[1][2]=3*y0-6*y1+3*y2;
	C[1][3]=-1*y0+3*y1-3*y2+y3;
	Vx=x0,Vy=y0;
	dx=1.0/m,t=0.0;
	for(i=1;i<=m;i++)
	{t+=dx;
	 Newx=C[0][0]+t*(C[0][1]+t*(C[0][2]+t*C[0][3]));
	 Newy=C[1][0]+t*(C[1][1]+t*(C[1][2]+t*C[1][3]));
	 Nx=(int)(Newx+0.5),Ny=(int)(Newy+0.5);
	 MidPointLine(Vx,Vy,Nx,Ny);
	 Vx=Nx,Vy=Ny;
	}
}
void CDisplaySquareBezierView::MidPointLine(int x0, int y0, int x1, int y1)
{
	int dx,dy,dxy,s1,s2,flag,i,d,x,y,color = 0;
	CDC* pDC = GetDC();
	x = x0;
	y = y0;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	s1 = (x1 - x0) > 0 ? 1:-1;
	s2 = (y1 - y0) > 0 ? 1:-1;
	if(dy > dx)
	{
		dxy = dx;dx = dy;dy = dxy;
		flag = 1;
	}
	else
		flag = 0;
	d = 2*dy - dx;
	for(i = 1;i <= dx;i++)
	{
		pDC->SetPixel(x,y,color);
		pDC->SetPixel(350-y,x+70,color);
		pDC->SetPixel(-x+280,420-y,color);
		pDC->SetPixel(y-70,-x+350,color);
        while(d >= 0)
            {
                if(flag == 1)
                    x += s1;
                else
                    y += s2;
                d += -2*dx;
			}
            if(flag == 1)
				y += s2;
			else
				x += s1;
			d += 2*dy;
	}
}
