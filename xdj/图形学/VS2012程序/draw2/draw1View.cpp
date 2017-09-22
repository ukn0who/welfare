// draw1View.cpp : Cdraw1View ���ʵ��
//

#include "stdafx.h"
#include "draw1.h"
#include <cmath>

#include "draw1Doc.h"
#include "draw1View.h"
#include ".\draw1view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdraw1View

IMPLEMENT_DYNCREATE(Cdraw1View, CView)

BEGIN_MESSAGE_MAP(Cdraw1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Cdraw1View ����/����

Cdraw1View::Cdraw1View()
{
	// TODO: �ڴ˴���ӹ������

}

Cdraw1View::~Cdraw1View()
{
}

BOOL Cdraw1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// Cdraw1View ����

void Cdraw1View::OnDraw(CDC* pDC)
{
	Cdraw1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	//����P119�ļ���ʵ�ֳ���
    int inLength=4,i=0;
	VertexArray inVertexArray;
	VertexArray outVertexArray;
	int * outLength;
	outLength=(int *)malloc(sizeof(int));
	Edge clipBoundary;
	//����Ҫ���ü���������
    inVertexArray[0].x=72;
    inVertexArray[0].y=60;
    inVertexArray[1].x=187;
	inVertexArray[1].y=99;
	inVertexArray[2].x=148;
	inVertexArray[2].y=60;
	inVertexArray[3].x=187;
	inVertexArray[3].y=21;

	clipBoundary[0].x=100;
	clipBoundary[0].y=80;
	clipBoundary[1].x=100;
	clipBoundary[1].y=40;
    SutherlandHodgmanEllipseClip(inLength,inVertexArray, outLength, outVertexArray,clipBoundary);
    //�±߲ü�
	clipBoundary[0].x=158;
	clipBoundary[0].y=80;
	clipBoundary[1].x=100;
	clipBoundary[1].y=80;
	inLength=*outLength;
    SutherlandHodgmanEllipseClip(inLength,outVertexArray, outLength, inVertexArray,clipBoundary);
    //�ұ߲ü�
	clipBoundary[0].x=158;
	clipBoundary[0].y=40;
	clipBoundary[1].x=158;
	clipBoundary[1].y=80;
	inLength=*outLength;
    SutherlandHodgmanEllipseClip(inLength, inVertexArray, outLength,outVertexArray,clipBoundary);
    //�ϱ߲ü�
	clipBoundary[0].x=100;
	clipBoundary[0].y=40;
	clipBoundary[1].x=158;
	clipBoundary[1].y=40;
	inLength=*outLength;
    SutherlandHodgmanEllipseClip(inLength, outVertexArray, outLength,inVertexArray,clipBoundary);
	/*CString cs;
	  cs.Format("%d",*outLength);
	  pDC->TextOut(100,50,cs);*/
    for(i=0;i<*outLength;i++)
	{
		if(i<*outLength-1)
		{
			MidPointLine(inVertexArray[i].x,inVertexArray[i+1].x,inVertexArray[i].y,inVertexArray[i+1].y,1);
            MidPointLine(200-inVertexArray[i].x,200-inVertexArray[i+1].x,inVertexArray[i].y,inVertexArray[i+1].y,1);
		
		}
		if(i==*outLength-1)
		{
			MidPointLine(inVertexArray[i].x,inVertexArray[0].x,inVertexArray[i].y,inVertexArray[0].y,1);
	        MidPointLine(200-inVertexArray[i].x,200-inVertexArray[0].x,inVertexArray[i].y,inVertexArray[0].y,1);
		}
	}
}


// Cdraw1View ��ӡ

BOOL Cdraw1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Cdraw1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void Cdraw1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// Cdraw1View ���

#ifdef _DEBUG
void Cdraw1View::AssertValid() const
{
	CView::AssertValid();
}

void Cdraw1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdraw1Doc* Cdraw1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdraw1Doc)));
	return (Cdraw1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cdraw1View ��Ϣ�������

void Cdraw1View::MidPointLine(int x0, int x1, int y0, int y1, int color)
{
	int dx,dy,incrE,incrNE,d,x,y,mid,xflag,yflag,changeflag;
	xflag=1;yflag=1;changeflag=0;
	float m;
	CDC* pDC = GetDC();
	if(x0>x1)
	  {
		  mid=x0;x0=x1;x1=mid;
	      mid=y0;y0=y1;y1=mid;
	  }
	dx = x1 - x0;
	dy = y1 - y0;
	m=(float)dy/dx;
	if(dx==0)
	{
		mid=y0;
		y0=min(y0,y1);
		y1=max(mid,y1);
		x = x0;
	    y = y0;
		while(y<y1)
		{
			pDC->SetPixel(x,y,255);
			y++;
		}
	}
	else if(m<0&&m>=-1)
	{
      y0=-y0;y1=-y1;
	  yflag=-1;
	}
	else if(abs(m)>1)
	{
        yflag=1;
		changeflag=1;
		mid=x0;x0=y0;y0=mid;
        mid=x1;x1=y1;y1=mid;
		if(m<-1)
		{
			x0=-x0;x1=-x1;
	        xflag=-1;
		}
	}
    dx = x1 - x0;
	dy = y1 - y0;
	d = dx - 2*dy;
	incrE = -2*dy;
	incrNE = 2*(dx - dy);
	x = x0;
	y = y0;
	if(changeflag==1)
	pDC->SetPixel(yflag*y,xflag*x,150);
	else
	pDC->SetPixel(xflag*x,yflag*y,150);
	  while(x < x1)
	  {
		if(d > 0)
			d += incrE;
		else
		{
			d += incrNE;
			y ++;
		}
		x ++;
		if(changeflag==1)
		pDC->SetPixel(yflag*y,xflag*x,255);
		else
			pDC->SetPixel(xflag*x,yflag*y,255);
	  }

}

void Cdraw1View::EllipsePoints(int x, int y, int color)
{
	CDC* pDC = GetDC();
	if(x<=70)
	{
	pDC->SetPixel(x + 300,y + 200,color);
	pDC->SetPixel(-x + 300,y + 200,color);
	//pDC->SetPixel(-x + 300,-y + 200,color);
	//pDC->SetPixel(x + 300,-y + 200,color);
	}
}

void Cdraw1View::MidPointEllipse(int a, int b, int color)
{
	int x,y,d,xP,yP,sa,sb;
	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;
	EllipsePoints(x,y,color);
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
        EllipsePoints(x,y,color);
	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;
	EllipsePoints(x,y,color);
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
        EllipsePoints(x,y,color);
	}

}

