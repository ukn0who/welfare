/*********************************
	��Ϸ����ͷ�ļ�Sprite.h
*********************************/

#ifndef DEF_Sprite

#define DEF_Sprite

#include <windows.h>
#include "wingdi.h"
#include "cximagelib\\ximage.h"

typedef  int		DRAWTYPE;			//��������
const DRAWTYPE		DT_NULL=0,			//��
					DT_DRAW=1,			//Draw()����
					DT_ALPHA=2,			//DrawAlpha()����
					DT_GRAY=3,			//DrawGray()����
					DT_TRANSALPHA=4,	//DrawTransAlpha()����
					DT_ANIMA=5,			//DrawAnima()����
					DT_RECT=6,			//DrawRect()����
					DT_CXIMAGE=7;	



/* ��Ϸ����Sprite��������Ϸͼ��Ĵ���������ͻ��� */
class Sprite
{
protected:
	static int m_nNewID;		//��һ�����õľ�����	
	int		m_ID;				//������
	HBITMAP m_hbm;				//λͼ���
	int		m_nWidth,m_nHeight;	//λͼ�����߶�
	int		m_nZOrder;			//Z˳��

	/*���������ڶ����ĳ�Ա����*/
	int		m_nFrameWidth,m_nFrameHeight;	//λͼ�й��ɶ����ĵ�֡ͼ��ĸ߶ȺͿ��
	int		m_nRowCount,m_nColCount;		//λͼ�й��ɶ�����ϵ��֡���С�������
	int		m_nRow,m_nCol;					//����ϵ��֡�еĵ�ǰ֡�С��б��

	int		m_nFrameDelay;		//ÿ������������ʱ��ʾ֡��
	unsigned long	m_lNextFrameTime;		//��һ֡����ʱ��
	BOOL	m_bInitAnima;		//�Ƿ��Ѿ���ʼ��


	/*��ʹ�þ��������ʱ�����ṩ�ľ�������*/

	DRAWTYPE m_dt;		//��ͼ����
	
	int		m_nX,m_nY;		//����ʱ��DCʱ���Ͻ�����
	BOOL	m_bTrans;		//�Ƿ�͸��
	COLORREF	m_crTrans;	//͸��ɫ
	int		m_nAlpha;		//��͸����

	//����������DrawTransAlpha()�����ı���ͼ���Ͻ����ꡢ�����߶�
	int		m_nXBack,m_nYBack,m_nWidthBack,m_nHeightBack;		

	//����������DrawRect()�����ľ����������Ͻ����ꡢ�����߶�
	int		m_nRectX,m_nRectY,m_nRectWidth,m_nRectHeight;
	
	BOOL	m_bVisible;		//�Ƿ�ɼ�(�粻�ɼ�������Ҫ���)


	CxImage * m_cxImage;	//CxImage����ָ��

public:
	/*���캯�������ݲ�ͬ�Ĳ���������ͬ��Spriteʵ��*/
	Sprite();	
	Sprite(HINSTANCE hInstance,LPTSTR szFileName);	//����λͼ�ļ�����������
	Sprite(HINSTANCE hInstance,UINT uRcID);	//����λͼ��ԴID��������
	//����ָ���Ĵ�С����ɫ��������
	Sprite(HDC hDC,int nWidth,int nHeight,COLORREF crColor=RGB(255,255,255));
	
	virtual ~Sprite();
	
	/****������Ա���ʷ���**********/
	
	
	int GetID()			//��ȡ����ͼ����
	{
		return m_ID;
	}
	
	HBITMAP GetBitmp()  //��ȡλͼ���
	{
		return m_hbm;
	}

	void SetBitmap(HBITMAP hbm)	//����λͼ���
	{
		if(m_hbm!=NULL)
			Release();

		m_hbm=hbm;

		BITMAP  bm;
		GetObject(m_hbm,sizeof(BITMAP),&bm);
		m_nWidth=bm.bmWidth;
		m_nHeight=bm.bmHeight;

	}

	int GetHeight()		//��ȡ����ͼ��߶�
	{
		return m_nHeight;
	}

	int GetWidth()		//��ȡ����ͼ����
	{
		return m_nWidth;
	}
	
	void SetZOrder(int nZOrder)	//����Z˳��
	{
		m_nZOrder=nZOrder;
	}

	int GetZOrder()				//��ȡZ˳��
	{
		return m_nZOrder;
	}

	/*** ���淽�� ***/

	//�ͷ���Դ
	void Release();

	//����ָ���Ĵ�С����ɫ����λͼ
	BOOL Create(HDC hDC,int nWidth,int nHeight,COLORREF crColor=RGB(0,0,0));

	//�����ļ��е�λͼ
	BOOL Load(HINSTANCE hInstance,LPTSTR szFileName);

	//������Դ�е�λͼ
	BOOL Load(HINSTANCE hInstance,UINT uRcid);
	
