// MidPointEllipseDoc.cpp :  CMidPointEllipseDoc ���ʵ��
//

#include "stdafx.h"
#include "MidPointEllipse.h"

#include "MidPointEllipseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidPointEllipseDoc

IMPLEMENT_DYNCREATE(CMidPointEllipseDoc, CDocument)

BEGIN_MESSAGE_MAP(CMidPointEllipseDoc, CDocument)
END_MESSAGE_MAP()


// CMidPointEllipseDoc ����/����

CMidPointEllipseDoc::CMidPointEllipseDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMidPointEllipseDoc::~CMidPointEllipseDoc()
{
}

BOOL CMidPointEllipseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMidPointEllipseDoc ���л�

void CMidPointEllipseDoc::Serialize(CArchive& ar)
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


// CMidPointEllipseDoc ���

#ifdef _DEBUG
void CMidPointEllipseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMidPointEllipseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMidPointEllipseDoc ����
