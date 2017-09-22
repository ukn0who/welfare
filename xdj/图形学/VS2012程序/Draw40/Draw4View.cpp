// Draw4View.cpp : CDraw4View ���ʵ��
//

#include "stdafx.h"
#include "Draw4.h"
#include <cmath>

#include "Draw4Doc.h"
#include "Draw4View.h"
#include ".\draw4view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
	struct Span
	{int y,xLeft,xRight;
	} span;



// CDraw4View

IMPLEMENT_DYNCREATE(CDraw4View, CView)

BEGIN_MESSAGE_MAP(CDraw4View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDraw4View ����/����

CDraw4View::CDraw4View()
{
	// TODO: �ڴ˴���ӹ������

}

CDraw4View::~CDraw4View()
{
}

BOOL CDraw4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CDraw4View ����

void CDraw4View::OnDraw(CDC* pDC)
{
// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	Draw01(100, 110);//��ͷ
	Draw02(10, 10);//����
	Draw02(3, 3);
	Draw03(10, 10);//����
	Draw03(3, 3);
	Draw04(100,85);//��
	Draw05(12, 12);//����
	Draw06(100,70);//�°�
    Draw14(100,70);//����
	Draw08(10, 10);//���
	Draw09(20, 20);//���
	Draw10(10, 10);//�Ҷ�
	Draw11(20, 20);//�Ҷ�
	Draw12(30, 30);//��
	Draw13(350, 385, 260, 400);//����
	Draw13(250, 215, 260, 400);//����
	Draw13(215, 385, 400, 400);//����

	Draw13(200, 145, 185, 255);//��
	Draw13(140, 158, 240, 240);
  	Draw13(158, 158, 240, 260);

	Draw13(400, 455, 185, 255);//�ҷ�
	Draw13(443, 461, 240, 240);
  	Draw13(443, 443, 240, 258);

	DisplaySquareBezier(7,21,14,14,28,28,28,42,50);
	DisplaySquareBezier(7,21,0,28,14,42,28,42,50);    //��
    Draw13(270,270-40,70,120);//��
    Draw13(330,330+40,70,120);
    Draw13(200,400,50,50);

	Draw13(270+20, 250+20, 400, 440);//���
	Draw13(240+20, 220+20, 400, 450);
	Draw13(220+20, 250+20, 450, 462);
	DisplaySquareBezier2(250,440,280,450,270,460,50);

	Draw13(330-20, 350-20, 400, 465);//�ҽ�
	Draw13(360-20, 370-20, 400, 430);
	Draw13(350-20, 385-20, 465, 445);
	DisplaySquareBezier3(370,430,410,428,388,450,100);

    LineDDA2(350-20,265+5,438-20,285+5);//����
	DisplaySquareBezier4(100-15,100+195,150-15,120+195,180-15,120+195,180-15,100+195,50);

	 DisplaySquareBezier4(40-60,14+260,10-60,20+260,20-60,37+260,40-60,37+260,50); //����
	 DisplaySquareBezier4(40-60,37+260,80-60,34+260,110-60,30+260,110-60,17+260,50);
	 DisplaySquareBezier4(40-60,20+260,60-60,8+260,110-60,8+260,110-60,17+260,50); 

//******************�ü�******************//
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

    for(i=0;i<*outLength;i++)
	{
		if(i<*outLength-1)
		{
			Draw13(inVertexArray[i].x+200,inVertexArray[i+1].x+200,inVertexArray[i].y-10,inVertexArray[i+1].y-10);
            Draw13(200-inVertexArray[i].x+200,200-inVertexArray[i+1].x+200,inVertexArray[i].y-10,inVertexArray[i+1].y-10);
		
		}
		if(i==*outLength-1)
		{
			Draw13(inVertexArray[i].x+200,inVertexArray[0].x+200,inVertexArray[i].y-10,inVertexArray[0].y-10);
	        Draw13(200-inVertexArray[i].x+200,200-inVertexArray[0].x+200,inVertexArray[i].y-10,inVertexArray[0].y-10);
		}
	}
//***********���**************************************//
	int oldColor;
    CPoint point;
	pDC=GetDC();
	point.x=300;point.y=300;
	oldColor=pDC->GetPixel(point);

	Fill(point,oldColor,RGB(0, 220, 100));//�� 

	point.x=280;point.y=420;
	Fill(point,oldColor,RGB(0, 255, 255));//���

	point.x=320;point.y=420;
	Fill(point,oldColor,RGB(0, 255, 255));//�ҽ�

	point.x=212;point.y=112;
	Fill(point,oldColor,RGB(150, 0, 100));//���
	point.x=225;point.y=127;
	Fill(point,oldColor,RGB(100, 0, 100));

	point.x=388;point.y=112;
	Fill(point,oldColor,RGB(150, 0, 100));//�Ҷ�
	point.x=400;point.y=127;
	Fill(point,oldColor,RGB(100, 0, 100));

    point.x=250;point.y=180;//������
	Fill(point,oldColor,RGB(0, 0, 0));

    point.x=350;point.y=180;//������
	Fill(point,oldColor,RGB(0, 0, 0));

	point.x=300;point.y=100;//��ͷ
	Fill(point,oldColor,RGB(150, 0, 100));
	
	point.x=400;point.y=300;  //����
	Fill(point,oldColor,RGB(0, 100, 200));

	point.x=280;point.y=280;  //����
	Fill(point,oldColor,RGB(0, 100, 200));
	point.x=280;point.y=270;
	Fill(point,oldColor,RGB(0, 100, 200));
	point.x=280;point.y=268;
	Fill(point,oldColor,RGB(0, 100, 200));
	point.x=240;point.y=280;
	Fill(point,oldColor,RGB(0, 100, 200));

	point.x=254;point.y=270;//����
	Fill(point,oldColor,RGB(150, 0, 100));
	point.x=350;point.y=270;
	Fill(point,oldColor,RGB(150, 0, 100));

	point.x=300;point.y=80;//ͷ��
	Fill(point,oldColor,RGB(0, 0, 0));

	point.x=310;point.y=55;//����
	Fill(point,oldColor,RGB(255, 0, 0));
	point.x=310;point.y=45;
	Fill(point,oldColor,RGB(255, 0, 0));
	point.x=290;point.y=45;
	Fill(point,oldColor,RGB(255, 0, 0));
	point.x=290;point.y=55;
	Fill(point,oldColor,RGB(255, 0, 0));

	point.x=390;point.y=45;
	Fill(point,oldColor,RGB(255, 0, 255));
	point.x=390;point.y=55;
	Fill(point,oldColor,RGB(255, 0, 255));
	point.x=410;point.y=45;
	Fill(point,oldColor,RGB(255, 0, 255));
	point.x=410;point.y=55;
	Fill(point,oldColor,RGB(255, 0, 255));

//********************�ַ���ʾ*******************//
  char ming24S[]={
/* ������ '��' �� 24�������� ��ģ��72 byte */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x08,0x00,0x07,0xF8,0x1F,0xC4,0x18,0x10,
  0x44,0x18,0x10,0x44,0x18,0x10,0x44,0x18,
  0x10,0x44,0x18,0x1F,0xC7,0xF8,0x10,0x44,
  0x18,0x10,0x44,0x18,0x10,0x44,0x18,0x10,
  0x44,0x18,0x10,0x4F,0xF8,0x1F,0xCC,0x18,
  0x10,0x48,0x18,0x10,0x08,0x18,0x00,0x18,
  0x18,0x00,0x10,0x18,0x00,0x20,0x18,0x00,
  0x40,0xF0,0x01,0x80,0x30,0x00,0x00,0x00,
};
     char zhong32L[]={
/* ������ '��' �� 32�������� ��ģ��128 byte */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x03,0x00,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x00,0x03,0x80,0x00,
  0x0F,0x3B,0xF0,0xE0,0x0F,0xFF,0xFF,0xF0,
  0x0C,0x03,0x80,0x60,0x0C,0x03,0x80,0x60,
  0x0C,0x03,0x80,0x60,0x0C,0x03,0x80,0x60,
  0x07,0xFF,0xFF,0xE0,0x06,0x03,0x81,0xE0,
  0x00,0x03,0x80,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
     char nan32L[]={
/* ������ '��' �� 32�������� ��ģ��128 byte */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x03,0x00,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x1F,0xFF,0xFF,0x00,
  0x3C,0x03,0x83,0xFC,0x00,0x03,0x80,0x38,
  0x00,0x03,0x80,0x00,0x01,0xFF,0xFF,0x80,
  0x01,0x08,0x01,0x80,0x01,0x08,0x41,0x80,
  0x01,0x1F,0xF1,0x80,0x01,0x03,0x01,0x80,
  0x01,0x03,0x01,0x80,0x01,0x3F,0xF1,0x80,
  0x01,0x03,0x01,0x80,0x03,0x03,0x01,0x80,
  0x06,0x03,0x01,0x80,0x0E,0x03,0x01,0x80,
  0x18,0x01,0x01,0x80,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
     char da32L[]={
/* ������ '��' �� 32�������� ��ģ��128 byte */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x01,0x00,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x01,0x03,0x80,0x00,
  0x03,0xFF,0xFF,0xC0,0x00,0x03,0x80,0x00,
  0x00,0x03,0x80,0x00,0x00,0x02,0x40,0x00,
  0x00,0x06,0x30,0x00,0x00,0x04,0x18,0x00,
  0x00,0x0C,0x0C,0x00,0x00,0x38,0x07,0x00,
  0x00,0xF0,0x07,0xC0,0x0F,0xE0,0x03,0xF8,
  0x1F,0xC0,0x01,0xFC,0x0E,0x00,0x00,0x78,
  0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
     char xue32L[]={
/* ������ 'ѧ' �� 32�������� ��ģ��128 byte */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x03,0x06,0x00,0x00,0x83,0x06,0x00,
  0x00,0xC1,0x04,0x00,0x00,0x40,0x08,0x00,
  0x00,0x00,0x08,0x20,0x0F,0xFF,0xFF,0xF0,
  0x0C,0x00,0x00,0x30,0x0C,0x01,0x00,0x30,
  0x08,0x18,0x38,0x20,0x00,0x20,0x3C,0x00,
  0x00,0x01,0x40,0x00,0x00,0x00,0xC0,0x00,
  0x10,0x00,0xC0,0x00,0x3F,0xFF,0xFF,0xFC,
  0x30,0x00,0xE0,0x3C,0x00,0x00,0xE0,0x00,
  0x00,0x00,0xE0,0x00,0x00,0x01,0xC0,0x00,
  0x00,0x3F,0x80,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

	 drawmat(ming24S,24,274,320,100);
	 drawmat(ming24S,24,306,320,100);
	 drawmat(zhong32L,32,245-2,345,0);  //��������
	 drawmat(nan32L,32,275-2,345,0);
	 drawmat(da32L,32,305-2,345,0);
	 drawmat(xue32L,32,335-2,345,0);





}


// CDraw4View ��ӡ

BOOL CDraw4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDraw4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CDraw4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CDraw4View ���

#ifdef _DEBUG
void CDraw4View::AssertValid() const
{
	CView::AssertValid();
}

void CDraw4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDraw4Doc* CDraw4View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDraw4Doc)));
	return (CDraw4Doc*)m_pDocument;
}
#endif //_DEBUG


// CDraw4View ��Ϣ�������

void CDraw4View::Draw01(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 200;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	//pDC->SetPixel(x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    //pDC->SetPixel(x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	//pDC->SetPixel(x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    //pDC->SetPixel(x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw02(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 250,y0 = 180;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw03(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 350,y0 = 180;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw04(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 200;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

    //pDC->SetPixel(x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    //pDC->SetPixel(x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	//pDC->SetPixel(x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    //pDC->SetPixel(x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw05(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 200;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw06(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 200;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,-y + y0,color);
	//pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,-y + y0,color);
	    //pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,-y + y0,color);
	//pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,-y + y0,color);
	    //pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw07(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 200;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	//pDC->SetPixel(x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    //pDC->SetPixel(x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	//pDC->SetPixel(x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    //pDC->SetPixel(x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw08(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 212,y0 = 112;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw09(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 212,y0 = 112;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw10(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 388,y0 = 112;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}

void CDraw4View::Draw11(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 388,y0 = 112;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,-y + y0,color);
	pDC->SetPixel(x + x0,-y + y0,color);

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

	    pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,-y + y0,color);
	    pDC->SetPixel(x + x0,-y + y0,color);

	}

}


