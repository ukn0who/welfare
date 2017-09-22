
// MFCApplication1Doc.h : CMFCApplication1Doc ��Ľӿ�
//


#pragma once
#include "Line.h"

class CMFCApplication1Doc : public CDocument
{
protected: // �������л�����
	CMFCApplication1Doc();
	DECLARE_DYNCREATE(CMFCApplication1Doc)

// ����
protected:
	CTypedPtrArray<CObArray, CLine*> m_LineArray;								//����߶ζ���
// ����
public:
	CLine *GetLine(int nIndex);													//��ȡָ������߶ζ����ָ��
	void AddLine(CPoint pt1, CPoint pt2);										// ��̬����������µ��߶ζ����ָ��
	int GetNumLines();															//��ȡ�߶ε�����
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
