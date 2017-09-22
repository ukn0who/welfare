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
	


	//������Ϸ���ֶ��󲢴��ļ�
	g_pMscPlaneFly=new GameMusic("resource\\fly.wav");
	g_pMscBGM=new GameMusic("resource\\bgm.mp3");
	g_pMscBGM->Play();	//��������	


	/*�����л�����ͼ��������˶�������������*/

	//�л�����ͼ��
	g_pSprEnemy[0]=new Sprite("resource\\enemy1.png");
	g_pSprEnemy[1]=new Sprite("resource\\enemy2.png");
	g_pSprEnemy[2]=new Sprite("resource\\enemy3.png");
	g_pSprEnemy[3]=new Sprite("resource\\enemy4.png");

	//��ӵ�����������
	g_Sprm.AddSprite(g_pSprEnemy[0],3);
	g_Sprm.AddSprite(g_pSprEnemy[1],3);
	g_Sprm.AddSprite(g_pSprEnemy[2],3);
	g_Sprm.AddSprite(g_pSprEnemy[3],3);

	//���������˶�����
	g_pPhyEnemy[0]=new GamePhysics();
	g_pPhyEnemy[1]=new GamePhysics();
	g_pPhyEnemy[2]=new GamePhysics();
	g_pPhyEnemy[3]=new GamePhysics();


	//���÷ɻ��������
	RECT rObject={200,400,300,500};
	RECT rBound={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
	POINTF ptFocus={0,0};
	POINTF ptVelo={0,5};
	POINTF ptAccelerate={0,0};
	POINTF ptDes={300,300};
	g_pPhyFight=new GamePhysics(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);


	g_pSprFightPlane->SetVisible(TRUE);
	g_pPhyFight->SetVisible(TRUE);


	//�����ӵ��������
	g_pSprShot=new Sprite("resource\\Shot.png");
	RECT rObjectShot={0,0,20,100};
	RECT rBoundShot={0,-100,400,600};
	POINTF ptFocusShot={10,0};
	POINTF ptVeloShot={0,10};
	POINTF ptAccelerateShot={0,0};
	POINTF ptDesShot={0,0};
	g_pPhyShot=new GamePhysics(rObjectShot,rBoundShot,ptFocusShot,ptVeloShot,ptAccelerateShot,ptDesShot,FALSE);

	g_pPhyShot->SetVisible(FALSE);
	g_Sprm.AddSprite(g_pSprShot,4);	


		
	//��ը�����ͽ�������
	g_pSprBlast=new Sprite("resource\\bom.gif");
	g_pSprGameOver=new Sprite("resource\\GameOver.png");
	g_Sprm.AddSprite(g_pSprBlast,4);
	g_Sprm.AddSprite(g_pSprGameOver,4);

	g_pSprGameOver->SetDrawCxImageInfo(30,300);
	g_pSprGameOver->SetVisible(FALSE);
	
	g_bShotEnemy=FALSE;	
	g_bShotFighter=FALSE;	

	g_nResult=0;

	g_bInitScene=TRUE;	//������ʼ�����
	

	return TRUE;
}

