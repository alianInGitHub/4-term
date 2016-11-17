// EditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "3DFigures.h"
#include "EditDialog.h"
#include "afxdialogex.h"


// CEditDialog dialog

//IMPLEMENT_DYNAMIC(CEditDialog, CDialogEx)

CEditDialog::CEditDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDIT_DIALOG, pParent)
{

}

CEditDialog::~CEditDialog()
{
}

void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, scaleSlider);
	DDX_Control(pDX, IDC_SLIDER3, yRotateSlider);
	DDX_Control(pDX, IDC_SLIDER4, zRotateSlider);
	DDX_Control(pDX, IDC_SLIDER2, xRotateSlider);
	DDX_Control(pDX, IDC_SLIDER5, xMoveSlider);
	DDX_Control(pDX, IDC_SLIDER6, yMoveSlider);
	DDX_Control(pDX, IDC_SLIDER7, zMoveSlider);
	DDX_Control(pDX, IDC_CHECK1, xoyProjection);
	DDX_Control(pDX, IDC_CHECK2, xozProjection);
	DDX_Control(pDX, IDC_CHECK3, yozProjection);
}

BOOL CEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	scaleSlider.SetRangeMin(1);
	scaleSlider.SetRangeMax(100);

	xRotateSlider.SetRangeMin(-180);
	xRotateSlider.SetRangeMax(180);
	yRotateSlider.SetRangeMin(-180);
	yRotateSlider.SetRangeMax(180);
	zRotateSlider.SetRangeMin(-180);
	zRotateSlider.SetRangeMax(180);

	xMoveSlider.SetRangeMin(-200);
	xMoveSlider.SetRangeMax(200);
	yMoveSlider.SetRangeMin(-200);
	yMoveSlider.SetRangeMax(200);
	zMoveSlider.SetRangeMin(-200);
	zMoveSlider.SetRangeMax(200);

	scaleSlider.SetPos(10);
	xRotateSlider.SetPos(0);
	yRotateSlider.SetPos(0);
	zRotateSlider.SetPos(0);
	xMoveSlider.SetPos(0);
	yMoveSlider.SetPos(0);
	zMoveSlider.SetPos(0);

	CString value;
	value.Format(_T("%d"), (int)(scaleSlider.GetPos() / 10));
	
	scaleEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT1));
	scaleEdit->SetWindowText(value);

	value.Format(_T("%d"), xRotateSlider.GetPos());
	xRotateEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT2));
	xRotateEdit->SetWindowTextW(value);

	value.Format(_T("%d"), yRotateSlider.GetPos());
	yRotateEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT3));
	yRotateEdit->SetWindowTextW(value);

	value.Format(_T("%d"), zRotateSlider.GetPos());
	zRotateEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT4));
	zRotateEdit->SetWindowTextW(value);

	value.Format(_T("%d"), xMoveSlider.GetPos());
	xMoveEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT5));
	xMoveEdit->SetWindowTextW(value);

	value.Format(_T("%d"), yMoveSlider.GetPos());
	yMoveEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT6));
	yMoveEdit->SetWindowTextW(value);

	value.Format(_T("%d"), zMoveSlider.GetPos());
	zMoveEdit = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT7));
	zMoveEdit->SetWindowTextW(value);
	return 0;
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CEditDialog::OnScaleSlider)
	ON_WM_CREATE()
	ON_WM_NCDESTROY()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT1, &CEditDialog::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CEditDialog::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CEditDialog::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CEditDialog::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CEditDialog::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CEditDialog::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CEditDialog::OnEnChangeEdit7)
END_MESSAGE_MAP()


// CEditDialog message handlers


void CEditDialog::OnScaleSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}


int CEditDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CEditDialog::OnNcDestroy()
{
	CDialogEx::OnNcDestroy();
	GetParent()->PostMessage(WM_CLOSE, 0, 0);
	delete this;

	delete scaleEdit;
}


void CEditDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString value;
	value.Format(_T("%d"), (int)(scaleSlider.GetPos() / 10));
	scaleEdit->SetWindowTextW(value);

	value.Format(_T("%d"), xRotateSlider.GetPos());
	xRotateEdit->SetWindowTextW(value);

	value.Format(_T("%d"), yRotateSlider.GetPos());
	yRotateEdit->SetWindowTextW(value);

	value.Format(_T("%d"), zRotateSlider.GetPos());
	zRotateEdit->SetWindowTextW(value);

	value.Format(_T("%d"), xMoveSlider.GetPos());
	xMoveEdit->SetWindowTextW(value);

	value.Format(_T("%d"), yMoveSlider.GetPos());
	yMoveEdit->SetWindowTextW(value);

	value.Format(_T("%d"), zMoveSlider.GetPos());
	zMoveEdit->SetWindowTextW(value);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CEditDialog::OnEnChangeEdit1()
{
	CString s;
	scaleEdit->GetWindowTextW(s);
	scaleSlider.SetPos(10 * _tstoi(s));
}


void CEditDialog::OnEnChangeEdit2()
{
	CString s;
	xRotateEdit->GetWindowTextW(s);
	xRotateSlider.SetPos(_tstoi(s));
}


void CEditDialog::OnEnChangeEdit3()
{
	CString s;
	yRotateEdit->GetWindowTextW(s);
	yRotateSlider.SetPos(_tstoi(s));
}


void CEditDialog::OnEnChangeEdit4()
{
	CString s;
	zRotateEdit->GetWindowTextW(s);
	zRotateSlider.SetPos(_tstoi(s));
}


void CEditDialog::OnEnChangeEdit5()
{
	CString s;
	xMoveEdit->GetWindowTextW(s);
	xMoveSlider.SetPos(_tstoi(s));
}


void CEditDialog::OnEnChangeEdit6()
{
	CString s;
	xMoveEdit->GetWindowTextW(s);
	xMoveSlider.SetPos(_tstoi(s));
}


void CEditDialog::OnEnChangeEdit7()
{
	CString s;
	xMoveEdit->GetWindowTextW(s);
	xMoveSlider.SetPos(_tstoi(s));
}
