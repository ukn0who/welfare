// draw1Doc.h :  Cdraw1Doc ��Ľӿ�
//


#pragma once

class Cdraw1Doc : public CDocument
{
protected: // �������л�����
	Cdraw1Doc();
	DECLARE_DYNCREATE(Cdraw1Doc)

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
	virtual ~Cdraw1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


