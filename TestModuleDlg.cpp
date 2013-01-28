// TestModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JuanTest.h"
#include "TestModuleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestModuleDlg dialog


CTestModuleDlg::CTestModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestModuleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestModuleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestModuleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestModuleDlg, CDialog)
	//{{AFX_MSG_MAP(CTestModuleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestModuleDlg message handlers
