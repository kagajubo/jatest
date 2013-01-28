// TestOemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JuanTest.h"
#include "TestOemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestOemDlg dialog


CTestOemDlg::CTestOemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestOemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestOemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestOemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestOemDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestOemDlg, CDialog)
	//{{AFX_MSG_MAP(CTestOemDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestOemDlg message handlers
