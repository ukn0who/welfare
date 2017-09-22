/*********************************
	游戏程序头文件GameStart.h
*********************************/

#include "GameEngine.h"		//包含游戏引擎
#include "resource.h"		//包含资源文件

GameEngine *	g_pGE;		//全局引擎指针	

/* 在这里添加游戏程序中要使用的其他变量定义 */

long	g_lPreTime;			//记录上次游戏循环时间
int		g_nFrequency;		//记录游戏频率