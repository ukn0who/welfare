// drawmatDoc.cpp :  CdrawmatDoc 类的实现
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


// CdrawmatDoc 构造/析构

CdrawmatDoc::CdrawmatDoc()
{
	// TODO: 在此添加一次性构造代码

}

CdrawmatDoc::~CdrawmatDoc()
{
}

BOOL CdrawmatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CdrawmatDoc 序列化

void CdrawmatDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CdrawmatDoc 诊断

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


// CdrawmatDoc 命令
