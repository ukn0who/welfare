/*********************************
	游戏音乐程序文件GameMusic.cpp
*********************************/

#include "GameMusic.h"
#pragma comment(lib,"winmm.lib")

int GameMusic::m_nNewID=1;		//初始化下一个可用编号

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameMusic::GameMusic()					//构造函数
{
	m_ID=m_nNewID;
	m_nNewID++;	
	m_nVolume=300;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameMusic::GameMusic(LPTSTR szMusicPath)	//带路径参数的构造函数
{

	m_ID=m_nNewID;
	m_nNewID++;	
	m_nVolume=300;
	if(strlen(szMusicPath)>0)	//判断路径不为空
	{
		Open(szMusicPath);	//打开音乐文件
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameMusic::~GameMusic()//析构函数
{
	Close();
}		

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::GetPlayState()		//获取音乐播放状态
{	
	char szStatus[20]={'\0'};
	char szCommand[50];
	
	sprintf(szCommand,"status MUSIC%d mode", m_ID);	//创建MCI命令字符串
	mciSendString(szCommand,szStatus,20,0);	//获取状态
	return(0==strcmp(szStatus,"playing"));	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::GetOpenState()		//获取音乐文件打开状态
{
	char szStatus[20]={'\0'};
	char szCommand[50];
	
	sprintf(szCommand,"status MUSIC%d mode", m_ID);	
	mciSendString(szCommand,szStatus,20,0);	

	return(0==strcmp(szStatus,"stopped")||0==strcmp(szStatus,"playing"));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::GetStopState()
{
	char szStatus[20]={'\0'};
	char szCommand[50];
	
	sprintf(szCommand,"status MUSIC%d mode", m_ID);	
	mciSendString(szCommand,szStatus,20,0);
	return(0==strcmp(szStatus,"stopped"));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GameMusic::GetVolume()			//获取音量大小
{
	return m_nVolume;	
}

void GameMusic::SetVolume(int nVolume)	//设置音量
{
	if(nVolume<0)
		nVolume=0;
	if(nVolume>1000)
		nVolume=1000;

	char szCommand[50];
	sprintf(szCommand,"Setaudio MUSIC%d volume to %d", m_ID,nVolume);	//创建MCI命令字符串
	mciSendString(szCommand,NULL,0,0);	//设置音量
	
	m_nVolume=nVolume;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameMusic::VolumeDown()		//减小音量
{
	SetVolume(m_nVolume-10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameMusic::VolumeUp()			//增大音量
{
	SetVolume(m_nVolume+10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::Open(LPTSTR szMusicPath)	//打开音乐文件
{

	if(strlen(szMusicPath)==0)
		return FALSE;
	
	if(GetPlayState()||GetStopState())	//如果已有音乐文件被打开，则先关闭
		Close();

	char szCommand[50];
	sprintf(szCommand,"OPEN %s ALIAS MUSIC%d", szMusicPath,m_ID);
	if(!mciSendString(szCommand,NULL,0,0))	//打开音乐文件
	{
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::Close()		//关闭音乐文件
{
	char szCommand[50];

	if(GetOpenState())
	{
		sprintf(szCommand,"CLOSE MUSIC%d", m_ID);
		if(!mciSendString(szCommand,NULL,0,0))
		{
			return TRUE;				
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::Play(int nVolume,BOOL bRepeat,BOOL bReStart) //播放音乐，可设置是否循环播放、重新播放
{
	char szCommand[50];	
	

	if(GetStopState()||bReStart)	//判断音乐在停止状态或要求重新播放时才播放
	{	
		if(bRepeat)
			sprintf(szCommand,"PLAY MUSIC%d FROM 0  repeat", m_ID);
		else
			sprintf(szCommand,"PLAY MUSIC%d FROM 0", m_ID);

		if(!mciSendString(szCommand,NULL,0,0))
		{
			SetVolume(nVolume);				
			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::Stop()		//停止播放
{
	char szCommand[50];
	if(GetPlayState())
	{	
		sprintf(szCommand,"STOP MUSIC%d", m_ID);
		if(!mciSendString(szCommand,NULL,0,0))
		{
			return TRUE;
		}
	}		
	return FALSE;
}	
