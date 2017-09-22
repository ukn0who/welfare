/*********************************
	游戏精灵头文件Sprite.h
*********************************/

#ifndef DEF_Sprite

#define DEF_Sprite

#include <windows.h>
#include "wingdi.h"
#include "cximagelib\\ximage.h"

typedef  int		DRAWTYPE;			//定义类型
const DRAWTYPE		DT_NULL=0,			//无
					DT_DRAW=1,			//Draw()方法
					DT_ALPHA=2,			//DrawAlpha()方法
					DT_GRAY=3,			//DrawGray()方法
					DT_TRANSALPHA=4,	//DrawTransAlpha()方法
					DT_ANIMA=5,			//DrawAnima()方法
					DT_RECT=6,			//DrawRect()方法
					DT_CXIMAGE=7;	



/* 游戏精灵Sprite类用于游戏图像的创建、载入和绘制 */
class Sprite
{
protected:
	static int m_nNewID;		//下一个可用的精灵编号	
	int		m_ID;				//精灵编号
	HBITMAP m_hbm;				//位图句柄
	int		m_nWidth,m_nHeight;	//位图宽度与高度
	int		m_nZOrder;			//Z顺序

	/*下面是用于动画的成员属性*/
	int		m_nFrameWidth,m_nFrameHeight;	//位图中构成动画的单帧图像的高度和宽度
	int		m_nRowCount,m_nColCount;		//位图中构成动画的系列帧的行、列总数
	int		m_nRow,m_nCol;					//动画系列帧中的当前帧行、列编号

	int		m_nFrameDelay;		//每个动画画面延时显示帧数
	unsigned long	m_lNextFrameTime;		//下一帧绘制时间
	BOOL	m_bInitAnima;		//是否已经初始化


	/*在使用精灵管理类时所需提供的精灵数据*/

	DRAWTYPE m_dt;		//绘图类型
	
	int		m_nX,m_nY;		//绘制时到DC时左上角坐标
	BOOL	m_bTrans;		//是否透明
	COLORREF	m_crTrans;	//透明色
	int		m_nAlpha;		//不透明度

	//下面是用于DrawTransAlpha()方法的背景图左上角坐标、宽度与高度
	int		m_nXBack,m_nYBack,m_nWidthBack,m_nHeightBack;		

	//下面是用于DrawRect()方法的矩形区域左上角坐标、宽度与高度
	int		m_nRectX,m_nRectY,m_nRectWidth,m_nRectHeight;
	
	BOOL	m_bVisible;		//是否可见(如不可见，则不需要绘出)


	CxImage * m_cxImage;	//CxImage对象指针

public:
	/*构造函数，根据不同的参数创建不同的Sprite实例*/
	Sprite();	
	Sprite(HINSTANCE hInstance,LPTSTR szFileName);	//根据位图文件名创建精灵
	Sprite(HINSTANCE hInstance,UINT uRcID);	//根据位图资源ID创建精灵
	//根据指定的大小、颜色创建精灵
	Sprite(HDC hDC,int nWidth,int nHeight,COLORREF crColor=RGB(255,255,255));
	
	virtual ~Sprite();
	
	/****声明成员访问方法**********/
	
	
	int GetID()			//获取精灵图像编号
	{
		return m_ID;
	}
	
	HBITMAP GetBitmp()  //获取位图句柄
	{
		return m_hbm;
	}

	void SetBitmap(HBITMAP hbm)	//设置位图句柄
	{
		if(m_hbm!=NULL)
			Release();

		m_hbm=hbm;

		BITMAP  bm;
		GetObject(m_hbm,sizeof(BITMAP),&bm);
		m_nWidth=bm.bmWidth;
		m_nHeight=bm.bmHeight;

	}

	int GetHeight()		//获取精灵图像高度
	{
		return m_nHeight;
	}

	int GetWidth()		//获取精灵图像宽度
	{
		return m_nWidth;
	}
	
	void SetZOrder(int nZOrder)	//设置Z顺序
	{
		m_nZOrder=nZOrder;
	}

	int GetZOrder()				//获取Z顺序
	{
		return m_nZOrder;
	}

	/*** 常规方法 ***/

	//释放资源
	void Release();

	//根据指定的大小、颜色创建位图
	BOOL Create(HDC hDC,int nWidth,int nHeight,COLORREF crColor=RGB(0,0,0));

	//加载文件中的位图
	BOOL Load(HINSTANCE hInstance,LPTSTR szFileName);

	//加载资源中的位图
	BOOL Load(HINSTANCE hInstance,UINT uRcid);
	
	//绘制位图，若设置bTrans为TRUE，则按指定颜色crTransparent镂空位图
	void Draw(HDC hDC,int x,int y,BOOL bTrans=FALSE,COLORREF crTransparent=RGB(0,0,0));
	
