#pragma once

#include <adecc_Scholar/MyForm.h>
#include "afxdialogex.h"
#include <FileAppProcess.h> //Independed

class CAuswertungDlg : public CDialogEx
{
public:
	CAuswertungDlg(CWnd* pParent = nullptr);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUSWERTUNGMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CStatusBar m_statusBar;

	TProcess proc;
// Implementation
protected:
	HICON m_hIcon;
	void InitStatusBar();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
