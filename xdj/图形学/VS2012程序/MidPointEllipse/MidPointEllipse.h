// MidPointEllipse.h : MidPointEllipse Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CMidPointEllipseApp:
// �йش����ʵ�֣������ MidPointEllipse.cpp
//

class CMidPointEllipseApp : public CWinApp
{
public:
	CMidPointEllipseApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMidPointEllipseApp theApp;
