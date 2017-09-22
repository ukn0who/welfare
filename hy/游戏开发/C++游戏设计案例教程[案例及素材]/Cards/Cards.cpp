/********************************
	游戏程序主文件Cards.cpp
********************************/
#include "Cards.h"
#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  游戏初始化 */
BOOL GameInitialize(HINSTANCE hInstance)
{
	/* 在这里构造游戏引擎实例，并设置初始化引擎参数 */
	
	//创建引擎
	g_pGE=new GameEngine(hInstance,TEXT(g_strTitle),TEXT(g_strTitle),
			IDI_BIGICON,IDI_SMALLICON,FALSE,32,800,600);
	if(g_pGE==NULL)
		return false;

	//初始化引擎参数
	g_pGE->SetFrameDelay(15) ;		//设置游戏帧延时为15毫秒
	g_pGE->SetPause(false);			//设置暂停状态为false
	
	if(!g_pGE->CreateGameWindow())	//创建游戏窗口
	{
		MessageBox(NULL,"修改显示模式失败!\r\n程序退出!","错误",MB_OK| MB_ICONERROR);
		return FALSE;		//退出程序
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏开始 */
void GameStart(HWND hWnd)
{
	/* 设置鼠标指针 */
	long lCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE (IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,lCur);

	/*循环设置卡片位置矩形和初始化卡片选择状态*/
	int i,j,n,m;
	for( i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)	
		{
			/* 设置卡片位置矩形范围*/
			g_rCardRect[i][j].left=CARSTARTX+(CARDWIDTH+COLSPACE)*j;
			g_rCardRect[i][j].right=g_rCardRect[i][j].left+CARDWIDTH;
			g_rCardRect[i][j].top=CARSTARTY+(CARDHEIGHT+ROWSPACE)*i;
			g_rCardRect[i][j].bottom=g_rCardRect[i][j].top+CARDHEIGHT;
			
			g_nCardState[i][j]=INITSELECT;	//初始化卡片选择状态
		}
	}	

	/*初始化卡片图案和位置*/
	srand((unsigned)time(NULL));	// 初始化随机数种子
	for(i=0;i<2;i++)	//2次外循环，即有且仅有两张卡片图案相同
	{
		for(j=0;j<ROWS*COLS/2;j++)	//循环确定m行、n列的图案号为j
		{
			do{
				m=rand()%ROWS;		//随机确定卡片行、列号
				n=rand()%COLS;				
			}while(g_nCardState[m][n]!=INITSELECT);	//如果卡片选择状态为初始化
			g_nCardPattern[m][n]=j;				//设置该卡片图案
			g_nCardState[m][n]=NOSELECT;	//设置该卡片选择状态为未选择
		}
	}

	g_nStartTime=timeGetTime();	//设置游戏起始时间
	g_nTimeCount=20000;			//规定游戏时间	

	SetRect(&g_rTimeBarFrame,100,150,700,170);	//设置时间条边框矩形	
	g_nTimeBarLength=0;			//初始化时间条长度
	//初始化被单击的行、列号
	g_nSelectRow1=g_nSelectRow2=g_nSelectCol1=g_nSelectCol2=-1; 
	g_nSelected=0;			//初始化正确配对的图案对数
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏逻辑 */
void GameAction(HWND hWnd)
{
	/* 计算游戏经过的时间和时间条长度 */
	long nCurrentTimes=timeGetTime()-g_nStartTime;
	if(nCurrentTimes<g_nTimeCount)
	{
		g_nTimeBarLength=nCurrentTimes*596/g_nTimeCount;	
	}
	
	/*如果已有2张卡片被单击过，判断2张卡片图案是否相同*/
	if(g_nSelectRow2!=-1)
	{
		if(g_nCardPattern[g_nSelectRow1][g_nSelectCol1]==g_nCardPattern[g_nSelectRow2] [g_nSelectCol2])
		{
			/*如果两张卡片图案相同*/
			//设置卡片状态为已正确配对
			g_nCardState[g_nSelectRow1][g_nSelectCol1]=SELECTOK;		
			g_nCardState[g_nSelectRow2][g_nSelectCol2]=SELECTOK;

			//设置卡片图案为空	
			g_nCardPattern[g_nSelectRow2][g_nSelectCol2]=NULLPATTERN;
			g_nCardPattern[g_nSelectRow1][g_nSelectCol1]=NULLPATTERN;

			g_nSelected++;	//已正确配对卡片数递增
			//重置单击选择行、列号
			g_nSelectRow1=g_nSelectRow2=g_nSelectCol1=g_nSelectCol2=-1;		
		}
		else
		{
			/* 如果两张卡片图案不同 */
			if(timeGetTime()-g_nTimeDelayStart>200)	/*图案显示延时0.2秒*/
			{
				//设置卡片状态为未选中
				g_nCardState[g_nSelectRow1][g_nSelectCol1]=NOSELECT;
				g_nCardState[g_nSelectRow2][g_nSelectCol2]=NOSELECT;
				//重置单击选择行、列号
				g_nSelectRow1=g_nSelectRow2=g_nSelectCol1=g_nSelectCol2=-1;	
			}
		}
	}

	InvalidateRect(hWnd,NULL,FALSE);	//强制刷新窗口
	UpdateWindow(hWnd);

	/* 检查游戏时间是否超出规定时间*/
	if(nCurrentTimes<g_nTimeCount)
	{
		/*未超出规定时间*/
		if(g_nSelected==6)	//检查是否所有卡片对已选完，如选完则赢
		{
			if(MessageBox(g_pGE->GetWindow(),"全部配对成功！你赢了！\r\n要继续游戏吗？","你赢了！",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
			{	

				GameStart(hWnd);		//重新开始
			}
			else
				DestroyWindow(hWnd);	//退出程序
		}	
	}
	else	
	{
		/*游戏时间超出规定时间，判游戏者失败*/
		if(MessageBox(g_pGE->GetWindow(),"时间到！你输了！\r\n要继续游戏吗？","你输了！",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		{	
			GameStart(hWnd);
		}
		else
			DestroyWindow(hWnd);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 鼠标单击事件处理 */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	/* 在这里添加具体的鼠标单击事件处理代码 */
	POINT pt={x,y};		//定义鼠标单击点

	//循环判断鼠标单击点是否在卡片矩形范围内				
	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			if(PtInRect(&g_rCardRect[i][j],pt))//判断卡片是否被单击
			{
				//卡片未被选择，且已被单击的卡片数不超过2张
				if(g_nCardState[i][j]==NOSELECT && g_nSelectRow2==-1)	
				{
					if(g_nSelectRow1 == -1 )	//是第1次单击
					{
						g_nSelectRow1=i;		//设置第1次选择的卡片行列号		
						g_nSelectCol1=j;
					}
					else
					{
						g_nSelectRow2=i;		//设置第2次选择的卡片行列号		
						g_nSelectCol2=j;				
						g_nTimeDelayStart=timeGetTime();	//设置延时启动	
					}
					g_nCardState[i][j]=SELECTED;	//设置卡片状态为已选择
					return;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  渲染游戏画面 ***/
void GamePaint(HDC hDC)
{
	/* 绘制窗口底色 */
	RECT rBG;
	GetClientRect(g_pGE->GetWindow(), &rBG);		//获取窗口矩形范围	
	HBRUSH hbrBG=(HBRUSH)GetStockObject(WHITE_BRUSH);	//选用标准白色画刷
	FillRect(hDC,&rBG,hbrBG);		//绘制背景
	DeleteObject(hbrBG);			//删除画刷

	/* 绘制标题 */
	LOGFONT lf={0};			//创建默认逻辑字体
	lf.lfHeight=80;			//设置字体高度
	lf.lfWidth=60;				//设置字体宽度
	lf.lfWeight=800;			//设置字体粗细
	lf.lfCharSet=DEFAULT_CHARSET;		//设置字符集
	strcpy(lf.lfFaceName,"黑体");			//设置字体	
	HFONT hFont=CreateFontIndirect(&lf);	//创建字体	
	HFONT hFontOld=(HFONT)SelectObject(hDC,hFont);	//选用字体
	TextOut(hDC,100,30,g_strTitle,strlen(g_strTitle));	//绘制文本	

	SelectObject(hDC,hFontOld);			//替换字体
	DeleteObject(hFont);				//删除字体

	/* 绘制时间条 */
	HBRUSH hbr=CreateSolidBrush(RGB(128,128,128));	//创建画刷
	HBRUSH hbrOld=(HBRUSH)SelectObject(hDC,hbr);	//选用画刷
	FrameRect(hDC,&g_rTimeBarFrame,hbr);				//绘制边框
	//绘制时间条
	Rectangle(hDC,g_rTimeBarFrame.left+2,g_rTimeBarFrame.top+2,g_rTimeBarFrame.left+2+g_nTimeBarLength,g_rTimeBarFrame.bottom-2);
	SelectObject(hDC,hbrOld);		//替出画刷				

	/* 绘制卡片 */
	//创建卡片背面画刷
	HBRUSH hbrBK=CreateHatchBrush(HS_BDIAGONAL,RGB(128,128,128)); 
	HBRUSH hbrCard;				//定义卡片正面画刷
	RECT r;						//定义卡片绘图矩形范围

	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			FrameRect(hDC,&g_rCardRect[i][j],hbr);//	绘制卡片边框	
			r=g_rCardRect[i][j];			//设置卡片图案矩形范围

			/* 判断卡片是否未被单击选择*/
			if(g_nCardState[i][j]==NOSELECT)	//
			{		
				/*未被单击选择,绘制背面图案*/
				InflateRect(&r,-10,-10);	//缩小矩形	
				FillRect(hDC,&r,hbrBK);		//绘制用背面图案画刷填充的矩形
			}
			else
			{	/*被单击选择,绘制正面图案*/
				InflateRect(&r,-20,-20);	//缩小矩形	
				switch(g_nCardPattern[i][j])	//选择绘制的指定的图案
				{
				case 0:
					hbrCard=CreateSolidBrush(RGB(128,255,0));	//创建画刷
					SelectObject(hDC,hbrCard);					//选用画刷
					RoundRect(hDC,r.left,r.top,r.right,r.bottom, 10,10);	//绘制圆角矩形
					SelectObject(hDC,hbrOld);		//替出画刷				
					break;

				case 1:
					hbrCard=CreateSolidBrush(RGB(255,128,255));
					SelectObject(hDC,hbrCard);		
					RoundRect(hDC,r.left,r.top,r.right,r.bottom, 10,10);	//绘制圆角矩形
					SelectObject(hDC,hbrOld);					
					break;

				case 2:
					hbrCard=CreateSolidBrush(RGB(255,128,128));
					SelectObject(hDC,hbrCard);		
					Rectangle(hDC,r.left,r.top,r.right,r.bottom);	//绘制矩形
					SelectObject(hDC,hbrOld);						
					break;

				case 3:
					hbrCard=CreateSolidBrush(RGB(0,128,128));
					SelectObject(hDC,hbrCard);		
					Rectangle(hDC,r.left,r.top,r.right,r.bottom);	//绘制矩形
					SelectObject(hDC,hbrOld);					
					break;

				case 4:
					hbrCard=CreateSolidBrush(RGB(128,0,255));
					SelectObject(hDC,hbrCard);		
					Ellipse(hDC,r.left,r.top,r.right,r.bottom);		//绘制圆形
					SelectObject(hDC,hbrOld);			
					break;

				case 5:
					hbrCard=CreateSolidBrush(RGB(255,0,128));
					SelectObject(hDC,hbrCard);		
					Ellipse(hDC,r.left,r.top,r.right,r.bottom);		//绘制圆形
					SelectObject(hDC,hbrOld);			
					break;

				default:
					/* 卡片图案为空,绘制白色填充矩形	*/
					//选用标准白色画刷
					hbrCard=(HBRUSH)GetStockObject(WHITE_BRUSH);	
					FillRect(hDC,&g_rCardRect[i][j],hbrCard);		//绘制白色矩形	
					break;	
				}
				DeleteObject(hbrCard);			//删除画刷	
			}
		}
	}
	
	/*清理GDI对象*/
	DeleteObject(hbrBK);
	DeleteObject(hbr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏结束 */
void GameEnd()
{
	delete g_pGE;	//清除游戏引擎指针	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏激活 */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏暂停 */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏窗口关闭 */
BOOL GameWindowClose(HWND hWnd)
{
	/* 游戏窗口关闭前的处理代码 */
	if(MessageBox(g_pGE->GetWindow(),"你确定要退出吗？","退出游戏",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}
