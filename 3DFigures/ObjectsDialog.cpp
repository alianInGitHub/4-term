// ObjectsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "3DFigures.h"
#include "ObjectsDialog.h"
#include "afxdialogex.h"


// CObjectsDialog dialog

IMPLEMENT_DYNAMIC(CObjectsDialog, CDialogEx)

CObjectsDialog::CObjectsDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBJECT_DIALOG, pParent)
{

}

CObjectsDialog::~CObjectsDialog()
{
}

void CObjectsDialog::Restruct()
{
	selection.ResetContent();
	CString s;
	for (auto i : objs)
	{
		switch (i.second)
		{
		case PIRAMID:
		{
			s.Format(_T("%d"), i.first);
			CString t;
			if (i.first < 10)
				t.Format(_T("%d"), 0);
			s.Insert(0, t);
			t = "Piramid.";
			s.Insert(0, t);
			selection.AddString(s);
			break;
		}
		case SPHERE:
		{
			s.Format(_T("%d"), i.first);
			CString t;
			if (i.first < 10)
				t.Format(_T("%d"), 0);
			s.Insert(0, t);
			t = "Sphere.";
			s.Insert(0, t);
			selection.AddString(s);
			break;
		}
		case POS:
		{
			s = "Position";
			selection.AddString(s);
		}
		default:
			break;
		}
	}
}

void CObjectsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, selection);
}

BOOL CObjectsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	//Restruct();
	return 0;
}


BEGIN_MESSAGE_MAP(CObjectsDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectsDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CObjectsDialog message handlers




void CObjectsDialog::OnBnClickedButton1()
{
	selection.GetWindowTextW(delItem);
}