void Cdraw1View::Intersect(Vertex * s, Vertex * p, Edge clipBoundary, Vertex * I)
//�����εı�SP��ü��ߵĽ���I
{
	if(clipBoundary[0].y==clipBoundary[1].y)     /*ˮƽ�ü���*/
	{
		I->y=clipBoundary[0].y;
		I->x=s->x+(clipBoundary[0].y-s->y)*(p->x-s->x)/(p->y-s->y);
	}
	else                                         /*��ֱ�ü���*/
	{
        I->x=clipBoundary[0].x;
		I->y=s->y+(clipBoundary[0].x-s->x)*(p->y-s->y)/(p->x-s->x);
	}
}

bool Cdraw1View::Inside(Vertex * testVertex, Edge clipBoundary)
{
	if(clipBoundary[1].x>clipBoundary[0].x)      /*�ü���Ϊ���ڵ��±�*/
	{    if(testVertex->y>=clipBoundary[0].y)
	     return true;
	}
	else if(clipBoundary[1].x<clipBoundary[0].x)  /*�ü���Ϊ���ڵ��ϱ�*/
	{
		if(testVertex->y<=clipBoundary[0].y)
			return true;
	}
    else if(clipBoundary[1].y>clipBoundary[0].y)  /*�ü���Ϊ���ڵ��ұ�*/
	{
		if(testVertex->x<=clipBoundary[0].x)
			return true;
	}
    else if(clipBoundary[1].y<clipBoundary[0].y)  /*�ü���Ϊ���ڵ����*/
	{
		if(testVertex->x>=clipBoundary[0].x)
			return true;
	}
	return false;
}/*����Inside()����*/

void Cdraw1View::Output(Vertex * newVertex, int * outLength, VertexArray outVertexArray)
/*��new Vertex���뵽�������ζ����outVertexArray*/
{
	outVertexArray[* outLength].x=newVertex->x;
	outVertexArray[* outLength].y=newVertex->y;
	/*CString cs;int i=0;
	  cs.Format("%d",outVertexArray[* outLength].x);
	  CDC *pDC;
	  pDC=GetDC();
	  pDC->TextOut(100+10*i,50,cs);*/
    (* outLength)++;
	//i++;

}/*����Output()����*/

void Cdraw1View::SutherlandHodgmanEllipseClip(int inLength, VertexArray inVertexArray,int * outLength, VertexArray outVertexArray, Edge clipBoundary)
/*inVertexArrayΪ�������ζ�������,outVertexArrayΪ�ü��������ζ�������,clipBoundaryΪ�ü���*/
{
	Vertex *s,*p,I;
	int j;
	*outLength=0;
	s=&(inVertexArray[inLength-1]);
	for(j=0;j<inLength;j++)
	{
		p=&(inVertexArray[j]);
		if(Inside(p,clipBoundary))
		{
			if(Inside(s,clipBoundary))
                Output(p,outLength,outVertexArray);/*p119���ϵ����1*/
			else
			{
			 Intersect(s,p,clipBoundary,&I);/*p119���ϵ����4*/
			 Output(&I,outLength,outVertexArray);
             Output(p,outLength,outVertexArray);
			}
		}
		else if(Inside(s,clipBoundary))
		{
           Intersect(s,p,clipBoundary,&I); /*p119���ϵ����2*/
		   Output(&I,outLength,outVertexArray);
		}/*p119���ϵ����3,û�����*/
		s=p;
	}
}/*����SutherlandHodgmanEllipseClip()����*/
