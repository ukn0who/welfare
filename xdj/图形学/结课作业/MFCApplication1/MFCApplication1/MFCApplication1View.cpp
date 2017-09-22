
// MFCApplication1View.cpp : CMFCApplication1View 类的实现
//

#include "stdafx.h"
#include <math.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/GLAUX.H>
#include <windows.h>

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static GLsizei iMode=1;  //选定的菜单项	
static GLfloat xRot=0.0f; //x方向旋转参数
static GLfloat yRot=0.0f; //y方向旋转参数
GLUquadricObj *obj;			//二次曲面对象


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

	BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
		// 标准打印命令
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

	// CMFCApplication1View 构造/析构

	CMFCApplication1View::CMFCApplication1View()
	{
		// TODO: 在此处添加构造代码
		m_bDragging = false;															//初始无法拖拽
		m_hCross=AfxGetApp()->LoadStandardCursor(IDC_SIZE);								//迷你光标
																						//直线、多边形裁剪
		WL=100;WR=400;WB=100;WT=300;
	}

	CMFCApplication1View::~CMFCApplication1View()
	{
	}

	BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CMFCApplication1View 绘制

	void CMFCApplication1View::OnDraw(CDC* pDC)
	{
		CMFCApplication1Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
		//pDC->SetPixel (250,250,RGB(0,0,0));								//画一个象素点
		//pDC->LineTo(300,200);												//画直线线
		//pDC->Ellipse (100,100,150,150);									//画圆

		int   nIndex=pDoc->GetNumLines();									// 取得线段的数量
		// 循环画出每一段线段
		while(nIndex--)  													// 数组下标从0到nIndex-1
		{
			pDoc->GetLine(nIndex)->DrawLine(pDC);  
			// 类CLine的成员函数
		}

		/*********************************************************/
		//MidpointEllise(pDC, 430, 220, 100, 40, RGB(255,0,0));
		//MidpointEllise(pDC, 430, 220, 40, 100, RGB(255,0,0));
		//PositiveNegativeParabola(pDC,-0.7,-20,3,RGB(255,0,0));
		//PositiveNegativeParabola(pDC,-0.1,-20,3,RGB(255,0,0));

		/******************************************************************/
		////定义三条直线的坐标
		//int x11,y11,x21,y21,x12,y12,x22,y22,x13,y13,x23,y23;
		//x11=50;y11=150;x21=450;y21=250;
		//x12=150;y12=150;x22=350;y22=240;
		//x13=50;y13=400;x23=500;y23=350;
		////定义画笔
		//CPen PenRed(PS_SOLID,1,RGB(255,0,0));								//定义红色笔
		//CPen PenBlue(PS_SOLID,1,RGB(0,0,255));							//定义蓝色笔
		//CPen Penwhite(PS_SOLID,1,RGB(255,255,255));						//定义白色笔
		////先画出窗口，用蓝色
		//pDC->SelectObject(&PenBlue);
		//pDC->Rectangle(WL,WB,WR,WT);
		////先画出三条直线,用红线
		//pDC->SelectObject(&PenRed);
		//pDC->MoveTo(x11,y11);pDC->LineTo(x21,y21);
		//pDC->MoveTo(x12,y12);pDC->LineTo(x22,y22);
		//pDC->MoveTo(x13,y13);pDC->LineTo(x23,y23);
		////画出剪裁后的窗口，用蓝色
		//pDC->SelectObject(&PenBlue);
		//pDC->Rectangle(WL+350,WB,WR+350,WT);
		////用蓝线，画出裁剪三条线
		//pDC->SelectObject(&PenBlue);
		//C_S_Line(pDC,x11,y11,x21,y21);
		//C_S_Line(pDC,x12,y12,x22,y22);
		//C_S_Line(pDC,x13,y13,x23,y23);
		/******************************************************************/

		//CPen newpen(PS_SOLID,1,RGB(255,0,0));
		//CPen *old=pDC->SelectObject(&newpen);
		//pDC->TextOut(20,20,(CString)"双击鼠标左键, 出现需填充的多边形, 点击相关功能菜单实现区域填充");
		//pDC->TextOut(20,50,(CString)"进行种子填充, 需用鼠标右键, 单击多边形内一点, 作为开始填充的种子点");
		//pDC->SelectObject(old);


	}


	// CMFCApplication1View 打印

	BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}


	// CMFCApplication1View 诊断

