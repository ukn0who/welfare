/*********************************
	��Ϸ����ͷ�ļ�Sprite.h
*********************************/

#ifndef DEF_Sprite

#define DEF_Sprite

#include <windows.h>
#include "wingdi.h"


/* ��Ϸ����Sprite��������Ϸͼ��Ĵ���������ͻ��� */
class Sprite
{
protected:
	static int m_nNewID;		//��һ�����õľ�����	
	int		m_ID;				//������
	HBITMAP m_hbm;				//λͼ���
	int		m_nWidth,m_nHeight;	//λͼ�����߶�
	int		m_nZOrder;			//Z˳��

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
	
	HBITMAP GetBitmp()	//��ȡλͼ���
	{
		return m_hbm;
	}

	void SetBitmap(HBITMAP hbm)	//����λͼ���
	{
		if(m_hbm!=NULL)
			Release();		//�ͷ���Դ

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