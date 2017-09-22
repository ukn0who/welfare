// MidPointEllipseDoc.cpp :  CMidPointEllipseDoc 类的实现
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


// CMidPointEllipseDoc 构造/析构

CMidPointEllipseDoc::CMidPointEllipseDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMidPointEllipseDoc::~CMidPointEllipseDoc()
{
}

BOOL CMidPointEllipseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMidPointEllipseDoc 序列化

void CMidPointEllipseDoc::Serialize(CArchive& ar)
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


// CMidPointEllipseDoc 诊断

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


// CMidPointEllipseDoc 命令
