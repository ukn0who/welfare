// Draw4Doc.h :  CDraw4Doc ��Ľӿ�
//


#pragma once

class CDraw4Doc : public CDocument
{
protected: // �������л�����
	CDraw4Doc();
	DECLARE_DYNCREATE(CDraw4Doc)

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
	virtual ~CDraw4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


