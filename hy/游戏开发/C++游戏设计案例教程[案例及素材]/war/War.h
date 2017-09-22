/*********************************
	游戏程序头文件War.h
*********************************/

#include "GameEngine.h"		//包含游戏引擎
#include "Sprite.h"			//包含游戏精灵

#include "resource.h"		//包含资源文件

GameEngine *	g_pGE;		//全局引擎指针	

///////////////////////////////////////////////////////////////////////////////////

//定义对话结构
typedef struct tgaDIALOG{
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

int g_nDialigIndex;	//对话索引	

/*定义精灵实例*/
Sprite * g_pSprBackGround;
Sprite * g_pSprFoeman;
Sprite * g_pSprGirl;
Sprite * g_pSprDlg;
Sprite * g_pSprSceneTitle;
Sprite * g_pSprSceneLoc;


//对话时绘制人名和内容的位置矩形
RECT g_rTalk={170,490,700,580};
RECT g_rName={170,460,220,500};

//场景标题的透明度
int g_nSceneTitleAlpha;

//人物的位置坐标变量
int g_nXFoeman,g_nYFoeman,g_nXGirl,g_nYGirl;