// MidPointEllipseView.cpp : CMidPointEllipseView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMidPointEllipseView ����/����

CMidPointEllipseView::CMidPointEllipseView()
{
	// TODO: �ڴ˴���ӹ������

}

CMidPointEllipseView::~CMidPointEllipseView()
{
}

BOOL CMidPointEllipseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CMidPointEllipseView ����

void CMidPointEllipseView::OnDraw(CDC* /*pDC*/)
{
	CMidPointEllipseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	MidPointEllipse(30,60,100,100);
	MidPointEllipse(60,30,100,100);

	MidPointEllipse(30,30,300,100);
	MidPointEllipse(30,30,330,130);
	MidPointEllipse(30,30,360,100);
	MidPointEllipse(30,30,330,70);
	//MidPointEllipse(30,30,330,200);
}


// CMidPointEllipseView ��ӡ

BOOL CMidPointEllipseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMidPointEllipseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CMidPointEllipseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CMidPointEllipseView ���

#ifdef _DEBUG
void CMidPointEllipseView::AssertValid() const
{
	CView::AssertValid();
}

void CMidPointEllipseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMidPointEllipseDoc* CMidPointEllipseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidPointEllipseDoc)));
	return (CMidPointEllipseDoc*)m_pDocument;
}
#endif //_DEBUG


// CMidPointEllipseView ��Ϣ�������
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
