// draw1.h : draw1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// Cdraw1App:
// �йش����ʵ�֣������ draw1.cpp
//

class Cdraw1App : public CWinApp
{
public:
	Cdraw1App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cdraw1App theApp;
