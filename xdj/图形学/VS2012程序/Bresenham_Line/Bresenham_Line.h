// Bresenham_Line.h : Bresenham_Line 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号


// CBresenham_LineApp:
// 有关此类的实现，请参阅 Bresenham_Line.cpp
//

class CBresenham_LineApp : public CWinApp
{
public:
	CBresenham_LineApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBresenham_LineApp theApp;
