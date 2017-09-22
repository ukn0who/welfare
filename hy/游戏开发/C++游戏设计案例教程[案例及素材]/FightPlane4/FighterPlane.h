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


/*下面是新增加的类和变量*/

//Blast类用于播放爆炸动画
class Blast
{
protected:
	long m_nEndBlastTime;	//结束时间
	Sprite * m_sprBlast;	//爆炸动画
	BOOL	m_bFree;		//是否空闲

public:
	Blast()	
	{
		m_sprBlast=NULL;
		m_nEndBlastTime=0;
		m_bFree=TRUE;	
	};
	~Blast(){};
	
	//设置动画播放参数，spr为GIF图像爆炸动画精灵，rBlast指定动画显示位置，nDelay为动画显示时间
	void Set(Sprite * spr,RECT rBlast,long nDelay)
	{
		m_sprBlast=spr;
		m_nEndBlastTime=timeGetTime()+nDelay;
		m_sprBlast->SetDrawCxImageInfo(rBlast.left-50,rBlast.top-50,100,100);
		m_sprBlast->SetVisible(TRUE);
		m_bFree=FALSE;
	};

	BOOL Play()	//播放动画
	{
		if(!m_bFree && m_nEndBlastTime<=timeGetTime())
		{
			m_sprBlast->SetVisible(FALSE);
			m_sprBlast=NULL;
			m_nEndBlastTime=0;
			m_bFree=TRUE;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	BOOL IsFree()		//动画是否空闲（即未播放）
	{
		return (m_bFree );
	}
};

Blast g_Blast;				//爆炸播放动画对象
Sprite * g_pSprBlast;		//爆炸动画精灵

GamePhysics * g_pPhyShot;	//子弹物理运动对象
Sprite * g_pSprShot;		//子弹精灵

BOOL g_bShotEnemy;			//判断是否击中敌机
BOOL g_bShotFighter;		//判断玩家是否被撞

int g_nResult;				//玩家成绩
Sprite * g_pSprGameOver;	//游戏结束图像精灵