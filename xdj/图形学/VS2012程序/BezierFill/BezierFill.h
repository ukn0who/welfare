// BezierFill.h : BezierFill Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CBezierFillApp:
// �йش����ʵ�֣������ BezierFill.cpp
//

class CBezierFillApp : public CWinApp
{
public:
	CBezierFillApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBezierFillApp theApp;