#ifdef _DEBUG
	void CMFCApplication1View::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMFCApplication1View::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
		return (CMFCApplication1Doc*)m_pDocument;
	}
#endif //_DEBUG


	// CMFCApplication1View 消息处理程序


	void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		SetCapture();																//捕捉当前窗口的鼠标
		::SetCursor(m_hCross);														//绘画时缩小光标
		m_ptOrigin=point;															//设置绘画起点
		m_bDragging=TRUE;															//允许拖拽
	}


	void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if(m_bDragging)
		{
			/*
			CClientDC dc(this);														//获取当前窗口上下文
			dc.MoveTo(m_ptOrigin);													//设置画线起始点
			dc.LineTo(point);														//连线到point位置
			m_ptOrigin=point;														//线末端作为新的起始点，保存
			*/
			CMFCApplication1Doc  *pDoc=GetDocument();								//获得文档对象指针
			ASSERT_VALID(pDoc);  													//测试文档对象是否运行有效
			pDoc->AddLine(m_ptOrigin, point);										//加入线段到指针数组
			CClientDC   dc(this);
			dc.MoveTo(m_ptOrigin); 
			dc.LineTo(point);														// 绘制线段
			m_ptOrigin=point;														// 新的起始点


		}
	}


	void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if(m_bDragging)
		{
			m_bDragging=false;														//不允许拖拽
			ReleaseCapture();														//释放当前窗口的鼠标
		}
		CView::OnLButtonUp(nFlags, point);
	}
	void CMFCApplication1View::OnScanfill()
	{
		// TODO: 在此添加命令处理程序代码
		CDC* pDC=GetDC();
		CPen newpen(PS_SOLID,1,RGB(0,255,0));
		CPen *old=pDC->SelectObject(&newpen);
		int j,k,s=0;
		int p[5];																//每根扫描线交点
		int pmin,pmax;
		for(int i=0;i<6;i++)													//建立边表
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
		for(int r=1;r<6;r++)	//排序edge(yUpper，xIntersect)
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
				if((scan>edge[j].ymin)&&(scan<=edge[j].ymax))//判断与线段相交
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
		// TODO: 在此添加命令处理程序代码
		CWindowDC     dc (this);
		int fill=RGB(0,255,0);								//绿色填充色
		int boundary=RGB(255,0,0);							//边界颜色
		CPoint pt=s_point;
		int x,y,p0,pmin,pmax;
		//求多边形的最大最小值
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
		//选择种子点
		x=s_point.x;
		y=s_point.y;
		//从边界内的第一条边开始
		for(;y<pmax+1;y++)
		{
			int current=dc.GetPixel(x,y);						//获得种子颜色
			while((current!=boundary)&&(current!=fill))			//如果没有填充
			{		
				dc.SetPixel(x,y,fill);							//填充
				x++;											//下一个点
				current=dc.GetPixel(x,y);						//h获取颜色
			}
			x=s_point.x;
			x--;												//填充种子点左边
			current=dc.GetPixel(x,y);
			while((current!=boundary)&&(current!=fill))
			{		
				dc.SetPixel(x,y,fill);
				x--;		
				current=dc.GetPixel(x,y);			
			}
			x=s_point.x;
		}
		x=s_point.x;											//设置新种子
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
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		RedrawWindow();
		CDC* pDC=GetDC();
		CPen newpen(PS_SOLID,1,RGB(255,0,0));
		CPen *old=pDC->SelectObject(&newpen);
		spt[0]=CPoint(100,100);										//绘制多边形区域
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
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		s_point=point;												//选择种子点 
		CView::OnRButtonDown(nFlags, point);

		CView::OnRButtonDown(nFlags, point);
	}

	void CMFCApplication1View::OnDrawleaf()
	{
		// TODO: 在此添加命令处理程序代码
		CMFCApplication1View::DrawLeaf();

	}


	void CMFCApplication1View::OnDrawrose()
	{
		// TODO: 在此添加命令处理程序代码
		CMFCApplication1View::DrawRose();
	}

	//CMFCApplication1View.h	自定义函数
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
		} //  上半部分
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
		} //下半部分
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
		encode(x1,y1,&code1);												//(x1,y1)处的编码
		encode(x2,y2,&code2);												//(x2,y2)处的编码
		while (code1!=0||code2!=0)											//当 code1 不等于 0 或 code2 不等于 0
		{
			if ((code1&code2)!=0) return 0;									//当 code1 与 code2 不等于 0，在同侧；
			code=code1;
			if (code1==0)	code=code2;
			if ((LEFT&code)!=0)												//求交点
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
		//end while,表示 code1，code2 都为 0，其中的线段为可视部分
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

		// TODO: 在此添加专用代码和/或调用基类
	}

	void CMFCApplication1View::Initial(void)
	{
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glColor3f(0.0f,0.0f,0.0f);
		obj=gluNewQuadric();										//激活二次曲面绘制器
		gluQuadricDrawStyle(obj,GLU_LINE);							//已选框方式绘制二次曲面对象

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
		glMatrixMode(GL_MODELVIEW);										//指定设置模型视图变换参数
		glLoadIdentity();												//消除以前的变换
		glRotatef(xRot,1.0f,0.0f,0.0f);									//绕x轴旋转图形
		glRotatef(yRot,0.0f,1.0f,0.0f);									//绕y轴旋转图行
		switch(iMode)
		{
		case 1:
			glutWireTetrahedron();
			break;														//绘制线框正四面体
		case 2:
			glutSolidTetrahedron();
			break;														//绘制实体正四面体
		case 3:
			glutWireOctahedron();
			break;														//绘制线框正八面体
		case 4:
			glutSolidOctahedron();
			break;														//绘制实体正八面体
		case 5:
			glutWireSphere(1.0f,15,15);
			break;														//绘制线框球
		case 6:
			glutSolidSphere(1.0f,15,15);
			break;														//绘制实体球
		case 7:
			glutWireTeapot(1.0f);
			break;														//绘制线框茶壶
		case 8:
			glutSolidTeapot(1.0f);
			break;														//绘制实体茶壶
		case 9:
			gluSphere(obj,1.0f,15,15);
			break;														//绘制二次曲面（球）
		case 10:
			gluCylinder(obj,1.0f,0.0f,1.0f,15,15);
			break;														//绘制二次曲面（圆锥）
		case 11:
			gluPartialDisk(obj,0.3f,0.8f,15,15,30.0f,260.0f);
			break;														//绘制二次曲面（圆环）
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
		//光标键控制图形的旋转
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

		// TODO: 在此添加命令处理程序代码
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);								//设置初始显示模式
		glutInitWindowSize(400,400);
		glutInitWindowPosition(100,100);
		glutCreateWindow("OpenGL模型绘制函数示例");

		int nGlutPolyMenu = glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("线框正四面体",1);
		glutAddMenuEntry("实体正四面体",2);
		glutAddMenuEntry("线框正八面体",3);
		glutAddMenuEntry("实体正八面体",4);

		int nGlutCurveMenu=glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("线框球面",5);
		glutAddMenuEntry("实体球面",6);
		glutAddMenuEntry("线框茶壶",7);
		glutAddMenuEntry("实体茶壶",8);

		int nGluCurveMenu=glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("线框球面",9);
		glutAddMenuEntry("线框圆锥面",10);
		glutAddMenuEntry("线框圆环面",11);

		int nMainMenu=glutCreateMenu(ProcessMenu);
		glutAddSubMenu("GLUT多面体",nGlutPolyMenu);
		glutAddSubMenu("GLUT曲面",nGlutCurveMenu);
		glutAddSubMenu("GLU曲面",nGluCurveMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutDisplayFunc(Display);
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		Initial();
		glutMainLoop();

	}

	///*************光感球*************************************/
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

	///*************光感球结束*************************************/

	///*************明暗处理 *************************************/

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
	//	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };							///定义点光源
	//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);														//打开0号光源
	//	glDepthFunc(GL_LESS);
	//	glEnable(GL_DEPTH_TEST);

	//}

	//void CALLBACK CMFCApplication1View::displayLD(void)
	//{
	//	glClear (GL_COLOR_BUFFER_BIT);												//清除颜色缓冲区
	//	object ();
	//	glFlush ();																	//开始绘制


	//}

	//void CALLBACK CMFCApplication1View::myReshapeLD(GLsizei w, GLsizei h)
	//{
	//	glViewport(0, 0, w, h);													//设置窗口大小
	//	glMatrixMode(GL_PROJECTION);											//指定当前操作的矩阵为投影矩阵
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();														//将投影矩阵设置为单位矩阵
	//	if (w <= h)																//二维图像的投影
	//		gluOrtho2D (0.0, 16.0, 0.0, 16.0 * (GLfloat) h/(GLfloat) w);
	//	else 
	//		gluOrtho2D (0.0, 16.0 * (GLfloat) w/(GLfloat) h, 0.0, 16.0);
	//	glMatrixMode(GL_MODELVIEW);


	//}

	///*************明暗处理结束*************************************/
	///*************材质处理*************************************/
	//void CMFCApplication1View::myinit3(void)
	//{
	//	GLfloat mat_ambient[]= { 0.8, 0.8, 0.8, 1.0 };
	//	GLfloat mat_diffuse[]= { 0.8, 0.0, 0.8, 1.0 };    /* 紫色 */
	//	GLfloat mat_specular[] = { 1.0, 0.0, 1.0, 1.0 };
	//	GLfloat mat_shininess[] = { 50.0 };
	//	GLfloat light_diffuse[]= { 0.0, 0.0, 1.0, 1.0};   /* 蓝色 */
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
	//	glViewport(0, 0, w, h);													//设置窗口大小
	//	glMatrixMode(GL_PROJECTION);											//指定当前操作的矩阵为投影矩阵
	//	glLoadIdentity();														//将投影矩阵设置为单位矩阵
	//	if (w <= h)																//二维图像的投影												
	//		glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
	//		1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	//	else
	//		glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
	//		1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	//	glMatrixMode(GL_MODELVIEW);												//指定当前操作的矩阵为模型视图矩阵
	//	glLoadIdentity();														//将模型视图矩阵为单位矩阵


	//}


//	void CMFCApplication1View::OnRealball()
//	{
//		// TODO: 在此添加命令处理程序代码
//		auxInitDisplayMode (AUX_SINGLE | AUX_RGBA);
//		auxInitPosition (0, 0, 500, 500);
//		auxInitWindow (TEXT("简单的光照模型"));
//		myinit();
//		auxReshapeFunc (myReshapeBall);
//		auxMainLoop(displayBall);
//
//	}


//	void CMFCApplication1View::OnDrawld()
//	{
//		// TODO: 在此添加命令处理程序代码
//		auxInitDisplayMode (AUX_SINGLE | AUX_RGBA	);				//设置模型显示模式
//		auxInitPosition (0, 0, 500, 500);							//设置模型显示位置和大小
//		auxInitWindow (TEXT("光滑明暗处理"));
//		myinit();
//		auxReshapeFunc (myReshapeLD);
//		auxMainLoop(displayLD);
//
//	}




//	void CMFCApplication1View::OnMaterial()
//	{
//		// TODO: 在此添加命令处理程序代码
//		auxInitDisplayMode (AUX_SINGLE | AUX_RGBA | AUX_DEPTH16);
//    auxInitPosition (0, 0, 500, 500);
//    auxInitWindow (TEXT("材质处理例子"));
//    myinit();
//    auxReshapeFunc (myReshapeM);
//    auxMainLoop(displayM);
//
//	}
