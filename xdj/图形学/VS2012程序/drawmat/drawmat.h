// drawmat.h : drawmat Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CdrawmatApp:
// �йش����ʵ�֣������ drawmat.cpp
//

class CdrawmatApp : public CWinApp
{
public:
	CdrawmatApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CdrawmatApp theApp;
