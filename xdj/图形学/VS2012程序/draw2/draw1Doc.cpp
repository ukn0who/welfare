// draw1Doc.cpp :  Cdraw1Doc ���ʵ��
//

#include "stdafx.h"
#include "draw1.h"

#include "draw1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdraw1Doc

IMPLEMENT_DYNCREATE(Cdraw1Doc, CDocument)

BEGIN_MESSAGE_MAP(Cdraw1Doc, CDocument)
END_MESSAGE_MAP()


// Cdraw1Doc ����/����

Cdraw1Doc::Cdraw1Doc()
{
	// TODO: �ڴ����һ���Թ������

}

Cdraw1Doc::~Cdraw1Doc()
{
}

BOOL Cdraw1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// Cdraw1Doc ���л�

void Cdraw1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// Cdraw1Doc ���

#ifdef _DEBUG
void Cdraw1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cdraw1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cdraw1Doc ����
