// DisplaySquareBezierDoc.h :  CDisplaySquareBezierDoc ��Ľӿ�
//


#pragma once

class CDisplaySquareBezierDoc : public CDocument
{
protected: // �������л�����
	CDisplaySquareBezierDoc();
	DECLARE_DYNCREATE(CDisplaySquareBezierDoc)

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
	virtual ~CDisplaySquareBezierDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


