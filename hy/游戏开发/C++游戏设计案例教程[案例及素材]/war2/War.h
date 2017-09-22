/*********************************
	游戏程序头文件War.h
*********************************/

#include "GameEngine.h"		//包含游戏引擎
#include "Sprite.h"			//包含游戏精灵
#include "SpriteManage.h"	//包含精灵管理类

#include "resource.h"		//包含资源文件

GameEngine *	g_pGE;		//全局引擎指针	

//定义对话结构
typedef struct tagDIALOG{
	LPTSTR	szName;		//人物
	LPTSTR	szTalk;		//谈话内容
} DIALOG;

//定义对话数组
DIALOG g_dlg[5]={{"队长","什么人?\n站住!\n这里已经被封锁了，不准通过!"},
				{"仙蒂","啊呀呀....\n不要这么凶嘛，人家只是出来打酱油的。"},
				{"队长","打酱油?\n为什么没带瓶?!\n还拿着根棍子?"},
				{"仙蒂","我买袋装的，不行吗?\n棍子是用来......"},
				{"队长","还敢狡辩!\n分明就是间谍!\n来人,给我拿下!"}
				};
int g_nDialigIndex;

/*定义精灵实例*/
Sprite * g_pSprBackGround;
Sprite * g_pSprFoeman;
Sprite * g_pSprGirl;
Sprite * g_pSprDlg;
Sprite * g_pSprDlgBG;
Sprite * g_pSprSceneTitle;
Sprite * g_pSprSceneLoc;
Sprite * g_pSprWarBar;
Sprite * g_pLoadScene;			//加载场景时的等待画面
Sprite * g_pSprGirlAnima;		//动画精灵
Sprite * g_pSprFoemanAnima;		//动画精灵

SpriteManage g_Sprm;			//精灵管理对象


//场景标题的透明度
int g_nSceneTitleAlpha;

//人物的位置坐标变量
int g_nXFoeman,g_nYFoeman,g_nXGirl,g_nYGirl;

int g_nScene;			//场景序号
BOOL g_bInitScene;		//场景初始化完成标志

BOOL InitScene_1(HWND hWnd);		//初始化场景1
BOOL PlayScene_1(HWND hWnd);		//运行场景1

BOOL InitScene_2(HWND hWnd);		//初始化场景2
BOOL PlayScene_2(HWND hWnd);		//运行场景2

//绘制精灵中的对话框图像与对话文字到位图中指定的矩形区域，并返回位图句柄
HBITMAP  DrawDlgToBmp(HDC hDC,Sprite * pSprDlgBG,LPTSTR szName,RECT & rName,LPTSTR szTalk,RECT & rTalk);


