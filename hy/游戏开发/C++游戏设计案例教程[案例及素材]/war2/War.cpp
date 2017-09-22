/********************************
	游戏程序主文件war.cpp
********************************/
#include "war.h"
//#include "stdio.h"	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  游戏初始化 */
BOOL GameInitialize(HINSTANCE hInstance)
{
	
	//创建引擎
	g_pGE=new GameEngine(hInstance,TEXT("War"),TEXT("War in Hurst"),
			IDI_BIGICON,IDI_SMALLICON,FALSE,32,800,600);
	if(g_pGE==NULL)
		return FALSE;

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏开始 */
void GameStart(HWND hWnd)
{
	/* 设置鼠标指针*/
	long lCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,lCur);

	g_pLoadScene=new Sprite(NULL,"resource\\LoadScene.bmp");

	g_nScene=1;			//设置场景标志
	g_bInitScene=FALSE;	//设置场景初始化标志

	InitScene_1(hWnd);	//初始化场景1

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 游戏逻辑 */
void GameAction(HWND hWnd)
{
	if(g_bInitScene)	//判断场景初始化是否完成
	{
		//通过场景标志来调用相关场景
		switch(g_nScene)	
		{
		case 1:
			if(PlayScene_1(hWnd))		//执行场景1游戏逻辑，通过返回值判断是否执行完毕
			{
				g_bInitScene=FALSE;	//设置场景初始化标志
				InitScene_2(hWnd);	//初始化场景2;
			}
			break;
		case 2:
			PlayScene_2(hWnd); 		//执行场景2游戏逻辑
			break;
		}
	}


	InvalidateRect(hWnd,NULL,FALSE);	//强制刷新窗口
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景1初始化 */
BOOL InitScene_1(HWND hWnd)
{
	//载入游戏图像
	g_pSprBackGround=new Sprite(NULL,"resource\\background.bmp");
	g_pSprFoeman=new Sprite(NULL,"resource\\foeman.bmp");
	g_pSprGirl=new Sprite(NULL,"resource\\girl.bmp");
	g_pSprDlgBG=new Sprite(NULL,"resource\\dialog.bmp");
	g_pSprSceneTitle=new Sprite(NULL,"resource\\SceneTitle.bmp");
	g_pSprSceneLoc=new Sprite(NULL,"resource\\SceneLoc.bmp");

	g_pSprDlg=new Sprite();	//位图为空的精灵，用于储存对话图像
	
	//将精灵添加到精灵管理对象，并设置相应Z顺序
	g_Sprm.AddSprite(g_pSprBackGround,0);
	g_Sprm.AddSprite(g_pSprSceneTitle,1);
	g_Sprm.AddSprite(g_pSprSceneLoc,1);
	g_Sprm.AddSprite(g_pSprGirl,2);
	g_Sprm.AddSprite(g_pSprFoeman,2);
	g_Sprm.AddSprite(g_pSprDlg,3);


	//场景状态变量初始化
	g_nSceneTitleAlpha=0;	
	g_nDialigIndex=0;
	g_nXFoeman=600;
	g_nYFoeman=200;
	g_nXGirl=20;
	g_nYGirl=200;

	g_bInitScene=TRUE;	//场景初始化完成
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景1运行 */
BOOL PlayScene_1(HWND hWnd)
{
	//设置精灵对象绘图信息
	g_pSprFoeman->SetDrawInfo(g_nXFoeman,g_nYFoeman,TRUE);
	g_pSprGirl->SetDrawInfo(g_nXGirl,g_nYGirl,TRUE);
	g_pSprBackGround->SetDrawInfo(0,0,TRUE);
	g_pSprDlg->SetDrawAlphaInfo(150,450,192);
	g_pSprSceneTitle->SetDrawTransAlphaInfo(0,0,g_pGE->GetWidth(),g_pGE->GetHeight(),140,30,g_nSceneTitleAlpha,RGB(0,0,0));
	g_pSprSceneLoc->SetDrawInfo(10,10,TRUE);


	//判断对话是否完成
	if(g_nDialigIndex<5)
	{
		RECT rTalk={20,40,460,120};
		RECT rName={20,10,460,30};
		HDC hDC=GetDC(hWnd);
		//调用DrawDlgToBmp()将对话文字绘制到对话框，再将位图返回作为g_pSprDlg的位图
		g_pSprDlg->SetBitmap(DrawDlgToBmp(hDC,g_pSprDlgBG,g_dlg[g_nDialigIndex].szName,rName,g_dlg[g_nDialigIndex].szTalk,rTalk));
		ReleaseDC(hWnd,hDC);
	}
	else if(g_nSceneTitleAlpha<255)
	{
		g_Sprm.SetSpriteVisible(g_pSprDlg,FALSE);	//设置对话框为不可见

		g_nXFoeman+=20;			//敌人向右移
		g_nXGirl-=20;			//主角向左移

		//若已移出场景，则设置为不可见，即不再绘制图像
		if(g_nXFoeman>g_pGE->GetWidth()) 
			g_Sprm.SetSpriteVisible(g_pSprFoeman,FALSE);	
		if(g_nXGirl+g_pSprGirl->GetWidth()<0) 
			g_Sprm.SetSpriteVisible(g_pSprGirl,FALSE);
		
		g_nSceneTitleAlpha+=5;	//场景标题透明度递增
	}


	//如果场景标题显示完成，则表示场景1结束，设置场景标志g_nScene为2
	if(g_nSceneTitleAlpha>=255)
	{

		g_Sprm.Release(TRUE);		//删除精灵图像

		g_nScene=2;

		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景2初始化 */
BOOL InitScene_2(HWND hWnd)
{
	//载入背景
	g_pSprBackGround=new Sprite(NULL,"resource\\background.bmp");

	 g_pSprWarBar=new Sprite(NULL,"resource\\WarBarBottomBG.bmp");

	//载入动画图像，并初始化动画参数
	g_pSprFoemanAnima=new Sprite(NULL,"resource\\FoemanAnima.bmp");
	g_pSprFoemanAnima->InitAnima(1,6,150);

	g_pSprGirlAnima=new Sprite(NULL,"resource\\GirlAnima.bmp");
	g_pSprGirlAnima->InitAnima(1,6,150);

	//将精灵添加到精灵管理对象
	g_Sprm.AddSprite(g_pSprBackGround,0);
	g_Sprm.AddSprite(g_pSprGirlAnima,3);
	g_Sprm.AddSprite(g_pSprFoemanAnima,3);
	g_Sprm.AddSprite(g_pSprWarBar,1);

	g_bInitScene=TRUE;	//设置场景初始化标志
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景2运行 */
BOOL PlayScene_2(HWND hWnd)
{
	//设置精灵对象信息
	g_pSprBackGround->SetDrawInfo(0,0,TRUE);
	g_pSprFoemanAnima->SetDrawAnimaInfo(100,240,0,TRUE);
	g_pSprGirlAnima->SetDrawAnimaInfo(400,280,0,TRUE);
	g_pSprWarBar->SetDrawInfo(0,445);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//绘制精灵中的对话框图像与对话文字到位图，并返回位图句柄
HBITMAP  DrawDlgToBmp(HDC hDC,Sprite * pSprDlgBG,LPTSTR szName,RECT & rName,LPTSTR szTalk,RECT & rTalk)
{

		HDC hMemDC=CreateCompatibleDC(hDC);	//创建内存兼容设备环境
		HBITMAP hbmTmp=CreateCompatibleBitmap(hDC, pSprDlgBG->GetWidth(), pSprDlgBG->GetHeight());			//创建兼容位图，用于绘制对话框

		HBITMAP hbmOld=(HBITMAP)SelectObject(hMemDC,hbmTmp);  //选入hbmTmp
		//将原来无字的对话框绘制到hMemDC，实际上就是绘制到hbmTmp上
		g_pSprDlgBG->Draw(hMemDC,0,0);
		//将对话文本绘制到hMemDC
		SetBkMode(hMemDC,TRANSPARENT);   	//设置背景模式为透明
		SetTextColor(hMemDC,RGB(255,255,0));		//设置文字颜色为黄色
		DrawText(hMemDC,szName,-1,&rName,DT_LEFT);		
		DrawText(hMemDC,szTalk,-1,&rTalk,DT_LEFT);

		SelectObject(hMemDC,hbmOld);	//替出hbmTmp
		DeleteDC(hMemDC);
		return hbmTmp;		//返回绘制对话框和文本后的图像
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*  渲染游戏画面 ***/
void GamePaint(HDC hDC)
{
	if(!g_bInitScene)	//判断场景初始化是否完成
		g_pLoadScene->Draw(hDC,0,0);	//绘制加载场景时的等待画面
	else
		g_Sprm.Draw(hDC);				//绘制场景
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 游戏结束 */
void GameEnd()
{
	g_Sprm.Release(TRUE);
	delete g_pGE;	//清除游戏引擎指针	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏激活 */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏暂停 */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏窗口关闭 */
BOOL GameWindowClose(HWND hWnd)
{
	if(MessageBox(g_pGE->GetWindow(),"你确定要退出吗？","退出游戏",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 鼠标单击事件处理 */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	g_nDialigIndex++;		//对话序号递增
}