/*��һ���������spr��һ������������phy�󶨣���nTypeָ���������˶�*/
void SetEnemyInfo(Sprite * spr,GamePhysics * phy,int nType)
{
	srand((unsigned)time(NULL));	// ��ʼ�����������
	int x=rand()%(g_pGE->GetWidth()-spr->GetWidth());	//���������
	//���·��
	POINTF ptPath[8]={{x+100,-spr->GetHeight()},
					{x+100,100},
					{x+200,100},
					{x-100,100}, 
					{x-100,200},
					{x+100,200},
					{x+100,300},
					{x,g_pGE->GetHeight()}};

	//�ж���������Ƿ����ƶ�����δ�ƶ�����������������������
	if( phy->GetPathArrive()&&nType==2 ||! phy->GetMoveState()&&nType==1)
	{
		RECT rObject={x,-spr->GetHeight(),x+spr->GetWidth(),0};
		RECT rBound={0,-spr->GetHeight(),g_pGE->GetWidth(),g_pGE->GetHeight()+spr->GetHeight()};
		POINTF ptFocus={0,0};
		POINTF ptVelo={0,rand()%9+1};
		POINTF ptAccelerate={0,0};
		POINTF ptDes={x,g_pGE->GetHeight()};
		phy->SetObject(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,TRUE);
	}
	
	//��ָ�����˶������ƶ�
	switch(nType)
	{
	case 1:
		phy->MoveToDes();
		break;
	case 2:
		phy->MoveAlongPath(ptPath,8);
		break;

	}

	spr->SetVisible( phy->GetVisible());
		
	//���þ����ͼ����
	if(spr->GetVisible())
		spr->SetDrawCxImageInfo(phy->GetLeftTop().x,phy->GetLeftTop().y);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1���� */
BOOL PlayScene_1(HWND hWnd)
{	

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

	//���������������󶨣���ָ���Ķ����˶�

	SetEnemyInfo(g_pSprEnemy[0],g_pPhyEnemy[0],2);
	SetEnemyInfo(g_pSprEnemy[1],g_pPhyEnemy[1],2);
	SetEnemyInfo(g_pSprEnemy[2],g_pPhyEnemy[2],1);
	SetEnemyInfo(g_pSprEnemy[3],g_pPhyEnemy[3],1);

	/*������ײ���ͼǷ�ϵͳ*/
	//�жϵл��Ƿ�����ҷɻ���ײ�򱻻���
	RECT r1,r2;
	
	for(i=0;i<4;i++)
	{
		//�ж��Ƿ�����ҷɻ���ײ

		if(g_pPhyEnemy[i]->Collision(g_pPhyFight,BA_CLEAR,&r1))
		{
			g_pPhyEnemy[i]->SetVisible(FALSE);	//���õл������˶�����Ϊ���ɼ�
			g_pSprEnemy[i]->SetVisible(FALSE);	//���õл�ͼ��Ϊ���ɼ�
			g_pPhyFight->SetVisible(FALSE);		//������Ϸ�߷ɻ������˶�����Ϊ���ɼ�
			g_pSprFightPlane->SetVisible(FALSE);		//������Ϸ�߷ɻ�ͼ��Ϊ���ɼ�
			g_bShotFighter=TRUE;
			break;
		}

		//�ж��Ƿ񱻻���
		if(g_pPhyShot->GetMoveState())
		{
			if(g_pSprEnemy[i]->GetVisible()&&g_pSprShot->GetVisible())
			{
				if(g_pPhyEnemy[i]->Collision(g_pPhyShot,BA_CLEAR,&r2))
				{
					g_bShotEnemy=TRUE;
					g_pSprShot->SetVisible(FALSE);
					g_pPhyShot->SetMoveState(FALSE);
					g_pSprEnemy[i]->SetVisible(FALSE);
					
					g_Blast.Set(g_pSprBlast,r2,800);	//���ű�ը����

					switch(i)		//����÷�
					{
						case 0:
							g_nResult+=5;
							break;
						case 1:
							g_nResult+=10;
							break;
						case 2:
							g_nResult+=3;
							break;
						case 3:
							g_nResult+=2;
							break;
					}
				}		
			}
		}

	}
	
	//�ж��ӵ��˶�״̬��������˶��У����ƶ������û�ͼ����
	if(g_pPhyShot->GetMoveState())
	{
		g_pPhyShot->MoveToDes();
		g_pSprShot->SetDrawCxImageInfo(g_pPhyShot->GetLeftTop().x,g_pPhyShot->GetLeftTop().y,20,100);
	}
	else
	{
		g_pSprShot->SetVisible(FALSE);
	}

	//��Ϸ�߷ɻ���ը��δ��ʾGameOver���֣�����ʾGameOver
	if(g_bShotFighter && !g_pSprGameOver->GetVisible())
	{
		g_Blast.Set(g_pSprBlast,r1,3000);
		g_pSprGameOver->SetVisible(TRUE);
	}

	if(!g_Blast.IsFree())	//�����ը�����������
	{
		//�ж��Ƿ�����Ϸ�߷ɻ���ը
		if(g_Blast.Play()&&g_bShotFighter)
				if(MessageBox(g_pGE->GetWindow(),"��Ϸ����������һ����","GameOver",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
				{

					g_Blast.Set(g_pSprBlast,r1,3000);
					g_pSprGameOver->SetVisible(FALSE);
					g_Sprm.Release(TRUE);
					delete g_pPhyFight;
					delete g_pPhyShot;
					delete g_pMscBGM;
					delete g_pMscPlaneFly;
					GameStart(hWnd);
				}
				else
					DestroyWindow(hWnd);     //�˳�����	
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


	//���Ƴɼ�
	SetBkMode(hDC,TRANSPARENT);   	//���ñ���ģʽΪ͸��
	SetTextColor(hDC,RGB(255,255,0));		//����������ɫΪ��ɫ
	char szResult[20];
	sprintf(szResult,"result:%d",g_nResult);

	RECT rResult={300,10,400,40};
	DrawText(hDC,szResult,-1,&rResult,DT_LEFT);		



}

/* ��Ϸ���� */
void GameEnd()
{
	delete g_pMscBGM;
	delete g_pMscPlaneFly;
	delete[] (*g_pPhyEnemy); 
	delete  g_pPhyFight;
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
		g_pPhyFight->MoveDirect(DI_UP);	//��Ϸ�߷ɻ������˶����������ƶ�
		g_pPhyFight->CheckErr(TRUE);	//����Ƿ񳬳������
		//ͨ�������˶��������÷ɻ�ͼ���ͼ����
		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x,g_pPhyFight->GetLeftTop().y,100,100);
		//���÷ɻ�ͼ��
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//���ŷɻ�������Ч
	}
	else 	if(GetAsyncKeyState(VK_DOWN)<0 )	//�ж��·�����Ƿ���
	{
		g_pPhyFight->MoveDirect(DI_DOWN);		//��Ϸ�߷ɻ������˶����������ƶ�
		g_pPhyFight->CheckErr(TRUE);		

		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x,g_pPhyFight->GetLeftTop().y,100,100);
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
	}
	else 	if(GetAsyncKeyState(VK_LEFT)<0  )	//�ж�������Ƿ���
	{
		g_pPhyFight->MoveDirect(DI_LEFT);		//��Ϸ�߷ɻ������˶����������ƶ�
		g_pPhyFight->CheckErr(TRUE);	

		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x+10,g_pPhyFight->GetLeftTop().y,80,100);
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[1]->GetCxImage());
		g_pMscPlaneFly->Play(300,FALSE,FALSE);	//���ŷɻ�������Ч
	}
	else 	if(GetAsyncKeyState(VK_RIGHT)<0  )	//�ж��ҷ�����Ƿ���
	{
		g_pPhyFight->MoveDirect(DI_RIGHT);		//��Ϸ�߷ɻ������˶����������ƶ�
		g_pPhyFight->CheckErr(TRUE);	

		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x+10,g_pPhyFight->GetLeftTop().y,80,100);
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[2]->GetCxImage());
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

	else			//������ϰ�����û�б�����
	{
		g_pSprFightPlane->SetCxImage(g_pSprFightPlanePic[0]->GetCxImage());
		g_pSprFightPlane->SetDrawCxImageInfo(g_pPhyFight->GetLeftTop().x,g_pPhyFight->GetLeftTop().y,100,100);
	}

	
	if(GetAsyncKeyState('S')<0 )	//�ж�S���Ƿ���,�簴���ҳ��������ӵ��������ӵ�
	{
		if(!g_pPhyShot->GetMoveState() && g_pSprFightPlane->GetVisible())
		{
			POINTF pt={(g_pPhyFight->GetPos().x+g_pPhyFight->GetWidth()/2),(g_pPhyFight->GetPos().y)};
			g_pPhyShot->SetPos(pt);
			g_pPhyShot->SetDes(pt.x,-100);
			g_pPhyShot->SetMoveState(TRUE);
			g_pPhyShot->SetVisible(TRUE);
			g_pSprShot->SetVisible(TRUE);
		}
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

