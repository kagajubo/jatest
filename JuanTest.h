// JuanTest.h : main header file for the JUANTEST application
//

#if !defined(AFX_JUANTEST_H__08EE06ED_8D7B_4525_A74D_B05895C220F1__INCLUDED_)
#define AFX_JUANTEST_H__08EE06ED_8D7B_4525_A74D_B05895C220F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJuanTestApp:
// See JuanTest.cpp for the implementation of this class
//

class CJuanTestApp : public CWinApp
{
public:
	CJuanTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJuanTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJuanTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUANTEST_H__08EE06ED_8D7B_4525_A74D_B05895C220F1__INCLUDED_)
