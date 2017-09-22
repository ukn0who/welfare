// Bresenham_LineView.cpp : CBresenham_LineView ���ʵ��
//

#include "stdafx.h"
#include "Bresenham_Line.h"

#include "Bresenham_LineDoc.h"
#include "Bresenham_LineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBresenham_LineView

IMPLEMENT_DYNCREATE(CBresenham_LineView, CView)

BEGIN_MESSAGE_MAP(CBresenham_LineView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CBresenham_LineView ����/����

CBresenham_LineView::CBresenham_LineView()
{
	// TODO: �ڴ˴���ӹ������

}

CBresenham_LineView::~CBresenham_LineView()
{
}

BOOL CBresenham_LineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CBresenham_LineView ����

void CBresenham_LineView::OnDraw(CDC* /*pDC*/)
{
	CBresenham_LineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	Bresenham_Line(110,110,110,160);
	Bresenham_Line(110,160,210,160);
	Bresenham_Line(210,160,210,210);
	Bresenham_Line(110,210,160,210);
    Bresenham_Line(160,210,160,110);
	Bresenham_Line(160,110,210,110);

	Bresenham_Line(310,110,410,210);
	Bresenham_Line(310,160,410,160);
	Bresenham_Line(310,210,410,110);
	Bresenham_Line(360,110,360,210);

}


// CBresenham_LineView ��ӡ

BOOL CBresenham_LineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBresenham_LineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CBresenham_LineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CBresenham_LineView ���

#ifdef _DEBUG
void CBresenham_LineView::AssertValid() const
{
	CView::AssertValid();
}

void CBresenham_LineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBresenham_LineDoc* CBresenham_LineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBresenham_LineDoc)));
	return (CBresenham_LineDoc*)m_pDocument;
}
#endif //_DEBUG


// CBresenham_LineView ��Ϣ�������
void CBresenham_LineView::Bresenham_Line(int x0, int y0, int x1, int y1)
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
