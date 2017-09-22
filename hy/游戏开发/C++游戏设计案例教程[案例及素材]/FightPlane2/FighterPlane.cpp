/********************************
	��Ϸ�������ļ�FighterPlane.cpp
********************************/
#include "FighterPlane.h"

#include <time.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ϸ��ʼ�� */
BOOL GameInitialize(HINSTANCE hInstance)
{
	
	//��������
	g_pGE=new GameEngine(hInstance,TEXT("Fight Plane"),TEXT("����ս��"),
			IDI_BIGICON,IDI_SMALLICON,FALSE,32,450,600);
	if(g_pGE==NULL)
		return FALSE;

	//��ʼ���������
	g_pGE->SetFrameDelay(30) ;		//������Ϸ֡��ʱΪ30����
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

	g_pSprLoadScene=new Sprite(NULL,"resource\\LoadScene.bmp");


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
		PlayScene_1(hWnd);
	}
	InvalidateRect(hWnd,NULL,FALSE);	//ǿ��ˢ�´���
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1��ʼ�� */
BOOL InitScene_1(HWND hWnd)
{
	//������Ϸͼ��
	g_pSprCloud[0]=new Sprite("resource\\cloud_1.png");	//�Ʋ�
	g_pSprCloud[1]=new Sprite("resource\\cloud_2.png");
	g_pSprCloud[2]=new Sprite("resource\\cloud_3.png");
	g_pSprCloud[3]=new Sprite("resource\\cloud_4.png");
	g_pSprCloud[4]=new Sprite("resource\\cloud_5.png");
	g_pSprCloud[5]=new Sprite("resource\\cloud_6.png");
	g_pSprCloud[6]=new Sprite("resource\\cloud_7.png");
	g_pSprCloud[7]=new Sprite("resource\\cloud_8.png");


	g_pSprFightPlanePic[0]=new Sprite("resource\\FighterPlane.png");//�洢�ɻ�ͼ��ľ���
	g_pSprFightPlanePic[1]=new Sprite("resource\\FighterPlaneL.png");
	g_pSprFightPlanePic[2]=new Sprite("resource\\FighterPlaneR.png");

	g_pSprFightPlane=new Sprite();			//�������Ʒɻ��ľ���
	g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage()); //����ͼ��


	//ʹ����ʱDC������ɫ����ͼ��
	HDC hDCTmp=GetDC(hWnd);
	g_pSprBackGround=new Sprite(hDCTmp,g_pGE->GetWidth(),g_pGE->GetHeight(),RGB(40,80,160));
	ReleaseDC(hWnd,hDCTmp);

	g_pSprBackGround->SetDrawInfo(0,0);
	g_Sprm.AddSprite(g_pSprBackGround,0);


	//��������ӵ����������󣬲�������ӦZ˳��	
	g_Sprm.AddSprite(g_pSprCloud[0],1);
	g_Sprm.AddSprite(g_pSprCloud[1],1);
	g_Sprm.AddSprite(g_pSprCloud[2],1);
	g_Sprm.AddSprite(g_pSprCloud[3],1);
	g_Sprm.AddSprite(g_pSprCloud[4],1);
	g_Sprm.AddSprite(g_pSprCloud[5],1);
	g_Sprm.AddSprite(g_pSprCloud[6],1);
	g_Sprm.AddSprite(g_pSprCloud[7],1);

	g_Sprm.AddSprite(g_pSprFightPlane,3);


	//����״̬������ʼ��
	srand((unsigned)time(NULL));	// ��ʼ�����������
	for(int i=0;i<8;i++)			//��ѭ������������Ʋʵ�λ��
	{
		g_ptCloud[i].x=rand()%g_pGE->GetWidth();
		g_ptCloud[i].y=rand()%g_pGE->GetHeight();
	}
	
	//���÷ɻ�λ��
	g_ptFightPlane.x=200;
	g_ptFightPlane.y=400;

	//������Ϸ���ֶ��󲢴��ļ�
	g_pMscPlaneFly=new GameMusic("resource\\fly.wav");
	g_pMscBGM=new GameMusic("resource\\bgm.mp3");
	g_pMscBGM->Play(300,TRUE);	//�ظ���������	

	g_bInitScene=TRUE;	//������ʼ�����
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1���� */
BOOL PlayScene_1(HWND hWnd)
{
	//���þ�������ͼ��Ϣ


	for(int i=0;i<8;i++)	//ѭ�������Ʋ�λ�ú�Z˳��
	{
		//�ж��Ʋ��Ƿ񵽴ﻭ��ײ�
		if(g_ptCloud[i].y>g_pGE->GetHeight())	
		{
			//����Ʋʵ��ﻭ��ײ����������ƲʵĴ�ֱλ�õ����涥�ˣ�ˮƽλ���������
			g_ptCloud[i].x=rand()%g_pGE->GetWidth()-g_pGE->GetWidth()/2;
			g_ptCloud[i].y=-(g_pSprCloud[i]->GetHeight());
			
			//��������Ʋ���ǰ���Ʋ㻹���ڱ����Ʋ���
			if(rand()%2)
				g_Sprm.SetZOrder(g_pSprCloud[i],1);
			else
				g_Sprm.SetZOrder(g_pSprCloud[i],4);				
		}
		else
		{
			//�ж��Ʋ�����ǰ���Ʋ㻹���ڱ����Ʋ�
			if(g_pSprCloud[i]->GetZOrder()<4)	
				g_ptCloud[i].y+=2;		//���ñ����Ʋ��е��Ʋ������ƶ�2����
			else
				g_ptCloud[i].y+=3;		//����ǰ���Ʋ��е��Ʋ������ƶ�3����
		}
		//�����Ʋʻ�ͼ����
		g_pSprCloud[i]->SetDrawCxImageInfo(g_ptCloud[i].x,g_ptCloud[i].y);
	}

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*  ��Ⱦ��Ϸ���� ***/
void GamePaint(HDC hDC)
{
	if(!g_bInitScene)		//�жϳ�����ʼ���Ƿ����
		g_pSprLoadScene->Draw(hDC,0,0);	//���Ƽ��س���ʱ�ĵȴ�����
	else
		g_Sprm.Draw(hDC);				//���Ƴ���
}

/* ��Ϸ���� */
void GameEnd()
{
	delete g_pMscBGM;
	delete g_pMscPlaneFly;
	g_Sprm.Release(TRUE);
	delete	g_pSprLoadScene;
	delete	g_pGE;	//�����Ϸ����ָ��	
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


/*������Ϣ����*/
void KeyEvent(HWND hWnd)
{
	if(GetAsyncKeyState(VK_UP)<0 )		//�ж��Ϸ�����Ƿ���
	{
		g_ptFightPlane.y-=5;			//�ɻ�y�����С

		//������ﴰ���ϱ�Ե����ֹͣ�ƶ�
		if(g_ptFightPlane.y<0)		
			g_ptFightPlane.y=0;

		//���÷ɻ�ͼ��ͻ�ͼ����
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,100,100);

		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//���ŷɻ�������Ч
	}
	else 	if(GetAsyncKeyState(VK_DOWN)<0 )	//�ж��·�����Ƿ���
	{
		g_ptFightPlane.y+=5;			//�ɻ�y��������

		//������ﴰ���±�Ե����ֹͣ�ƶ�
		if(g_ptFightPlane.y>g_pGE->GetHeight()-g_pSprFightPlane->GetHeight())	
			g_ptFightPlane.y=g_pGE->GetHeight()-g_pSprFightPlane->GetHeight();

		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,100,100);
	}
	else 	if(GetAsyncKeyState(VK_LEFT)<0  )	//�ж�������Ƿ���
	{
		g_ptFightPlane.x-=5;			//�ɻ�x�����С	
		//������ﴰ�����Ե����ֹͣ�ƶ�	
		if(g_ptFightPlane.x<0)					
			g_ptFightPlane.x=0;

		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[1]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,80,100);

		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//���ŷɻ�������Ч
	}
	else 	if(GetAsyncKeyState(VK_RIGHT)<0  )	//�ж��ҷ�����Ƿ���
	{
		g_ptFightPlane.x+=5;			//�ɻ�x��������	

		//������ﴰ���ұ�Ե����ֹͣ�ƶ�
		if(g_ptFightPlane.x>g_pGE->GetWidth()-g_pSprFightPlane->GetWidth())
			g_ptFightPlane.x=g_pGE->GetWidth()-g_pSprFightPlane->GetWidth();

		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[2]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,80,100);
		
		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//���ŷɻ�������Ч
	}
	else if(GetAsyncKeyState(VK_PRIOR)<0)	//����PageUp��������������������
		g_pMscBGM->VolumeUp();
	else if(GetAsyncKeyState(VK_NEXT)<0)	//����PageDown������������������С
		g_pMscBGM->VolumeDown();
	else if(GetAsyncKeyState(VK_HOME )<0)	//����Home�������²��ű�������
		g_pMscBGM->Play(300,TRUE);
	else if(GetAsyncKeyState(VK_END )<0)	//����End����ֹͣ���ű�������
		g_pMscBGM->Stop();
	else if(GetAsyncKeyState(VK_ESCAPE)<0 )	//�ж�ESC���Ƿ���
		SendMessage(hWnd,WM_CLOSE,0,0);     //�˳�����
	else			//�������������δ������
	{
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,100,100);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*�����������Ϣ��������������δʹ�ã�����Ϊ��*/
//������������Ϣ������
void MouseLButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
	
}

//������������Ϣ������
void MouseLButtonUp(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//������˫����Ϣ������
void MouseDoubleClick(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//����Ҽ�������Ϣ������
void MouseRButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//����ƶ���Ϣ������
void MouseVove(HWND hWnd,int x,int y,WPARAM wParam)
{
}

