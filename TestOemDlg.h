#if !defined(AFX_TESTOEMDLG_H__C581477F_FEE6_4CE3_8B1D_6315AC7E35C1__INCLUDED_)
#define AFX_TESTOEMDLG_H__C581477F_FEE6_4CE3_8B1D_6315AC7E35C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestOemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestOemDlg dialog

class CTestOemDlg : public CDialog
{
// Construction
public:
	CTestOemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestOemDlg)
	enum { IDD = IDD_OEM_MODULE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestOemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestOemDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOEMDLG_H__C581477F_FEE6_4CE3_8B1D_6315AC7E35C1__INCLUDED_)
