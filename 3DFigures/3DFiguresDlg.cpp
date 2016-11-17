
// 3DFiguresDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3DFigures.h"
#include "3DFiguresDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMy3DFiguresDlg dialog



CMy3DFiguresDlg::CMy3DFiguresDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY3DFIGURES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3DFiguresDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy3DFiguresDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ADD_SPHERE, &CMy3DFiguresDlg::OnAddSphere)
	ON_COMMAND(ID_ADD_PIRAMID, &CMy3DFiguresDlg::OnAddPiramid)
	ON_COMMAND(ID_FILE_QUIT, &CMy3DFiguresDlg::OnFileQuit)
	ON_COMMAND(ID_FILE_SAVE32771, &CMy3DFiguresDlg::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN32774, &CMy3DFiguresDlg::OnFileOpen)
END_MESSAGE_MAP()


// CMy3DFiguresDlg message handlers

BOOL CMy3DFiguresDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	CRect rect;

	// Get size and position of the picture control
	GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);
	GetDlgItem(IDC_OPENGL)->SetFocus();
	

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.Create(rect, this);

	// Setup the OpenGL Window's timer to render
	m_oglWindow.timer = m_oglWindow.SetTimer(1, 1, 0);

	this->GetWindowRect(rect);

	m_objDlg = new CObjectsDialog;
	m_objDlg->Create(IDD_OBJECT_DIALOG, GetDesktopWindow());
	m_objDlg->SetWindowPos(&wndTopMost, rect.right - 150, rect.top + 129, 100, 100, SWP_NOSIZE);
	m_objDlg->SetRange(m_oglWindow.getRange());
	m_objDlg->ShowWindow(SW_SHOW);

	m_editDlg = new CEditDialog;
	m_editDlg->Create(IDD_EDIT_DIALOG, GetDesktopWindow());
	m_editDlg->SetWindowPos(&wndTop, rect.right - 150, rect.top + 230, 100, 100, SWP_NOSIZE);
	m_editDlg->ShowWindow(SW_SHOW);
	
	m_oglWindow.setDialog(m_objDlg, m_editDlg);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3DFiguresDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3DFiguresDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy3DFiguresDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy3DFiguresDlg::OnAddSphere()
{
	m_oglWindow.addObject(SPHERE);
	m_objDlg->SetRange(m_oglWindow.getRange());
}



void CMy3DFiguresDlg::OnAddPiramid()
{
	m_oglWindow.addObject(PIRAMID);
	m_objDlg->SetRange(m_oglWindow.getRange());
}


void CMy3DFiguresDlg::OnFileQuit()
{
	DestroyWindow();
}



void CMy3DFiguresDlg::OnFileSave()
{
	this->m_oglWindow.onSave();
}


void CMy3DFiguresDlg::OnFileOpen()
{
	this->m_oglWindow.onOpen();
}
