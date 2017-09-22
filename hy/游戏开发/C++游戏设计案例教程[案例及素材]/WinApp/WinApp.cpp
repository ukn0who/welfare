/********************
	WinApp.cpp
********************/

#include "windows.h"		//包含头文件windows.h,Windows程序包含该文件
	

#include "resource.h"		//包含资源头文件resource.h

/*函数声明*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);//声明消息处理函数
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);//声明程序入口函数

/*程序入口函数*/
int WINAPI WinMain(HINSTANCE hInstance,		//实例句柄
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdline,
				   int nCmdShow)
{
	WNDCLASS wcApp;			//定义窗口
	MSG msg;				//定义Windows消息
	HWND ghWnd=NULL;		//定义程序主窗口句柄
	char* szAppName="Windows API Application";	//程序名称
	char *szAppTitle="Windows API窗口程序";		//程序窗口标题

	//给窗口属性赋值
	wcApp.style=CS_HREDRAW;			//定义窗口风格
	wcApp.lpfnWndProc=WndProc;		//消息处理
	wcApp.cbWndExtra=0;		
	wcApp.cbClsExtra=0;
	wcApp.hInstance=hInstance;		//指定义窗口应用程序的句柄
	//加载图标资源
	wcApp.hIcon=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));	
	//加载光标资源
	wcApp.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));		
	wcApp.hbrBackground=(HBRUSH)COLOR_WINDOW;//设置窗口背景色
	wcApp.lpszMenuName=NULL;			//不设置窗口菜单
	wcApp.lpszClassName=szAppName;	//设置窗口类名

	RegisterClass(&wcApp);			//注册窗口

	//调用函数CreateWindow建立窗口
	ghWnd=CreateWindow(szAppName,				//注册窗口类名
						szAppTitle,			//设置窗口标题
						WS_OVERLAPPEDWINDOW,	//设置窗口风格
						100,			//设置窗口左上角X坐标		
						100,			//设置窗口左上角Y坐标	
						350,			//设置窗口宽度
						300,			//设置窗口高度
						NULL,		//父窗口句柄
						NULL,		//菜单的句柄
						hInstance,	//程序实例句柄
						NULL);	

	if(NULL==ghWnd)				//如果窗口建立失败则返回
		return 0;

	ShowWindow(ghWnd,nCmdShow);		//显示窗口
	UpdateWindow(ghWnd);			//更新窗口

	//创建消息循环
	while(GetMessage(&msg,NULL,0,0))	//接收消息
	{
		TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
		DispatchMessage(&msg);		//处理消息
	}
	return msg.wParam;
}

/*消息处理函数*/
LRESULT CALLBACK WndProc(HWND hwnd,		//窗口句柄
						 UINT message,	//消息标识
						 WPARAM wParam,	//消息参数
						 LPARAM lParam)	//消息参数
{	
	//定义信息字符串
	LPCSTR  lpszCreate ="收到WM_CREATE消息，建立窗口";	
	LPCSTR  lpszDestroy ="收到WM_DESTROY消息，窗口关闭";	
	LPCSTR  lpszCaption ="收到消息";				//消息对话框标题
	LPCSTR  lpszLBTN ="鼠标左键按下，收到WM_LBUTTONDOWN消息";
	LPCSTR  lpszExit ="你确定要退出吗？";

	//用开关语句对信息进行相应处理
	switch(message)		
	{
	case WM_CREATE:		//响应窗口建立消息
		//MessageBox( )函数弹出消息框
		MessageBox(GetFocus( ),lpszCreate,lpszCaption,MB_OK|MB_ICONEXCLAMATION);
		break;

	case WM_LBUTTONDOWN:	//响应鼠标左键按下消息
		MessageBox(GetFocus( ),lpszLBTN,lpszCaption,MB_OK|MB_ICONINFORMATION);
		break;

	case WM_KEYDOWN:						//键盘按键消息
		if(wParam==VK_ESCAPE)				//判断是否按下ESC键	
			SendMessage(hwnd,WM_CLOSE,NULL,NULL);	//发送窗口关闭消息
		break;

	case WM_CLOSE:					//窗口关闭消息
		if(MessageBox(NULL,lpszExit,lpszCaption,MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		{
			DestroyWindow(hwnd);	//发出销毁窗口消息
		}		
		break;

	case WM_DESTROY:			//响应销毁窗口消息

		PostQuitMessage(0);		//通知WINDOWS，线程已发出终止请求
		break;
	default:
		//没有其他消息时，Windows将调用此缺省函数进行处理
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return FALSE;
}