void CDraw4View::Draw12(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 200;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	if(y+y0 > 212)
	{
	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,-y + y0,color);
	//pDC->SetPixel(x + x0,-y + y0,color);
	}

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

	    if(y+y0>212)
		{
		pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	   // pDC->SetPixel(-x + x0,-y + y0,color);
	    //pDC->SetPixel(x + x0,-y + y0,color);
		}

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	if(y+y0>212)
	{
	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,-y + y0,color);
	//pDC->SetPixel(x + x0,-y + y0,color);
	}

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

	    if(y+y0>212)
		{
		pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,-y + y0,color);
	    //pDC->SetPixel(x + x0,-y + y0,color);
		}

	}

}

void CDraw4View::Draw13(int x0, int x1, int y0, int y1)
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



void CDraw4View::DisplaySquareBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int m)
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
	 LineDDA1(Vx,Vy,Nx,Ny);
	 Vx=Nx,Vy=Ny;
	}
	
}

void CDraw4View::LineDDA1(int x0, int y0, int x1, int y1)
{int x,color = 0;
 float dy,dx,y,m,t;
 CDC*pDC=GetDC();
 if(x0==x1)                             /*б�ʲ����ڵ�����*/
    {if(y0>y1)
       {t=y0;y0=y1;y1=t;}                     /*ʹ��y0<y1*/
     for(x=x0,y=y0;y<y1;y++)
	 {
		 pDC->SetPixel(x+272+100,y-5+13,color);
		 pDC->SetPixel(342-y+100,x+9+13,color);
		 pDC->SetPixel(-x+328+100,-y+79+13,color);
		 pDC->SetPixel(y+258+100,-x+65+13,color);
	 }
    }
 else                                      /*��б�ʵ�����*/
 {
      dx=x1-x0;
      dy=y1-y0;
      m=dy/dx;     
      y=y0;  	  /*����б��ֵ*/
      if(x0>x1)
    {
		t=x0;x0=x1,y=y1;x1=t;
	}                  /*ʹ��x0<x1*/
    for(x=x0;x<=x1;x++)
        {
            pDC->SetPixel(x+272+100,(int)(y-5+0.5)+13,color);
			pDC->SetPixel((int)(-y+342+0.5)+100,x+9+13,color);
			pDC->SetPixel(-x+328+100,(int)(-y+79+0.5)+13,color);
			pDC->SetPixel((int)(y+258+0.5)+100,-x+65+13,color);

            y+=m;
		}
 }
}


