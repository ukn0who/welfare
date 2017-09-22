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

