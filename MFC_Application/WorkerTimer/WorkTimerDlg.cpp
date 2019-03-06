
// WorkTimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorkTimer.h"
#include "WorkTimerDlg.h"
#include "afxdialogex.h"
#include <thread>
#include <chrono>         
#include <cstdlib>

#include <string>
#include <exception>

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


// CWorkTimerDlg dialog
CWorkTimerDlg::~CWorkTimerDlg(){
	if (this->threadStarted) {
		this->threadStarted = false;
		timerThread.detach();
	}
}

CWorkTimerDlg::CWorkTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORKTIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWorkTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWorkTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENTER, &CWorkTimerDlg::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CWorkTimerDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CWorkTimerDlg message handlers

BOOL CWorkTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	threadStarted = false;

	CFont font;
	font.CreateFont(
		14,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));                 // lpszFacename

	GetDlgItem(IDC_STATIC_TIMER)->SetFont(&font);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWorkTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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



void CWorkTimerDlg::OnPaint()
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


HCURSOR CWorkTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWorkTimerDlg::TimerFunction(CWorkTimerDlg *obj) {
	
	int timerSec = 0;
	while (obj->threadStarted) {
		try {
			std::this_thread::sleep_for(std::chrono::seconds(1));
				
			timerSec++;
			obj->ShowTimer(timerSec);
		}
		catch (std::exception& e) {

		}
	}
}

void CWorkTimerDlg::ShowTimer(int secund) {
	SetDlgItemInt(IDC_STATIC_TIMER, secund);
}



void CWorkTimerDlg::OnBnClickedButtonEnter()
{
	this->threadStarted = true;

	timerThread = std::thread(CWorkTimerDlg::TimerFunction,this);


	GetDlgItem(IDC_BUTTON_EXIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ENTER)->EnableWindow(FALSE);
}


void CWorkTimerDlg::OnBnClickedButtonExit()
{
	this->threadStarted = false;
	timerThread.detach();
	GetDlgItem(IDC_BUTTON_EXIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ENTER)->EnableWindow(TRUE);
}
