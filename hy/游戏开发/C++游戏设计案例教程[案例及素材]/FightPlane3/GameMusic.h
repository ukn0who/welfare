/*********************************
	游戏音乐头文件GameMusic.h
*********************************/

#ifndef DEF_GAMEMUSIC		//条件编译，目的是防止文件被重复编译

#define DEF_GAMEMUSIC  1

#include "windows.h"
#include "stdio.h"
#include "mmsystem.h"		//包含文件

/*游戏音乐类*/
class GameMusic
{
protected:
	int		m_ID;				//编号
	static int m_nNewID;		//下一个可用编号

	int		m_nVolume;			//音量(0~1000)

public:
	GameMusic();					//构造函数

	GameMusic(LPTSTR szMusicPath);	//带路径参数的构造函数

	~GameMusic();				//析构函数

	BOOL GetPlayState();		//获取音乐播放状态

	BOOL GetOpenState();		//获取音乐文件打开状态

	BOOL GetStopState();		//获取音乐停止状态

	int GetVolume();			//获取音量大小

	void SetVolume(int nVolume);	//设置音量

	void VolumeDown();			//减小音量

	void VolumeUp();			//增大音量
	
	BOOL Open(LPTSTR szMusicPath);	//打开音乐文件

	BOOL Close();				//关闭音乐文件

	BOOL Stop();				//停止播放

	BOOL Play(int nVolume=300,BOOL bRepeat=FALSE,BOOL bReStart=TRUE); //播放音乐，可设置是否循环播放、重新开始

};

#endif