void CDraw4View::LineDDA2(int x0, int y0, int x1, int y1)
{int x,color = 0;
 float dy,dx,y,m,t;
 CDC*pDC=GetDC();
 if(x0==x1)                             /*б�ʲ����ڵ�����*/
    {if(y0>y1)
       {t=y0;y0=y1;y1=t;}                     /*ʹ��y0<y1*/
     for(x=x0,y=y0;y<y1;y++)
	 {
		 if(y<463)
		 {
		 pDC->SetPixel(x+20,y,color);
		 }
	 }
    }
 else                                      /*��б�ʵ�����*/
 {
      dx=x1-x0;
      dy=y1-y0;
      m=dy/dx;     
      y=y0;  	  /*����б��ֵ*/
      if(x0>x1)
    {
		t=x0;x0=x1,y=y1;x1=t;
	}                  /*ʹ��x0<x1*/
    for(x=x0;x<=x1;x++)
        {
		   if(y<463)
           {
            pDC->SetPixel(x+20,(int)(y+0.5),color);
		   }
            y+=m;
		}
 }
}

void CDraw4View::DisplaySquareBezier2(int x0, int y0, int x1, int y1, int x2, int y2, int m)
{//����Bezier����
	float C[2][3],t,dx,Newx,Newy;
	int Vx,Vy,Nx,Ny,i,j;
	
	C[0][0]=x0;
	C[0][1]=-3*x0+3*x1;
	C[0][2]=3*x0-6*x1+3*x2;
    C[1][0]=y0;
	C[1][1]=-3*y0+3*y1;
	C[1][2]=3*y0-6*y1+3*y2;

	Vx=x0,Vy=y0;
	dx=1.0/m,t=0.0;
	for(i=1;i<=m;i++)
	{t+=dx;
	 Newx=C[0][0]+t*(C[0][1]+t*(C[0][2]));
	 Newy=C[1][0]+t*(C[1][1]+t*(C[1][2]));
	 Nx=(int)(Newx+0.5),Ny=(int)(Newy+0.5);
	 LineDDA2(Vx,Vy,Nx,Ny);
	 Vx=Nx,Vy=Ny;
	}
	
}


