
// StudentAdminView.cpp: CStudentAdminView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "StudentAdmin.h"
#endif

#include "StudentAdminDoc.h"
#include "StudentAdminView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentAdminView

IMPLEMENT_DYNCREATE(CStudentAdminView, CScrollView)

BEGIN_MESSAGE_MAP(CStudentAdminView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CStudentAdminView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CStudentAdminView 构造/析构

CStudentAdminView::CStudentAdminView() noexcept
{
	// TODO: 在此处添加构造代码

}

CStudentAdminView::~CStudentAdminView()
{
}

BOOL CStudentAdminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CStudentAdminView 绘图

void CStudentAdminView::OnDraw(CDC* pDC)
{
	CStudentAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	CFont *old_font = (CFont *)pDC->SelectStockObject(ANSI_FIXED_FONT);  //设置新字体
	for (int i = 0, num = pDoc->infolist.size(); i < num; i++)
	{
		Info *st = new Info();
		pDoc->get_info(i, st);
		CString temp;       //将学生的信息存储为一个格式化的CString类型变量
		temp.Format(_T("%-20.20s%-20.20s%-20.20s%-20.20s%-20.20s%-20.20s"), st->sno, st->name, st->sex, st->birthdate, st->birthplace, st->address);
		if (i != pDoc->current)   //设置背景色和字体颜色（区分选中的信息）
		{
			pDC->SetTextColor(RGB(220, 20, 60));
			pDC->SetBkColor(RGB(255, 255, 255));
		}
		else
		{
			pDC->SetBkColor(RGB(220, 20, 60));
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		pDC->TextOut(0, i * 20, temp);  //输出字符串
	}
	pDC->SelectObject(old_font);  //将字体还原
}

void CStudentAdminView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CStudentAdminDoc* pDoc = GetDocument();
	CSize sizeTotal, sizePage, sizeLine;
	sizeTotal.cx = 1000;
	sizeTotal.cy = pDoc->infolist.size() * 20;  //重新设置滚动页的大小
	RECT rect;
	GetClientRect(&rect); //获取视窗口的大小
	sizePage.cx = rect.right - rect.left - 8;
	sizePage.cy = rect.bottom - rect.top - 20;
	sizeLine.cx = 8;
	sizeLine.cy = 20;
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
	
	/*CScrollView::OnInitialUpdate();
	CStudentAdminDoc* pDoc = GetDocument();
	CSize sizeTotal;
	sizeTotal.cx = 1000;
	sizeTotal.cy = pDoc->infolist.size() * 20;  //重新设置滚动页的大小
	SetScrollSizes(MM_TEXT, sizeTotal);*/

}


// CStudentAdminView 打印


void CStudentAdminView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CStudentAdminView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStudentAdminView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CStudentAdminView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CStudentAdminView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStudentAdminView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CStudentAdminView 诊断

#ifdef _DEBUG
void CStudentAdminView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CStudentAdminView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CStudentAdminDoc* CStudentAdminView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentAdminDoc)));
	return (CStudentAdminDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudentAdminView 消息处理程序


void CStudentAdminView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//利用DC类来讲物理坐标转化为逻辑坐标
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
	CStudentAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int y = point.y;
	int line = y / 20;
	if(line < pDoc->infolist.size())
		pDoc->current = line;
	Invalidate();

	CScrollView::OnLButtonDown(nFlags, point);
}

void CStudentAdminView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//在文档大小变化的时候动态改变滚动条的范围
	CStudentAdminDoc* pDoc = GetDocument();
	CSize sizeTotal, sizePage, sizeLine;
	sizeTotal.cx = 1000;
	sizeTotal.cy = pDoc->infolist.size() * 20;
	RECT rect;
	GetClientRect(&rect); //获取视窗口的大小
	sizePage.cx = rect.right - rect.left - 8;
	sizePage.cy = rect.bottom - rect.top - 20;
	sizeLine.cx = 8;
	sizeLine.cy = 20;
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);  //根据视窗大小调整滚动条的范围
	Invalidate();
}

void CStudentAdminView::OnSize(UINT nType, int cx, int cy)
{
	//在视窗大小变化的时候动态改变滚动条的范围
	CScrollView::OnSize(nType, cx, cy);
	CStudentAdminDoc* pDoc = GetDocument();
	CSize sizeTotal, sizePage, sizeLine;  //得到视窗的真实大小
	sizeTotal.cx = 1000;
	sizeTotal.cy = pDoc->infolist.size() * 20;
	sizePage.cx = cx - 8;
	sizePage.cy = cy - 20;
	sizeLine.cx = 8;
	sizeLine.cy = 20;
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

void CStudentAdminView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CStudentAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	StuDialog dlg = new StuDialog();
	Info *get = new Info();
	pDoc->get_info(pDoc->current, get);
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
		pDoc->infolist.insert(pDoc->infolist.begin() + pDoc->current, info);
		pDoc->infolist.erase(pDoc->infolist.begin() + pDoc->current + 1);
		pDoc->SetModifiedFlag(true);
		pDoc->UpdateAllViews(NULL);
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}
