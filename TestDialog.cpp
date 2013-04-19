// TestDialog.cpp : implementation file
//

#include "stdafx.h"
#include "JuanTest.h"
#include "TestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog


CTestDialog::CTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDialog, CDialog)
	//{{AFX_MSG_MAP(CTestDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDialog message handlers

void CTestDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();

}

BOOL CTestDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
}

void CTestDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here	
	
}

void CTestDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
