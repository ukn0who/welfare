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
	g_pCloud[0]=new Sprite("resource\\cloud_1.png");	//�Ʋ�
	g_pCloud[1]=new Sprite("resource\\cloud_2.png");
	g_pCloud[2]=new Sprite("resource\\cloud_3.png");
	g_pCloud[3]=new Sprite("resource\\cloud_4.png");
	g_pCloud[4]=new Sprite("resource\\cloud_5.png");
	g_pCloud[5]=new Sprite("resource\\cloud_6.png");
	g_pCloud[6]=new Sprite("resource\\cloud_7.png");
	g_pCloud[7]=new Sprite("resource\\cloud_8.png");


	g_pFightPlanePic[0]=new Sprite("resource\\FighterPlane.png");//�洢�ɻ�ͼ��ľ���
	g_pFightPlanePic[1]=new Sprite("resource\\FighterPlaneL.png");
	g_pFightPlanePic[2]=new Sprite("resource\\FighterPlaneR.png");

	g_pFightPlane=new Sprite();			//�������Ʒɻ��ľ���
	g_pFightPlane->SetCxImage(g_pFightPlanePic[0]->GetCxImage()); //����ͼ��


	//ʹ����ʱDC������ɫ����ͼ��
	HDC hDCTmp=GetDC(hWnd);
	g_pBackGround=new Sprite(hDCTmp,g_pGE->GetWidth(),g_pGE->GetHeight(),RGB(40,80,160));
	ReleaseDC(hWnd,hDCTmp);

	g_pBackGround->SetDrawInfo(0,0);
	g_Sprm.AddSprite(g_pBackGround,0);


	//��������ӵ����������󣬲�������ӦZ˳��	
	g_Sprm.AddSprite(g_pCloud[0],1);
	g_Sprm.AddSprite(g_pCloud[1],1);
	g_Sprm.AddSprite(g_pCloud[2],1);
	g_Sprm.AddSprite(g_pCloud[3],1);
	g_Sprm.AddSprite(g_pCloud[4],1);
	g_Sprm.AddSprite(g_pCloud[5],1);
	g_Sprm.AddSprite(g_pCloud[6],1);
	g_Sprm.AddSprite(g_pCloud[7],1);

	g_Sprm.AddSprite(g_pFightPlane,3);


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
			g_ptCloud[i].y=-(g_pCloud[i]->GetHeight());
			
			//��������Ʋ���ǰ���Ʋ㻹���ڱ����Ʋ���
			if(rand()%2)
				g_Sprm.SetZOrder(g_pCloud[i],1);
			else
				g_Sprm.SetZOrder(g_pCloud[i],4);				
		}
		else
		{
			//�ж��Ʋ�����ǰ���Ʋ㻹���ڱ����Ʋ�
			if(g_pCloud[i]->GetZOrder()<4)	
				g_ptCloud[i].y+=2;		//���ñ����Ʋ��е��Ʋ������ƶ�2����
			else
				g_ptCloud[i].y+=3;		//����ǰ���Ʋ��е��Ʋ������ƶ�3����
		}
		//�����Ʋʻ�ͼ����
		g_pCloud[i]->SetDrawCxImageInfo(g_ptCloud[i].x,g_ptCloud[i].y);
	}

	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*  ��Ⱦ��Ϸ���� ***/
void GamePaint(HDC hDC)
{
	if(!g_bInitScene)		//�жϳ�����ʼ���Ƿ����
		g_pLoadScene->Draw(hDC,0,0);	//���Ƽ��س���ʱ�ĵȴ�����
	else
		g_Sprm.Draw(hDC);				//���Ƴ���

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameEnd()
{
	g_Sprm.Release(TRUE);
	delete	g_pLoadScene;
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
		g_pFightPlane->SetCxImage(g_pFightPlanePic[0]->GetCxImage());
		g_pFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,100,100);
	}
	else 	if(GetAsyncKeyState(VK_DOWN)<0 )	//�ж��·�����Ƿ���
	{
		g_ptFightPlane.y+=5;			//�ɻ�y��������

		//������ﴰ���±�Ե����ֹͣ�ƶ�
		if(g_ptFightPlane.y>g_pGE->GetHeight()-g_pFightPlane->GetHeight())	
			g_ptFightPlane.y=g_pGE->GetHeight()-g_pFightPlane->GetHeight();

		g_pFightPlane->SetCxImage(g_pFightPlanePic[0]->GetCxImage());
		g_pFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,100,100);
	}
	else 	if(GetAsyncKeyState(VK_LEFT)<0  )	//�ж�������Ƿ���
	{
		g_ptFightPlane.x-=5;			//�ɻ�x�����С	
		//������ﴰ�����Ե����ֹͣ�ƶ�	
		if(g_ptFightPlane.x<0)					
			g_ptFightPlane.x=0;

		g_pFightPlane->SetCxImage(g_pFightPlanePic[1]->GetCxImage());
		g_pFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,80,100);

	}
	else 	if(GetAsyncKeyState(VK_RIGHT)<0  )	//�ж��ҷ�����Ƿ���
	{
		g_ptFightPlane.x+=5;			//�ɻ�x��������	

		//������ﴰ���ұ�Ե����ֹͣ�ƶ�
		if(g_ptFightPlane.x>g_pGE->GetWidth()-g_pFightPlane->GetWidth())
			g_ptFightPlane.x=g_pGE->GetWidth()-g_pFightPlane->GetWidth();

		g_pFightPlane->SetCxImage(g_pFightPlanePic[2]->GetCxImage());
		g_pFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,80,100);
	}
	else if(GetAsyncKeyState(VK_ESCAPE)<0 )	//�ж�ESC���Ƿ���
		SendMessage(hWnd,WM_CLOSE,0,0);     //�˳�����

	else			//���û�з����������
	{
		g_pFightPlane->SetCxImage(g_pFightPlanePic[0]->GetCxImage());
		g_pFightPlane->SetDrawCxImageInfo(g_ptFightPlane.x,g_ptFightPlane.y,100,100);
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

