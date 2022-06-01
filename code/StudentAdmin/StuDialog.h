#pragma once


// StuDialog 对话框

class StuDialog : public CDialog
{
	DECLARE_DYNAMIC(StuDialog)

public:
	StuDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~StuDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_StuDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sno;
	CString name;
	CString sex;
	CString birthdate;
	CString birthplace;
	CString address;
};
