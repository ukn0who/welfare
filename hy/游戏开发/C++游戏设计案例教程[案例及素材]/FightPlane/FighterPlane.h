/*********************************
	��Ϸ����ͷ�ļ�FighterPlane.h
*********************************/

#include "GameEngine.h"		//������Ϸ����
#include "Sprite.h"			//������Ϸ����
#include "SpriteManage.h"	//�������������

#include "resource.h"		//������Դ�ļ�

GameEngine *	g_pGE;		//ȫ������ָ��	

/*���徫��ʵ��*/
Sprite * g_pLoadScene;		//���س���ʱ�ĵȴ�����
Sprite * g_pBackGround;		//��ɫ����ͼ��	

Sprite * g_pCloud[8];		//�Ʋ�ͼ����
Sprite * g_pFightPlane;		//���ڻ��Ʒɻ�ͼ��
Sprite * g_pFightPlanePic[3];	//���ڴ洢�ɻ�ͼ��

POINT g_ptCloud[8];			//�Ʋʵ����Ͻ�����
POINT g_ptFightPlane;		//�ɻ������Ͻ�����

SpriteManage g_Sprm;		//����������

int g_nScene;				//�������
BOOL g_bInitScene;			//������ʼ����ɱ�־

BOOL InitScene_1(HWND hWnd);	//��ʼ������1
BOOL PlayScene_1(HWND hWnd);	//���г���1

