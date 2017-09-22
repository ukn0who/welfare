
// MFCApplication1View.h : CMFCApplication1View 类的接口
//

#pragma once

#define LEFT	1						//编码数值
#define	RIGHT 2							//编码数值
#define	BOTTOM 4/						//编码数值
#define  TOP	8						//编码数值
#include <gl/glut.h>
#include<vector>


typedef struct								//建立边表结构
{
	int num, ymin,ymax;						//起点坐标，终点坐标
	float xmin,xmax,dx;						//dx :扫描线增量
}  Edge;


class CMFCApplication1View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

	// 特性
public:
	int WT;										//边框顶部
	int WB;										//边框底部
	int WR;										//边框右边
	int WL;										//边框左边
	CPoint  spt [7],s_point;					//多边形顶点坐标数组和起始种子坐标点
	Edge   edge[7],edge1[7],newedge[1];


	CMFCApplication1Doc* GetDocument() const;
protected:
	CPoint		 m_ptOrigin;	 // 起点坐标
	bool		 m_bDragging;    // 拖拽标记	
	HCURSOR		 m_hCross;		 // 光标句柄

private:
	HGLRC m_hRC;  
	CClientDC* m_pDC;  


	// 操作
public:
	//椭圆花瓣
	void MidpointEllise(CDC *pDC, int x0, int y0, int a, int b, COLORREF color);
	void PositiveNegativeParabola(CDC *pDC, float a, float b, float c, int color);
	//直线与多边形裁剪
	int C_S_Line(CDC* pDC,int x1,int y1,int x2,int y2);
	void encode(int x,int y,int *code);
	void DrawRose();
	void DrawLeaf();
	//GL
	void Initial(void);
	void static ChangeSize(int w,int h);
	void static Display();
	void static ProcessMenu(int value);
	void static SpecialKeys(int key,int x,int y);
	//光感球
	void myinit(void);
	void static CALLBACK myReshapeBall(GLsizei w, GLsizei h);
	void static CALLBACK displayBall(void);

	//光滑明暗
	void myinit2(void);
	void  static object(void);
	void static CALLBACK myReshapeLD(GLsizei w, GLsizei h);
	void static CALLBACK displayLD(void);
	//材质处理
	void myinit3(void);
	void static CALLBACK myReshapeM(GLsizei w, GLsizei h);
	void static CALLBACK displayM(void);



	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


	// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnScanfill();
	afx_msg void OnSeedfill();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawleaf();
	afx_msg void OnDrawrose();
	//	afx_msg void OnNcMButtonUp(UINT nHitTest, CPoint point);
	//	afx_msg void OnSize(UINT nType, int cx, int cy);
	//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	//	afx_msg void OnDrawgl();
	afx_msg void OnDrawgl();
	//	afx_msg void OnRealball();
//	afx_msg void OnRealball();
//	afx_msg void OnDrawld();
//	afx_msg void OnMaterial();
};

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{ return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

