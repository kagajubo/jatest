// JuanTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JuanTest.h"
#include "JuanTestDlg.h"
#include "TestSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char *sz_inifile="E:/woks/vc++/JuanTest/conf/conf.ini";

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJuanTestDlg dialog

CJuanTestDlg::CJuanTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJuanTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJuanTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJuanTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJuanTestDlg)
	DDX_Control(pDX, IDC_COMBO_DEV_TYPE, m_dev_list);
	DDX_Control(pDX, IDC_COMBO_COM_LIST, m_com_list);
	DDX_Control(pDX, IDC_TAB_MODULE, m_tabModule);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJuanTestDlg, CDialog)
	//{{AFX_MSG_MAP(CJuanTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MODULE, OnSelchangeTabModule)
	ON_BN_CLICKED(IDC_BUTTON_BOARD_TEST, OnButtonBoardTest)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_CBN_SELCHANGE(IDC_COMBO_COM_LIST, OnSelchangeComboComList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
void CJuanTestDlg::init_all_widgets()
{
	// load device name
	m_dev_list.ResetContent();
	for(int i=0; i < 255; i++){
		CString key;
		key.Format("DNAME_%d",i+1);
		char s[512];
		int ret=GetPrivateProfileString("DEVNAME",key,"",s,sizeof(s),sz_inifile);
		if ( ret == 0 ){
			printf("read total dev:%d\n",i);
			break;	
		}else if(ret < 0){
			CString err_msg;
			err_msg.Format("last err no: %d ",GetLastError());
			MessageBox(err_msg);
		}
		m_dev_list.AddString(s);
	}
	//
	
}

// CJuanTestDlg message handlers

BOOL CJuanTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// create tab control
	m_tabModule.InsertItem(0,"测试选项");
	m_tabModule.InsertItem(1,"OEM选项");
	m_module_set.Create(IDD_TEST_MODULE,GetDlgItem(IDC_TAB_MODULE));
	m_oem_set.Create(IDD_OEM_MODULE,GetDlgItem(IDC_TAB_MODULE));
	CRect rect;
	m_tabModule.GetClientRect(&rect);
	rect.top+=30;
	rect.bottom -=32;
	rect.left+=1;
	rect.right-=2;
	m_module_set.MoveWindow(&rect);
	m_oem_set.MoveWindow(&rect);
	m_module_set.ShowWindow(true);
	m_oem_set.ShowWindow(false);
	m_tabModule.SetCurSel(0);
	//load available serial ports
	m_com_list.ResetContent();
	for(int i=1; i < 256; i++){
		CString s;
		COMMCONFIG cc;
		DWORD ccsize=sizeof(COMMCONFIG);
		s.Format("COM%d",i);
		if(GetDefaultCommConfig(s,&cc,&ccsize)==TRUE){
			m_com_list.AddString(s);
		}
	}
	//
	init_all_widgets();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJuanTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJuanTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJuanTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CJuanTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CJuanTestDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CJuanTestDlg::OnOnCommMscomm() 
{
	// TODO: Add your control notification handler code here
	
}

void CJuanTestDlg::OnSelchangeTabModule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int sel=m_tabModule.GetCurSel();
	if(sel==0){
		m_module_set.ShowWindow(true);
		m_oem_set.ShowWindow(false);
	} else {
		m_module_set.ShowWindow(false);
		m_oem_set.ShowWindow(true);
	}

	*pResult = 0;
}

void CJuanTestDlg::OnButtonBoardTest() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(false);
	m_test_dlg.Create(IDD_DIALOG_TEST,GetDlgItem(IDD_JUANTEST_DIALOG));
	//m_test_dlg.DoModal();
	m_test_dlg.ShowWindow(true);
}

void CJuanTestDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}

void CJuanTestDlg::OnSelchangeComboComList() 
{
	/*
	// TODO: Add your control notification handler code here
	CString old_dev=g_TestSystem.comm->GetDevName();
	if(old_dev!="null"){
		if(g_TestSystem.comm->isOpen()==TRUE){
			g_TestSystem.comm->Close();
		}
	}
	CString new_dev;
	GetDlgItem(IDC_COMBO_COM_LIST)->GetWindowText(new_dev);
	g_TestSystem.comm->SetDevName(new_dev);
	g_TestSystem.comm->Open();
	printf("open dev:%s %s\n",new_dev,g_TestSystem.comm->isOpen() ? "true" : "false");
	*/
}
