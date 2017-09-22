// drawmatView.cpp : CdrawmatView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CdrawmatView ����/����

CdrawmatView::CdrawmatView()
{
	// TODO: �ڴ˴���ӹ������

}

CdrawmatView::~CdrawmatView()
{
}

BOOL CdrawmatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CdrawmatView ����

void CdrawmatView::OnDraw(CDC* /*pDC*/)
{
	CdrawmatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	  char ming24S[]={/* ������ '��' �� 24�������� ��ģ��72 byte */
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


// CdrawmatView ��ӡ

BOOL CdrawmatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CdrawmatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CdrawmatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CdrawmatView ���

#ifdef _DEBUG
void CdrawmatView::AssertValid() const
{
	CView::AssertValid();
}

void CdrawmatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdrawmatDoc* CdrawmatView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdrawmatDoc)));
	return (CdrawmatDoc*)m_pDocument;
}
#endif //_DEBUG


// CdrawmatView ��Ϣ�������
void CdrawmatView::drawmat(char *mat,int matsize,int x,int y,int color)
{/*���Σ���ģָ�롢�����С����ʼ����(x,y)����ɫ*/
	CDC *pDC = GetDC();
	int i,j,k,n;
    n=(matsize-1)/8+1;
    for(j=0;j<matsize;j++)
        for(i=0;i<n;i++)
            for(k=0;k<8;k++)
                if(mat[j*n+i]&(0x80>>k))  /*����Ϊ1��λ����ʾ*/
					pDC->SetPixel(x+i*8+k,y+j,color);
}
