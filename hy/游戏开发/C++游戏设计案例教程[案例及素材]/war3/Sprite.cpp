/*********************************
	��Ϸ��������ļ�Sprite.cpp
*********************************/

#include "Sprite.h"

#pragma   comment(lib,"gdi32.lib")		//���ÿ�
#pragma   comment(lib,"msimg32.lib")

#pragma comment(lib,"cximagelib\\cximage.lib")

int Sprite::m_nNewID=1;		//��ʼ��������

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ���캯�������ݲ�ͬ�Ĳ���������ͬ��Spriteʵ��*/

/* Ĭ�Ϲ��캯�� */
Sprite::Sprite()
{
	m_hbm=NULL;
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ����λͼ�ļ�����Spriteʵ�� */
Sprite::Sprite(HINSTANCE hInstance,LPTSTR szFileName)
{
	//����ָ����λͼ�ļ�
	Load(hInstance,szFileName);
	m_ID=m_nNewID;
	m_nNewID++;	
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ����λͼ��Դ����Spriteʵ�� */
Sprite::Sprite(HINSTANCE hInstance,UINT uRcID)
{
	Load(hInstance,uRcID);
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ���Ĵ�С����ɫ����Spriteʵ��*/
Sprite::Sprite(HDC hDC,int nWidth,int nHeight,COLORREF crColor)
{
	Create(hDC,nWidth,nHeight,crColor);//����Create����λͼ
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��������*/
Sprite::~Sprite()
{
	Release();		//����Release()�������ͷ���Դ
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Release���������ͷ���Դ */
void Sprite::Release()
{
  if (m_hbm != NULL)
  {
    DeleteObject(m_hbm);
    m_hbm = NULL;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ���Ĵ�С����ɫ����λͼ*/
BOOL Sprite::Create(HDC hDC,int nWidth,int nHeight,COLORREF crColor)
{
	Release();	//�ͷ�ԭ��λͼ��Դ

	//��������λͼ
	m_hbm=CreateCompatibleBitmap(hDC,nWidth,nHeight);
	if(m_hbm==NULL)
		return false;

	//���ÿ�Ⱥ͸߶�
	m_nWidth = nWidth;	
	m_nHeight = nHeight;

	//ͨ����λͼ�л���������������λͼ
	HDC hdcMem = CreateCompatibleDC(hDC);		//���������豸
	HBRUSH hBrush = CreateSolidBrush(crColor);	//���嵥ɫ��ˢ
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, m_hbm);		//��λͼѡ���豸
	RECT rc = {0, 0, nWidth, nHeight };			//������δ�С
	FillRect(hdcMem, &rc, hBrush);				//����������

	// ������ʱ�����ͷ���Դ
	SelectObject(hdcMem, hOldBitmap);	//���λͼm_hbm��ʹ����Ա���
	DeleteDC(hdcMem);
	DeleteObject(hBrush);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����ָ����λͼ�ļ� */
BOOL Sprite::Load(HINSTANCE hInstance,LPTSTR szFileName)
{
	Release();	//�ͷ�ԭ��λͼ��Դ	
	//����ָ����λͼ
	m_hbm=(HBITMAP)LoadImage(NULL,szFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//ͨ��BITMAP�ṹ����λͼ��Ⱥ͸߶�	
	BITMAP  bm;
	GetObject(m_hbm,sizeof(BITMAP),&bm);
	m_nWidth=bm.bmWidth;
	m_nHeight=bm.bmHeight;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����λͼ��Դ */
BOOL Sprite::Load(HINSTANCE hInstance,UINT uRcid)
{
	Release();	//�ͷ�ԭ��λͼ��Դ	
	//����ָ����λͼ��Դ
	m_hbm=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(uRcid),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	//ͨ��BITMAP�ṹ����λͼ��Ⱥ͸߶�	
	BITMAP  bm;
	GetObject(m_hbm,sizeof(BITMAP),&bm);
	m_nWidth=bm.bmWidth;
	m_nHeight=bm.bmHeight;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��hDC��ָ��λ��(x,y)����λͼ,�����͸���ο�λͼ(bTransΪTRUE),ָ��crTransΪ͸��ɫ */
void Sprite::Draw(HDC hDC,int x,int y,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//���������豸
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);	//��λͼѡ������豸������¼�¾ɵľ��

		if (bTrans)
			//���͸��λͼ
			 TransparentBlt(hDC, x, y,m_nWidth,m_nHeight, hdcMem, 0,0,m_nWidth,m_nHeight, crTrans);
		else
			//�����͸��λͼ
			BitBlt(hDC, x, y, m_nWidth,m_nHeight, hdcMem, 0,0, SRCCOPY);
		// ������ʱ�����ͷ���Դ
		SelectObject(hdcMem,hOldBmp);	
		DeleteObject(hOldBmp);
		DeleteDC(hdcMem);		
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��hDC��ָ��λ��(x,y)����λͼ��ָ���ľ��������ڵ�ͼ�����Ͻ�����Ϊ(nRectX,nRectY),
 ��nRectWidth,��nRectHeight,�����͸���ο�ͼ(bTransΪTRUE),ָ��crTransΪ͸��ɫ*/
void Sprite::DrawRect(HDC hDC,int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//���������豸
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);	//��λͼѡ������豸������¼�¾ɵľ��

		if (bTrans)
			//���͸��λͼ
			TransparentBlt(hDC, x, y, nRectWidth, nRectHeight, hdcMem, nRectX,nRectY,nRectWidth, nRectHeight, crTrans);
			// TransBitmap(hDC, x, y, iRectWidth, iRectHeight, hdcMem, iRectX,iRectY,iRectWidth, iRectHeight, crTransparent);
		else
			//�����͸��λͼ
			BitBlt(hDC, x, y,nRectWidth, nRectHeight, hdcMem, 0,0, SRCCOPY);


		// ������ʱ�����ͷ���Դ
		SelectObject(hdcMem,hOldBmp);	
		DeleteDC(hdcMem);				
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��hDC��ָ��λ��(x,y)���͸����ΪnAlpha(0~255)�İ�͸��ͼ�� */
void Sprite::DrawAlpha(HDC hDC,int x,int y,int nAlpha)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//���������豸
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);

		//����bf�ṹ
		BLENDFUNCTION bf;
		bf.BlendOp=AC_SRC_OVER;
		bf.BlendFlags=0;
		bf.SourceConstantAlpha=nAlpha;
		bf.AlphaFormat=0x00;
		//�����͸��ͼ��
		AlphaBlend(hDC, x, y, m_nWidth, m_nHeight, hdcMem, 0,0,GetWidth(), GetHeight(), bf);
		
		// ������ʱ�����ͷ���Դ
		SelectObject(hdcMem,hOldBmp);	
		DeleteDC(hdcMem);			
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���ư�͸���ο�ͼ*/
void Sprite::DrawTransAlpha(HDC hdcBack, int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nAlpha,	COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL && nAlpha >0)
	{
		HDC hdcMem= CreateCompatibleDC(hdcBack);		//���������豸

		//����һ���뱳��ͬ����С����ʱͼ��	
		RECT rBackRect={nXBack,nYBack,nWidthBack, nHeightBack};
		HBITMAP	hbmTmp=CreateCompatibleBitmap(hdcBack,nWidthBack,nHeightBack); 

		HBITMAP hbmBk=(HBITMAP)SelectObject(hdcBack,hbmTmp);	//�������ͼ��

		RECT rForeRect={nXFore,nYFore,nXFore+m_nWidth,nYFore+m_nHeight};
		RECT rTransRect,rTransRect2;

		//��ȡǰ�������뱳�����εĽ���,�粻�ཻ������Ҫ������ɫ���� 
		if(IntersectRect(&rTransRect,&rBackRect,&rForeRect))
		{
			BITMAP  bm,bmBk;	
			GetObject(m_hbm,sizeof(BITMAP),&bm);
			BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //�����ݴ�����
			GetBitmapBits(m_hbm,bm.bmHeight*bm.bmWidthBytes,px); //ȡ��Դλͼ�����ص�� RGB ֵ���� px ������

			GetObject(hbmBk,sizeof(BITMAP),&bmBk);
			BYTE * pxBk = new unsigned char[bmBk.bmHeight*bmBk.bmWidthBytes];  //�����ݴ�����

			GetBitmapBits(hbmBk,bmBk.bmHeight*bmBk.bmWidthBytes,pxBk); //ȡ��Դλͼ�����ص�� RGB ֵ���� pxBk������

			rTransRect2=rTransRect;
			OffsetRect (&rTransRect2, -rForeRect.left,-rForeRect.top ) ;	//ƫ�ƾ�������
			
			int pb=bm.bmBitsPixel/8;		//��ȡÿ������ռ�ֽ���
			int pbBk=bmBk.bmBitsPixel/8;

			//dy1Ϊ����ͼ��������,dy2Ϊǰ��ͼ��������
			//dx1Ϊ����ͼ��������,dx2Ϊǰ��ͼ��������
			int dx1,dx2,dy1,dy2;	
			//ѭ�������ؽ��м��㣬������ǰ������Ҫ���м�������طֱ��ڸ��Զ�Ӧ�ľ���rTransRect��rTransRect2�ķ�Χ��ѭ�� 
			for(dy1=rTransRect.top,dy2=rTransRect2.top;dy1<rTransRect.bottom;dy1++,dy2++)
				for(dx1=rTransRect.left,dx2=rTransRect2.left;dx1<rTransRect.right;dx1++,dx2++)
				{
					int nBackRGB_B=dy1*bmBk.bmWidthBytes+dx1*pbBk;		//���㱳��ͼ������ʼλ��
					int nForeRGB_B=dy2*bm.bmWidthBytes+dx2*pb;			//����ǰ��ͼ������ʼλ��
					
					if( RGB(px[nForeRGB_B+2],px[nForeRGB_B+1],px[nForeRGB_B])!=crTrans)
					{
					pxBk[nBackRGB_B] = (px[nForeRGB_B]*nAlpha+pxBk[nBackRGB_B]*(255-nAlpha))/255;	//��Bɫ��ֵ����nAlpha���� px ���
					pxBk[nBackRGB_B+1] =(px[nForeRGB_B+1]*nAlpha+pxBk[nBackRGB_B+1]*(255-nAlpha))/255;//�� G ɫ��ֵ����nAlpha���� px ���
					pxBk[nBackRGB_B+2] = (px[nForeRGB_B+2]*nAlpha+pxBk[nBackRGB_B+2]*(255-nAlpha))/255;//�� R ɫ��ֵ���� nAlpha���� px ���
					}
				}
			
			SetBitmapBits(hbmTmp,bmBk.bmHeight*bmBk.bmWidthBytes,pxBk); //���ñ���ͼ����
			HBITMAP hbmOld=(HBITMAP)SelectObject(hdcMem,hbmTmp); 
			BitBlt(hdcBack,0,0,rBackRect.right,rBackRect.bottom,hdcMem,0,0,SRCCOPY);
	
			delete[] px;		//ɾ������
			delete[] pxBk;
			SelectObject(hdcMem,hbmOld);
		}
	
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);				//ɾ�������豸
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���ƻҶ��ο�ͼ*/
void Sprite::DrawGray(HDC hDC,int x,int y,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//���������豸

	
		BITMAP  bm;	
		GetObject(m_hbm,sizeof(BITMAP),&bm);
		BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //�����ݴ�����
		GetBitmapBits(m_hbm,bm.bmHeight*bm.bmWidthBytes,px); //ȡ��Դλͼ�����ص�� RGB ֵ���� px ������

	
		int pb=bm.bmBitsPixel/8;
		//ѭ������Ҷ�ֵ
		for(int dy=0;dy<bm.bmHeight;dy++)
		{	for(int dx=0;dx<bm.bmWidth;dx++)
			{
			int rgb_b=dy*bm.bmWidthBytes+dx*pb;	
			px[rgb_b] =(px[rgb_b] *299+px[rgb_b+1]*587+px[rgb_b+2] *114)/1000;
			px[rgb_b+1] =px[rgb_b] ;
			px[rgb_b+2] =px[rgb_b] ;
			};
		}
		//������ʱλͼ���Դ洢�Ҷ�ͼ��
		HBITMAP	hbmTmp=CreateCompatibleBitmap(hDC,bm.bmWidth,bm.bmHeight); 	
		SetBitmapBits(hbmTmp,bm.bmHeight*bm.bmWidthBytes,px);

		HBITMAP hOldBmp=(HBITMAP)SelectObject(hdcMem,hbmTmp); 

		if (bTrans)
			//���͸��λͼ
			 TransparentBlt(hDC, x, y,bm.bmWidth,bm.bmHeight, hdcMem, 0,0,bm.bmWidth,bm.bmHeight, crTrans);
		else
			//�����͸��λͼ
			BitBlt(hDC, x, y, bm.bmWidth,bm.bmHeight, hdcMem, 0,0, SRCCOPY);
	
		
		delete[] px;		//ɾ������

		SelectObject(hdcMem,hOldBmp);	
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);				//ɾ�������豸
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* ����͸���ο�λͼ */
void Sprite::TransBitmap( HDC hdcDest, int nXDest,int nYDest,int nWidthDest,int nHeightDest,
						 HDC hdcSrc,int nXSrc,int nYSrc,  int nWidthSrc, int nHeightSrc,COLORREF crTrans)
{
	// ��������λͼ
	HBITMAP hbmTmp = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	
	// ������ɫλͼ
	HBITMAP hbmMask = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);	
	//���������豸����
	HDC		hdcMem = CreateCompatibleDC(hdcDest);
	HDC		hdcMask = CreateCompatibleDC(hdcDest);

	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmTmp);
	HBITMAP hbmMaskOld = (HBITMAP)SelectObject(hdcMask, hbmMask);

	// ��ԴDC�е�λͼ��������ʱ�豸������
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, SRCCOPY);
	else
		StretchBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, 
					hdcSrc, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// ����͸��ɫ
	SetBkColor(hdcMem, crTrans);

	// ����͸������Ϊ��ɫ����������Ϊ��ɫ���ɰ�λͼ
	BitBlt(hdcMask, 0, 0, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCCOPY);

	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hdcMem, RGB(0,0,0));
	SetTextColor(hdcMem, RGB(255,255,255));
	BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// ͸�����ֶ�Ӧ�ı������ֲ��䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(255,255,255));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// "��"����,��������Ч��
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCPAINT);

	// ������ʱ���ݣ��ͷ���Դ
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	SelectObject(hdcMask, hbmMaskOld);
	DeleteDC(hdcMask);
	DeleteObject(hbmTmp);
	DeleteObject(hbmMask);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*���������ڶ����ĳ�Ա����*/

/*ʹ����nRowCount����nColCount������֡��ʾ��ʱnFrameDelay����ʼ���������� */
void Sprite::InitAnima(int nRowCount,int nColCount,int nFrameDelay)
{
	if (m_hbm == NULL )
		return;
	m_nRowCount=nRowCount;			//����
	m_nColCount=nColCount;			//����	

	m_nFrameWidth=m_nWidth/nColCount;		//֡���
	m_nFrameHeight=m_nHeight/nRowCount;		//֡�߶�

	m_lNextFrameTime=nFrameDelay+timeGetTime();	//������һ֡��ʱ��
	m_nFrameDelay=nFrameDelay;					//ÿ֡����ʾʱ��

	m_nCol=0;			//�к�
	m_nRow=0;			//�к�

	m_bInitAnima=TRUE;							//��ʼ����־
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���ƶ�����������(x,y)���괦����һ������֡���棬֡�����еļ�ʱ����ѭ������ʱ�Զ����»���*/
void Sprite::DrawAnima(HDC hDC,int x,int y,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if(m_hbm == NULL || !m_bInitAnima)
		return;
	if(timeGetTime()>m_lNextFrameTime)	//����Ƿ���һ֡����ʱ��
	{	//�������һ֡����ʱ�䣬�����ü�ʱ��
		m_lNextFrameTime=timeGetTime()+m_nFrameDelay;	
		
		m_nCol++;				//����ŵ���				
		if(m_nCol>=m_nColCount)	//������ų���������ʱ��0������ѭ��		
			m_nCol=0;
	}
	DrawRowCol(hDC,x,y,m_nRow,m_nCol,bTrans,crTrans);	//����ָ�����кŵ�֡����
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��hDC��(x,y)λ�û��Ƶ�ͼ��nRow��nCol�е�֡����,������ο�ͼ(bTransΪTRUE),ָ��crTransparentΪ͸��ɫ*/
void Sprite::DrawRowCol(HDC hDC,int x,int y,int nRow,int nCol,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm == NULL || !m_bInitAnima)
		return;
	HDC hdcMem= CreateCompatibleDC(hDC);		//���������豸
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, m_hbm);	//��λͼѡ������豸������¼�¾ɵľ��

	if (bTrans)
		//���͸��λͼ
		TransparentBlt(hDC, x, y,m_nFrameWidth,m_nFrameHeight,hdcMem, m_nFrameWidth*nCol,m_nFrameHeight*nRow,m_nFrameWidth, m_nFrameHeight, crTrans);
		// TransBitmap(hDC, x, y,iAnimaWidth, iAnimaHeight,hdcMem, iAnimaWidth*iCol,iAnimaHeight*iRow,iAnimaWidth, iAnimaHeight, crTransparent);
	else
		//�����͸��λͼ			
		BitBlt(hDC, x, y,m_nFrameWidth, m_nFrameHeight, hdcMem,m_nFrameWidth*nCol,m_nFrameHeight*nRow, SRCCOPY);
	// ������ʱ�����ͷ���Դ		
	SelectObject(hdcMem,hbmOld);
	DeleteObject(hbmOld);
	DeleteDC(hdcMem);		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*����������ʹ�þ���������ͼʱ����ķ���*/

//��������DrawTransAlpha()�����Ĳ���
void Sprite::SetDrawAlphaInfo(int x,int y,int nAlpha)
{
	m_dt=DT_ALPHA;
	m_nX=x;
	m_nY=y;
	m_nAlpha=nAlpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������Draw()�����Ĳ���
void Sprite::SetDrawInfo(int x,int y,BOOL bTrans,COLORREF crTrans)
{
	m_dt=DT_DRAW;
	m_nX=x;
	m_nY=y;
	m_bTrans=bTrans;
	m_crTrans=crTrans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������DrawAnima()�����Ĳ���
void Sprite::SetDrawAnimaInfo(int x,int y,int nRow,BOOL bTrans,COLORREF crTrans)                  
{
	m_dt=DT_ANIMA;
	m_nX=x;
	m_nY=y;
	m_nRow=nRow;
	m_bTrans=bTrans;
	m_crTrans=crTrans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������DrawGray()�����Ĳ���
void Sprite::SetDrawGrayInfo(int x,int y,COLORREF crTrans)                  
{
	m_dt=DT_GRAY;
	m_nX=x;
	m_nY=y;
	m_bTrans=TRUE;
	m_crTrans=crTrans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������DrawRect()�����Ĳ���
void Sprite::SetDrawRectInfo(int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans,COLORREF crTrans)
{
	m_dt=DT_RECT;
	m_nX=x;
	m_nY=y;
	m_nRectX=nRectX;
	m_nRectY=nRectY;
	m_nRectWidth=nRectWidth;
	m_nRectHeight=nRectHeight;
	m_bTrans=bTrans;
	m_crTrans=crTrans;
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������DrawTransAlpha()�����Ĳ���
void Sprite::SetDrawTransAlphaInfo(int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nAlpha,COLORREF crTrans)
{
	m_dt=DT_TRANSALPHA;
	m_nX=nXFore;
	m_nY=nYFore;
	m_nXBack=nXBack;
	m_nYBack=nYBack;
	m_nWidthBack=nWidthBack;
	m_nHeightBack=nHeightBack;
	m_nAlpha=nAlpha;
	m_crTrans=crTrans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ͳһ�Ļ�ͼ�ӿ�
void Sprite::DrawSprite(HDC hDC)
{
	switch(m_dt)
	{
	case DT_DRAW:
		Draw(hDC,m_nX,m_nY,m_bTrans,m_crTrans);
		break;
	case DT_ALPHA:
		DrawAlpha(hDC,m_nX,m_nY,m_nAlpha);
		break;
	case DT_GRAY:
		DrawGray(hDC,m_nX,m_nY,m_bTrans,m_crTrans);
		break;
	case DT_TRANSALPHA:
		DrawTransAlpha(hDC,m_nXBack,m_nYBack,m_nWidthBack,m_nHeightBack,m_nX,m_nY,m_nAlpha,m_crTrans);
		break;
	case DT_ANIMA:
		DrawAnima(hDC,m_nX,m_nY,m_bTrans,m_crTrans);
		break;
	case DT_RECT:
		DrawRect(hDC,m_nX,m_nY,m_nRectX,m_nRectY,m_nRectWidth,m_nRectHeight,m_bTrans,m_crTrans);
		break;
	case DT_CXIMAGE:
		DrawCxImage(hDC,m_nX,m_nY,m_nWidth,m_nHeight,m_nFrameDelay);
	default:
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* ����������CxImage�ķ��� */ 

//�������飬����ͼ���ļ�szFileName�����������Ƿ���ת��ΪHBITMAP���Ա���ԭ�еķ��������
Sprite::Sprite(LPTSTR szFileName,BOOL bConvertBmp)
{
	LoadCxImage(szFileName,bConvertBmp);
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//����ͼ���ļ�szFileName�����������Ƿ���ת��ΪHBITMAP���Ա���ԭ�еķ��������
BOOL Sprite::LoadCxImage(LPTSTR szFileName,BOOL bConvertBmp)
{
	Release();

	m_cxImage=new CxImage();	//����CxImage����
	m_cxImage->Load(szFileName);	//����ͼ���ļ�

	if (!m_cxImage->IsValid())		//��������Ƿ�ɹ�
		return FALSE;

	if(m_cxImage->GetType()==CXIMAGE_FORMAT_GIF)	//�ж��ļ��Ƿ���GIF�ļ�
	{
		m_cxImage->SetRetreiveAllFrames(true);		//��������֡��ͬһ������
		m_cxImage->SetFrame(m_cxImage->GetNumFrames()-1);	//����Ҫ���ص�֡
		m_cxImage->Load(szFileName);			//����ͼ��
		m_lNextFrameTime=0;						//������һ֡��ʾʱ��
	}
		
	if(bConvertBmp)		
		m_hbm= m_cxImage->MakeBitmap();	//ת��ͼ��ΪHBITMAP���Ա������з�������

	m_nWidth=m_cxImage->GetWidth();		//���ÿ��
	m_nHeight=m_cxImage->GetHeight();	//���ø߶�	
	m_bVisible=TRUE;					//�����Ƿ�ɼ�
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//����x��yΪ���Ͻǣ���nWidth����nHeight�ķ�Χ�ڻ���ͼ�񣬲������ö���֡��ʱΪnFrameDelay
void Sprite::DrawCxImage(HDC hDC,int x,int y,int nWidth,int nHeight,int nFrameDelay)
{
	if(m_cxImage==NULL)		//���ͼ���Ƿ����
		return;

	int ImgType=m_cxImage->GetType();	//��ȡͼ������

	/*�����ǻ���GIF�������貽��*/
	if(ImgType==CXIMAGE_FORMAT_GIF)		//�ж��Ƿ�ΪGIFͼ��
	{
		if(timeGetTime()>=m_lNextFrameTime)		//�ж��Ƿ���һ֡
		{
			m_lNextFrameTime=timeGetTime()+nFrameDelay;		//������һ֡��ʱ	
			
			long m = m_cxImage->GetNumFrames();		//��ȡ֡����
			long n = m_cxImage->GetFrame()+1;		//������һ֡����
			if (n>=m)								//�жϵ�ǰ֡�����Ƿ����һ֡
					n=0;				//�������һ֡����������Χ������һ֡Ϊ��0֡

			if (m_cxImage->GetFrame(n))		//�ж��Ƿ��ܻ�ȡ��һ֡
				m_cxImage->Copy(*m_cxImage->GetFrame(n));	//����ͼ��ΪΪ��һ֡
			m_cxImage->SetFrame(n);		//���õ�ǰ֡����
		}
	}
	
	m_cxImage->Draw(hDC,x,y,nWidth,nHeight);	//����ͼ��
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������DrawCxImage()�����Ĳ���
void Sprite::SetDrawCxImageInfo(int x,int y,int nWidth,int nHeight,int nFrameDelay)
{
	m_dt=DT_CXIMAGE;
	m_nX=x;
	m_nY=y;
	if(nWidth!=0)
		m_nWidth=nWidth;
	if(nHeight!=0)
		m_nHeight=nHeight;
	m_nFrameDelay=nFrameDelay;
}