	//����λͼ��������bTransΪTRUE����ָ����ɫcrTransparent�ο�λͼ
	void Draw(HDC hDC,int x,int y,BOOL bTrans=FALSE,COLORREF crTransparent=RGB(0,0,0));
	
	//����λͼ�е�һ�����������ڵ�ͼ��
	void DrawRect(HDC hDC,int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));
	
	//���ư�͸��λͼ,��͸����nAphaȡֵΪ0~255
	void DrawAlpha(HDC hDC,int x,int y,int nAlpha);

	
	//���ƻҶ�λͼ��������Ϊ�ο�
	void DrawGray(HDC hDC,int x,int y,BOOL bTrans=FALSE,COLORREF crTransparent=RGB(0,0,0));	

	//���ư�͸���ο�λͼ
	void DrawTransAlpha( HDC hdcBack,	// ����DC
					int nXBack,			// ����ͼ���Ͻ�X����
					int nYBack,			// ����ͼ���Ͻ�Y����
					int nWidthBack,     // ����ͼ���
					int nHeightBack,    // ����ͼ�߶�
					int nXFore,			// ǰ��ͼ���Ͻ�X����
					int nYFore,			// ����ͼ���Ͻ�Y����
					int nAlpha=100,		// ��͸����
					COLORREF crTrans=RGB(0,0,0));	//�ο�ɫ

	/*���������ڶ����ĳ�Ա����*/
	//��ʼ����������
	void InitAnima(int nRowCount,int nColCount,int nFrameDelay);

	//��hDC�ϵ�ָ��λ��(x,y)�����Ƶ�nRow��nCol�е�ͼ�񣬿�����Ϊ�ο�
	void DrawRowCol(HDC hDC,int x,int y,int nRow,int nCol,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));
	
	//���ƶ���֡
	void DrawAnima(HDC hDC,int x,int y,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));
	
	/*����������ʹ�þ���������ͼʱʱ����ķ���*/
	//��������DrawTransAlpha()�����Ĳ���
	void SetDrawAlphaInfo(int x,int y,int nAlpha=255);

	//��������Draw()�����Ĳ���
	void SetDrawInfo(int x,int y,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));

	//��������DrawAnima()�����Ĳ���
	void SetDrawAnimaInfo(int x,int y,int nRow,BOOL bTrans,COLORREF crTrans=RGB(0,0,0));

	//��������DrawGray()�����Ĳ���
	void SetDrawGrayInfo(int x,int y,COLORREF crTrans=RGB(0,0,0));

	//��������DrawRect()�����Ĳ���
	void SetDrawRectInfo(int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans,COLORREF crTrans=RGB(0,0,0));

	//��������DrawTransAlpha()�����Ĳ���
	void SetDrawTransAlphaInfo(int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nAlpha=255,COLORREF crTrans=RGB(0,0,0));

	//ͳһ�Ļ�ͼ�ӿ�
	void DrawSprite(HDC hDC);
	
	//���þ����Ƿ�ɼ�
	void SetVisible(BOOL bVisible)
	{
		m_bVisible=bVisible;
	}

	//��ȡ�����Ƿ�ɼ�	
	BOOL GetVisible()
	{
		return m_bVisible;
	}

	/* ����������CxImage�ķ��� */ 
	//�������飬����ͼ���ļ�szFileName�����������Ƿ���ת��ΪHBITMAP���Ա���ԭ�еķ��������
	Sprite(LPTSTR szFileName,BOOL bConvertBmp=FALSE);

	//����ͼ���ļ�szFileName�����������Ƿ���ת��ΪHBITMAP���Ա���ԭ�еķ��������
	BOOL LoadCxImage(LPTSTR szFileName,BOOL bConvertBmp=FALSE);

	//��ȡCxImage����
	CxImage * GetCxImage() const
	{
		return m_cxImage;
	}
	//����CxImage����
	void SetCxImage(CxImage * image) 
	{
		m_cxImage=image;
	}

	//����x��yΪ���Ͻǣ���nWidth����nHeight�ķ�Χ�ڻ���ͼ�񣬲������ö���֡��ʱΪnFrameDelay
	void DrawCxImage(HDC hDC,int x,int y,int nWidth=0,int nHeight=0,int nFrameDelay=100);


	//��������DrawCxImage()�����Ĳ���
	void SetDrawCxImageInfo(int x,int y,int nWidth=0,int nHeight=0,int nFrameDelay=100);



private:
	//�Զ���Ļ����ο�ͼ�ķ���
	void TransBitmap( HDC hdcDest,      // Ŀ��DC
					int nXDest,			// Ŀ�����Ͻ�X����
					int nYDest,			// Ŀ�����Ͻ�Y����
					int nWidthDest,     // Ŀ����
					int nHeightDest,    // Ŀ��߶�
					HDC hdcSrc,         // ԴDC
					int nXSrc,			// ԴX���
					int nYSrc,			// ԴY���
					int nWidthSrc,      // Դ���
					int nHeightSrc,     // Դ�߶�
					COLORREF crTrans=RGB(255,255,255)  // ͸��ɫ
					);

};

#endif