
// StudentAdminDoc.h: CStudentAdminDoc 类的接口
//


#pragma once

#include "StuDialog.h"
//#include "MainFrm.h"
//#include "StudentAdminView.h"

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
//学生信息结构体
struct Info {
	CString sno;
	CString name;
	CString sex;
	CString birthdate;
	CString birthplace;
	CString address;
};


class CStudentAdminDoc : public CDocument
{
protected: // 仅从序列化创建
	CStudentAdminDoc() noexcept;
	DECLARE_DYNCREATE(CStudentAdminDoc)

// 特性
public:

// 操作
public:

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
	virtual ~CStudentAdminDoc();
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
public:
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDelete();
	afx_msg void OnRankSno();
	afx_msg void OnRankName();

	vector<Info> infolist;
	void get_info(int index, Info *info);
	int current;
//	afx_msg void OnFileSave();
};
