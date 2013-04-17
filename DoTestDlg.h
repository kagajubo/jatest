#if !defined(AFX_DOTESTDLG_H__61E9EB48_04A7_4A09_A648_C8528A287AF5__INCLUDED_)
#define AFX_DOTESTDLG_H__61E9EB48_04A7_4A09_A648_C8528A287AF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoTestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoTestDlg dialog

class CDoTestDlg : public CDialog
{
// Construction
public:
	CDoTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDoTestDlg)
	enum { IDD = IDD_DIALOG_TEST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDoTestDlg)
	afx_msg void OnButtonGotoSetupDlg();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonOpenCom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOTESTDLG_H__61E9EB48_04A7_4A09_A648_C8528A287AF5__INCLUDED_)
