
// StudentAdminDoc.cpp: CStudentAdminDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "StudentAdmin.h"
#endif

#include "StudentAdminDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStudentAdminDoc

IMPLEMENT_DYNCREATE(CStudentAdminDoc, CDocument)

BEGIN_MESSAGE_MAP(CStudentAdminDoc, CDocument)
	ON_COMMAND(ID_ADD, &CStudentAdminDoc::OnAdd)
	ON_COMMAND(ID_MODIFY, &CStudentAdminDoc::OnModify)
	ON_COMMAND(ID_DELETE, &CStudentAdminDoc::OnDelete)
	ON_COMMAND(ID_RANK_SNO, &CStudentAdminDoc::OnRankSno)
	ON_COMMAND(ID_RANK_NAME, &CStudentAdminDoc::OnRankName)
//	ON_COMMAND(ID_FILE_SAVE, &CStudentAdminDoc::OnFileSave)
END_MESSAGE_MAP()


// CStudentAdminDoc 构造/析构

CStudentAdminDoc::CStudentAdminDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	infolist.clear();
	current = -1;
}

CStudentAdminDoc::~CStudentAdminDoc()
{
}

BOOL CStudentAdminDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CStudentAdminDoc 序列化

void CStudentAdminDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar << infolist.size();   //存入学生信息的条数
		for (int i = 0; i < infolist.size(); i++)  //存入每一条学生的信息
		{
			ar << infolist[i].sno << infolist[i].name << infolist[i].sex << infolist[i].birthdate << infolist[i].birthplace << infolist[i].address;
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		int len = 0;
		ar >> len;  //读取信息长度
		infolist.clear();
		current = -1;
		for (int i = 0; i < len; i++)   //将信息读入构建好的结构中
		{
			Info info;
			ar >> info.sno >> info.name >> info.sex >> info.birthdate >> info.birthplace >> info.address;
			infolist.push_back(info);
			current = i;
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CStudentAdminDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CStudentAdminDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CStudentAdminDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CStudentAdminDoc 诊断

#ifdef _DEBUG
void CStudentAdminDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStudentAdminDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CStudentAdminDoc::get_info(int index, Info *info)
{
	*info = infolist[index];
}

// CStudentAdminDoc 命令

void CStudentAdminDoc::OnAdd()
{
	// TODO: 在此添加命令处理程序代码
	StuDialog dlg = new StuDialog();  //弹出对话框
	dlg.sno = "";
	dlg.name = "";
	dlg.sex = "";
	dlg.birthdate = "";
	dlg.birthplace = "";
	dlg.address = "";
	if (dlg.DoModal() == IDOK)  //判断是否是确定
	{
		Info info;  //存储用户输入
		info.sno = dlg.sno;
		info.name = dlg.name;
		info.sex = dlg.sex;
		info.birthdate = dlg.birthdate;
		info.birthplace = dlg.birthplace;
		info.address = dlg.address;
		infolist.push_back(info);  //存入信息表中 
		current = infolist.size() - 1;
		SetModifiedFlag(true);
		UpdateAllViews(NULL);  //更新视图
	}
}


void CStudentAdminDoc::OnModify()
{
	// TODO: 在此添加命令处理程序代码
	if (current < 0)
		return;
	StuDialog dlg = new StuDialog();  //弹出对话框
	Info *get = new Info();  //得到选中行的信息
	get_info(current, get);
	dlg.sno = get->sno;
	dlg.name = get->name;
	dlg.sex = get->sex;
	dlg.birthdate = get->birthdate;
	dlg.birthplace = get->birthplace;
	dlg.address = get->address;
	if (dlg.DoModal() == IDOK)
	{
		Info info;
		info.sno = dlg.sno;
		info.name = dlg.name;
		info.sex = dlg.sex;
		info.birthdate = dlg.birthdate;
		info.birthplace = dlg.birthplace;
		info.address = dlg.address;
		infolist.insert(infolist.begin() + current, info);
		infolist.erase(infolist.begin() + current + 1);
		SetModifiedFlag(true);
		UpdateAllViews(NULL);
	}
}


void CStudentAdminDoc::OnDelete()
{
	// TODO: 在此添加命令处理程序代码
	if (current < 0)
		return;
	infolist.erase(infolist.begin() + current);
	if (current == infolist.size())
		current--;
	SetModifiedFlag(true);
	UpdateAllViews(NULL);
}

struct      //自定义比较函数
{
	bool operator()(Info v1, Info v2) const
	{
		int x1 = _ttoi(v1.sno);
		int x2 = _ttoi(v2.sno);
		return x1 < x2;
     }
} sno_rank;


void CStudentAdminDoc::OnRankSno()
{
	// TODO: 在此添加命令处理程序代码
	std::sort(infolist.begin(), infolist.end(), sno_rank);  //利用sort函数排序
	SetModifiedFlag(true);
	UpdateAllViews(NULL);  //更新视图
}

struct
{
	bool operator()(Info v1, Info v2) const
	{
		CString x1 = v1.name;
		CString x2 = v2.name;
		return x1 < x2;
	}
} name_rank;

void CStudentAdminDoc::OnRankName()
{
	// TODO: 在此添加命令处理程序代码
	std::sort(infolist.begin(), infolist.end(), name_rank);
	SetModifiedFlag(true);
	UpdateAllViews(NULL);
}


//void CStudentAdminDoc::OnFileSave()
//{
//	// TODO: 在此添加命令处理程序代码
//
//}
