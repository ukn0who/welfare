/*********************************
	��Ϸ����ͷ�ļ�War.h
*********************************/

#include "GameEngine.h"		//������Ϸ����
#include "Sprite.h"			//������Ϸ����

#include "resource.h"		//������Դ�ļ�

GameEngine *	g_pGE;		//ȫ������ָ��	

///////////////////////////////////////////////////////////////////////////////////

//����Ի��ṹ
typedef struct tgaDIALOG{
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

int g_nDialigIndex;	//�Ի�����	

/*���徫��ʵ��*/
Sprite * g_pSprBackGround;
Sprite * g_pSprFoeman;
Sprite * g_pSprGirl;
Sprite * g_pSprDlg;
Sprite * g_pSprSceneTitle;
Sprite * g_pSprSceneLoc;


//�Ի�ʱ�������������ݵ�λ�þ���
RECT g_rTalk={170,490,700,580};
RECT g_rName={170,460,220,500};

//���������͸����
int g_nSceneTitleAlpha;

//�����λ���������
int g_nXFoeman,g_nYFoeman,g_nXGirl,g_nYGirl;