void CDraw4View::LineDDA3(int x0, int y0, int x1, int y1)
{int x,color = 0;
 float dy,dx,y,m,t;
 CDC*pDC=GetDC();
 if(x0==x1)                             /*б�ʲ����ڵ�����*/
    {if(y0>y1)
       {t=y0;y0=y1;y1=t;}                     /*ʹ��y0<y1*/
     for(x=x0,y=y0;y<y1;y++)
	 {
		 if(y<450)
		 {
		 pDC->SetPixel(x-20,y,color);
		 }
	 }
    }
 else                                      /*��б�ʵ�����*/
 {
      dx=x1-x0;
      dy=y1-y0;
      m=dy/dx;     
      y=y0;  	  /*����б��ֵ*/
      if(x0>x1)
    {
		t=x0;x0=x1,y=y1;x1=t;
	}                  /*ʹ��x0<x1*/
    for(x=x0;x<=x1;x++)
        {
		   if(y<450)
           {
            pDC->SetPixel(x-20,(int)(y+0.5),color);
		   }
            y+=m;
		}
 }
}

void CDraw4View::DisplaySquareBezier3(int x0, int y0, int x1, int y1, int x2, int y2, int m)
{//����Bezier����
	float C[2][3],t,dx,Newx,Newy;
	int Vx,Vy,Nx,Ny,i,j;
	
	C[0][0]=x0;
	C[0][1]=-3*x0+3*x1;
	C[0][2]=3*x0-6*x1+3*x2;
    C[1][0]=y0;
	C[1][1]=-3*y0+3*y1;
	C[1][2]=3*y0-6*y1+3*y2;

	Vx=x0,Vy=y0;
	dx=1.0/m,t=0.0;
	for(i=1;i<=m;i++)
	{t+=dx;
	 Newx=C[0][0]+t*(C[0][1]+t*(C[0][2]));
	 Newy=C[1][0]+t*(C[1][1]+t*(C[1][2]));
	 Nx=(int)(Newx+0.5),Ny=(int)(Newy+0.5);
	 LineDDA3(Vx,Vy,Nx,Ny);
	 Vx=Nx,Vy=Ny;
	}
	
}



