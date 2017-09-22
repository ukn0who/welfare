// BezierFillView.cpp : CBezierFillView ���ʵ��
//

#include "stdafx.h"
#include "BezierFill.h"

#include "BezierFillDoc.h"
#include "BezierFillView.h"
#include ".\bezierfillview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
	struct Span
	{int y,xLeft,xRight;
	} span;

// CBezierFillView

IMPLEMENT_DYNCREATE(CBezierFillView, CView)

BEGIN_MESSAGE_MAP(CBezierFillView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CBezierFillView ����/����

CBezierFillView::CBezierFillView()
{
	// TODO: �ڴ˴���ӹ������

}

CBezierFillView::~CBezierFillView()
{
}

BOOL CBezierFillView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CBezierFillView ����

void CBezierFillView::OnDraw(CDC* pDC)
{
	CBezierFillDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	int oldColor;
    CPoint point;
	pDC=GetDC();
    DisplaySquareBezier(120,110,190,40,330,180,330,320,50);
    DisplaySquareBezier(120,110,50,180,190,320,330,320,50);
	point.x=150;point.y=200;
	oldColor=pDC->GetPixel(point);
	Fill(point,oldColor,RGB(175, 0,50));

}


// CBezierFillView ��ӡ

BOOL CBezierFillView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBezierFillView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CBezierFillView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CBezierFillView ���

#ifdef _DEBUG
void CBezierFillView::AssertValid() const
{
	CView::AssertValid();
}

void CBezierFillView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBezierFillDoc* CBezierFillView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBezierFillDoc)));
	return (CBezierFillDoc*)m_pDocument;
}
#endif //_DEBUG


// CBezierFillView ��Ϣ�������

void CBezierFillView::Scan(CPoint point, int oldColor,int newColor)
{
	int i;
    i=point.x;
	CDC* pDC=GetDC();
	while(pDC->GetPixel(point)==oldColor)
	{pDC->SetPixel(point,newColor);
	 point.x++;
	}
	span.xRight=point.x-1;
	point.x=i-1;
	while(pDC->GetPixel(point)==oldColor)
	{pDC->SetPixel(point,newColor);
	 point.x--;
	}
	span.xLeft=point.x+1;
	span.y=point.y;

}

void CBezierFillView::ScanNext(int oldColor, int newColor)
{
	int i,xLeft,xRight,y;
	bool isScan=FALSE;
	CPoint point;
	xLeft=span.xLeft;xRight=span.xRight;
	y=span.y;
	CDC* pDC=GetDC();
    for(i=xLeft;i<=xRight;i++)
	{if(pDC->GetPixel(i,y+1)==oldColor)
	 {isScan=TRUE;
	  point.x=i;point.y=y+1;
	  Scan(point, oldColor, newColor);
	 }
	 if(isScan)
         ScanNext(oldColor,newColor);
	 isScan=FALSE;
	 if(pDC->GetPixel(i,y-1)==oldColor)
	 {isScan=TRUE;
	  point.x=i;point.y=y-1;
	  Scan(point, oldColor, newColor);
	 }
     if(isScan)
		 ScanNext(oldColor,newColor);
	}

}

void CBezierFillView::Fill(CPoint point, int oldColor, int newColor)
{
	Scan(point,oldColor,newColor);
	ScanNext(oldColor,newColor);

}
void CBezierFillView::DisplaySquareBezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int m)
{//����Bezier����
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
void CBezierFillView::MidPointLine(int x0, int y0, int x1, int y1)
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
