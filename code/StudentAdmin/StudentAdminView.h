
// StudentAdminView.h: CStudentAdminView 类的接口
//

#pragma once


class CStudentAdminView : public CScrollView
{
protected: // 仅从序列化创建
	CStudentAdminView() noexcept;
	DECLARE_DYNCREATE(CStudentAdminView)

// 特性
public:
	CStudentAdminDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnSize(UINT nType, int cx, int cy);


// 实现
public:
	virtual ~CStudentAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // StudentAdminView.cpp 中的调试版本
inline CStudentAdminDoc* CStudentAdminView::GetDocument() const
   { return reinterpret_cast<CStudentAdminDoc*>(m_pDocument); }
#endif

