/********************************
	游戏程序主文件FighterPlane.cpp
********************************/
#include "FighterPlane.h"

#include <time.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  游戏初始化 */
BOOL GameInitialize(HINSTANCE hInstance)
{
	
	//创建引擎
	g_pGE=new GameEngine(hInstance,TEXT("Fight Plane"),TEXT("云中战机"),
			IDI_BIGICON,IDI_SMALLICON,FALSE,32,450,600);
	if(g_pGE==NULL)
		return FALSE;

	//初始化引擎参数
	g_pGE->SetFrameDelay(30) ;		//设置游戏帧延时为30毫秒
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

	g_pSprLoadScene=new Sprite(NULL,"resource\\LoadScene.bmp");


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
		PlayScene_1(hWnd);
	}
	InvalidateRect(hWnd,NULL,FALSE);	//强制刷新窗口
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景1初始化 */
BOOL InitScene_1(HWND hWnd)
{
	//载入游戏图像
	g_pSprCloud[0]=new Sprite("resource\\cloud_1.png");	//云彩
	g_pSprCloud[1]=new Sprite("resource\\cloud_2.png");
	g_pSprCloud[2]=new Sprite("resource\\cloud_3.png");
	g_pSprCloud[3]=new Sprite("resource\\cloud_4.png");
	g_pSprCloud[4]=new Sprite("resource\\cloud_5.png");
	g_pSprCloud[5]=new Sprite("resource\\cloud_6.png");
	g_pSprCloud[6]=new Sprite("resource\\cloud_7.png");
	g_pSprCloud[7]=new Sprite("resource\\cloud_8.png");


	g_pSprFightPlanePic[0]=new Sprite("resource\\FighterPlane.png");//存储飞机图像的精灵
	g_pSprFightPlanePic[1]=new Sprite("resource\\FighterPlaneL.png");
	g_pSprFightPlanePic[2]=new Sprite("resource\\FighterPlaneR.png");

	g_pSprFightPlane=new Sprite();			//创建绘制飞机的精灵
	g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage()); //赋予图像


	//使用临时DC创建蓝色背景图像
	HDC hDCTmp=GetDC(hWnd);
	g_pSprBackGround=new Sprite(hDCTmp,g_pGE->GetWidth(),g_pGE->GetHeight(),RGB(40,80,160));
	ReleaseDC(hWnd,hDCTmp);

	g_pSprBackGround->SetDrawInfo(0,0);
	g_Sprm.AddSprite(g_pSprBackGround,0);


	//将精灵添加到精灵管理对象，并设置相应Z顺序	
	g_Sprm.AddSprite(g_pSprCloud[0],1);
	g_Sprm.AddSprite(g_pSprCloud[1],1);
	g_Sprm.AddSprite(g_pSprCloud[2],1);
	g_Sprm.AddSprite(g_pSprCloud[3],1);
	g_Sprm.AddSprite(g_pSprCloud[4],1);
	g_Sprm.AddSprite(g_pSprCloud[5],1);
	g_Sprm.AddSprite(g_pSprCloud[6],1);
	g_Sprm.AddSprite(g_pSprCloud[7],1);

	g_Sprm.AddSprite(g_pSprFightPlane,3);


	//场景状态变量初始化
	srand((unsigned)time(NULL));	// 初始化随机数种子
	for(int i=0;i<8;i++)			//在循环中随机设置云彩的位置
	{
		g_ptCloud[i].x=rand()%g_pGE->GetWidth();
		g_ptCloud[i].y=rand()%g_pGE->GetHeight();
	}
	
	//创建游戏音乐对象并打开文件
	g_pMscPlaneFly=new GameMusic("resource\\fly.wav");
	g_pMscBGM=new GameMusic("resource\\bgm.mp3");
	g_pMscBGM->Play(300,TRUE);	//重复播放音乐	


	/*新增敌机精灵图像和物理运动对象的相关内容*/

	//敌机精灵图像
	g_pSprEnemy[0]=new Sprite("resource\\enemy1.png");
	g_pSprEnemy[1]=new Sprite("resource\\enemy2.png");
	g_pSprEnemy[2]=new Sprite("resource\\enemy3.png");
	g_pSprEnemy[3]=new Sprite("resource\\enemy4.png");

	//添加到精灵管理对象
	g_Sprm.AddSprite(g_pSprEnemy[0],3);
	g_Sprm.AddSprite(g_pSprEnemy[1],3);
	g_Sprm.AddSprite(g_pSprEnemy[2],3);
	g_Sprm.AddSprite(g_pSprEnemy[3],3);

	//创建敌机物理运动对象
	g_pPhyEnemy[0]=new GamePhysics();
	g_pPhyEnemy[1]=new GamePhysics();
	g_pPhyEnemy[2]=new GamePhysics();
	g_pPhyEnemy[3]=new GamePhysics();

	//创建游戏者飞机物理运动对象
	RECT rObject={200,400,300,500};
	RECT rBound={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
	POINTF ptFocus={0,0};
	POINTF ptVelo={0,5};
	POINTF ptAccelerate={0,0};
	POINTF ptDes={300,300};
	g_pPhyFight=new GamePhysics(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);

	g_bInitScene=TRUE;	//场景初始化完成
	
	return TRUE;
}

