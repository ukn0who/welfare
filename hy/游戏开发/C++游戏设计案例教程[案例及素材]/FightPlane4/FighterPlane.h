/*********************************
	��Ϸ����ͷ�ļ�FighterPlane.h
*********************************/

#include "GameEngine.h"		//������Ϸ����
#include "Sprite.h"			//������Ϸ����
#include "SpriteManage.h"	//�������������
#include "GameMusic.h"		//������Ϸ����
#include "GamePhysics.h"	//������Ϸ������

#include "resource.h"		//������Դ�ļ�

GameEngine *	g_pGE;		//ȫ������ָ��	


/*���徫��ʵ��*/
Sprite * g_pSprLoadScene;		//���س���ʱ�ĵȴ�����
Sprite * g_pSprBackGround;		//��ɫ����ͼ��	

Sprite * g_pSprCloud[8];		//�Ʋ�ͼ����
Sprite * g_pSprFightPlane;		//���ڻ��Ʒɻ�ͼ��
Sprite * g_pSprFightPlanePic[3];	//���ڴ洢�ɻ�ͼ��

POINT g_ptCloud[8];			//�Ʋʵ����Ͻ�����

SpriteManage g_Sprm;		//����������

int g_nScene;				//�������
BOOL g_bInitScene;			//������ʼ����ɱ�־

BOOL InitScene_1(HWND hWnd);	//��ʼ������1
BOOL PlayScene_1(HWND hWnd);	//���г���1

GameMusic * g_pMscBGM;			//��������
GameMusic * g_pMscPlaneFly;		//�ɻ�������Ч

Sprite * g_pSprEnemy[4];			//�л�ͼ��	

GamePhysics * g_pPhyFight;		//��Ϸ�߷ɻ���������
GamePhysics * g_pPhyEnemy[4];	//�л���������

//����SetEnemyInfo()���������ڰ󶨾������������˶�����
void SetEnemyInfo(Sprite * spr,GamePhysics * phy,int nType);


/*�����������ӵ���ͱ���*/

//Blast�����ڲ��ű�ը����
class Blast
{
protected:
	long m_nEndBlastTime;	//����ʱ��
	Sprite * m_sprBlast;	//��ը����
	BOOL	m_bFree;		//�Ƿ����

public:
	Blast()	
	{
		m_sprBlast=NULL;
		m_nEndBlastTime=0;
		m_bFree=TRUE;	
	};
	~Blast(){};
	
	//���ö������Ų�����sprΪGIFͼ��ը�������飬rBlastָ��������ʾλ�ã�nDelayΪ������ʾʱ��
	void Set(Sprite * spr,RECT rBlast,long nDelay)
	{
		m_sprBlast=spr;
		m_nEndBlastTime=timeGetTime()+nDelay;
		m_sprBlast->SetDrawCxImageInfo(rBlast.left-50,rBlast.top-50,100,100);
		m_sprBlast->SetVisible(TRUE);
		m_bFree=FALSE;
	};

	BOOL Play()	//���Ŷ���
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

	BOOL IsFree()		//�����Ƿ���У���δ���ţ�
	{
		return (m_bFree );
	}
};

Blast g_Blast;				//��ը���Ŷ�������
Sprite * g_pSprBlast;		//��ը��������

GamePhysics * g_pPhyShot;	//�ӵ������˶�����
Sprite * g_pSprShot;		//�ӵ�����

BOOL g_bShotEnemy;			//�ж��Ƿ���ел�
BOOL g_bShotFighter;		//�ж�����Ƿ�ײ

int g_nResult;				//��ҳɼ�
Sprite * g_pSprGameOver;	//��Ϸ����ͼ����