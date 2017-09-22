// draw1Doc.cpp :  Cdraw1Doc 类的实现
//

#include "stdafx.h"
#include "draw1.h"

#include "draw1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdraw1Doc

IMPLEMENT_DYNCREATE(Cdraw1Doc, CDocument)

BEGIN_MESSAGE_MAP(Cdraw1Doc, CDocument)
END_MESSAGE_MAP()


// Cdraw1Doc 构造/析构

Cdraw1Doc::Cdraw1Doc()
{
	// TODO: 在此添加一次性构造代码

}

Cdraw1Doc::~Cdraw1Doc()
{
}

BOOL Cdraw1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// Cdraw1Doc 序列化

void Cdraw1Doc::Serialize(CArchive& ar)
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


// Cdraw1Doc 诊断

#ifdef _DEBUG
void Cdraw1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cdraw1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cdraw1Doc 命令
