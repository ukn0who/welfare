// drawmatDoc.cpp :  CdrawmatDoc ���ʵ��
//

#include "stdafx.h"
#include "drawmat.h"

#include "drawmatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdrawmatDoc

IMPLEMENT_DYNCREATE(CdrawmatDoc, CDocument)

BEGIN_MESSAGE_MAP(CdrawmatDoc, CDocument)
END_MESSAGE_MAP()


// CdrawmatDoc ����/����

CdrawmatDoc::CdrawmatDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CdrawmatDoc::~CdrawmatDoc()
{
}

BOOL CdrawmatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CdrawmatDoc ���л�

void CdrawmatDoc::Serialize(CArchive& ar)
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


// CdrawmatDoc ���

#ifdef _DEBUG
void CdrawmatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CdrawmatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CdrawmatDoc ����
