
// MFCApplication1View.h : CMFCApplication1View ��Ľӿ�
//

#pragma once

#define LEFT	1						//������ֵ
#define	RIGHT 2							//������ֵ
#define	BOTTOM 4/						//������ֵ
#define  TOP	8						//������ֵ
#include <gl/glut.h>
#include<vector>


typedef struct								//�����߱�ṹ
{
	int num, ymin,ymax;						//������꣬�յ�����
	float xmin,xmax,dx;						//dx :ɨ��������
}  Edge;


class CMFCApplication1View : public CView
{
protected: // �������л�����
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

	// ����
public:
	int WT;										//�߿򶥲�
	int WB;										//�߿�ײ�
	int WR;										//�߿��ұ�
	int WL;										//�߿����
	CPoint  spt [7],s_point;					//����ζ��������������ʼ���������
	Edge   edge[7],edge1[7],newedge[1];


	CMFCApplication1Doc* GetDocument() const;
protected:
	CPoint		 m_ptOrigin;	 // �������
	bool		 m_bDragging;    // ��ק���	
	HCURSOR		 m_hCross;		 // �����

private:
	HGLRC m_hRC;  
	CClientDC* m_pDC;  


	// ����
public:
	//��Բ����
	void MidpointEllise(CDC *pDC, int x0, int y0, int a, int b, COLORREF color);
	void PositiveNegativeParabola(CDC *pDC, float a, float b, float c, int color);
	//ֱ�������βü�
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
	//�����
	void myinit(void);
	void static CALLBACK myReshapeBall(GLsizei w, GLsizei h);
	void static CALLBACK displayBall(void);

	//�⻬����
	void myinit2(void);
	void  static object(void);
	void static CALLBACK myReshapeLD(GLsizei w, GLsizei h);
	void static CALLBACK displayLD(void);
	//���ʴ���
	void myinit3(void);
	void static CALLBACK myReshapeM(GLsizei w, GLsizei h);
	void static CALLBACK displayM(void);



	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


	// ʵ��
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MFCApplication1View.cpp �еĵ��԰汾
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{ return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

