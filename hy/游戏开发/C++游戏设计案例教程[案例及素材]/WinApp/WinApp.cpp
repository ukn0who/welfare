/********************
	WinApp.cpp
********************/

#include "windows.h"		//����ͷ�ļ�windows.h,Windows����������ļ�
	

#include "resource.h"		//������Դͷ�ļ�resource.h

/*��������*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);//������Ϣ������
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);//����������ں���

/*������ں���*/
int WINAPI WinMain(HINSTANCE hInstance,		//ʵ�����
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdline,
				   int nCmdShow)
{
	WNDCLASS wcApp;			//���崰��
	MSG msg;				//����Windows��Ϣ
	HWND ghWnd=NULL;		//������������ھ��
	char* szAppName="Windows API Application";	//��������
	char *szAppTitle="Windows API���ڳ���";		//���򴰿ڱ���

	//���������Ը�ֵ
	wcApp.style=CS_HREDRAW;			//���崰�ڷ��
	wcApp.lpfnWndProc=WndProc;		//��Ϣ����
	wcApp.cbWndExtra=0;		
	wcApp.cbClsExtra=0;
	wcApp.hInstance=hInstance;		//ָ���崰��Ӧ�ó���ľ��
	//����ͼ����Դ
	wcApp.hIcon=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));	
	//���ع����Դ
	wcApp.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));		
	wcApp.hbrBackground=(HBRUSH)COLOR_WINDOW;//���ô��ڱ���ɫ
	wcApp.lpszMenuName=NULL;			//�����ô��ڲ˵�
	wcApp.lpszClassName=szAppName;	//���ô�������

	RegisterClass(&wcApp);			//ע�ᴰ��

	//���ú���CreateWindow��������
	ghWnd=CreateWindow(szAppName,				//ע�ᴰ������
						szAppTitle,			//���ô��ڱ���
						WS_OVERLAPPEDWINDOW,	//���ô��ڷ��
						100,			//���ô������Ͻ�X����		
						100,			//���ô������Ͻ�Y����	
						350,			//���ô��ڿ��
						300,			//���ô��ڸ߶�
						NULL,		//�����ھ��
						NULL,		//�˵��ľ��
						hInstance,	//����ʵ�����
						NULL);	

	if(NULL==ghWnd)				//������ڽ���ʧ���򷵻�
		return 0;

	ShowWindow(ghWnd,nCmdShow);		//��ʾ����
	UpdateWindow(ghWnd);			//���´���

	//������Ϣѭ��
	while(GetMessage(&msg,NULL,0,0))	//������Ϣ
	{
		TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg);		//������Ϣ
	}
	return msg.wParam;
}

/*��Ϣ������*/
LRESULT CALLBACK WndProc(HWND hwnd,		//���ھ��
						 UINT message,	//��Ϣ��ʶ
						 WPARAM wParam,	//��Ϣ����
						 LPARAM lParam)	//��Ϣ����
{	
	//������Ϣ�ַ���
	LPCSTR  lpszCreate ="�յ�WM_CREATE��Ϣ����������";	
	LPCSTR  lpszDestroy ="�յ�WM_DESTROY��Ϣ�����ڹر�";	
	LPCSTR  lpszCaption ="�յ���Ϣ";				//��Ϣ�Ի������
	LPCSTR  lpszLBTN ="���������£��յ�WM_LBUTTONDOWN��Ϣ";
	LPCSTR  lpszExit ="��ȷ��Ҫ�˳���";

	//�ÿ���������Ϣ������Ӧ����
	switch(message)		
	{
	case WM_CREATE:		//��Ӧ���ڽ�����Ϣ
		//MessageBox( )����������Ϣ��
		MessageBox(GetFocus( ),lpszCreate,lpszCaption,MB_OK|MB_ICONEXCLAMATION);
		break;

	case WM_LBUTTONDOWN:	//��Ӧ������������Ϣ
		MessageBox(GetFocus( ),lpszLBTN,lpszCaption,MB_OK|MB_ICONINFORMATION);
		break;

	case WM_KEYDOWN:						//���̰�����Ϣ
		if(wParam==VK_ESCAPE)				//�ж��Ƿ���ESC��	
			SendMessage(hwnd,WM_CLOSE,NULL,NULL);	//���ʹ��ڹر���Ϣ
		break;

	case WM_CLOSE:					//���ڹر���Ϣ
		if(MessageBox(NULL,lpszExit,lpszCaption,MB_YESNO|MB_DEFBUTTON2|MB_ICONASTERISK)==IDYES)
		{
			DestroyWindow(hwnd);	//�������ٴ�����Ϣ
		}		
		break;

	case WM_DESTROY:			//��Ӧ���ٴ�����Ϣ

		PostQuitMessage(0);		//֪ͨWINDOWS���߳��ѷ�����ֹ����
		break;
	default:
		//û��������Ϣʱ��Windows�����ô�ȱʡ�������д���
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return FALSE;
}
