/*********************************
	游戏精灵头文件Sprite.h
*********************************/

#ifndef DEF_Sprite

#define DEF_Sprite

#include <windows.h>
#include "wingdi.h"


/* 游戏精灵Sprite类用于游戏图像的创建、载入和绘制 */
class Sprite
{
protected:
	static int m_nNewID;		//下一个可用的精灵编号	
	int		m_ID;				//精灵编号
	HBITMAP m_hbm;				//位图句柄
	int		m_nWidth,m_nHeight;	//位图宽度与高度
	int		m_nZOrder;			//Z顺序

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
	
	HBITMAP GetBitmp()	//获取位图句柄
	{
		return m_hbm;
	}

	void SetBitmap(HBITMAP hbm)	//设置位图句柄
	{
		if(m_hbm!=NULL)
			Release();		//释放资源

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