// BezierFillDoc.cpp :  CBezierFillDoc ���ʵ��
//

#include "stdafx.h"
#include "BezierFill.h"

#include "BezierFillDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierFillDoc

IMPLEMENT_DYNCREATE(CBezierFillDoc, CDocument)

BEGIN_MESSAGE_MAP(CBezierFillDoc, CDocument)
END_MESSAGE_MAP()


// CBezierFillDoc ����/����

CBezierFillDoc::CBezierFillDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CBezierFillDoc::~CBezierFillDoc()
{
}

BOOL CBezierFillDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CBezierFillDoc ���л�

void CBezierFillDoc::Serialize(CArchive& ar)
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


// CBezierFillDoc ���

#ifdef _DEBUG
void CBezierFillDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBezierFillDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBezierFillDoc ����
