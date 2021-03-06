#include "stdafx.h"
#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

/**
 *
 * \return 
 */
COutputWnd::COutputWnd()
{
}

/**
 *
 * \return 
 */
COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/**
 *
 * \param lpszMessage 
 * \param clr 
 * \return 
 */
void	COutputWnd::OutputDebugMessage(const LPCTSTR& lpszMessage, COLORREF clr)
{
	m_wDebug.AddString(lpszMessage, clr);
}

/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int		COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		return -1; 
	}

	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS;
	if (!m_wBuild.Create(dwStyle, rectDummy, &m_wTabs, 2) ||
		!m_wDebug.Create(dwStyle, rectDummy, &m_wTabs, 3) ||
		!m_wFind.Create(dwStyle, rectDummy, &m_wTabs, 4))
	{
		return -1; 
	}

	m_wBuild.SetFont(&m_Font);
	m_wDebug.SetFont(&m_Font);
	m_wFind.SetFont(&m_Font);

	CString strTabName;

	BOOL bNameValid;
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wTabs.AddTab(&m_wDebug, strTabName, (UINT)1);

	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wTabs.AddTab(&m_wBuild, strTabName, (UINT)0);

	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wTabs.AddTab(&m_wFind, strTabName, (UINT)2);

	return 0;
}

/**
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	m_wTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

/**
 *
 * \param wndListBox 
 */
void	COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_Font);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

/**
 *
 * \return 
 */
COutputList::COutputList()
{
}

/**
 *
 * \return 
 */
COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY,		OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR,		OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND,	OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


/**
 *
 * \param pWnd 
 * \param point 
 */
void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

/**
 *
 */
void	COutputList::OnEditCopy()
{
	MessageBox(_T("�������"));
}

/**
 *
 */
void	COutputList::OnEditClear()
{
	MessageBox(_T("������"));
}

/**
 *
 */
void	COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();
	}
}
