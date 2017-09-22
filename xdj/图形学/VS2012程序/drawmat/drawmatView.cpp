// drawmatView.cpp : CdrawmatView 类的实现
//

#include "stdafx.h"
#include "drawmat.h"

#include "drawmatDoc.h"
#include "drawmatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdrawmatView

IMPLEMENT_DYNCREATE(CdrawmatView, CView)

BEGIN_MESSAGE_MAP(CdrawmatView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CdrawmatView 构造/析构

CdrawmatView::CdrawmatView()
{
	// TODO: 在此处添加构造代码

}

CdrawmatView::~CdrawmatView()
{
}

BOOL CdrawmatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CdrawmatView 绘制

void CdrawmatView::OnDraw(CDC* /*pDC*/)
{
	CdrawmatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	  char ming24S[]={/* 以下是 '明' 的 24点阵宋体 字模，72 byte */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x08,0x00,0x07,0xF8,0x1F,0xC4,0x18,0x10,
  0x44,0x18,0x10,0x44,0x18,0x10,0x44,0x18,
  0x10,0x44,0x18,0x1F,0xC7,0xF8,0x10,0x44,
  0x18,0x10,0x44,0x18,0x10,0x44,0x18,0x10,
  0x44,0x18,0x10,0x4F,0xF8,0x1F,0xCC,0x18,
  0x10,0x48,0x18,0x10,0x08,0x18,0x00,0x18,
  0x18,0x00,0x10,0x18,0x00,0x20,0x18,0x00,
  0x40,0xF0,0x01,0x80,0x30,0x00,0x00,0x00,
};
drawmat(ming24S,24,100,50,255);

}


// CdrawmatView 打印

BOOL CdrawmatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CdrawmatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CdrawmatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CdrawmatView 诊断

#ifdef _DEBUG
void CdrawmatView::AssertValid() const
{
	CView::AssertValid();
}

void CdrawmatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdrawmatDoc* CdrawmatView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdrawmatDoc)));
	return (CdrawmatDoc*)m_pDocument;
}
#endif //_DEBUG


// CdrawmatView 消息处理程序
void CdrawmatView::drawmat(char *mat,int matsize,int x,int y,int color)
{/*依次：字模指针、点阵大小、起始坐标(x,y)、颜色*/
	CDC *pDC = GetDC();
	int i,j,k,n;
    n=(matsize-1)/8+1;
    for(j=0;j<matsize;j++)
        for(i=0;i<n;i++)
            for(k=0;k<8;k++)
                if(mat[j*n+i]&(0x80>>k))  /*测试为1的位则显示*/
					pDC->SetPixel(x+i*8+k,y+j,color);
}
