#if !defined(AFX_TESTDIALOG_H__3D90139F_80E9_483D_BE1D_611D4AE75600__INCLUDED_)
#define AFX_TESTDIALOG_H__3D90139F_80E9_483D_BE1D_611D4AE75600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDialog.h : header file
//
#include "serialport.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog

class CTestDialog : public CDialog
{
private:
	cnComm *serialport;

// Construction
public:
	CTestDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOG_H__3D90139F_80E9_483D_BE1D_611D4AE75600__INCLUDED_)
