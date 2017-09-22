
// MFCApplication1Doc.h : CMFCApplication1Doc 类的接口
//


#pragma once
#include "Line.h"

class CMFCApplication1Doc : public CDocument
{
protected: // 仅从序列化创建
	CMFCApplication1Doc();
	DECLARE_DYNCREATE(CMFCApplication1Doc)

// 特性
protected:
	CTypedPtrArray<CObArray, CLine*> m_LineArray;								//存放线段对象
// 操作
public:
	CLine *GetLine(int nIndex);													//获取指定序号线段对象的指针
	void AddLine(CPoint pt1, CPoint pt2);										// 向动态数组中添加新的线段对象的指针
	int GetNumLines();															//获取线段的数量
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
