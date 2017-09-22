/*********************************
	游戏程序头文件Cards.h
*********************************/

#include "GameEngine.h"	//包含游戏引擎
#include "resource.h"		//包含资源文件

GameEngine *	g_pGE;		//全局引擎指针	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*定义游戏中用到的常量*/
//定义卡片选择状态常量
enum SELECTSTATE{INITSELECT=0,	//选择状态初始化
				NOSELECT,		//未选择
				SELECTED,		//已选择
				SELECTOK};		//正确配对


const	int NULLPATTERN=-1;		//定义空图案

const int	CARDWIDTH=100;		//设置卡片大小
const int	CARDHEIGHT=100;
const int	ROWS=3;				//设置卡片行、列数
const int	COLS=4;
const int	ROWSPACE=20;		//设置卡片行、列间距
const int	COLSPACE=50;
const int	CARSTARTX=120;		//设置绘制卡片时左上角起始位置		
const int	CARSTARTY=200;

/*定义游戏全局变量*/
char *  g_strTitle="卡片对对碰";	//游戏标题

int		g_nCardPattern[ROWS][COLS];	//卡片图案数组
RECT	g_rCardRect[ROWS][COLS];	//卡片位置矩形数组
SELECTSTATE	g_nCardState[ROWS][COLS];	//卡片状态数组

int		g_nSelectRow1,g_nSelectRow2,g_nSelectCol1,g_nSelectCol2;	//单击选择卡片行列号
int		g_nSelected;			//已选择正确的图案对数

RECT	g_rTimeBarFrame;		//时间条边框矩形大小
int		g_nTimeBarLength;		//时间条长度
int		g_nTimeCount;			//规定的时间长度
int		g_nStartTime;			//起始时间
long	g_nTimeDelayStart;		//延时启动时间
