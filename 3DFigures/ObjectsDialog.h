#pragma once
#include "afxcmn.h"
#include <vector>
#include "common.h"
#include "afxwin.h"

// CObjectsDialog dialog

class CObjectsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectsDialog)
	std::vector<std::pair<unsigned, ObjType>> objs;
	void Restruct();

public:
	CObjectsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CObjectsDialog();

	void SetRange(std::vector<std::pair<unsigned, ObjType>> _objs) { objs = _objs; Restruct(); }
	CString delItem;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox selection;
	afx_msg void OnBnClickedButton1();
};
