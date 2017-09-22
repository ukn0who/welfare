#pragma once
#include "afx.h"
class CLine :
	public CObject
{
	//成员变量
private:
	CPoint m_pt1;					//自定义起始坐标
	CPoint m_pt2;					//自定义中点坐标
public:
	CLine(void);
	CLine(CPoint pt1, CPoint pt2);
	~CLine(void);
	void DrawLine(CDC *pDC);
};

