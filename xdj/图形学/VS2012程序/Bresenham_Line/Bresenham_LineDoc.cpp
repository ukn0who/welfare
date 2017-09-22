// Bresenham_LineDoc.cpp :  CBresenham_LineDoc 类的实现
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


// CBresenham_LineDoc 构造/析构

CBresenham_LineDoc::CBresenham_LineDoc()
{
	// TODO: 在此添加一次性构造代码

}

CBresenham_LineDoc::~CBresenham_LineDoc()
{
}

BOOL CBresenham_LineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CBresenham_LineDoc 序列化

void CBresenham_LineDoc::Serialize(CArchive& ar)
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


// CBresenham_LineDoc 诊断

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


// CBresenham_LineDoc 命令
