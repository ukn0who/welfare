// drawmatDoc.h :  CdrawmatDoc ��Ľӿ�
//


#pragma once

class CdrawmatDoc : public CDocument
{
protected: // �������л�����
	CdrawmatDoc();
	DECLARE_DYNCREATE(CdrawmatDoc)

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
	virtual ~CdrawmatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


