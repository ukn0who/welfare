/********************************
	游戏程序主文件war.cpp
********************************/
#include "war.h"
#include "stdio.h"	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  游戏初始化 */
BOOL GameInitialize(HINSTANCE hInstance)
{
	
	//创建引擎
	g_pGE=new GameEngine(hInstance,TEXT("War"),TEXT("War in Hurst"),
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏逻辑 */
void GameAction(HWND hWnd)
{
	//如果对话完成，且场景标题未完全显示
	if(g_nDialigIndex >=5 && g_nSceneTitleAlpha<255)
	{
		g_nSceneTitleAlpha+=5;	//场景标题透明度递增	
		g_nXFoeman+=20;			//敌人向右移
		g_nXGirl-=20;				//主角向左移
	}

	InvalidateRect(hWnd,NULL,FALSE);	//强制刷新窗口
	UpdateWindow(hWnd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  渲染游戏画面 ***/
void GamePaint(HDC hDC)
{
	//绘制背景和左上角的场景地点名称
	g_pSprBackGround->Draw(hDC,0,0);
	g_pSprSceneLoc->Draw(hDC,0,0,TRUE,RGB(0,0,0));

	//绘制主角与敌人
	g_pSprFoeman->Draw(hDC,g_nXFoeman,g_nYFoeman,TRUE,RGB(0,0,0));
	g_pSprGirl->Draw(hDC,g_nXGirl,g_nYGirl,TRUE,RGB(0,0,0));


	SetBkMode(hDC,TRANSPARENT);   		//设置背景模式为透明
	SetTextColor(hDC,RGB(255,255,0));	//设置文字颜色为黄色
	//判断对话是否完成
	if(g_nDialigIndex<5)
	{
		//绘制对话框与对话文字
		g_pSprDlg->DrawAlpha(hDC,150,450,180);
		DrawText(hDC,g_dlg[g_nDialigIndex].szName,-1,&g_rName,DT_LEFT);
		DrawText(hDC,g_dlg[g_nDialigIndex].szTalk,-1,&g_rTalk,DT_LEFT);
	}
	else
	{	//绘制场景标题
		g_pSprSceneTitle->DrawTransAlpha(hDC,0,0,800,600,140,30,g_nSceneTitleAlpha,RGB(0,0,0));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏开始 */
void GameStart(HWND hWnd)
{
	/* 设置鼠标指针*/
	long lCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,lCur);

	//载入游戏图像
	g_pSprBackGround=new Sprite(NULL,"resource\\background.bmp");
	g_pSprFoeman=new Sprite(NULL,"resource\\foeman.bmp");
	g_pSprGirl=new Sprite(NULL,"resource\\girl.bmp");
	g_pSprDlg=new Sprite(NULL,"resource\\dialog.bmp");
	g_pSprSceneTitle=new Sprite(NULL,"resource\\SceneTitle.bmp");
	g_pSprSceneLoc=new Sprite(NULL,"resource\\SceneLoc.bmp");

	//场景状态变量初始化
	g_nSceneTitleAlpha=0;	
	g_nDialigIndex=0;
	g_nXFoeman=600;
	g_nYFoeman=200;
	g_nXGirl=20;
	g_nYGirl=200;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏结束 */
void GameEnd()
{
	//释放位图资源
	delete	g_pSprBackGround;
	delete	g_pSprFoeman;
	delete	g_pSprGirl;
	delete	g_pSprDlg;
	delete	g_pSprSceneTitle;
	delete	g_pSprSceneLoc;

	delete g_pGE;	//清除游戏引擎指针	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏激活 */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏暂停 */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏窗口关闭 */
BOOL GameWindowClose(HWND hWnd)
{
	if(MessageBox(g_pGE->GetWindow(),"你确定要退出吗？","退出游戏",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 鼠标单击事件处理 */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	g_nDialigIndex++;		//对话序号递增
}