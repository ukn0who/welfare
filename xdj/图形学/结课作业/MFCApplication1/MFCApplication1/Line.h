#pragma once
#include "afx.h"
class CLine :
	public CObject
{
	//��Ա����
private:
	CPoint m_pt1;					//�Զ�����ʼ����
	CPoint m_pt2;					//�Զ����е�����
public:
	CLine(void);
	CLine(CPoint pt1, CPoint pt2);
	~CLine(void);
	void DrawLine(CDC *pDC);
};

