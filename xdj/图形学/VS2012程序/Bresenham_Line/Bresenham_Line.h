// Bresenham_Line.h : Bresenham_Line Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CBresenham_LineApp:
// �йش����ʵ�֣������ Bresenham_Line.cpp
//

class CBresenham_LineApp : public CWinApp
{
public:
	CBresenham_LineApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBresenham_LineApp theApp;
