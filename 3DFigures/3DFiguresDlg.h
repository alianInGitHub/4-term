
// 3DFiguresDlg.h : header file
//

#pragma once
#include "afxdialogex.h"
#include "OpenGLControl.h"
#include "EditDialog.h"
#include "ObjectsDialog.h"


// CMy3DFiguresDlg dialog
class CMy3DFiguresDlg : public CDialogEx
{
// Construction
	COpenGLControl m_oglWindow;
	CEditDialog* m_editDlg;
	CObjectsDialog* m_objDlg;
	UINT_PTR timer;
public:
	CMy3DFiguresDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY3DFIGURES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddSphere();
	afx_msg void OnAddPiramid();
	afx_msg void OnFileQuit();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};