void CDraw4View::Draw14(int a, int b)
{
	int x,y,d,xP,yP,sa,sb,color = 0;
	int x0 = 300,y0 = 210;
	CDC* pDC = GetDC();

	sa = a*a;sb = b*b;
	xP = (int)(0.5 + (float)sa/sqrt((float)(sa + sb)));
	yP = (int)(0.5 + (float)sb/sqrt((float)(sa + sb)));
	x = 0;
	y = b;
	d = 4*(sb - sa*b) + sa;

	if(y+y0>269)
	{
	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,-y + y0,color);
	//pDC->SetPixel(x + x0,-y + y0,color);
	}

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

	    if(y+y0>269)
		{
		pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,-y + y0,color);
	    //pDC->SetPixel(x + x0,-y + y0,color);
		}

	}
	x = a;
	y = 0;
	d = 4*(sa - sb*a) + sb;

	if(y+y0>269)
	{
	pDC->SetPixel(x + x0,y + y0,color);
	pDC->SetPixel(-x + x0,y + y0,color);
	//pDC->SetPixel(-x + x0,-y + y0,color);
	//pDC->SetPixel(x + x0,-y + y0,color);
	}

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

	    if(y+y0>269)
		{
		pDC->SetPixel(x + x0,y + y0,color);
	    pDC->SetPixel(-x + x0,y + y0,color);
	    //pDC->SetPixel(-x + x0,-y + y0,color);
	    //pDC->SetPixel(x + x0,-y + y0,color);
		}

	}

}


