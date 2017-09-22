// DisplaySquareBezierDoc.cpp :  CDisplaySquareBezierDoc 类的实现
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


// CDisplaySquareBezierDoc 构造/析构

CDisplaySquareBezierDoc::CDisplaySquareBezierDoc()
{
	// TODO: 在此添加一次性构造代码

}

CDisplaySquareBezierDoc::~CDisplaySquareBezierDoc()
{
}

BOOL CDisplaySquareBezierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDisplaySquareBezierDoc 序列化

void CDisplaySquareBezierDoc::Serialize(CArchive& ar)
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


// CDisplaySquareBezierDoc 诊断

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


// CDisplaySquareBezierDoc 命令
