// Bresenham_LineDoc.cpp :  CBresenham_LineDoc ���ʵ��
//

#include "stdafx.h"
#include "Bresenham_Line.h"

#include "Bresenham_LineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBresenham_LineDoc

IMPLEMENT_DYNCREATE(CBresenham_LineDoc, CDocument)

BEGIN_MESSAGE_MAP(CBresenham_LineDoc, CDocument)
END_MESSAGE_MAP()


// CBresenham_LineDoc ����/����

CBresenham_LineDoc::CBresenham_LineDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CBresenham_LineDoc::~CBresenham_LineDoc()
{
}

BOOL CBresenham_LineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CBresenham_LineDoc ���л�

void CBresenham_LineDoc::Serialize(CArchive& ar)
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


// CBresenham_LineDoc ���

#ifdef _DEBUG
void CBresenham_LineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBresenham_LineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBresenham_LineDoc ����
