#include "framework.h"
#include "AuswertungMFC.h"
#include "AuswertungDlg.h"

CAuswertungDlg::CAuswertungDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUSWERTUNGMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAuswertungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAuswertungDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CAuswertungDlg message handlers

BOOL CAuswertungDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetDefID(IDB_ACTION);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAuswertungDlg::OnPaint()
{
	CDialogEx::OnPaint();
}

