// Draw4Doc.cpp :  CDraw4Doc 类的实现
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


// CDraw4Doc 构造/析构

CDraw4Doc::CDraw4Doc()
{
	// TODO: 在此添加一次性构造代码

}

CDraw4Doc::~CDraw4Doc()
{
}

BOOL CDraw4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDraw4Doc 序列化

void CDraw4Doc::Serialize(CArchive& ar)
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


// CDraw4Doc 诊断

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


// CDraw4Doc 命令
