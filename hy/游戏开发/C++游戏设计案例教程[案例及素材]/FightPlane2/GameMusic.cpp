/*********************************
	��Ϸ���ֳ����ļ�GameMusic.cpp
*********************************/

#include "GameMusic.h"
#pragma comment(lib,"winmm.lib")

int GameMusic::m_nNewID=1;		//��ʼ����һ�����ñ��

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameMusic::GameMusic()					//���캯��
{
	m_ID=m_nNewID;
	m_nNewID++;	
	m_nVolume=300;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameMusic::GameMusic(LPTSTR szMusicPath)	//��·�������Ĺ��캯��
{

	m_ID=m_nNewID;
	m_nNewID++;	
	m_nVolume=300;
	if(strlen(szMusicPath)>0)	//�ж�·����Ϊ��
	{
		Open(szMusicPath);	//�������ļ�
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameMusic::~GameMusic()//��������
{
	Close();
}		

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::GetPlayState()		//��ȡ���ֲ���״̬
{	
	char szStatus[20]={'\0'};
	char szCommand[50];
	
	sprintf(szCommand,"status MUSIC%d mode", m_ID);	//����MCI�����ַ���
	mciSendString(szCommand,szStatus,20,0);	//��ȡ״̬
	return(0==strcmp(szStatus,"playing"));	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::GetOpenState()		//��ȡ�����ļ���״̬
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

int GameMusic::GetVolume()			//��ȡ������С
{
	return m_nVolume;	
}

void GameMusic::SetVolume(int nVolume)	//��������
{
	if(nVolume<0)
		nVolume=0;
	if(nVolume>1000)
		nVolume=1000;

	char szCommand[50];
	sprintf(szCommand,"Setaudio MUSIC%d volume to %d", m_ID,nVolume);	//����MCI�����ַ���
	mciSendString(szCommand,NULL,0,0);	//��������
	
	m_nVolume=nVolume;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameMusic::VolumeDown()		//��С����
{
	SetVolume(m_nVolume-10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameMusic::VolumeUp()			//��������
{
	SetVolume(m_nVolume+10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::Open(LPTSTR szMusicPath)	//�������ļ�
{

	if(strlen(szMusicPath)==0)
		return FALSE;
	
	if(GetPlayState()||GetStopState())	//������������ļ����򿪣����ȹر�
		Close();

	char szCommand[50];
	sprintf(szCommand,"OPEN %s ALIAS MUSIC%d", szMusicPath,m_ID);
	if(!mciSendString(szCommand,NULL,0,0))	//�������ļ�
	{
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GameMusic::Close()		//�ر������ļ�
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

BOOL GameMusic::Play(int nVolume,BOOL bRepeat,BOOL bReStart) //�������֣��������Ƿ�ѭ�����š����²���
{
	char szCommand[50];	
	

	if(GetStopState()||bReStart)	//�ж�������ֹͣ״̬��Ҫ�����²���ʱ�Ų���
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

BOOL GameMusic::Stop()		//ֹͣ����
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