/*将一个精灵对象spr与一个物理动作对象phy绑定，按nType指定的类型运动*/
void SetEnemyInfo(Sprite * spr,GamePhysics * phy,int nType)
{
	srand((unsigned)time(NULL));	// 初始化随机数种子
	int x=rand()%(g_pGE->GetWidth()-spr->GetWidth());	//计算横坐标
	//设计路径
	POINTF ptPath[8]={{x+100,-spr->GetHeight()},
					{x+100,100},
					{x+200,100},
					{x-100,100}, 
					{x-100,200},
					{x+100,200},
					{x+100,300},
					{x,g_pGE->GetHeight()}};

	//判断物理对象是否在移动，如未移动，则重新设置物理对象参数
	if( phy->GetPathArrive()&&nType==2 ||! phy->GetMoveState()&&nType==1)
	{
		RECT rObject={x,-spr->GetHeight(),x+spr->GetWidth(),0};
		RECT rBound={0,-spr->GetHeight(),g_pGE->GetWidth(),g_pGE->GetHeight()+spr->GetHeight()};
		POINTF ptFocus={0,0};
		POINTF ptVelo={0,rand()%9+1};
		POINTF ptAccelerate={0,0};
		POINTF ptDes={x,g_pGE->GetHeight()};
		phy->SetObject(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,TRUE);
	}
	
	//按指定的运动类型移动
	switch(nType)
	{
	case 1:
		phy->MoveToDes();
		break;
	case 2:
		phy->MoveAlongPath(ptPath,8);
		break;

	}

	spr->SetVisible( phy->GetVisible());
		
	//设置精灵绘图参数
	if(spr->GetVisible())
		spr->SetDrawCxImageInfo(phy->GetLeftTop().x,phy->GetLeftTop().y);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景1运行 */
BOOL PlayScene_1(HWND hWnd)
{
	//设置精灵对象绘图信息

	for(int i=0;i<8;i++)	//循环设置云彩位置和Z顺序
	{
		//判断云彩是否到达画面底部
		if(g_ptCloud[i].y>g_pGE->GetHeight())	
		{
			//如果云彩到达画面底部，则设置云彩的垂直位置到画面顶端，水平位置随机设置
			g_ptCloud[i].x=rand()%g_pGE->GetWidth()-g_pGE->GetWidth()/2;
			g_ptCloud[i].y=-(g_pSprCloud[i]->GetHeight());
			
			//随机设置云彩在前景云层还是在背景云层中
			if(rand()%2)
				g_Sprm.SetZOrder(g_pSprCloud[i],1);
			else
				g_Sprm.SetZOrder(g_pSprCloud[i],4);				
		}
		else
		{
			//判断云彩是在前景云层还是在背景云层
			if(g_pSprCloud[i]->GetZOrder()<4)	
				g_ptCloud[i].y+=2;		//设置背景云层中的云彩向下移动2像素
			else
				g_ptCloud[i].y+=3;		//设置前景云层中的云彩向下移动3像素
		}
		//设置云彩绘图参数
		g_pSprCloud[i]->SetDrawCxImageInfo(g_ptCloud[i].x,g_ptCloud[i].y);
	}

	//将精灵与物理对象绑定，按指定的动作运动
	SetEnemyInfo(g_pSprEnemy[0],g_pPhyEnemy[0],2);
	SetEnemyInfo(g_pSprEnemy[1],g_pPhyEnemy[1],2);
	SetEnemyInfo(g_pSprEnemy[2],g_pPhyEnemy[2],1);
	SetEnemyInfo(g_pSprEnemy[3],g_pPhyEnemy[3],1);


	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*  渲染游戏画面 ***/
void GamePaint(HDC hDC)
{
	if(!g_bInitScene)		//判断场景初始化是否完成
		g_pSprLoadScene->Draw(hDC,0,0);	//绘制加载场景时的等待画面
	else
		g_Sprm.Draw(hDC);				//绘制场景
}

/* 游戏结束 */
void GameEnd()
{
	delete g_pMscBGM;
	delete g_pMscPlaneFly;
	delete[] (*g_pPhyEnemy); 
	delete  g_pPhyFight;
	g_Sprm.Release(TRUE);
	delete	g_pSprLoadScene;
	delete	g_pGE;	//清除游戏引擎指针	
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


/*键盘消息处理*/
void KeyEvent(HWND hWnd)
{
	if(GetAsyncKeyState(VK_UP)<0 )		//判断上方向键是否按下
	{
		g_pPhyFight->MoveDirect(DI_UP);	//游戏者飞机物理运动对象向上移动
		g_pPhyFight->CheckErr(TRUE);	//检查是否超出焦点框
		//通过物理运动对象设置飞机图像绘图参数
		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x,g_pPhyFight->GetLeftTop().y,100,100);
		//设置飞机图像
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//播放飞机飞行音效
	}
	else 	if(GetAsyncKeyState(VK_DOWN)<0 )	//判断下方向键是否按下
	{
		g_pPhyFight->MoveDirect(DI_DOWN);		//游戏者飞机物理运动对象向下移动
		g_pPhyFight->CheckErr(TRUE);		

		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x,g_pPhyFight->GetLeftTop().y,100,100);
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
	}
	else 	if(GetAsyncKeyState(VK_LEFT)<0  )	//判断左方向键是否按下
	{
		g_pPhyFight->MoveDirect(DI_LEFT);		//游戏者飞机物理运动对象向左移动
		g_pPhyFight->CheckErr(TRUE);	

		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x+10,g_pPhyFight->GetLeftTop().y,80,100);
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[1]->GetCxImage());
		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//播放飞机飞行音效
	}
	else 	if(GetAsyncKeyState(VK_RIGHT)<0  )	//判断右方向键是否按下
	{
		g_pPhyFight->MoveDirect(DI_RIGHT);		//游戏者飞机物理运动对象向右移动
		g_pPhyFight->CheckErr(TRUE);	

		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x+10,g_pPhyFight->GetLeftTop().y,80,100);
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[2]->GetCxImage());
		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//播放飞机飞行音效
	}
	else if(GetAsyncKeyState(VK_PRIOR)<0)	//按下PageUp键，背景音乐音量增大
		g_pMscBGM->VolumeUp();
	else if(GetAsyncKeyState(VK_NEXT)<0)	//按下PageDown键，背景音乐音量减小
		g_pMscBGM->VolumeDown();
	else if(GetAsyncKeyState(VK_HOME )<0)	//按下Home键，重新播放背景音乐
		g_pMscBGM->Play(300,TRUE);
	else if(GetAsyncKeyState(VK_END )<0)	//按下End键，停止播放背景音乐
		g_pMscBGM->Stop();
	else if(GetAsyncKeyState(VK_ESCAPE)<0 )	//判断ESC键是否按下
		SendMessage(hWnd,WM_CLOSE,0,0);     //退出程序

	else			//如果以上按键都没有被按下
	{
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x,g_pPhyFight->GetLeftTop().y,100,100);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*以下是鼠标消息处理函数，本例中未使用，内容为空*/
//鼠标左键按下消息处理函数
void MouseLButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
	
}

//鼠标左键弹起消息处理函数
void MouseLButtonUp(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//鼠标左键双击消息处理函数
void MouseDoubleClick(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//鼠标右键按下消息处理函数
void MouseRButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//鼠标移动消息处理函数
void MouseVove(HWND hWnd,int x,int y,WPARAM wParam)
{
}

