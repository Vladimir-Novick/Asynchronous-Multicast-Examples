
// WorkTimerDlg.h : header file
//

#pragma once

#include <thread> 
#include <mutex>


// CWorkTimerDlg dialog
class CWorkTimerDlg : public CDialogEx
{
// Construction
public:
	CWorkTimerDlg(CWnd* pParent = nullptr);	// standard constructor
	~CWorkTimerDlg();
	std::mutex _mutex;
	volatile   bool threadStarted;

	void ShowTimer(int sec);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORKTIMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	std::thread timerThread;
	
	static void CWorkTimerDlg::TimerFunction(CWorkTimerDlg *obj);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonExit();
};
