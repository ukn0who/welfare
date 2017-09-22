// BezierFillDoc.cpp :  CBezierFillDoc 类的实现
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


// CBezierFillDoc 构造/析构

CBezierFillDoc::CBezierFillDoc()
{
	// TODO: 在此添加一次性构造代码

}

CBezierFillDoc::~CBezierFillDoc()
{
}

BOOL CBezierFillDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CBezierFillDoc 序列化

void CBezierFillDoc::Serialize(CArchive& ar)
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


// CBezierFillDoc 诊断

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


// CBezierFillDoc 命令
