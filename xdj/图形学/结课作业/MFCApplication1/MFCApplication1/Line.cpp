#include "stdafx.h"
#include "Line.h"


CLine::CLine(void)
{
}


CLine::~CLine(void)
{
}

CLine::CLine(CPoint pt1, CPoint pt2)
	//初始化坐标
{
	m_pt1=pt1;
	m_pt2=pt2;
}

void CLine::DrawLine(CDC *pDC)
	//从m_pt1 画线到 m_pt2
{
	pDC->MoveTo(m_pt1);
	pDC->LineTo(m_pt2);

}