	//绘制位图中的一个矩形区域内的图像
	void DrawRect(HDC hDC,int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));
	
	//绘制半透明位图,不透明度nApha取值为0~255
	void DrawAlpha(HDC hDC,int x,int y,int nAlpha);

	
	//绘制灰度位图，可设置为镂空
	void DrawGray(HDC hDC,int x,int y,BOOL bTrans=FALSE,COLORREF crTransparent=RGB(0,0,0));	

	//绘制半透明镂空位图
	void DrawTransAlpha( HDC hdcBack,	// 背景DC
					int nXBack,			// 背景图左上角X坐标
					int nYBack,			// 背景图左上角Y坐标
					int nWidthBack,     // 背景图宽度
					int nHeightBack,    // 背景图高度
					int nXFore,			// 前景图左上角X坐标
					int nYFore,			// 背景图左上角Y坐标
					int nAlpha=100,		// 不透明度
					COLORREF crTrans=RGB(0,0,0));	//镂空色

	/*下面是用于动画的成员方法*/
	//初始化动画参数
	void InitAnima(int nRowCount,int nColCount,int nFrameDelay);

	//在hDC上的指定位置(x,y)，绘制第nRow行nCol列的图像，可设置为镂空
	void DrawRowCol(HDC hDC,int x,int y,int nRow,int nCol,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));
	
	//绘制动画帧
	void DrawAnima(HDC hDC,int x,int y,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));
	
	/*下面是用于使用精灵管理类绘图时时所需的方法*/
	//设置用于DrawTransAlpha()方法的参数
	void SetDrawAlphaInfo(int x,int y,int nAlpha=255);

	//设置用于Draw()方法的参数
	void SetDrawInfo(int x,int y,BOOL bTrans=FALSE,COLORREF crTrans=RGB(0,0,0));

	//设置用于DrawAnima()方法的参数
	void SetDrawAnimaInfo(int x,int y,int nRow,BOOL bTrans,COLORREF crTrans=RGB(0,0,0));

	//设置用于DrawGray()方法的参数
	void SetDrawGrayInfo(int x,int y,COLORREF crTrans=RGB(0,0,0));

	//设置用于DrawRect()方法的参数
	void SetDrawRectInfo(int x,int y,int nRectX,int nRectY,int nRectWidth,int nRectHeight,BOOL bTrans,COLORREF crTrans=RGB(0,0,0));

	//设置用于DrawTransAlpha()方法的参数
	void SetDrawTransAlphaInfo(int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nAlpha=255,COLORREF crTrans=RGB(0,0,0));

	//统一的绘图接口
	void DrawSprite(HDC hDC);
	
	//设置精灵是否可见
	void SetVisible(BOOL bVisible)
	{
		m_bVisible=bVisible;
	}

	//获取精灵是否可见	
	BOOL GetVisible()
	{
		return m_bVisible;
	}

	/* 下面是用于CxImage的方法 */ 
	//创建精灵，载入图像文件szFileName，并可设置是否将其转换为HBITMAP，以便与原有的方法相兼容
	Sprite(LPTSTR szFileName,BOOL bConvertBmp=FALSE);

	//载入图像文件szFileName，并可设置是否将其转换为HBITMAP，以便与原有的方法相兼容
	BOOL LoadCxImage(LPTSTR szFileName,BOOL bConvertBmp=FALSE);

	//获取CxImage属性
	CxImage * GetCxImage() const
	{
		return m_cxImage;
	}
	//设置CxImage属性
	void SetCxImage(CxImage * image) 
	{
		m_cxImage=image;
	}

	//在以x和y为左上角，宽nWidth，高nHeight的范围内绘制图像，并可设置动画帧延时为nFrameDelay
	void DrawCxImage(HDC hDC,int x,int y,int nWidth=0,int nHeight=0,int nFrameDelay=100);


	//设置用于DrawCxImage()方法的参数
	void SetDrawCxImageInfo(int x,int y,int nWidth=0,int nHeight=0,int nFrameDelay=100);



private:
	//自定义的绘制镂空图的方法
	void TransBitmap( HDC hdcDest,      // 目标DC
					int nXDest,			// 目标左上角X坐标
					int nYDest,			// 目标左上角Y坐标
					int nWidthDest,     // 目标宽度
					int nHeightDest,    // 目标高度
					HDC hdcSrc,         // 源DC
					int nXSrc,			// 源X起点
					int nYSrc,			// 源Y起点
					int nWidthSrc,      // 源宽度
					int nHeightSrc,     // 源高度
					COLORREF crTrans=RGB(255,255,255)  // 透明色
					);

};

#endif