/********************************
	游戏程序主文件GameStart.cpp
********************************/
#include "GameStart.h"
#include "stdio.h"	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  游戏初始化 */
BOOL GameInitialize(HINSTANCE hInstance)
{
	/* 在这里构造游戏引擎实例，并设置初始化引擎参数 */
	
	/* 下面代码不是游戏引擎本身所有的，仅用于演示，在游戏设计时由开发者具体实现*/
	//创建游戏引擎
	g_pGE=new GameEngine(hInstance,TEXT("GameStart"),TEXT("GameStart"),
		IDI_BIGICON,IDI_SMALLICON,	TRUE,32,800,600);
	if(g_pGE==NULL)
		return false;

	//初始化引擎参数
	g_pGE->SetFrameDelay(15) ;		//设置游戏帧延时为15毫秒
	g_pGE->SetPause(false);			//设置暂停状态为false
	g_pGE->CreateGameWindow();		//创建游戏窗口

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏逻辑 */
void GameAction(HWND hWnd)
{
	/* 在这里添加游戏逻辑相关代码 */
	
	long nTick=timeGetTime();	//获取当前时间
	g_nFrequency=1000/(nTick-g_lPreTime);	//计算游戏频率
	g_lPreTime=nTick;			//记录当前时间

	InvalidateRect(hWnd,NULL,FALSE);	//强制刷新窗口
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  渲染游戏画面 */
void GamePaint(HDC hDC)
{
	/* 在这里添加游戏画面渲染的代码 */
	
	/* 下面的绘图和字符串输出代码不是游戏引擎的内容，只是为了演示*/
	HDC  dc=CreateCompatibleDC(hDC);	//创建兼容设备环境

	//载入位图
	HBITMAP	hbm=(HBITMAP)LoadImage(g_pGE->GetInstance(),MAKEINTRESOURCE (IDB_BKBITMAP),IMAGE_BITMAP,800,600,LR_DEFAULTCOLOR);
	SelectObject(dc,hbm);	//将位图选入设备环境
	
	//绘制图像
	BitBlt(hDC,0,0,800,600,dc,0,0,SRCCOPY);

	//清理位图对象
	DeleteObject(SelectObject(dc, hbm));
	DeleteObject(hbm);
	
	SetBkMode(hDC,TRANSPARENT);  //设置背景模式为透明
	SetTextColor(hDC,RGB(255,255,0));	//设置文字颜色为黄色
	char str[100];						//定义临时字符串空间
	int nGameTime=timeGetTime()-g_pGE->GetStartTime();//计算游戏运行时间
	int nBits=GetDeviceCaps(hDC,BITSPIXEL);			//获取屏幕颜色位数
	int nScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//获取屏幕像素宽度
	int nScreenHeight=GetSystemMetrics(SM_CYSCREEN);	//获取屏幕像素高度
	
	//格式化字符串，将结果存入str
	sprintf(str,"游戏运行时间：%d ms    帧频：%d    显示模式：%d bit,%d*%d",nGameTime, g_nFrequency, nBits,nScreenWidth,nScreenHeight); 
	TextOut(hDC,10,10,str,strlen(str));	//输出字符串

	// 清理兼容设备环境
	DeleteDC(dc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏开始 */
void GameStart(HWND hWnd)
{
	/* 在这里添加游戏开始时的初始化代码 */

	/* 设置鼠标指针，这不是引擎必须的 */
	long nCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,nCur);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏结束 */
void GameEnd()
{
	/* 在这里添加释放资源的相关代码*/

	delete g_pGE;		//清除游戏引擎指针	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏激活 */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	

	/* 在这里添加具体的游戏激活事件处理代码 */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏暂停 */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);

	/* 在这里添加具体的游戏暂停事件处理代码 */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏窗口关闭 */
BOOL GameWindowClose(HWND hWnd)
{
	/* 游戏窗口关闭前的处理代码 */

	/* 调出消息对话框，征询是否结束程序。
	这不是引擎必须的，可以在游戏设计中改为设计者自己的代码*/
	if(MessageBox(g_pGE->GetWindow(),"你确定要退出吗？","退出游戏",MB_YESNO|MB_DEFBUTTON2 | MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 鼠标单击事件处理 */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	/* 在这里添加具体的鼠标单击事件处理代码 */
}
