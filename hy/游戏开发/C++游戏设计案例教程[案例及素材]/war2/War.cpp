/********************************
	��Ϸ�������ļ�war.cpp
********************************/
#include "war.h"
//#include "stdio.h"	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ϸ��ʼ�� */
BOOL GameInitialize(HINSTANCE hInstance)
{
	
	//��������
	g_pGE=new GameEngine(hInstance,TEXT("War"),TEXT("War in Hurst"),
			IDI_BIGICON,IDI_SMALLICON,FALSE,32,800,600);
	if(g_pGE==NULL)
		return FALSE;

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ʼ */
void GameStart(HWND hWnd)
{
	/* �������ָ��*/
	long lCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,lCur);

	g_pLoadScene=new Sprite(NULL,"resource\\LoadScene.bmp");

	g_nScene=1;			//���ó�����־
	g_bInitScene=FALSE;	//���ó�����ʼ����־

	InitScene_1(hWnd);	//��ʼ������1

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* ��Ϸ�߼� */
void GameAction(HWND hWnd)
{
	if(g_bInitScene)	//�жϳ�����ʼ���Ƿ����
	{
		//ͨ��������־��������س���
		switch(g_nScene)	
		{
		case 1:
			if(PlayScene_1(hWnd))		//ִ�г���1��Ϸ�߼���ͨ������ֵ�ж��Ƿ�ִ�����
			{
				g_bInitScene=FALSE;	//���ó�����ʼ����־
				InitScene_2(hWnd);	//��ʼ������2;
			}
			break;
		case 2:
			PlayScene_2(hWnd); 		//ִ�г���2��Ϸ�߼�
			break;
		}
	}


	InvalidateRect(hWnd,NULL,FALSE);	//ǿ��ˢ�´���
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1��ʼ�� */
BOOL InitScene_1(HWND hWnd)
{
	//������Ϸͼ��
	g_pSprBackGround=new Sprite(NULL,"resource\\background.bmp");
	g_pSprFoeman=new Sprite(NULL,"resource\\foeman.bmp");
	g_pSprGirl=new Sprite(NULL,"resource\\girl.bmp");
	g_pSprDlgBG=new Sprite(NULL,"resource\\dialog.bmp");
	g_pSprSceneTitle=new Sprite(NULL,"resource\\SceneTitle.bmp");
	g_pSprSceneLoc=new Sprite(NULL,"resource\\SceneLoc.bmp");

	g_pSprDlg=new Sprite();	//λͼΪ�յľ��飬���ڴ���Ի�ͼ��
	
	//��������ӵ����������󣬲�������ӦZ˳��
	g_Sprm.AddSprite(g_pSprBackGround,0);
	g_Sprm.AddSprite(g_pSprSceneTitle,1);
	g_Sprm.AddSprite(g_pSprSceneLoc,1);
	g_Sprm.AddSprite(g_pSprGirl,2);
	g_Sprm.AddSprite(g_pSprFoeman,2);
	g_Sprm.AddSprite(g_pSprDlg,3);


	//����״̬������ʼ��
	g_nSceneTitleAlpha=0;	
	g_nDialigIndex=0;
	g_nXFoeman=600;
	g_nYFoeman=200;
	g_nXGirl=20;
	g_nYGirl=200;

	g_bInitScene=TRUE;	//������ʼ�����
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1���� */
BOOL PlayScene_1(HWND hWnd)
{
	//���þ�������ͼ��Ϣ
	g_pSprFoeman->SetDrawInfo(g_nXFoeman,g_nYFoeman,TRUE);
	g_pSprGirl->SetDrawInfo(g_nXGirl,g_nYGirl,TRUE);
	g_pSprBackGround->SetDrawInfo(0,0,TRUE);
	g_pSprDlg->SetDrawAlphaInfo(150,450,192);
	g_pSprSceneTitle->SetDrawTransAlphaInfo(0,0,g_pGE->GetWidth(),g_pGE->GetHeight(),140,30,g_nSceneTitleAlpha,RGB(0,0,0));
	g_pSprSceneLoc->SetDrawInfo(10,10,TRUE);


	//�ж϶Ի��Ƿ����
	if(g_nDialigIndex<5)
	{
		RECT rTalk={20,40,460,120};
		RECT rName={20,10,460,30};
		HDC hDC=GetDC(hWnd);
		//����DrawDlgToBmp()���Ի����ֻ��Ƶ��Ի����ٽ�λͼ������Ϊg_pSprDlg��λͼ
		g_pSprDlg->SetBitmap(DrawDlgToBmp(hDC,g_pSprDlgBG,g_dlg[g_nDialigIndex].szName,rName,g_dlg[g_nDialigIndex].szTalk,rTalk));
		ReleaseDC(hWnd,hDC);
	}
	else if(g_nSceneTitleAlpha<255)
	{
		g_Sprm.SetSpriteVisible(g_pSprDlg,FALSE);	//���öԻ���Ϊ���ɼ�

		g_nXFoeman+=20;			//����������
		g_nXGirl-=20;			//����������

		//�����Ƴ�������������Ϊ���ɼ��������ٻ���ͼ��
		if(g_nXFoeman>g_pGE->GetWidth()) 
			g_Sprm.SetSpriteVisible(g_pSprFoeman,FALSE);	
		if(g_nXGirl+g_pSprGirl->GetWidth()<0) 
			g_Sprm.SetSpriteVisible(g_pSprGirl,FALSE);
		
		g_nSceneTitleAlpha+=5;	//��������͸���ȵ���
	}


	//�������������ʾ��ɣ����ʾ����1���������ó�����־g_nSceneΪ2
	if(g_nSceneTitleAlpha>=255)
	{

		g_Sprm.Release(TRUE);		//ɾ������ͼ��

		g_nScene=2;

		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����2��ʼ�� */
BOOL InitScene_2(HWND hWnd)
{
	//���뱳��
	g_pSprBackGround=new Sprite(NULL,"resource\\background.bmp");

	 g_pSprWarBar=new Sprite(NULL,"resource\\WarBarBottomBG.bmp");

	//���붯��ͼ�񣬲���ʼ����������
	g_pSprFoemanAnima=new Sprite(NULL,"resource\\FoemanAnima.bmp");
	g_pSprFoemanAnima->InitAnima(1,6,150);

	g_pSprGirlAnima=new Sprite(NULL,"resource\\GirlAnima.bmp");
	g_pSprGirlAnima->InitAnima(1,6,150);

	//��������ӵ�����������
	g_Sprm.AddSprite(g_pSprBackGround,0);
	g_Sprm.AddSprite(g_pSprGirlAnima,3);
	g_Sprm.AddSprite(g_pSprFoemanAnima,3);
	g_Sprm.AddSprite(g_pSprWarBar,1);

	g_bInitScene=TRUE;	//���ó�����ʼ����־
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����2���� */
BOOL PlayScene_2(HWND hWnd)
{
	//���þ��������Ϣ
	g_pSprBackGround->SetDrawInfo(0,0,TRUE);
	g_pSprFoemanAnima->SetDrawAnimaInfo(100,240,0,TRUE);
	g_pSprGirlAnima->SetDrawAnimaInfo(400,280,0,TRUE);
	g_pSprWarBar->SetDrawInfo(0,445);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//���ƾ����еĶԻ���ͼ����Ի����ֵ�λͼ��������λͼ���
HBITMAP  DrawDlgToBmp(HDC hDC,Sprite * pSprDlgBG,LPTSTR szName,RECT & rName,LPTSTR szTalk,RECT & rTalk)
{

		HDC hMemDC=CreateCompatibleDC(hDC);	//�����ڴ�����豸����
		HBITMAP hbmTmp=CreateCompatibleBitmap(hDC, pSprDlgBG->GetWidth(), pSprDlgBG->GetHeight());			//��������λͼ�����ڻ��ƶԻ���

		HBITMAP hbmOld=(HBITMAP)SelectObject(hMemDC,hbmTmp);  //ѡ��hbmTmp
		//��ԭ�����ֵĶԻ�����Ƶ�hMemDC��ʵ���Ͼ��ǻ��Ƶ�hbmTmp��
		g_pSprDlgBG->Draw(hMemDC,0,0);
		//���Ի��ı����Ƶ�hMemDC
		SetBkMode(hMemDC,TRANSPARENT);   	//���ñ���ģʽΪ͸��
		SetTextColor(hMemDC,RGB(255,255,0));		//����������ɫΪ��ɫ
		DrawText(hMemDC,szName,-1,&rName,DT_LEFT);		
		DrawText(hMemDC,szTalk,-1,&rTalk,DT_LEFT);

		SelectObject(hMemDC,hbmOld);	//���hbmTmp
		DeleteDC(hMemDC);
		return hbmTmp;		//���ػ��ƶԻ�����ı����ͼ��
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*  ��Ⱦ��Ϸ���� ***/
void GamePaint(HDC hDC)
{
	if(!g_bInitScene)	//�жϳ�����ʼ���Ƿ����
		g_pLoadScene->Draw(hDC,0,0);	//���Ƽ��س���ʱ�ĵȴ�����
	else
		g_Sprm.Draw(hDC);				//���Ƴ���
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* ��Ϸ���� */
void GameEnd()
{
	g_Sprm.Release(TRUE);
	delete g_pGE;	//�����Ϸ����ָ��	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ͣ */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���ڹر� */
BOOL GameWindowClose(HWND hWnd)
{
	if(MessageBox(g_pGE->GetWindow(),"��ȷ��Ҫ�˳���","�˳���Ϸ",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��굥���¼����� */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	g_nDialigIndex++;		//�Ի���ŵ���
}

