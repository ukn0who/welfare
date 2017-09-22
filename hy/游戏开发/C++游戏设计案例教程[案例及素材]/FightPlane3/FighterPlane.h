/*********************************
	游戏程序头文件FighterPlane.h
*********************************/

#include "GameEngine.h"		//包含游戏引擎
#include "Sprite.h"			//包含游戏精灵
#include "SpriteManage.h"	//包含精灵管理类
#include "GameMusic.h"		//包含游戏音乐
#include "GamePhysics.h"	//包含游戏物理动作

#include "resource.h"		//包含资源文件

GameEngine *	g_pGE;		//全局引擎指针	

/*定义精灵实例*/
Sprite * g_pSprLoadScene;		//加载场景时的等待画面
Sprite * g_pSprBackGround;		//蓝色背景图像	

Sprite * g_pSprCloud[8];		//云彩图像组
Sprite * g_pSprFightPlane;		//用于绘制飞机图像
Sprite * g_pSprFightPlanePic[3];	//用于存储飞机图像

POINT g_ptCloud[8];			//云彩的左上角坐标

SpriteManage g_Sprm;		//精灵管理对象

int g_nScene;				//场景序号
BOOL g_bInitScene;			//场景初始化完成标志

BOOL InitScene_1(HWND hWnd);	//初始化场景1
BOOL PlayScene_1(HWND hWnd);	//运行场景1

GameMusic * g_pMscBGM;			//背景音乐
GameMusic * g_pMscPlaneFly;		//飞机飞行音效

Sprite * g_pSprEnemy[4];			//敌机图像	

GamePhysics * g_pPhyFight;		//游戏者飞机的物理动作
GamePhysics * g_pPhyEnemy[4];	//敌机的物理动作

//声明SetEnemyInfo()方法，用于绑定精灵对象和物理运动对象
void SetEnemyInfo(Sprite * spr,GamePhysics * phy,int nType);

