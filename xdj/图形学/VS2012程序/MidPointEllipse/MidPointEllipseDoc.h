// MidPointEllipseDoc.h :  CMidPointEllipseDoc ��Ľӿ�
//


#pragma once

class CMidPointEllipseDoc : public CDocument
{
protected: // �������л�����
	CMidPointEllipseDoc();
	DECLARE_DYNCREATE(CMidPointEllipseDoc)

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
	virtual ~CMidPointEllipseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


