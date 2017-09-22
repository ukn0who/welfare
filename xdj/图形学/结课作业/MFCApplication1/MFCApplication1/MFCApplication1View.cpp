
// MFCApplication1View.cpp : CMFCApplication1View ���ʵ��
//

#include "stdafx.h"
#include <math.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/GLAUX.H>
#include <windows.h>

// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static GLsizei iMode=1;  //ѡ���Ĳ˵���	
static GLfloat xRot=0.0f; //x������ת����
static GLfloat yRot=0.0f; //y������ת����
GLUquadricObj *obj;			//�����������


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

	BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
		// ��׼��ӡ����
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_LBUTTONDOWN()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONUP()
		ON_COMMAND(ID_Scanfill, &CMFCApplication1View::OnScanfill)
		ON_COMMAND(ID_Seedfill, &CMFCApplication1View::OnSeedfill)
		ON_WM_LBUTTONDBLCLK()
		ON_WM_RBUTTONDOWN()
		ON_COMMAND(ID_DrawLeaf, &CMFCApplication1View::OnDrawleaf)
		ON_COMMAND(ID_DrawRose, &CMFCApplication1View::OnDrawrose)
		//		ON_WM_NCMBUTTONUP()
		//		ON_WM_SIZE()
		//		ON_WM_CREATE()
		//		ON_WM_DESTROY()
		//		ON_COMMAND(ID_DrawGL, &CMFCApplication1View::OnDrawgl)
		ON_COMMAND(ID_DrawGL, &CMFCApplication1View::OnDrawgl)
		//		ON_COMMAND(ID_Realball, &CMFCApplication1View::OnRealball)
//		ON_COMMAND(ID_Realball, &CMFCApplication1View::OnRealball)
//		ON_COMMAND(ID_DrawLD, &CMFCApplication1View::OnDrawld)
		ON_COMMAND(Material, &CMFCApplication1View::OnMaterial)
//		ON_COMMAND(ID_Material, &CMFCApplication1View::OnMaterial)
	END_MESSAGE_MAP()

	// CMFCApplication1View ����/����

	CMFCApplication1View::CMFCApplication1View()
	{
		// TODO: �ڴ˴���ӹ������
		m_bDragging = false;															//��ʼ�޷���ק
		m_hCross=AfxGetApp()->LoadStandardCursor(IDC_SIZE);								//������
																						//ֱ�ߡ�����βü�
		WL=100;WR=400;WB=100;WT=300;
	}

	CMFCApplication1View::~CMFCApplication1View()
	{
	}

	BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CMFCApplication1View ����

	void CMFCApplication1View::OnDraw(CDC* pDC)
	{
		CMFCApplication1Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
		//pDC->SetPixel (250,250,RGB(0,0,0));								//��һ�����ص�
		//pDC->LineTo(300,200);												//��ֱ����
		//pDC->Ellipse (100,100,150,150);									//��Բ

		int   nIndex=pDoc->GetNumLines();									// ȡ���߶ε�����
		// ѭ������ÿһ���߶�
		while(nIndex--)  													// �����±��0��nIndex-1
		{
			pDoc->GetLine(nIndex)->DrawLine(pDC);  
			// ��CLine�ĳ�Ա����
		}

		/*********************************************************/
		//MidpointEllise(pDC, 430, 220, 100, 40, RGB(255,0,0));
		//MidpointEllise(pDC, 430, 220, 40, 100, RGB(255,0,0));
		//PositiveNegativeParabola(pDC,-0.7,-20,3,RGB(255,0,0));
		//PositiveNegativeParabola(pDC,-0.1,-20,3,RGB(255,0,0));

		/******************************************************************/
		////��������ֱ�ߵ�����
		//int x11,y11,x21,y21,x12,y12,x22,y22,x13,y13,x23,y23;
		//x11=50;y11=150;x21=450;y21=250;
		//x12=150;y12=150;x22=350;y22=240;
		//x13=50;y13=400;x23=500;y23=350;
		////���廭��
		//CPen PenRed(PS_SOLID,1,RGB(255,0,0));								//�����ɫ��
		//CPen PenBlue(PS_SOLID,1,RGB(0,0,255));							//������ɫ��
		//CPen Penwhite(PS_SOLID,1,RGB(255,255,255));						//�����ɫ��
		////�Ȼ������ڣ�����ɫ
		//pDC->SelectObject(&PenBlue);
		//pDC->Rectangle(WL,WB,WR,WT);
		////�Ȼ�������ֱ��,�ú���
		//pDC->SelectObject(&PenRed);
		//pDC->MoveTo(x11,y11);pDC->LineTo(x21,y21);
		//pDC->MoveTo(x12,y12);pDC->LineTo(x22,y22);
		//pDC->MoveTo(x13,y13);pDC->LineTo(x23,y23);
		////�������ú�Ĵ��ڣ�����ɫ
		//pDC->SelectObject(&PenBlue);
		//pDC->Rectangle(WL+350,WB,WR+350,WT);
		////�����ߣ������ü�������
		//pDC->SelectObject(&PenBlue);
		//C_S_Line(pDC,x11,y11,x21,y21);
		//C_S_Line(pDC,x12,y12,x22,y22);
		//C_S_Line(pDC,x13,y13,x23,y23);
		/******************************************************************/

		//CPen newpen(PS_SOLID,1,RGB(255,0,0));
		//CPen *old=pDC->SelectObject(&newpen);
		//pDC->TextOut(20,20,(CString)"˫��������, ���������Ķ����, �����ع��ܲ˵�ʵ���������");
		//pDC->TextOut(20,50,(CString)"�����������, ��������Ҽ�, �����������һ��, ��Ϊ��ʼ�������ӵ�");
		//pDC->SelectObject(old);


	}


	// CMFCApplication1View ��ӡ

	BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
	}


	// CMFCApplication1View ���

#ifdef _DEBUG
	void CMFCApplication1View::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMFCApplication1View::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
		return (CMFCApplication1Doc*)m_pDocument;
	}
#endif //_DEBUG


	// CMFCApplication1View ��Ϣ�������


	void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		SetCapture();																//��׽��ǰ���ڵ����
		::SetCursor(m_hCross);														//�滭ʱ��С���
		m_ptOrigin=point;															//���û滭���
		m_bDragging=TRUE;															//������ק
	}


	void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_bDragging)
		{
			/*
			CClientDC dc(this);														//��ȡ��ǰ����������
			dc.MoveTo(m_ptOrigin);													//���û�����ʼ��
			dc.LineTo(point);														//���ߵ�pointλ��
			m_ptOrigin=point;														//��ĩ����Ϊ�µ���ʼ�㣬����
			*/
			CMFCApplication1Doc  *pDoc=GetDocument();								//����ĵ�����ָ��
			ASSERT_VALID(pDoc);  													//�����ĵ������Ƿ�������Ч
			pDoc->AddLine(m_ptOrigin, point);										//�����߶ε�ָ������
			CClientDC   dc(this);
			dc.MoveTo(m_ptOrigin); 
			dc.LineTo(point);														// �����߶�
			m_ptOrigin=point;														// �µ���ʼ��


		}
	}


	void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_bDragging)
		{
			m_bDragging=false;														//��������ק
			ReleaseCapture();														//�ͷŵ�ǰ���ڵ����
		}
		CView::OnLButtonUp(nFlags, point);
	}
	void CMFCApplication1View::OnScanfill()
	{
		// TODO: �ڴ���������������
		CDC* pDC=GetDC();
		CPen newpen(PS_SOLID,1,RGB(0,255,0));
		CPen *old=pDC->SelectObject(&newpen);
		int j,k,s=0;
		int p[5];																//ÿ��ɨ���߽���
		int pmin,pmax;
		for(int i=0;i<6;i++)													//�����߱�
		{
			edge[i].dx=(float)(spt[i+1].x-spt[i].
				x)/(spt[i+1].y-spt[i].y);
			if(spt[i].y<=spt[i+1].y){
				edge[i].num=i;
				edge[i].ymin=spt[i].y;
				edge[i].ymax=spt[i+1].y;
				edge[i].xmin=(float)spt[i].x;
				edge[i].xmax=(float)spt[i+1].x;
				pmax=spt[i+1].y;
				pmin=spt[i].y;

			}
			else{
				edge[i].num=i;
				edge[i].ymin=spt[i+1].y;
				edge[i].ymax=spt[i].y;
				edge[i].xmax=(float)spt[i].x;
				edge[i].xmin=(float)spt[i+1].x;
				pmax=spt[i].y;
				pmin=spt[i+1].y;
			}
		}
		for(int r=1;r<6;r++)	//����edge(yUpper��xIntersect)
		{
			for(int q=0;q<6-r;q++)
			{
				if(edge[q].ymin<edge[q+1].ymin)
				{
					newedge[0]=edge[q];	edge[q]=edge[q+1];
					edge[q+1]=newedge[0];
				}				
			}
		}
		for(int scan=pmax-1;scan>pmin+1;scan--)
		{
			int b=0;
			k=s;
			for(j=k;j<6;j++)
			{	
				if((scan>edge[j].ymin)&&(scan<=edge[j].ymax))//�ж����߶��ཻ
				{
					if(scan==edge[j].ymax)
					{
						if(spt[edge[j].num+1].y<edge[j].ymax)
						{
							b++;
							p[b]=(int)edge[j].xmax;
						}
						if(spt[edge[j].num-1].y<edge[j].ymax)
						{
							b++;		
							p[b]=(int)edge[j].xmax;
						}			
					}			
					if((scan>edge[j].ymin)&&(scan<edge[j].ymax))
					{
						b++;
						p[b]=(int)(edge[j].xmax+edge[j].dx*(scan-edge[j]. 
							ymax));
					}
				}
				//pDC->LineTo(spt[edge[0].num].x,spt[edge[0].num].y);
				if(scan<=edge[j].ymin)//
					s=j;
			}		
			if(b>1)
			{					
				for(int u=1;u<b;u++)
				{
					pDC->MoveTo(p[u]+3,scan);
					u++;
					pDC->LineTo(p[u],scan);
				}
			}		
		}
		pDC->SelectObject(old);	

	}


	void CMFCApplication1View::OnSeedfill()
	{
		// TODO: �ڴ���������������
		CWindowDC     dc (this);
		int fill=RGB(0,255,0);								//��ɫ���ɫ
		int boundary=RGB(255,0,0);							//�߽���ɫ
		CPoint pt=s_point;
		int x,y,p0,pmin,pmax;
		//�����ε������Сֵ
		for(int m=1;m<7;m++)
		{
			for(int n=0;n<7-m;n++)
			{
				if(spt[n].y<spt[n+1].y)
				{
					p0=spt[n].y;	spt[n]=spt[n+1];
					spt[n+1]=p0;
				}				
			}
		}
		pmax=spt[0].y,pmin=spt[6].y;
		//ѡ�����ӵ�
		x=s_point.x;
		y=s_point.y;
		//�ӱ߽��ڵĵ�һ���߿�ʼ
		for(;y<pmax+1;y++)
		{
			int current=dc.GetPixel(x,y);						//���������ɫ
			while((current!=boundary)&&(current!=fill))			//���û�����
			{		
				dc.SetPixel(x,y,fill);							//���
				x++;											//��һ����
				current=dc.GetPixel(x,y);						//h��ȡ��ɫ
			}
			x=s_point.x;
			x--;												//������ӵ����
			current=dc.GetPixel(x,y);
			while((current!=boundary)&&(current!=fill))
			{		
				dc.SetPixel(x,y,fill);
				x--;		
				current=dc.GetPixel(x,y);			
			}
			x=s_point.x;
		}
		x=s_point.x;											//����������
		y=s_point.y-1;											//ditto
		for(;y>pmin-2;y--)
		{
			int current=dc.GetPixel(x,y);
			while((current!=boundary)&&(current!=fill))
			{		
				dc.SetPixel(x,y,fill);
				x++;		
				current=dc.GetPixel(x,y);
			}					
			x=s_point.x;
			x--;
			current=dc.GetPixel(x,y);
			while((current!=boundary)&&(current!=fill))
			{		
				dc.SetPixel(x,y,fill);
				x--;		
				current=dc.GetPixel(x,y);
			}
			x=s_point.x;
		}

	}


	void CMFCApplication1View::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		RedrawWindow();
		CDC* pDC=GetDC();
		CPen newpen(PS_SOLID,1,RGB(255,0,0));
		CPen *old=pDC->SelectObject(&newpen);
		spt[0]=CPoint(100,100);										//���ƶ��������
		spt[1]=CPoint(300,100);
		spt[2]=CPoint(250,250);
		spt[3]=CPoint(100,250);	
		spt[4]=CPoint(150,200);
		spt[5]=CPoint(90,180);
		spt[6]=CPoint(150,150);
		spt[7]=CPoint(100,100);
		pDC->Polyline(spt,8);
		pDC->SelectObject(old);
		ReleaseDC(pDC);

		CView::OnLButtonDblClk(nFlags, point);
	}


	void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		s_point=point;												//ѡ�����ӵ� 
		CView::OnRButtonDown(nFlags, point);

		CView::OnRButtonDown(nFlags, point);
	}

	void CMFCApplication1View::OnDrawleaf()
	{
		// TODO: �ڴ���������������
		CMFCApplication1View::DrawLeaf();

	}


	void CMFCApplication1View::OnDrawrose()
	{
		// TODO: �ڴ���������������
		CMFCApplication1View::DrawRose();
	}

	//CMFCApplication1View.h	�Զ��庯��
	void CMFCApplication1View::MidpointEllise(CDC *pDC, int x0, int y0, int a, int b, COLORREF color)
	{
		int x,y;									
		float d1,d2;
		x=0;y=b;
		d1=b*b+a*a*(-b+0.25);
		pDC->SetPixel(x+x0,y+y0,color);
		while (b*b*(x+1)<a*a*(y-0.5))
		{
			if (d1<0)
			{
				d1+=b*b*(2*x+3);
				x++;
			}
			else
			{
				d1+=(b*b*(2*x+3)+a*a*(-2*y+2));
				x++;	y--;
			}
			pDC->SetPixel(x0+x,y0+y,color);
			pDC->SetPixel(x0+x,y0-y,color);
			pDC->SetPixel(x0-x,y0+y,color);
			pDC->SetPixel(x0-x,y0-y,color);
		} //  �ϰ벿��
		d2=(b*(x+0.5))*(b*(x+0.5))+(a*(y-1))*(a*(y-1))-(a*b)*(a*b);
		while (y>0)
		{
			if (d2<0)
			{
				d2+=b*b*(2*x+2)+a*a*(-2*y+3);
				x++;	y--;
			}
			else
			{
				d2+=a*a*(-2*y+3);
				y--;
			}
			pDC->SetPixel(x0+x,y0+y,color);
			pDC->SetPixel(x0+x,y0-y,color);
			pDC->SetPixel(x0-x,y0+y,color);
			pDC->SetPixel(x0-x,y0-y,color);
		} //�°벿��
	}

	void CMFCApplication1View::PositiveNegativeParabola(CDC *pDC, float a, float b, float c, int color)
	{
		int x,y,d;
		x=0;
		y=0;
		pDC->SetPixel(x+450+b,y+225+c,color);
		if(a>0)
		{   
			y=1;
			pDC->SetPixel(x+450+b,y+225+c,color);
			d=1;
			while(y<=30)
			{
				if(d>=0)
				{
					d=d-2*a*x-a;
					x++;
				}
				else
				{
					d=d+1;
					y++;
				}
				pDC->SetPixel(-x+450+b,y+225+c,color);
				pDC->SetPixel(x+450+b,y+225+c,color);
			}
		}
		else if(a<0)
		{
			x=1;
			pDC->SetPixel(x+450+b,y+225+c,color);
			d=1;
			while(y>=-35)
			{
				if(d>=0)
				{
					d=d-1;
					y--;
				}
				else
				{
					d=d-2*a*x-a;
					x++;
				}
				pDC->SetPixel(-x+450+b,y+225+c,color);
				pDC->SetPixel(x+450+b,y+225+c,color);
			}
		}
		else
		{
			printf("this is not a Parabola!\n");
		}
	}

	int CMFCApplication1View::C_S_Line(CDC *pDC, int x1, int y1, int x2, int y2)
	{
		int code1,code2,code,x,y;
		encode(x1,y1,&code1);												//(x1,y1)���ı���
		encode(x2,y2,&code2);												//(x2,y2)���ı���
		while (code1!=0||code2!=0)											//�� code1 ������ 0 �� code2 ������ 0
		{
			if ((code1&code2)!=0) return 0;									//�� code1 �� code2 ������ 0����ͬ�ࣻ
			code=code1;
			if (code1==0)	code=code2;
			if ((LEFT&code)!=0)												//�󽻵�
			{
				x=WL;
				y=y1+(y2-y1)*(WL-x1)/(x2-x1);
			}
			else if ((RIGHT&code)!=0)
			{
				x=WR;
				y=y1+(y2-y1)*(WR-x1)/(x2-x1);
			}
			else if ((BOTTOM&code)!=0)
			{
				y=WB;
				x=x1+(x2-x1)*(WB-y1)/(y2-y1);
			}
			else if ((TOP&code)!=0)
			{
				y=WT;
				x=x1+(x2-x1)*(WT-y1)/(y2-y1);
			}
			if (code==code1)
			{
				x1=x;y1=y;
				encode(x,y,&code1);
			}
			else
			{
				x2=x;y2=y;
				encode(x,y,&code2);
			}
		}
		//end while,��ʾ code1��code2 ��Ϊ 0�����е��߶�Ϊ���Ӳ���
		pDC->MoveTo(x1+350,y1);
		pDC->LineTo(x2+350,y2);
	}
	void CMFCApplication1View::encode(int x, int y, int *code)
	{
		int c=0;
		if (x<WL)	c=c|LEFT;
		else if (x>WR) c=c|RIGHT;
		if (y<WB)	c=c|BOTTOM;
		else if (y>WT)	c=c|TOP;
		*code=c;
	}


	void CMFCApplication1View::DrawRose()
	{
		CDC *pDC=GetDC();
		int d,k,x1,x2,y1,y2;  
		float pi,a,e;  
		CPen pen;  
		pen.CreatePen(PS_SOLID,1,RGB(0xff,0,0));  
		CPen *pOldPen = pDC->SelectObject(&pen);  
		pi = 3.1415926;  
		d = 80;  
		for (a = 0; a<=2 * pi; a+= pi/360)  
		{  
			e = d * (1+0.25*sin(4*a));  
			e = e * (1 + sin(8*a));  
			x1 = int(320+e*cos(a));  
			x2 = int(320+e*cos(a + pi/8));  
			y1 = int(200+e*sin(a));  
			y2 = int(200+e*sin(a + pi/8));  
			pDC->MoveTo(x1,y1);  
			pDC->LineTo(x2,y2);  
		}  	

	}

	void CMFCApplication1View::DrawLeaf()
	{
		CDC *pDc=GetDC();
		CPen pen;  
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0xff));  
		CPen *pOldPen = pDc->SelectObject(&pen);  

		int a,n,cx,cy,gx,gy,flag,k;  
		double r,p,th,x,y,pi;  
		a = 160;n = 2;pi = 3.1415926;  
		cx = 700;  
		cy = 500;  
		flag = 0; k = 200;  
		for (p = 1; p >= 0.2; p-=0.2)  
		{  
			for (th = 0; th <= 2*pi+0.1; th += pi/k)  
			{  
				r = fabs(a*cos(n*th)*p);  
				x = r*cos(th);  
				y = r*sin(th);  
				gx = int(cx+x);  
				gy = int(cy+y);  
				if (flag == 0)  
				{  
					pDc->MoveTo(gx,gy);  
				}  
				flag = 1;  
				pDc->LineTo(gx,gy);  
			}  
			flag = 0;  
		}  
		pDc->SelectObject(pOldPen); 	

	}



	void CMFCApplication1View::OnInitialUpdate()
	{
		CView::OnInitialUpdate();

		// TODO: �ڴ����ר�ô����/����û���
	}

	void CMFCApplication1View::Initial(void)
	{
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glColor3f(0.0f,0.0f,0.0f);
		obj=gluNewQuadric();										//����������������
		gluQuadricDrawStyle(obj,GLU_LINE);							//��ѡ��ʽ���ƶ����������

	}

	void CMFCApplication1View::ChangeSize(int w,int h)
	{
		glViewport(0,0,w,h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1.5f,1.5f,-1.5f,1.5f);
	}

	void CMFCApplication1View::Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);										//ָ������ģ����ͼ�任����
		glLoadIdentity();												//������ǰ�ı任
		glRotatef(xRot,1.0f,0.0f,0.0f);									//��x����תͼ��
		glRotatef(yRot,0.0f,1.0f,0.0f);									//��y����תͼ��
		switch(iMode)
		{
		case 1:
			glutWireTetrahedron();
			break;														//�����߿���������
		case 2:
			glutSolidTetrahedron();
			break;														//����ʵ����������
		case 3:
			glutWireOctahedron();
			break;														//�����߿���������
		case 4:
			glutSolidOctahedron();
			break;														//����ʵ����������
		case 5:
			glutWireSphere(1.0f,15,15);
			break;														//�����߿���
		case 6:
			glutSolidSphere(1.0f,15,15);
			break;														//����ʵ����
		case 7:
			glutWireTeapot(1.0f);
			break;														//�����߿���
		case 8:
			glutSolidTeapot(1.0f);
			break;														//����ʵ����
		case 9:
			gluSphere(obj,1.0f,15,15);
			break;														//���ƶ������棨��
		case 10:
			gluCylinder(obj,1.0f,0.0f,1.0f,15,15);
			break;														//���ƶ������棨Բ׶��
		case 11:
			gluPartialDisk(obj,0.3f,0.8f,15,15,30.0f,260.0f);
			break;														//���ƶ������棨Բ����
		default:
			break;
		}
		glFlush();
	}

	void CMFCApplication1View::ProcessMenu(int value)
	{
		iMode=value;
		glutPostRedisplay();
	}

	void CMFCApplication1View::SpecialKeys(int key,int x,int y)
	{
		//��������ͼ�ε���ת
		if(key==GLUT_KEY_UP)    xRot-=5.0f;
		if(key==GLUT_KEY_DOWN)    xRot+=5.0f;
		if(key==GLUT_KEY_LEFT)    yRot-=5.0f;
		if(key==GLUT_KEY_DOWN)    yRot+=5.0f;
		if(xRot>356.0f)    xRot=0.0f;
		if(xRot<-1.0f)    xRot=355.0f;
		if(yRot>356.0f)    yRot=0.0f;
		if(yRot<-1.0f)    yRot=355.0f;
		glutPostRedisplay();
	}




	void CMFCApplication1View::OnDrawgl()
	{

		// TODO: �ڴ���������������
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);								//���ó�ʼ��ʾģʽ
		glutInitWindowSize(400,400);
		glutInitWindowPosition(100,100);
		glutCreateWindow("OpenGLģ�ͻ��ƺ���ʾ��");

		int nGlutPolyMenu = glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("�߿���������",1);
		glutAddMenuEntry("ʵ����������",2);
		glutAddMenuEntry("�߿���������",3);
		glutAddMenuEntry("ʵ����������",4);

		int nGlutCurveMenu=glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("�߿�����",5);
		glutAddMenuEntry("ʵ������",6);
		glutAddMenuEntry("�߿���",7);
		glutAddMenuEntry("ʵ����",8);

		int nGluCurveMenu=glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("�߿�����",9);
		glutAddMenuEntry("�߿�Բ׶��",10);
		glutAddMenuEntry("�߿�Բ����",11);

		int nMainMenu=glutCreateMenu(ProcessMenu);
		glutAddSubMenu("GLUT������",nGlutPolyMenu);
		glutAddSubMenu("GLUT����",nGlutCurveMenu);
		glutAddSubMenu("GLU����",nGluCurveMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutDisplayFunc(Display);
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		Initial();
		glutMainLoop();

	}

	///*************�����*************************************/
	//void CMFCApplication1View::myinit(void)
	//{
	//	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);
	//	glDepthFunc(GL_LESS);
	//	glEnable(GL_DEPTH_TEST);

	//}

	//void CALLBACK CMFCApplication1View::displayBall(void)
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	auxSolidSphere(1.0);
	//	glFlush();


	//}

	//void CALLBACK CMFCApplication1View::myReshapeBall(GLsizei w, GLsizei h)
	//{
	//	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);
	//	glDepthFunc(GL_LESS);
	//	glEnable(GL_DEPTH_TEST);

	//}

	///*************��������*************************************/

	///*************�������� *************************************/

	//void CMFCApplication1View::object(void)
	//{
	//	glBegin (GL_POLYGON);
	//	glColor3f (1.0, 0.0, 0.0);
	//	glVertex2f (4.0, 4.0);
	//	glColor3f(1.0,1.0,1.0);
	//	glVertex2f (12.0, 4.0);
	//	glColor3f(0.0,0.0,1.0);
	//	glVertex2f (12.0, 12.0);
	//	glColor3f(0.0,1.0,0.0);
	//	glVertex2f (4.0, 12.0);
	//	glEnd ();
	//}
	//void CMFCApplication1View::myinit2(void)
	//{
	//	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };							///������Դ
	//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);														//��0�Ź�Դ
	//	glDepthFunc(GL_LESS);
	//	glEnable(GL_DEPTH_TEST);

	//}

	//void CALLBACK CMFCApplication1View::displayLD(void)
	//{
	//	glClear (GL_COLOR_BUFFER_BIT);												//�����ɫ������
	//	object ();
	//	glFlush ();																	//��ʼ����


	//}

	//void CALLBACK CMFCApplication1View::myReshapeLD(GLsizei w, GLsizei h)
	//{
	//	glViewport(0, 0, w, h);													//���ô��ڴ�С
	//	glMatrixMode(GL_PROJECTION);											//ָ����ǰ�����ľ���ΪͶӰ����
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();														//��ͶӰ��������Ϊ��λ����
	//	if (w <= h)																//��άͼ���ͶӰ
	//		gluOrtho2D (0.0, 16.0, 0.0, 16.0 * (GLfloat) h/(GLfloat) w);
	//	else 
	//		gluOrtho2D (0.0, 16.0 * (GLfloat) w/(GLfloat) h, 0.0, 16.0);
	//	glMatrixMode(GL_MODELVIEW);


	//}

	///*************�����������*************************************/
	///*************���ʴ���*************************************/
	//void CMFCApplication1View::myinit3(void)
	//{
	//	GLfloat mat_ambient[]= { 0.8, 0.8, 0.8, 1.0 };
	//	GLfloat mat_diffuse[]= { 0.8, 0.0, 0.8, 1.0 };    /* ��ɫ */
	//	GLfloat mat_specular[] = { 1.0, 0.0, 1.0, 1.0 };
	//	GLfloat mat_shininess[] = { 50.0 };
	//	GLfloat light_diffuse[]= { 0.0, 0.0, 1.0, 1.0};   /* ��ɫ */
	//	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);
	//	glDepthFunc(GL_LESS);
	//	glEnable(GL_DEPTH_TEST);


	//}

	//void CALLBACK CMFCApplication1View::displayM(void)
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	auxSolidSphere(1.0);
	//	glFlush();


	//}

	//void CALLBACK CMFCApplication1View::myReshapeM(GLsizei w, GLsizei h)
	//{
	//	glViewport(0, 0, w, h);													//���ô��ڴ�С
	//	glMatrixMode(GL_PROJECTION);											//ָ����ǰ�����ľ���ΪͶӰ����
	//	glLoadIdentity();														//��ͶӰ��������Ϊ��λ����
	//	if (w <= h)																//��άͼ���ͶӰ												
	//		glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
	//		1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	//	else
	//		glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
	//		1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	//	glMatrixMode(GL_MODELVIEW);												//ָ����ǰ�����ľ���Ϊģ����ͼ����
	//	glLoadIdentity();														//��ģ����ͼ����Ϊ��λ����


	//}


