/********************************
	��Ϸ�������ļ�Cards.cpp
********************************/
#include "Cards.h"
#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ϸ��ʼ�� */
BOOL GameInitialize(HINSTANCE hInstance)
{
	/* �����ﹹ����Ϸ����ʵ���������ó�ʼ��������� */
	
	//��������
	g_pGE=new GameEngine(hInstance,TEXT(g_strTitle),TEXT(g_strTitle),
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ʼ */
void GameStart(HWND hWnd)
{
	/* �������ָ�� */
	long lCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE (IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,lCur);

	/*ѭ�����ÿ�Ƭλ�þ��κͳ�ʼ����Ƭѡ��״̬*/
	int i,j,n,m;
	for( i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)	
		{
			/* ���ÿ�Ƭλ�þ��η�Χ*/
			g_rCardRect[i][j].left=CARSTARTX+(CARDWIDTH+COLSPACE)*j;
			g_rCardRect[i][j].right=g_rCardRect[i][j].left+CARDWIDTH;
			g_rCardRect[i][j].top=CARSTARTY+(CARDHEIGHT+ROWSPACE)*i;
			g_rCardRect[i][j].bottom=g_rCardRect[i][j].top+CARDHEIGHT;
			
			g_nCardState[i][j]=INITSELECT;	//��ʼ����Ƭѡ��״̬
		}
	}	

	/*��ʼ����Ƭͼ����λ��*/
	srand((unsigned)time(NULL));	// ��ʼ�����������
	for(i=0;i<2;i++)	//2����ѭ���������ҽ������ſ�Ƭͼ����ͬ
	{
		for(j=0;j<ROWS*COLS/2;j++)	//ѭ��ȷ��m�С�n�е�ͼ����Ϊj
		{
			do{
				m=rand()%ROWS;		//���ȷ����Ƭ�С��к�
				n=rand()%COLS;				
			}while(g_nCardState[m][n]!=INITSELECT);	//�����Ƭѡ��״̬Ϊ��ʼ��
			g_nCardPattern[m][n]=j;				//���øÿ�Ƭͼ��
			g_nCardState[m][n]=NOSELECT;	//���øÿ�Ƭѡ��״̬Ϊδѡ��
		}
	}

	g_nStartTime=timeGetTime();	//������Ϸ��ʼʱ��
	g_nTimeCount=20000;			//�涨��Ϸʱ��	

	SetRect(&g_rTimeBarFrame,100,150,700,170);	//����ʱ�����߿����	
	g_nTimeBarLength=0;			//��ʼ��ʱ��������
	//��ʼ�����������С��к�
	g_nSelectRow1=g_nSelectRow2=g_nSelectCol1=g_nSelectCol2=-1; 
	g_nSelected=0;			//��ʼ����ȷ��Ե�ͼ������
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ�߼� */
void GameAction(HWND hWnd)
{
	/* ������Ϸ������ʱ���ʱ�������� */
	long nCurrentTimes=timeGetTime()-g_nStartTime;
	if(nCurrentTimes<g_nTimeCount)
	{
		g_nTimeBarLength=nCurrentTimes*596/g_nTimeCount;	
	}
	
	/*�������2�ſ�Ƭ�����������ж�2�ſ�Ƭͼ���Ƿ���ͬ*/
	if(g_nSelectRow2!=-1)
	{
		if(g_nCardPattern[g_nSelectRow1][g_nSelectCol1]==g_nCardPattern[g_nSelectRow2] [g_nSelectCol2])
		{
			/*������ſ�Ƭͼ����ͬ*/
			//���ÿ�Ƭ״̬Ϊ����ȷ���
			g_nCardState[g_nSelectRow1][g_nSelectCol1]=SELECTOK;		
			g_nCardState[g_nSelectRow2][g_nSelectCol2]=SELECTOK;

			//���ÿ�Ƭͼ��Ϊ��	
			g_nCardPattern[g_nSelectRow2][g_nSelectCol2]=NULLPATTERN;
			g_nCardPattern[g_nSelectRow1][g_nSelectCol1]=NULLPATTERN;

			g_nSelected++;	//����ȷ��Կ�Ƭ������
			//���õ���ѡ���С��к�
			g_nSelectRow1=g_nSelectRow2=g_nSelectCol1=g_nSelectCol2=-1;		
		}
		else
		{
			/* ������ſ�Ƭͼ����ͬ */
			if(timeGetTime()-g_nTimeDelayStart>200)	/*ͼ����ʾ��ʱ0.2��*/
			{
				//���ÿ�Ƭ״̬Ϊδѡ��
				g_nCardState[g_nSelectRow1][g_nSelectCol1]=NOSELECT;
				g_nCardState[g_nSelectRow2][g_nSelectCol2]=NOSELECT;
				//���õ���ѡ���С��к�
				g_nSelectRow1=g_nSelectRow2=g_nSelectCol1=g_nSelectCol2=-1;	
			}
		}
	}

	InvalidateRect(hWnd,NULL,FALSE);	//ǿ��ˢ�´���
	UpdateWindow(hWnd);

	/* �����Ϸʱ���Ƿ񳬳��涨ʱ��*/
	if(nCurrentTimes<g_nTimeCount)
	{
		/*δ�����涨ʱ��*/
		if(g_nSelected==6)	//����Ƿ����п�Ƭ����ѡ�꣬��ѡ����Ӯ
		{
			if(MessageBox(g_pGE->GetWindow(),"ȫ����Գɹ�����Ӯ�ˣ�\r\nҪ������Ϸ��","��Ӯ�ˣ�",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
			{	

				GameStart(hWnd);		//���¿�ʼ
			}
			else
				DestroyWindow(hWnd);	//�˳�����
		}	
	}
	else	
	{
		/*��Ϸʱ�䳬���涨ʱ�䣬����Ϸ��ʧ��*/
		if(MessageBox(g_pGE->GetWindow(),"ʱ�䵽�������ˣ�\r\nҪ������Ϸ��","�����ˣ�",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		{	
			GameStart(hWnd);
		}
		else
			DestroyWindow(hWnd);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��굥���¼����� */
void MouseClick(HWND hWnd,int x,int y,WPARAM wParam)
{
	/* ��������Ӿ������굥���¼�������� */
	POINT pt={x,y};		//������굥����

	//ѭ���ж���굥�����Ƿ��ڿ�Ƭ���η�Χ��				
	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			if(PtInRect(&g_rCardRect[i][j],pt))//�жϿ�Ƭ�Ƿ񱻵���
			{
				//��Ƭδ��ѡ�����ѱ������Ŀ�Ƭ��������2��
				if(g_nCardState[i][j]==NOSELECT && g_nSelectRow2==-1)	
				{
					if(g_nSelectRow1 == -1 )	//�ǵ�1�ε���
					{
						g_nSelectRow1=i;		//���õ�1��ѡ��Ŀ�Ƭ���к�		
						g_nSelectCol1=j;
					}
					else
					{
						g_nSelectRow2=i;		//���õ�2��ѡ��Ŀ�Ƭ���к�		
						g_nSelectCol2=j;				
						g_nTimeDelayStart=timeGetTime();	//������ʱ����	
					}
					g_nCardState[i][j]=SELECTED;	//���ÿ�Ƭ״̬Ϊ��ѡ��
					return;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ⱦ��Ϸ���� ***/
void GamePaint(HDC hDC)
{
	/* ���ƴ��ڵ�ɫ */
	RECT rBG;
	GetClientRect(g_pGE->GetWindow(), &rBG);		//��ȡ���ھ��η�Χ	
	HBRUSH hbrBG=(HBRUSH)GetStockObject(WHITE_BRUSH);	//ѡ�ñ�׼��ɫ��ˢ
	FillRect(hDC,&rBG,hbrBG);		//���Ʊ���
	DeleteObject(hbrBG);			//ɾ����ˢ

	/* ���Ʊ��� */
	LOGFONT lf={0};			//����Ĭ���߼�����
	lf.lfHeight=80;			//��������߶�
	lf.lfWidth=60;				//����������
	lf.lfWeight=800;			//���������ϸ
	lf.lfCharSet=DEFAULT_CHARSET;		//�����ַ���
	strcpy(lf.lfFaceName,"����");			//��������	
	HFONT hFont=CreateFontIndirect(&lf);	//��������	
	HFONT hFontOld=(HFONT)SelectObject(hDC,hFont);	//ѡ������
	TextOut(hDC,100,30,g_strTitle,strlen(g_strTitle));	//�����ı�	

	SelectObject(hDC,hFontOld);			//�滻����
	DeleteObject(hFont);				//ɾ������

	/* ����ʱ���� */
	HBRUSH hbr=CreateSolidBrush(RGB(128,128,128));	//������ˢ
	HBRUSH hbrOld=(HBRUSH)SelectObject(hDC,hbr);	//ѡ�û�ˢ
	FrameRect(hDC,&g_rTimeBarFrame,hbr);				//���Ʊ߿�
	//����ʱ����
	Rectangle(hDC,g_rTimeBarFrame.left+2,g_rTimeBarFrame.top+2,g_rTimeBarFrame.left+2+g_nTimeBarLength,g_rTimeBarFrame.bottom-2);
	SelectObject(hDC,hbrOld);		//�����ˢ				

	/* ���ƿ�Ƭ */
	//������Ƭ���滭ˢ
	HBRUSH hbrBK=CreateHatchBrush(HS_BDIAGONAL,RGB(128,128,128)); 
	HBRUSH hbrCard;				//���忨Ƭ���滭ˢ
	RECT r;						//���忨Ƭ��ͼ���η�Χ

	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			FrameRect(hDC,&g_rCardRect[i][j],hbr);//	���ƿ�Ƭ�߿�	
			r=g_rCardRect[i][j];			//���ÿ�Ƭͼ�����η�Χ

			/* �жϿ�Ƭ�Ƿ�δ������ѡ��*/
			if(g_nCardState[i][j]==NOSELECT)	//
			{		
				/*δ������ѡ��,���Ʊ���ͼ��*/
				InflateRect(&r,-10,-10);	//��С����	
				FillRect(hDC,&r,hbrBK);		//�����ñ���ͼ����ˢ���ľ���
			}
			else
			{	/*������ѡ��,��������ͼ��*/
				InflateRect(&r,-20,-20);	//��С����	
				switch(g_nCardPattern[i][j])	//ѡ����Ƶ�ָ����ͼ��
				{
				case 0:
					hbrCard=CreateSolidBrush(RGB(128,255,0));	//������ˢ
					SelectObject(hDC,hbrCard);					//ѡ�û�ˢ
					RoundRect(hDC,r.left,r.top,r.right,r.bottom, 10,10);	//����Բ�Ǿ���
					SelectObject(hDC,hbrOld);		//�����ˢ				
					break;

				case 1:
					hbrCard=CreateSolidBrush(RGB(255,128,255));
					SelectObject(hDC,hbrCard);		
					RoundRect(hDC,r.left,r.top,r.right,r.bottom, 10,10);	//����Բ�Ǿ���
					SelectObject(hDC,hbrOld);					
					break;

				case 2:
					hbrCard=CreateSolidBrush(RGB(255,128,128));
					SelectObject(hDC,hbrCard);		
					Rectangle(hDC,r.left,r.top,r.right,r.bottom);	//���ƾ���
					SelectObject(hDC,hbrOld);						
					break;

				case 3:
					hbrCard=CreateSolidBrush(RGB(0,128,128));
					SelectObject(hDC,hbrCard);		
					Rectangle(hDC,r.left,r.top,r.right,r.bottom);	//���ƾ���
					SelectObject(hDC,hbrOld);					
					break;

				case 4:
					hbrCard=CreateSolidBrush(RGB(128,0,255));
					SelectObject(hDC,hbrCard);		
					Ellipse(hDC,r.left,r.top,r.right,r.bottom);		//����Բ��
					SelectObject(hDC,hbrOld);			
					break;

				case 5:
					hbrCard=CreateSolidBrush(RGB(255,0,128));
					SelectObject(hDC,hbrCard);		
					Ellipse(hDC,r.left,r.top,r.right,r.bottom);		//����Բ��
					SelectObject(hDC,hbrOld);			
					break;

				default:
					/* ��Ƭͼ��Ϊ��,���ư�ɫ������	*/
					//ѡ�ñ�׼��ɫ��ˢ
					hbrCard=(HBRUSH)GetStockObject(WHITE_BRUSH);	
					FillRect(hDC,&g_rCardRect[i][j],hbrCard);		//���ư�ɫ����	
					break;	
				}
				DeleteObject(hbrCard);			//ɾ����ˢ	
			}
		}
	}
	
	/*����GDI����*/
	DeleteObject(hbrBK);
	DeleteObject(hbr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameEnd()
{
	delete g_pGE;	//�����Ϸ����ָ��	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ͣ */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���ڹر� */
BOOL GameWindowClose(HWND hWnd)
{
	/* ��Ϸ���ڹر�ǰ�Ĵ������ */
	if(MessageBox(g_pGE->GetWindow(),"��ȷ��Ҫ�˳���","�˳���Ϸ",MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}
