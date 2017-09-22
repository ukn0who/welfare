// draw1.h : draw1 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号


// Cdraw1App:
// 有关此类的实现，请参阅 draw1.cpp
//

class Cdraw1App : public CWinApp
{
public:
	Cdraw1App();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cdraw1App theApp;