//	void CMFCApplication1View::OnRealball()
//	{
//		// TODO: �ڴ���������������
//		auxInitDisplayMode (AUX_SINGLE | AUX_RGBA);
//		auxInitPosition (0, 0, 500, 500);
//		auxInitWindow (TEXT("�򵥵Ĺ���ģ��"));
//		myinit();
//		auxReshapeFunc (myReshapeBall);
//		auxMainLoop(displayBall);
//
//	}


//	void CMFCApplication1View::OnDrawld()
//	{
//		// TODO: �ڴ���������������
//		auxInitDisplayMode (AUX_SINGLE | AUX_RGBA	);				//����ģ����ʾģʽ
//		auxInitPosition (0, 0, 500, 500);							//����ģ����ʾλ�úʹ�С
//		auxInitWindow (TEXT("�⻬��������"));
//		myinit();
//		auxReshapeFunc (myReshapeLD);
//		auxMainLoop(displayLD);
//
//	}




//	void CMFCApplication1View::OnMaterial()
//	{
//		// TODO: �ڴ���������������
//		auxInitDisplayMode (AUX_SINGLE | AUX_RGBA | AUX_DEPTH16);
//    auxInitPosition (0, 0, 500, 500);
//    auxInitWindow (TEXT("���ʴ�������"));
//    myinit();
//    auxReshapeFunc (myReshapeM);
//    auxMainLoop(displayM);
//
//	}
