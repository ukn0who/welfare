// DisplaySquareBezierDoc.cpp :  CDisplaySquareBezierDoc ���ʵ��
//

#include "stdafx.h"
#include "DisplaySquareBezier.h"

#include "DisplaySquareBezierDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDisplaySquareBezierDoc

IMPLEMENT_DYNCREATE(CDisplaySquareBezierDoc, CDocument)

BEGIN_MESSAGE_MAP(CDisplaySquareBezierDoc, CDocument)
END_MESSAGE_MAP()


// CDisplaySquareBezierDoc ����/����

CDisplaySquareBezierDoc::CDisplaySquareBezierDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDisplaySquareBezierDoc::~CDisplaySquareBezierDoc()
{
}

BOOL CDisplaySquareBezierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDisplaySquareBezierDoc ���л�

void CDisplaySquareBezierDoc::Serialize(CArchive& ar)
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


// CDisplaySquareBezierDoc ���

#ifdef _DEBUG
void CDisplaySquareBezierDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDisplaySquareBezierDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDisplaySquareBezierDoc ����
