// Bresenham_LineDoc.h :  CBresenham_LineDoc ��Ľӿ�
//


#pragma once

class CBresenham_LineDoc : public CDocument
{
protected: // �������л�����
	CBresenham_LineDoc();
	DECLARE_DYNCREATE(CBresenham_LineDoc)

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
	virtual ~CBresenham_LineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


