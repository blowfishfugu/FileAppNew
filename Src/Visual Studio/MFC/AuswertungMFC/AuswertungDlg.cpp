#include "AuswertungMFC.h"
#include "AuswertungDlg.h"
#include "resource.h"
#include <array>

CAuswertungDlg::CAuswertungDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUSWERTUNGMFC_DIALOG, pParent)
{
	//static resources
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAuswertungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAuswertungDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CAuswertungDlg message handlers

BOOL CAuswertungDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	SetDefID(IDB_ACTION);
	
	InitStatusBar();
	
	proc.Init({ this,false });
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAuswertungDlg::InitStatusBar()
{
	m_statusBar.Create(this); 
	
	//TODO: herausfinden, wie statusbar in nativem win32 ist, hat der auch diverse sectionen, die innerhalb vom control beschickbar sind?

	static std::array<UINT, 1> indicators{ IDS_STATUSBAR };
	m_statusBar.SetIndicators(indicators.data(), static_cast<int>(indicators.size()));

	CRect rect; GetClientRect(&rect);
	m_statusBar.SetPaneInfo(0, IDS_STATUSBAR, SBPS_NORMAL, rect.Width());
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDS_STATUSBAR);
	m_pDynamicLayout->AddItem(m_statusBar.m_hWnd, CMFCDynamicLayout::MoveVertical(100), CMFCDynamicLayout::SizeHorizontal(100));

	m_statusBar.SetPaneText(0, "update statusbar");

}

void CAuswertungDlg::OnPaint()
{
	CDialogEx::OnPaint();
}


void CAuswertungDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu menu;
	ClientToScreen(&point);
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_APP_EXIT, _T("Exit"));
	menu.TrackPopupMenu(0, point.x-24,point.y-10,this);

	CDialogEx::OnRButtonDown(nFlags, point);
}

BOOL CAuswertungDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//switch (wParam) { //menu-command
	//case(wm_user+xxx):
	//default:
	//	break;
	//}

	//defaults in afxres.h z.B. ID_APP_EXIT
	return CDialogEx::OnCommand(wParam, lParam);
}
