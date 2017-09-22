/********************************
	��Ϸ�������ļ�war.cpp
********************************/
#include "war.h"
#include "stdio.h"	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ϸ��ʼ�� */
BOOL GameInitialize(HINSTANCE hInstance)
{
	
	//��������
	g_pGE=new GameEngine(hInstance,TEXT("War"),TEXT("War in Hurst"),
			IDI_BIGICON,IDI_SMALLICON,FALSE,32,800,600);
	if(g_pGE==NULL)
		return false;

	//��ʼ���������
	g_pGE->SetFrameDelay(15) ;		//������Ϸ֡��ʱΪ15����
	g_pGE->SetPause(false);			//������ͣ״̬Ϊfalse
	if(!g_pGE->CreateGameWindow())	//������Ϸ����
	{
		MessageBox(NULL,"�޸���ʾģʽʧ��!\r\n�����˳�!","����",MB_OK| MB_ICONERROR);
		return FALSE;		//�˳�����
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ�߼� */
void GameAction(HWND hWnd)
{
	//����Ի���ɣ��ҳ�������δ��ȫ��ʾ
	if(g_nDialigIndex >=5 && g_nSceneTitleAlpha<255)
	{
		g_nSceneTitleAlpha+=5;	//��������͸���ȵ���	
		g_nXFoeman+=20;			//����������
		g_nXGirl-=20;				//����������
	}

	InvalidateRect(hWnd,NULL,FALSE);	//ǿ��ˢ�´���
	UpdateWindow(hWnd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ⱦ��Ϸ���� ***/
void GamePaint(HDC hDC)
{
	//���Ʊ��������Ͻǵĳ����ص�����
	g_pSprBackGround->Draw(hDC,0,0);
	g_pSprSceneLoc->Draw(hDC,0,0,TRUE,RGB(0,0,0));

	//�������������
	g_pSprFoeman->Draw(hDC,g_nXFoeman,g_nYFoeman,TRUE,RGB(0,0,0));
	g_pSprGirl->Draw(hDC,g_nXGirl,g_nYGirl,TRUE,RGB(0,0,0));


	SetBkMode(hDC,TRANSPARENT);   		//���ñ���ģʽΪ͸��
	SetTextColor(hDC,RGB(255,255,0));	//����������ɫΪ��ɫ
	//�ж϶Ի��Ƿ����
	if(g_nDialigIndex<5)
	{
		//���ƶԻ�����Ի�����
		g_pSprDlg->DrawAlpha(hDC,150,450,180);
		DrawText(hDC,g_dlg[g_nDialigIndex].szName,-1,&g_rName,DT_LEFT);
		DrawText(hDC,g_dlg[g_nDialigIndex].szTalk,-1,&g_rTalk,DT_LEFT);
	}
	else
	{	//���Ƴ�������
		g_pSprSceneTitle->DrawTransAlpha(hDC,0,0,800,600,140,30,g_nSceneTitleAlpha,RGB(0,0,0));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ʼ */
void GameStart(HWND hWnd)
{
	/* �������ָ��*/
	long lCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,lCur);

	//������Ϸͼ��
	g_pSprBackGround=new Sprite(NULL,"resource\\background.bmp");
	g_pSprFoeman=new Sprite(NULL,"resource\\foeman.bmp");
	g_pSprGirl=new Sprite(NULL,"resource\\girl.bmp");
	g_pSprDlg=new Sprite(NULL,"resource\\dialog.bmp");
	g_pSprSceneTitle=new Sprite(NULL,"resource\\SceneTitle.bmp");
	g_pSprSceneLoc=new Sprite(NULL,"resource\\SceneLoc.bmp");

	//����״̬������ʼ��
	g_nSceneTitleAlpha=0;	
	g_nDialigIndex=0;
	g_nXFoeman=600;
	g_nYFoeman=200;
	g_nXGirl=20;
	g_nYGirl=200;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameEnd()
{
	//�ͷ�λͼ��Դ
	delete	g_pSprBackGround;
	delete	g_pSprFoeman;
	delete	g_pSprGirl;
	delete	g_pSprDlg;
	delete	g_pSprSceneTitle;
	delete	g_pSprSceneLoc;

	delete g_pGE;	//�����Ϸ����ָ��	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ͣ */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���ڹر� */
BOOL GameWindowClose(HWND hWnd)
{
	if(MessageBox(g_pGE->GetWindow(),"��ȷ��Ҫ�˳���","�˳���Ϸ",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��굥���¼����� */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	g_nDialigIndex++;		//�Ի���ŵ���
}