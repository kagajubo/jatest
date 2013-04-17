// DoTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JuanTest.h"
#include "DoTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoTestDlg dialog


CDoTestDlg::CDoTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDoTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDoTestDlg)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_SETUP_DLG, OnButtonGotoSetupDlg)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_COM, OnButtonOpenCom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoTestDlg message handlers

void CDoTestDlg::OnButtonGotoSetupDlg() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(false);
	this->GetParent()->ShowWindow(true);
}

void CDoTestDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}

void CDoTestDlg::OnButtonOpenCom() 
{
	// TODO: Add your control notification handler code here
	
}
