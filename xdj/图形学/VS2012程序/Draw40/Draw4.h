// Draw4.h : Draw4 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CDraw4App:
// �йش����ʵ�֣������ Draw4.cpp
//

class CDraw4App : public CWinApp
{
public:
	CDraw4App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDraw4App theApp;
