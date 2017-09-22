/********************************
	��Ϸ�������ļ�GameStart.cpp
********************************/
#include "GameStart.h"
#include "stdio.h"	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ϸ��ʼ�� */
BOOL GameInitialize(HINSTANCE hInstance)
{
	/* �����ﹹ����Ϸ����ʵ���������ó�ʼ��������� */
	
	/* ������벻����Ϸ���汾�����еģ���������ʾ������Ϸ���ʱ�ɿ����߾���ʵ��*/
	//������Ϸ����
	g_pGE=new GameEngine(hInstance,TEXT("GameStart"),TEXT("GameStart"),
		IDI_BIGICON,IDI_SMALLICON,	TRUE,32,800,600);
	if(g_pGE==NULL)
		return false;

	//��ʼ���������
	g_pGE->SetFrameDelay(15) ;		//������Ϸ֡��ʱΪ15����
	g_pGE->SetPause(false);			//������ͣ״̬Ϊfalse
	g_pGE->CreateGameWindow();		//������Ϸ����

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ�߼� */
void GameAction(HWND hWnd)
{
	/* �����������Ϸ�߼���ش��� */
	
	long nTick=timeGetTime();	//��ȡ��ǰʱ��
	g_nFrequency=1000/(nTick-g_lPreTime);	//������ϷƵ��
	g_lPreTime=nTick;			//��¼��ǰʱ��

	InvalidateRect(hWnd,NULL,FALSE);	//ǿ��ˢ�´���
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ⱦ��Ϸ���� */
void GamePaint(HDC hDC)
{
	/* �����������Ϸ������Ⱦ�Ĵ��� */
	
	/* ����Ļ�ͼ���ַ���������벻����Ϸ��������ݣ�ֻ��Ϊ����ʾ*/
	HDC  dc=CreateCompatibleDC(hDC);	//���������豸����

	//����λͼ
	HBITMAP	hbm=(HBITMAP)LoadImage(g_pGE->GetInstance(),MAKEINTRESOURCE (IDB_BKBITMAP),IMAGE_BITMAP,800,600,LR_DEFAULTCOLOR);
	SelectObject(dc,hbm);	//��λͼѡ���豸����
	
	//����ͼ��
	BitBlt(hDC,0,0,800,600,dc,0,0,SRCCOPY);

	//����λͼ����
	DeleteObject(SelectObject(dc, hbm));
	DeleteObject(hbm);
	
	SetBkMode(hDC,TRANSPARENT);  //���ñ���ģʽΪ͸��
	SetTextColor(hDC,RGB(255,255,0));	//����������ɫΪ��ɫ
	char str[100];						//������ʱ�ַ����ռ�
	int nGameTime=timeGetTime()-g_pGE->GetStartTime();//������Ϸ����ʱ��
	int nBits=GetDeviceCaps(hDC,BITSPIXEL);			//��ȡ��Ļ��ɫλ��
	int nScreenWidth=GetSystemMetrics(SM_CXSCREEN);	//��ȡ��Ļ���ؿ��
	int nScreenHeight=GetSystemMetrics(SM_CYSCREEN);	//��ȡ��Ļ���ظ߶�
	
	//��ʽ���ַ��������������str
	sprintf(str,"��Ϸ����ʱ�䣺%d ms    ֡Ƶ��%d    ��ʾģʽ��%d bit,%d*%d",nGameTime, g_nFrequency, nBits,nScreenWidth,nScreenHeight); 
	TextOut(hDC,10,10,str,strlen(str));	//����ַ���

	// ��������豸����
	DeleteDC(dc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ʼ */
void GameStart(HWND hWnd)
{
	/* �����������Ϸ��ʼʱ�ĳ�ʼ������ */

	/* �������ָ�룬�ⲻ���������� */
	long nCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,nCur);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameEnd()
{
	/* ����������ͷ���Դ����ش���*/

	delete g_pGE;		//�����Ϸ����ָ��	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	

	/* ��������Ӿ������Ϸ�����¼�������� */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ͣ */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);

	/* ��������Ӿ������Ϸ��ͣ�¼�������� */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���ڹر� */
BOOL GameWindowClose(HWND hWnd)
{
	/* ��Ϸ���ڹر�ǰ�Ĵ������ */

	/* ������Ϣ�Ի�����ѯ�Ƿ��������
	�ⲻ���������ģ���������Ϸ����и�Ϊ������Լ��Ĵ���*/
	if(MessageBox(g_pGE->GetWindow(),"��ȷ��Ҫ�˳���","�˳���Ϸ",MB_YESNO|MB_DEFBUTTON2 | MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��굥���¼����� */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	/* ��������Ӿ������굥���¼�������� */
}
