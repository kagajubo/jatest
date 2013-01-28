// JuanTestDlg.h : header file
//

#if !defined(AFX_JUANTESTDLG_H__E9FBAD96_1A20_4B8F_8046_3788309CDFD6__INCLUDED_)
#define AFX_JUANTESTDLG_H__E9FBAD96_1A20_4B8F_8046_3788309CDFD6__INCLUDED_

#include "TestModuleDlg.h"
#include "TestOemDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CJuanTestDlg dialog

class CJuanTestDlg : public CDialog
{
// Construction
private:
	CTestModuleDlg m_module_set;
	CTestOemDlg m_oem_set;

public:
	CJuanTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJuanTestDlg)
	enum { IDD = IDD_JUANTEST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJuanTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJuanTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnOnCommMscomm();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUANTESTDLG_H__E9FBAD96_1A20_4B8F_8046_3788309CDFD6__INCLUDED_)
