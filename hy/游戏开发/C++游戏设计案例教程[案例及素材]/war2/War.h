/*********************************
	��Ϸ����ͷ�ļ�War.h
*********************************/

#include "GameEngine.h"		//������Ϸ����
#include "Sprite.h"			//������Ϸ����
#include "SpriteManage.h"	//�������������

#include "resource.h"		//������Դ�ļ�

GameEngine *	g_pGE;		//ȫ������ָ��	

//����Ի��ṹ
typedef struct tagDIALOG{
	LPTSTR	szName;		//����
	LPTSTR	szTalk;		//̸������
} DIALOG;

//����Ի�����
DIALOG g_dlg[5]={{"�ӳ�","ʲô��?\nվס!\n�����Ѿ��������ˣ���׼ͨ��!"},
				{"�ɵ�","��ѽѽ....\n��Ҫ��ô����˼�ֻ�ǳ������͵ġ�"},
				{"�ӳ�","����?\nΪʲôû��ƿ?!\n�����Ÿ�����?"},
				{"�ɵ�","�����װ�ģ�������?\n����������......"},
				{"�ӳ�","���ҽƱ�!\n�������Ǽ��!\n����,��������!"}
				};
int g_nDialigIndex;

/*���徫��ʵ��*/
Sprite * g_pSprBackGround;
Sprite * g_pSprFoeman;
Sprite * g_pSprGirl;
Sprite * g_pSprDlg;
Sprite * g_pSprDlgBG;
Sprite * g_pSprSceneTitle;
Sprite * g_pSprSceneLoc;
Sprite * g_pSprWarBar;
Sprite * g_pLoadScene;			//���س���ʱ�ĵȴ�����
Sprite * g_pSprGirlAnima;		//��������
Sprite * g_pSprFoemanAnima;		//��������

SpriteManage g_Sprm;			//����������


//���������͸����
int g_nSceneTitleAlpha;

//�����λ���������
int g_nXFoeman,g_nYFoeman,g_nXGirl,g_nYGirl;

int g_nScene;			//�������
BOOL g_bInitScene;		//������ʼ����ɱ�־

BOOL InitScene_1(HWND hWnd);		//��ʼ������1
BOOL PlayScene_1(HWND hWnd);		//���г���1

BOOL InitScene_2(HWND hWnd);		//��ʼ������2
BOOL PlayScene_2(HWND hWnd);		//���г���2

//���ƾ����еĶԻ���ͼ����Ի����ֵ�λͼ��ָ���ľ������򣬲�����λͼ���
HBITMAP  DrawDlgToBmp(HDC hDC,Sprite * pSprDlgBG,LPTSTR szName,RECT & rName,LPTSTR szTalk,RECT & rTalk);


