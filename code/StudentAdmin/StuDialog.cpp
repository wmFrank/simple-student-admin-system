// StuDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "StudentAdmin.h"
#include "StuDialog.h"
#include "afxdialogex.h"


// StuDialog 对话框

IMPLEMENT_DYNAMIC(StuDialog, CDialog)

StuDialog::StuDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_StuDialog, pParent)
	, sno(_T(""))
	, name(_T(""))
	, sex(_T(""))
	, birthdate(_T(""))
	, birthplace(_T(""))
	, address(_T(""))
{

}

StuDialog::~StuDialog()
{
}

void StuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SNO, sno);
	DDV_MaxChars(pDX, sno, 20);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDV_MaxChars(pDX, name, 20);
	DDX_CBString(pDX, IDC_COMBO_SEX, sex);
	DDV_MaxChars(pDX, sex, 20);
	DDX_Text(pDX, IDC_EDIT_BIRTHDATE, birthdate);
	DDV_MaxChars(pDX, birthdate, 20);
	DDX_Text(pDX, IDC_EDIT_BIRTHPLACE, birthplace);
	DDV_MaxChars(pDX, birthplace, 40);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, address);
	DDV_MaxChars(pDX, address, 40);
}


BEGIN_MESSAGE_MAP(StuDialog, CDialog)
END_MESSAGE_MAP()


// StuDialog 消息处理程序
