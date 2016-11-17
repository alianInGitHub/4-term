#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEditDialog dialog

class CEditDialog : public CDialogEx
{
	//DECLARE_DYNAMIC(CEditDialog)

public:
	CEditDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnScaleSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	CEdit* scaleEdit;
	CSliderCtrl scaleSlider;

	CEdit* xRotateEdit;
	CEdit* yRotateEdit;
	CEdit* zRotateEdit;
	CSliderCtrl xRotateSlider;
	CSliderCtrl yRotateSlider;
	CSliderCtrl zRotateSlider;

	CEdit* xMoveEdit;
	CEdit* yMoveEdit;
	CEdit* zMoveEdit;
	CSliderCtrl xMoveSlider;
	CSliderCtrl yMoveSlider;
	CSliderCtrl zMoveSlider;

	CButton xoyProjection;
	CButton xozProjection;
	CButton yozProjection;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
};
