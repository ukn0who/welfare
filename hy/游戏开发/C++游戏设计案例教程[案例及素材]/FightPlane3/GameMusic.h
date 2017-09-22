/*********************************
	��Ϸ����ͷ�ļ�GameMusic.h
*********************************/

#ifndef DEF_GAMEMUSIC		//�������룬Ŀ���Ƿ�ֹ�ļ����ظ�����

#define DEF_GAMEMUSIC  1

#include "windows.h"
#include "stdio.h"
#include "mmsystem.h"		//�����ļ�

/*��Ϸ������*/
class GameMusic
{
protected:
	int		m_ID;				//���
	static int m_nNewID;		//��һ�����ñ��

	int		m_nVolume;			//����(0~1000)

public:
	GameMusic();					//���캯��

	GameMusic(LPTSTR szMusicPath);	//��·�������Ĺ��캯��

	~GameMusic();				//��������

	BOOL GetPlayState();		//��ȡ���ֲ���״̬

	BOOL GetOpenState();		//��ȡ�����ļ���״̬

	BOOL GetStopState();		//��ȡ����ֹͣ״̬

	int GetVolume();			//��ȡ������С

	void SetVolume(int nVolume);	//��������

	void VolumeDown();			//��С����

	void VolumeUp();			//��������
	
	BOOL Open(LPTSTR szMusicPath);	//�������ļ�

	BOOL Close();				//�ر������ļ�

	BOOL Stop();				//ֹͣ����

	BOOL Play(int nVolume=300,BOOL bRepeat=FALSE,BOOL bReStart=TRUE); //�������֣��������Ƿ�ѭ�����š����¿�ʼ

};

#endif