void CDraw4View::DisplaySquareBezier4(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int m)
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
	 LineDDA4(Vx,Vy,Nx,Ny);
	 Vx=Nx,Vy=Ny;
	}
	
}

void CDraw4View::LineDDA4(int x0, int y0, int x1, int y1)
{int x,color = 0;
 float dy,dx,y,m,t;
 CDC*pDC=GetDC();
 if(x0==x1)                             /*б�ʲ����ڵ�����*/
    {if(y0>y1)
       {t=y0;y0=y1;y1=t;}                     /*ʹ��y0<y1*/
     for(x=x0,y=y0;y<y1;y++)
	 {
		 pDC->SetPixel(x+272,y-5,color);

	 }
    }
 else                                      /*��б�ʵ�����*/
 {
      dx=x1-x0;
      dy=y1-y0;
      m=dy/dx;     
      y=y0;  	  /*����б��ֵ*/
      if(x0>x1)
    {
		t=x0;x0=x1,y=y1;x1=t;
	}                  /*ʹ��x0<x1*/
    for(x=x0;x<=x1;x++)
        {
            pDC->SetPixel(x+272,(int)(y-5+0.5),color);
            y+=m;
		}
 }
}

void CDraw4View::drawmat(char *mat,int matsize,int x,int y,int color)
/*���Σ���ģָ�롢�����С����ʼ����(x,y)����ɫ*/
{
	CDC *pDC = GetDC();
	int i,j,k,n;
    n=(matsize-1)/8+1;
    for(j=0;j<matsize;j++)
        for(i=0;i<n;i++)
            for(k=0;k<8;k++)
                if(mat[j*n+i]&(0x80>>k))  /*����Ϊ1��λ����ʾ*/
					pDC->SetPixel(x+i*8+k,y+j,color);
}

void CDraw4View::Scan(CPoint point, int oldColor, int newColor)
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

void CDraw4View::ScanNext(int oldColor, int newColor)
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

void CDraw4View::Fill(CPoint point, int oldColor, int newColor)
{
	Scan(point,oldColor,newColor);
	ScanNext(oldColor,newColor);
}


void CDraw4View::Intersect(Vertex * s, Vertex * p, Edge clipBoundary, Vertex * I)
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

bool CDraw4View::Inside(Vertex * testVertex, Edge clipBoundary)
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

void CDraw4View::Output(Vertex * newVertex, int * outLength, VertexArray outVertexArray)
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

void CDraw4View::SutherlandHodgmanEllipseClip(int inLength, VertexArray inVertexArray,int * outLength, VertexArray outVertexArray, Edge clipBoundary)
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

