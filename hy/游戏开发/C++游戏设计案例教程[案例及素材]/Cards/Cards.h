/*********************************
	��Ϸ����ͷ�ļ�Cards.h
*********************************/

#include "GameEngine.h"	//������Ϸ����
#include "resource.h"		//������Դ�ļ�

GameEngine *	g_pGE;		//ȫ������ָ��	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*������Ϸ���õ��ĳ���*/
//���忨Ƭѡ��״̬����
enum SELECTSTATE{INITSELECT=0,	//ѡ��״̬��ʼ��
				NOSELECT,		//δѡ��
				SELECTED,		//��ѡ��
				SELECTOK};		//��ȷ���


const	int NULLPATTERN=-1;		//�����ͼ��

const int	CARDWIDTH=100;		//���ÿ�Ƭ��С
const int	CARDHEIGHT=100;
const int	ROWS=3;				//���ÿ�Ƭ�С�����
const int	COLS=4;
const int	ROWSPACE=20;		//���ÿ�Ƭ�С��м��
const int	COLSPACE=50;
const int	CARSTARTX=120;		//���û��ƿ�Ƭʱ���Ͻ���ʼλ��		
const int	CARSTARTY=200;

/*������Ϸȫ�ֱ���*/
char *  g_strTitle="��Ƭ�Զ���";	//��Ϸ����

int		g_nCardPattern[ROWS][COLS];	//��Ƭͼ������
RECT	g_rCardRect[ROWS][COLS];	//��Ƭλ�þ�������
SELECTSTATE	g_nCardState[ROWS][COLS];	//��Ƭ״̬����

int		g_nSelectRow1,g_nSelectRow2,g_nSelectCol1,g_nSelectCol2;	//����ѡ��Ƭ���к�
int		g_nSelected;			//��ѡ����ȷ��ͼ������

RECT	g_rTimeBarFrame;		//ʱ�����߿���δ�С
int		g_nTimeBarLength;		//ʱ��������
int		g_nTimeCount;			//�涨��ʱ�䳤��
int		g_nStartTime;			//��ʼʱ��
long	g_nTimeDelayStart;		//��ʱ����ʱ��
