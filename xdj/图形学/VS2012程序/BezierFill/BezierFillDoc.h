// BezierFillDoc.h :  CBezierFillDoc ��Ľӿ�
//


#pragma once

class CBezierFillDoc : public CDocument
{
protected: // �������л�����
	CBezierFillDoc();
	DECLARE_DYNCREATE(CBezierFillDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CBezierFillDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


