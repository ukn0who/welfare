/*********************************
	游戏程序头文件FighterPlane.h
*********************************/

#include "GameEngine.h"		//包含游戏引擎
#include "Sprite.h"			//包含游戏精灵
#include "SpriteManage.h"	//包含精灵管理类

#include "resource.h"		//包含资源文件

GameEngine *	g_pGE;		//全局引擎指针	

/*定义精灵实例*/
Sprite * g_pLoadScene;		//加载场景时的等待画面
Sprite * g_pBackGround;		//蓝色背景图像	

Sprite * g_pCloud[8];		//云彩图像组
Sprite * g_pFightPlane;		//用于绘制飞机图像
Sprite * g_pFightPlanePic[3];	//用于存储飞机图像

POINT g_ptCloud[8];			//云彩的左上角坐标
POINT g_ptFightPlane;		//飞机的左上角坐标

SpriteManage g_Sprm;		//精灵管理对象

int g_nScene;				//场景序号
BOOL g_bInitScene;			//场景初始化完成标志

BOOL InitScene_1(HWND hWnd);	//初始化场景1
BOOL PlayScene_1(HWND hWnd);	//运行场景1

