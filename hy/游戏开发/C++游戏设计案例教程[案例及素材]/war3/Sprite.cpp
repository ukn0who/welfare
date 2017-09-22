/*********************************
	游戏精灵程序文件Sprite.cpp
*********************************/

#include "Sprite.h"

#pragma   comment(lib,"gdi32.lib")		//引用库
#pragma   comment(lib,"msimg32.lib")

#pragma comment(lib,"cximagelib\\cximage.lib")

int Sprite::m_nNewID=1;		//初始化精灵编号

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 构造函数，根据不同的参数创建不同的Sprite实例*/

/* 默认构造函数 */
Sprite::Sprite()
{
	m_hbm=NULL;
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 用指定的位图文件创建Sprite实例 */
Sprite::Sprite(HINSTANCE hInstance,LPTSTR szFileName)
{
	//载入指定的位图文件
	Load(hInstance,szFileName);
	m_ID=m_nNewID;
	m_nNewID++;	
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 用指定的位图资源创建Sprite实例 */
Sprite::Sprite(HINSTANCE hInstance,UINT uRcID)
{
	Load(hInstance,uRcID);
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 用指定的大小和颜色创建Sprite实例*/
Sprite::Sprite(HDC hDC,int nWidth,int nHeight,COLORREF crColor)
{
	Create(hDC,nWidth,nHeight,crColor);//调用Create建立位图
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;
	m_bVisible=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 析构函数*/
Sprite::~Sprite()
{
	Release();		//调用Release()函数以释放资源
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Release方法用于释放资源 */
void Sprite::Release()
{
  if (m_hbm != NULL)
  {
    DeleteObject(m_hbm);
    m_hbm = NULL;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 用指定的大小和颜色创建位图*/
BOOL Sprite::Create(HDC hDC,int nWidth,int nHeight,COLORREF crColor)
{
	Release();	//释放原有位图资源

	//创建兼容位图
	m_hbm=CreateCompatibleBitmap(hDC,nWidth,nHeight);
	if(m_hbm==NULL)
		return false;

	//设置宽度和高度
	m_nWidth = nWidth;	
	m_nHeight = nHeight;

	//通过在位图中绘制填充矩形来设置位图
	HDC hdcMem = CreateCompatibleDC(hDC);		//创建兼容设备
	HBRUSH hBrush = CreateSolidBrush(crColor);	//定义单色画刷
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, m_hbm);		//将位图选入设备
	RECT rc = {0, 0, nWidth, nHeight };			//定义矩形大小
	FillRect(hdcMem, &rc, hBrush);				//绘制填充矩形

	// 清理临时对象，释放资源
	SelectObject(hdcMem, hOldBitmap);	//替出位图m_hbm，使其得以保留
	DeleteDC(hdcMem);
	DeleteObject(hBrush);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 载入指定的位图文件 */
BOOL Sprite::Load(HINSTANCE hInstance,LPTSTR szFileName)
{
	Release();	//释放原有位图资源	
	//载入指定的位图
	m_hbm=(HBITMAP)LoadImage(NULL,szFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//通过BITMAP结构设置位图宽度和高度	
	BITMAP  bm;
	GetObject(m_hbm,sizeof(BITMAP),&bm);
	m_nWidth=bm.bmWidth;
	m_nHeight=bm.bmHeight;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 载入位图资源 */
BOOL Sprite::Load(HINSTANCE hInstance,UINT uRcid)
{
	Release();	//释放原有位图资源	
	//载入指定的位图资源
	m_hbm=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(uRcid),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	//通过BITMAP结构设置位图宽度和高度	
	BITMAP  bm;
	GetObject(m_hbm,sizeof(BITMAP),&bm);
	m_nWidth=bm.bmWidth;
	m_nHeight=bm.bmHeight;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 在hDC的指定位置(x,y)绘制位图,如果是透明镂空位图(bTrans为TRUE),指定crTrans为透明色 */
void Sprite::Draw(HDC hDC,int x,int y,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//创建兼容设备
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);	//将位图选入兼容设备，并记录下旧的句柄

		if (bTrans)
			//输出透明位图
			 TransparentBlt(hDC, x, y,m_nWidth,m_nHeight, hdcMem, 0,0,m_nWidth,m_nHeight, crTrans);
		else
			//输出不透明位图
			BitBlt(hDC, x, y, m_nWidth,m_nHeight, hdcMem, 0,0, SRCCOPY);
		// 清理临时对象，释放资源
		SelectObject(hdcMem,hOldBmp);	
		DeleteObject(hOldBmp);
		DeleteDC(hdcMem);		
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 在hDC的指定位置(x,y)绘制位图中指定的矩形区域内的图像，左上角坐标为(nRectX,nRectY),
 宽nRectWidth,高nRectHeight,如果是透明镂空图(bTrans为TRUE),指定crTrans为透明色*/
void Sprite::DrawRect(HDC hDC,int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//创建兼容设备
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);	//将位图选入兼容设备，并记录下旧的句柄

		if (bTrans)
			//输出透明位图
			TransparentBlt(hDC, x, y, nRectWidth, nRectHeight, hdcMem, nRectX,nRectY,nRectWidth, nRectHeight, crTrans);
			// TransBitmap(hDC, x, y, iRectWidth, iRectHeight, hdcMem, iRectX,iRectY,iRectWidth, iRectHeight, crTransparent);
		else
			//输出不透明位图
			BitBlt(hDC, x, y,nRectWidth, nRectHeight, hdcMem, 0,0, SRCCOPY);


		// 清理临时对象，释放资源
		SelectObject(hdcMem,hOldBmp);	
		DeleteDC(hdcMem);				
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 在hDC的指定位置(x,y)输出透明度为nAlpha(0~255)的半透明图像 */
void Sprite::DrawAlpha(HDC hDC,int x,int y,int nAlpha)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//创建兼容设备
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);

		//设置bf结构
		BLENDFUNCTION bf;
		bf.BlendOp=AC_SRC_OVER;
		bf.BlendFlags=0;
		bf.SourceConstantAlpha=nAlpha;
		bf.AlphaFormat=0x00;
		//输出半透明图像
		AlphaBlend(hDC, x, y, m_nWidth, m_nHeight, hdcMem, 0,0,GetWidth(), GetHeight(), bf);
		
		// 清理临时对象，释放资源
		SelectObject(hdcMem,hOldBmp);	
		DeleteDC(hdcMem);			
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*绘制半透明镂空图*/
void Sprite::DrawTransAlpha(HDC hdcBack, int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nAlpha,	COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL && nAlpha >0)
	{
		HDC hdcMem= CreateCompatibleDC(hdcBack);		//创建兼容设备

		//创建一个与背景同样大小的临时图像	
		RECT rBackRect={nXBack,nYBack,nWidthBack, nHeightBack};
		HBITMAP	hbmTmp=CreateCompatibleBitmap(hdcBack,nWidthBack,nHeightBack); 

		HBITMAP hbmBk=(HBITMAP)SelectObject(hdcBack,hbmTmp);	//替出背景图像

		RECT rForeRect={nXFore,nYFore,nXFore+m_nWidth,nYFore+m_nHeight};
		RECT rTransRect,rTransRect2;

		//获取前景矩形与背景矩形的交集,如不相交，则不需要进行颜色计算 
		if(IntersectRect(&rTransRect,&rBackRect,&rForeRect))
		{
			BITMAP  bm,bmBk;	
			GetObject(m_hbm,sizeof(BITMAP),&bm);
			BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //声明暂存数组
			GetBitmapBits(m_hbm,bm.bmHeight*bm.bmWidthBytes,px); //取得源位图各像素点的 RGB 值存入 px 数组中

			GetObject(hbmBk,sizeof(BITMAP),&bmBk);
			BYTE * pxBk = new unsigned char[bmBk.bmHeight*bmBk.bmWidthBytes];  //声明暂存数组

			GetBitmapBits(hbmBk,bmBk.bmHeight*bmBk.bmWidthBytes,pxBk); //取得源位图各像素点的 RGB 值存入 pxBk数组中

			rTransRect2=rTransRect;
			OffsetRect (&rTransRect2, -rForeRect.left,-rForeRect.top ) ;	//偏移矩形坐标
			
			int pb=bm.bmBitsPixel/8;		//获取每像素所占字节数
			int pbBk=bmBk.bmBitsPixel/8;

			//dy1为背景图像素行数,dy2为前景图像素行数
			//dx1为背景图像素列数,dx2为前景图像素列数
			int dx1,dx2,dy1,dy2;	
			//循环对像素进行计算，背景和前景中需要进行计算的像素分别在各自对应的矩形rTransRect和rTransRect2的范围内循环 
			for(dy1=rTransRect.top,dy2=rTransRect2.top;dy1<rTransRect.bottom;dy1++,dy2++)
				for(dx1=rTransRect.left,dx2=rTransRect2.left;dx1<rTransRect.right;dx1++,dx2++)
				{
					int nBackRGB_B=dy1*bmBk.bmWidthBytes+dx1*pbBk;		//计算背景图像素起始位置
					int nForeRGB_B=dy2*bm.bmWidthBytes+dx2*pb;			//计算前景图像素起始位置
					
					if( RGB(px[nForeRGB_B+2],px[nForeRGB_B+1],px[nForeRGB_B])!=crTrans)
					{
					pxBk[nBackRGB_B] = (px[nForeRGB_B]*nAlpha+pxBk[nBackRGB_B]*(255-nAlpha))/255;	//将B色彩值乘以nAlpha并与 px 相加
					pxBk[nBackRGB_B+1] =(px[nForeRGB_B+1]*nAlpha+pxBk[nBackRGB_B+1]*(255-nAlpha))/255;//将 G 色彩值乘以nAlpha并与 px 相加
					pxBk[nBackRGB_B+2] = (px[nForeRGB_B+2]*nAlpha+pxBk[nBackRGB_B+2]*(255-nAlpha))/255;//将 R 色彩值乘以 nAlpha并与 px 相加
					}
				}
			
			SetBitmapBits(hbmTmp,bmBk.bmHeight*bmBk.bmWidthBytes,pxBk); //设置背景图数据
			HBITMAP hbmOld=(HBITMAP)SelectObject(hdcMem,hbmTmp); 
			BitBlt(hdcBack,0,0,rBackRect.right,rBackRect.bottom,hdcMem,0,0,SRCCOPY);
	
			delete[] px;		//删除数组
			delete[] pxBk;
			SelectObject(hdcMem,hbmOld);
		}
	
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);				//删除兼容设备
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*绘制灰度镂空图*/
void Sprite::DrawGray(HDC hDC,int x,int y,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm != NULL)
	{
		HDC hdcMem= CreateCompatibleDC(hDC);		//创建兼容设备

	
		BITMAP  bm;	
		GetObject(m_hbm,sizeof(BITMAP),&bm);
		BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //声明暂存数组
		GetBitmapBits(m_hbm,bm.bmHeight*bm.bmWidthBytes,px); //取得源位图各像素点的 RGB 值存入 px 数组中

	
		int pb=bm.bmBitsPixel/8;
		//循环计算灰度值
		for(int dy=0;dy<bm.bmHeight;dy++)
		{	for(int dx=0;dx<bm.bmWidth;dx++)
			{
			int rgb_b=dy*bm.bmWidthBytes+dx*pb;	
			px[rgb_b] =(px[rgb_b] *299+px[rgb_b+1]*587+px[rgb_b+2] *114)/1000;
			px[rgb_b+1] =px[rgb_b] ;
			px[rgb_b+2] =px[rgb_b] ;
			};
		}
		//创建临时位图，以存储灰度图像
		HBITMAP	hbmTmp=CreateCompatibleBitmap(hDC,bm.bmWidth,bm.bmHeight); 	
		SetBitmapBits(hbmTmp,bm.bmHeight*bm.bmWidthBytes,px);

		HBITMAP hOldBmp=(HBITMAP)SelectObject(hdcMem,hbmTmp); 

		if (bTrans)
			//输出透明位图
			 TransparentBlt(hDC, x, y,bm.bmWidth,bm.bmHeight, hdcMem, 0,0,bm.bmWidth,bm.bmHeight, crTrans);
		else
			//输出不透明位图
			BitBlt(hDC, x, y, bm.bmWidth,bm.bmHeight, hdcMem, 0,0, SRCCOPY);
	
		
		delete[] px;		//删除数组

		SelectObject(hdcMem,hOldBmp);	
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);				//删除兼容设备
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* 绘制透明镂空位图 */
void Sprite::TransBitmap( HDC hdcDest, int nXDest,int nYDest,int nWidthDest,int nHeightDest,
						 HDC hdcSrc,int nXSrc,int nYSrc,  int nWidthSrc, int nHeightSrc,COLORREF crTrans)
{
	// 创建兼容位图
	HBITMAP hbmTmp = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	
	// 创建单色位图
	HBITMAP hbmMask = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);	
	//创建兼容设备环境
	HDC		hdcMem = CreateCompatibleDC(hdcDest);
	HDC		hdcMask = CreateCompatibleDC(hdcDest);

	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmTmp);
	HBITMAP hbmMaskOld = (HBITMAP)SelectObject(hdcMask, hbmMask);

	// 将源DC中的位图拷贝到临时设备环境中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, SRCCOPY);
	else
		StretchBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, 
					hdcSrc, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// 设置透明色
	SetBkColor(hdcMem, crTrans);

	// 生成透明区域为白色，其它区域为黑色的蒙版位图
	BitBlt(hdcMask, 0, 0, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hdcMem, RGB(0,0,0));
	SetTextColor(hdcMem, RGB(255,255,255));
	BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// 透明部分对应的背景保持不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(255,255,255));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCPAINT);

	// 清理临时内容，释放资源
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	SelectObject(hdcMask, hbmMaskOld);
	DeleteDC(hdcMask);
	DeleteObject(hbmTmp);
	DeleteObject(hbmMask);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*下面是用于动画的成员方法*/

/*使用行nRowCount、列nColCount总数和帧显示延时nFrameDelay来初始化动画参数 */
void Sprite::InitAnima(int nRowCount,int nColCount,int nFrameDelay)
{
	if (m_hbm == NULL )
		return;
	m_nRowCount=nRowCount;			//行数
	m_nColCount=nColCount;			//列数	

	m_nFrameWidth=m_nWidth/nColCount;		//帧宽度
	m_nFrameHeight=m_nHeight/nRowCount;		//帧高度

	m_lNextFrameTime=nFrameDelay+timeGetTime();	//绘制下一帧的时间
	m_nFrameDelay=nFrameDelay;					//每帧的显示时间

	m_nCol=0;			//列号
	m_nRow=0;			//行号

	m_bInitAnima=TRUE;							//初始化标志
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*绘制动画方法，在(x,y)坐标处绘制一个动画帧画面，帧画面中的计时会在循环绘制时自动更新画面*/
void Sprite::DrawAnima(HDC hDC,int x,int y,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if(m_hbm == NULL || !m_bInitAnima)
		return;
	if(timeGetTime()>m_lNextFrameTime)	//检查是否到下一帧绘制时间
	{	//如果到下一帧绘制时间，重新置计时器
		m_lNextFrameTime=timeGetTime()+m_nFrameDelay;	
		
		m_nCol++;				//列序号递增				
		if(m_nCol>=m_nColCount)	//当列序号超过列总数时归0，重新循环		
			m_nCol=0;
	}
	DrawRowCol(hDC,x,y,m_nRow,m_nCol,bTrans,crTrans);	//绘制指定行列号的帧画面
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 在hDC的(x,y)位置绘制的图像nRow行nCol列的帧画面,如果是镂空图(bTrans为TRUE),指定crTransparent为透明色*/
void Sprite::DrawRowCol(HDC hDC,int x,int y,int nRow,int nCol,BOOL bTrans,COLORREF crTrans)
{
	if(!m_bVisible)
		return;
	if (m_hbm == NULL || !m_bInitAnima)
		return;
	HDC hdcMem= CreateCompatibleDC(hDC);		//创建兼容设备
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, m_hbm);	//将位图选入兼容设备，并记录下旧的句柄

	if (bTrans)
		//输出透明位图
		TransparentBlt(hDC, x, y,m_nFrameWidth,m_nFrameHeight,hdcMem, m_nFrameWidth*nCol,m_nFrameHeight*nRow,m_nFrameWidth, m_nFrameHeight, crTrans);
		// TransBitmap(hDC, x, y,iAnimaWidth, iAnimaHeight,hdcMem, iAnimaWidth*iCol,iAnimaHeight*iRow,iAnimaWidth, iAnimaHeight, crTransparent);
	else
		//输出不透明位图			
		BitBlt(hDC, x, y,m_nFrameWidth, m_nFrameHeight, hdcMem,m_nFrameWidth*nCol,m_nFrameHeight*nRow, SRCCOPY);
	// 清理临时对象，释放资源		
	SelectObject(hdcMem,hbmOld);
	DeleteObject(hbmOld);
	DeleteDC(hdcMem);		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*下面是用于使用精灵管理类绘图时所需的方法*/

//设置用于DrawTransAlpha()方法的参数
void Sprite::SetDrawAlphaInfo(int x,int y,int nAlpha)
{
	m_dt=DT_ALPHA;
	m_nX=x;
	m_nY=y;
	m_nAlpha=nAlpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//设置用于Draw()方法的参数
void Sprite::SetDrawInfo(int x,int y,BOOL bTrans,COLORREF crTrans)
{
	m_dt=DT_DRAW;
	m_nX=x;
	m_nY=y;
	m_bTrans=bTrans;
	m_crTrans=crTrans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//设置用于DrawAnima()方法的参数
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

//设置用于DrawGray()方法的参数
void Sprite::SetDrawGrayInfo(int x,int y,COLORREF crTrans)                  
{
	m_dt=DT_GRAY;
	m_nX=x;
	m_nY=y;
	m_bTrans=TRUE;
	m_crTrans=crTrans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//设置用于DrawRect()方法的参数
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

//设置用于DrawTransAlpha()方法的参数
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

//统一的绘图接口
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


/* 下面是用于CxImage的方法 */ 

//创建精灵，载入图像文件szFileName，并可设置是否将其转换为HBITMAP，以便与原有的方法相兼容
Sprite::Sprite(LPTSTR szFileName,BOOL bConvertBmp)
{
	LoadCxImage(szFileName,bConvertBmp);
	m_ID=m_nNewID;
	m_nNewID++;
	m_nZOrder=0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//载入图像文件szFileName，并可设置是否将其转换为HBITMAP，以便与原有的方法相兼容
BOOL Sprite::LoadCxImage(LPTSTR szFileName,BOOL bConvertBmp)
{
	Release();

	m_cxImage=new CxImage();	//创建CxImage对象
	m_cxImage->Load(szFileName);	//加载图像文件

	if (!m_cxImage->IsValid())		//检验加载是否成功
		return FALSE;

	if(m_cxImage->GetType()==CXIMAGE_FORMAT_GIF)	//判断文件是否是GIF文件
	{
		m_cxImage->SetRetreiveAllFrames(true);		//设置所有帧在同一对象中
		m_cxImage->SetFrame(m_cxImage->GetNumFrames()-1);	//设置要加载的帧
		m_cxImage->Load(szFileName);			//载入图像
		m_lNextFrameTime=0;						//设置下一帧显示时间
	}
		
	if(bConvertBmp)		
		m_hbm= m_cxImage->MakeBitmap();	//转换图像为HBITMAP，以便与已有方法兼容

	m_nWidth=m_cxImage->GetWidth();		//设置宽度
	m_nHeight=m_cxImage->GetHeight();	//设置高度	
	m_bVisible=TRUE;					//设置是否可见
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//在以x和y为左上角，宽nWidth，高nHeight的范围内绘制图像，并可设置动画帧延时为nFrameDelay
void Sprite::DrawCxImage(HDC hDC,int x,int y,int nWidth,int nHeight,int nFrameDelay)
{
	if(m_cxImage==NULL)		//检查图像是否存在
		return;

	int ImgType=m_cxImage->GetType();	//获取图像类型

	/*下面是绘制GIF动画所需步骤*/
	if(ImgType==CXIMAGE_FORMAT_GIF)		//判断是否为GIF图像
	{
		if(timeGetTime()>=m_lNextFrameTime)		//判断是否到下一帧
		{
			m_lNextFrameTime=timeGetTime()+nFrameDelay;		//设置下一帧延时	
			
			long m = m_cxImage->GetNumFrames();		//获取帧总数
			long n = m_cxImage->GetFrame()+1;		//计算下一帧索引
			if (n>=m)								//判断当前帧索引是否到最后一帧
					n=0;				//如果当下一帧超出索引范围，则下一帧为第0帧

			if (m_cxImage->GetFrame(n))		//判断是否能获取下一帧
				m_cxImage->Copy(*m_cxImage->GetFrame(n));	//设置图像为为下一帧
			m_cxImage->SetFrame(n);		//设置当前帧索引
		}
	}
	
	m_cxImage->Draw(hDC,x,y,nWidth,nHeight);	//绘制图像
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//设置用于DrawCxImage()方法的参数
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


