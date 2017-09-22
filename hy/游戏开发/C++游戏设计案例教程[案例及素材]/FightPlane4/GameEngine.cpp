/*************************************
	��Ϸ����Դ�ļ� GameEngine.cpp
*************************************/

#include "GameEngine.h"	

/* ������Ϸ��������Ҫ�õ���ͷ�ļ�����ؿ��ļ� */
#include "winuser.h"
#include "mmsystem.h"
#include "wingdi.h"

#pragma   comment(lib,"user32.lib")
#pragma   comment(lib,"winmm.lib")
#pragma   comment(lib,"gdi32.lib")


/* ��ʼ����Ϸ���澲ָ̬�� */
GameEngine * GameEngine::m_pGameEngine=NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���湹�캯�� */
GameEngine::GameEngine(HINSTANCE hInstance,LPTSTR szWindowClass,LPTSTR szTitle,WORD wIcon,WORD wSmallIcon,BOOL bFullScreen,int nColorbit,int nWidth,int nHeight)
{
	m_pGameEngine=this;			//����ǰʵ��������ָ̬��m_pGameEngine
	m_hInstance=hInstance;			//��������ʵ��Ϊ��ǰ����ʵ�����

	lstrcpy(m_szWindowClass,szWindowClass);	//��������ע�����Ƹ���_szWindowClass
	lstrcpy(m_szTitle,szTitle);					//�����⸳��m_szTitle

	/* ������Ļģʽ�ʹ�С */
	m_bFullScreen=bFullScreen;			
	m_nColorbit=nColorbit;
	m_nWidth=nWidth;
	m_nHeight=nHeight;

	/*����ͼ��͹��*/
	m_wIcon=wIcon;
	m_wSmallIcon=wSmallIcon;
	
	/* ��¼��Ϸ��ʼʱ����´�ѭ��ʱ�� */
	m_lStartTime=timeGetTime();
	m_lNextGameTick=m_lStartTime;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ������������ */
GameEngine::~GameEngine() {   }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ������Ϸ���� */
BOOL	GameEngine::CreateGameWindow()
{
	WNDCLASSEX wcApp;				//����������
	HWND hWnd=NULL;					//�������������ھ��

	int nPosX,nPosY,nWndWidth,nWndHeight;	//��������λ�úʹ�С����
	DWORD dwWinStyle;					//�������ڷ�����
	wcApp.cbSize=sizeof(wcApp);

	//���������Ը�ֵ
	wcApp.lpszClassName=m_szWindowClass;	//���ô�������
	wcApp.style=CS_HREDRAW;				//���崰�ڷ��
	wcApp.lpfnWndProc=WndProc;				//ָ����Ϣ������
	wcApp.hInstance=m_hInstance;				//ָ���崰��Ӧ�ó���ľ��
	wcApp.cbWndExtra=0;		
	wcApp.cbClsExtra=0;
	//���س���ͼ�꣨��
	wcApp.hIconSm=LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wIcon));		
	//���س���ͼ�꣨С��
	wcApp.hIcon=LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wSmallIcon));	
	wcApp.hCursor=LoadCursor(NULL,IDC_ARROW);			//���������ʽ
	wcApp.hbrBackground=(HBRUSH)(COLOR_WINDOW);	//���ô��ڱ���ɫ
	wcApp.lpszMenuName=NULL;							//���ô���û�в˵�

	RegisterClassEx(&wcApp);		//ע�ᴰ����

	/*ʹ��DEVMODE�ṹ������Ļ��ʾģʽ*/
	DEVMODE DevMode;
	ZeroMemory(&DevMode, sizeof(DevMode));	//���ṹDevMode���ڴ�����
	DevMode.dmSize=sizeof(DevMode);		//����DevMode�洢�ռ��Դ洢��Ļ��������
	
	//�õ�ǰ��Ļ��ʾģʽ�������DevMode
	EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&DevMode);

	BOOL bDisplayChange=FALSE;			//��ʶ��Ļ��ʾģʽ�Ƿ�ı�

	//�����Ļ��ʾģʽλ������Ϸ��ͬ
	if(	DevMode.dmBitsPerPel!=(unsigned long)m_nColorbit)	
	{
		DevMode.dmBitsPerPel=m_nColorbit;	//������ʾģʽλ��
		bDisplayChange=TRUE;
	}

	//���ȫ��״̬�µ���Ļ�ߴ��봰�ڲ�ͬ������Ļ�ߴ�С�ڴ���,����Ҫ������ʾģʽ
	if((m_bFullScreen && m_nWidth!=GetSystemMetrics(SM_CXSCREEN))	
		|| m_nWidth>GetSystemMetrics(SM_CXSCREEN))			 
	{
		DevMode.dmPelsWidth=m_nWidth;		//��Ļ���
		DevMode.dmPelsHeight=m_nHeight;		//��Ļ�߶�	
		bDisplayChange=TRUE;		
	}
	
	//�����ʾģʽ�����ı�
	if(bDisplayChange)		
	{
		LONG result=ChangeDisplaySettings(&DevMode,0);	//��̬�޸���Ļ��ʾģʽ	
		//�ж��޸���ʾģʽ�Ƿ�ɹ�
		if(result==DISP_CHANGE_SUCCESSFUL)	
		{	
			// �����̬�޸���ʾģʽ�ɹ������޸���ʾģʽ
			ChangeDisplaySettings(&DevMode, CDS_FULLSCREEN);
		}
		else
		{
			//�����̬�޸���ʾģʽʧ�ܣ��ָ�ԭ������Ļ����
			ChangeDisplaySettings(NULL,0);		//�ָ�ԭ������Ļ����
			return FALSE;						//����FALSE
		}
	}

	/* �жϴ�����ʾ��ʽ����������Ӧ�Ĵ������� */
	if(m_bFullScreen)
	{
		/* ȫ��״̬�� */
		//���ô������Ͻ�λ��
		nPosX=0;
		nPosY=0;
		dwWinStyle=WS_POPUP;			//������Ϸ���ڷ��Ϊ�ޱ߿�ĵ���ʽ����
		nWndWidth=m_nWidth;			//���ô��ڴ�СΪ��Ϸ�����С
		nWndHeight=m_nHeight;	
	}
	else
	{	
		/*��ȫ��״̬�£�������ʾ����Ļ����*/
		//������ϱ߿��Ĵ��ڴ�С
		nWndWidth=m_nWidth+GetSystemMetrics(SM_CXFIXEDFRAME)*2;
		nWndHeight=m_nHeight+GetSystemMetrics(SM_CYFIXEDFRAME)*10;

		//�����ڴ��ھ���ʱ���������Ͻǵ�λ��
		nPosX=(GetSystemMetrics(SM_CXSCREEN)-nWndWidth)/2;		
		nPosY=(GetSystemMetrics(SM_CYSCREEN)-nWndHeight)/2;	
		
		//������Ϸ���ڷ��Ϊ����������ϵͳ�˵��Ĵ���
		dwWinStyle=WS_SYSMENU|WS_CAPTION;		
	}

	//���ú���CreateWindow��������
	hWnd=CreateWindow(m_szWindowClass,		//������ע����
						m_szTitle,			//���ô��ڱ���
						dwWinStyle,			//���ô��ڷ��
						nPosX,				//���ô������Ͻ�X����		
						nPosY,				//���ô������Ͻ�Y����	
						nWndWidth,			//���ô��ڿ��
						nWndHeight,			//���ô��ڸ߶�
						NULL,				//�����ھ��
						NULL,				//�˵��ľ��
						m_hInstance,		//����ʵ�����
						NULL);		

	if(!hWnd)								//������ڽ���ʧ���򷵻�FALSE
		return FALSE;
	ShowWindow(hWnd,SW_SHOWNORMAL);	//��ʾ����
	UpdateWindow(hWnd);						//���´���

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ������ں������� */
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance,LPSTR lpCmdline,int nCmdShow)
{
	MSG msg;					//������Ϣ�ṹ
	
	/* ��ʼ����Ϸ */
	if(!GameInitialize(hInstance))			
		return false;

	/* ��Ϣѭ�� */
	while(true)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))	//������Ϣ
		{
			if(msg.message==WM_QUIT)		//������˳���Ϣ�����˳�ѭ��
				break;

			TranslateMessage(&msg);			//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);			//������Ϣ
		}
		else
		{
			if (!GameEngine::GetGameEngine()->GetPause())	//�ж���Ϸ�Ƿ���ͣ
			{
				/* ��Ϸѭ�� */
				long nTick=timeGetTime();			//��ȡ��ǰ��Ϸʱ��
				//��ȡ�´�ѭ��ʱ��
				long nNextTick=GameEngine::GetGameEngine()->GetNextGameTick();

				if(nTick>nNextTick)				//�����Ϸʱ�䵽���´�ѭ��ʱ��
				{
					//�����´�ѭ����ʱ��
					long nNextGameTick = 
							nTick+GameEngine::GetGameEngine()->GetFrameDelay();
					GameEngine::GetGameEngine()->SetNextGameTick(nNextGameTick);

					KeyEvent(GameEngine::GetGameEngine()->GetWindow());		//���������Ϣ
					//ִ����Ϸ�߼�����
					GameAction(GameEngine::GetGameEngine()->GetWindow());
				}
			}
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϣ���������� */
LRESULT CALLBACK WndProc(HWND hWnd,		//���ھ��
						 UINT message,		 	//��Ϣ��ʶ
						 WPARAM wParam,		//��Ϣ����
						 LPARAM lParam)		//��Ϣ����
{	
	/*�ÿ�������ж���Ϣ��������Ӧ����*/
	switch(message)		
	{
	case WM_CREATE:					//���ڽ�����Ϣ
		GameEngine::GetGameEngine()->SetWindow(hWnd);//���ô��ھ��
		GameStart(hWnd);				//��Ϸ��ʼ
		break;

	case WM_PAINT:					//���ڻ�����Ϣ
		HDC hDC;					//�����ͼ�õ��豸����
		HDC hMemDC;					//�ڴ滺���豸����
		HBITMAP hbmMem,hbmOld;		//�ڴ滺���豸�����е�λͼ
		PAINTSTRUCT ps;				//��ͼ�ṹps
		hDC=BeginPaint(hWnd,&ps);	//��ʼ��ͼ������ȡ��ͼ����hDC

		hMemDC=CreateCompatibleDC(hDC);	//�����ڴ�����豸����
		//�����ڴ����λͼ
		hbmMem=CreateCompatibleBitmap(hDC,GameEngine::GetGameEngine()->GetWidth(),GameEngine::GetGameEngine()->GetHeight());
		hbmOld=(HBITMAP)SelectObject(hMemDC,hbmMem);
		GamePaint(hMemDC);				//����GamePaint()������ͼ���ڴ��豸����
		//���ڴ��豸�����е����ݻ��Ƶ������豸����
		BitBlt(hDC,0,0,GameEngine::GetGameEngine()->GetWidth(),GameEngine::GetGameEngine()->GetHeight(),hMemDC,0,0,SRCCOPY);
		//�ͷ���Դ
		SelectObject(hMemDC,hbmOld);
		DeleteObject(hbmMem);
		DeleteDC(hMemDC);
		EndPaint(hWnd,&ps);			//������ͼ
		break;

	case WM_LBUTTONDOWN:			//������������Ϣ
			//����������������Ϣ������
			MouseLButtonDown(hWnd,LOWORD(lParam),HIWORD(lParam),wParam);
		break;

	case WM_LBUTTONUP:			//������������Ϣ
			//����������������Ϣ������
			MouseLButtonUp(hWnd,LOWORD(lParam),HIWORD(lParam),wParam);
		break;

	case WM_LBUTTONDBLCLK :			//������˫����Ϣ
			//����������˫����Ϣ������
			MouseDoubleClick(hWnd,LOWORD(lParam),HIWORD(lParam),wParam);
		break;

	case WM_RBUTTONDOWN:			//����Ҽ�������Ϣ
			//��������Ҽ�������Ϣ������
			MouseRButtonDown(hWnd,LOWORD(lParam),HIWORD(lParam),wParam);
		break;

	case WM_MOUSEMOVE:				//����ƶ���Ϣ
			//��������ƶ���Ϣ������
			MouseVove(hWnd,LOWORD(lParam),HIWORD(lParam),wParam);
		break;

	case WM_SETFOCUS:				//��Ϸ���ڵõ�������Ϣ
		GameActive(hWnd);			//��Ϸ����
		GameEngine::GetGameEngine()->SetPause(FALSE);
		break;

	case WM_KILLFOCUS:			//��Ϸ����ʧȥ������Ϣ
		GamePause(hWnd);			//��Ϸ��ͣ
		GameEngine::GetGameEngine()->SetPause(TRUE);
		break;

	case WM_CLOSE:					//���ڹر���Ϣ
		if(GameWindowClose(hWnd))	//���ڹر�ǰ�Ĵ���
			DestroyWindow(hWnd);	//�������ٴ�����Ϣ
		break;

	case WM_DESTROY:				//����������Ϣ
		GameEnd();					//��Ϸ�������ͷ���Դ
		PostQuitMessage(0);			//֪ͨWINDOWS�������ѷ�����ֹ����
		break;

	default:
		//û��������Ϣʱ��Windows�����ô�ȱʡ�������д���
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return false;
}

