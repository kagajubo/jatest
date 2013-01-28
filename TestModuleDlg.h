#if !defined(AFX_TESTMODULEDLG_H__421D3DFD_C421_4267_BE8A_C95B94BE4F50__INCLUDED_)
#define AFX_TESTMODULEDLG_H__421D3DFD_C421_4267_BE8A_C95B94BE4F50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestModuleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestModuleDlg dialog

class CTestModuleDlg : public CDialog
{
// Construction
public:
	CTestModuleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestModuleDlg)
	enum { IDD = IDD_TEST_MODULE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestModuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestModuleDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMODULEDLG_H__421D3DFD_C421_4267_BE8A_C95B94BE4F50__INCLUDED_)
