#include "stdafx.h"
#include "Line.h"


CLine::CLine(void)
{
}


CLine::~CLine(void)
{
}

CLine::CLine(CPoint pt1, CPoint pt2)
	//��ʼ������
{
	m_pt1=pt1;
	m_pt2=pt2;
}

void CLine::DrawLine(CDC *pDC)
	//��m_pt1 ���ߵ� m_pt2
{
	pDC->MoveTo(m_pt1);
	pDC->LineTo(m_pt2);

}
