// DisplaySquareBezier.h : DisplaySquareBezier Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CDisplaySquareBezierApp:
// �йش����ʵ�֣������ DisplaySquareBezier.cpp
//

class CDisplaySquareBezierApp : public CWinApp
{
public:
	CDisplaySquareBezierApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDisplaySquareBezierApp theApp;
