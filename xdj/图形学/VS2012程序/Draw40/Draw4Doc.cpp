// Draw4Doc.cpp :  CDraw4Doc ���ʵ��
//

#include "stdafx.h"
#include "Draw4.h"

#include "Draw4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraw4Doc

IMPLEMENT_DYNCREATE(CDraw4Doc, CDocument)

BEGIN_MESSAGE_MAP(CDraw4Doc, CDocument)
END_MESSAGE_MAP()


// CDraw4Doc ����/����

CDraw4Doc::CDraw4Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CDraw4Doc::~CDraw4Doc()
{
}

BOOL CDraw4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDraw4Doc ���л�

void CDraw4Doc::Serialize(CArchive& ar)
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


// CDraw4Doc ���

#ifdef _DEBUG
void CDraw4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDraw4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDraw4Doc ����
