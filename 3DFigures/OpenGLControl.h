#pragma once
#include "afxwin.h"
#include <GLEW\glew.h>
#include <_GL\GLU.H>
#include "Object.h"
#include "ObjectsDialog.h"
#include "EditDialog.h"

class COpenGLControl :
	public CWnd
{
public:
	COpenGLControl();
	virtual ~COpenGLControl();
	UINT_PTR timer;

private:
	CWnd *hWnd;
	HDC hdc;
	HGLRC hrc;
	int pixelFormat;
	CRect rect;
	CRect oldWindow;
	CRect orinalRect;

	CObjectsDialog *m_objDialog;
	CEditDialog *m_editDialog;

	//camera controls
	float m_fLastX, m_fLastY;
	glm::vec3 m_fPos;
	float m_fZoom;    // Zoom on model in camera view
	float m_fRotX;    // Rotation on model in camera view
	float m_fRotY;    // Rotation on model in camera view
	int WND_Width, WND_Height;

	glm::mat4 MVP;
	glm::mat4 Model;

	std::vector<Object> objects;
	int selectedItem;

	glm::vec3 placement;
	GLuint VAO;

	void CalculateCameraMatrices();
	void PositionControls();
	void ObjectControls(std::pair<unsigned, ObjType>);

public:
	void Create(CRect rect, CWnd *parent);
	void Initialize(void);
	void DrawScene(void);
	void addObject(ObjType type);
	void deleteObject(unsigned i) { objects.erase(objects.begin() + i); }
	std::vector<std::pair<unsigned, ObjType>> getRange();
	void setDialog(CObjectsDialog* & od, CEditDialog* &ed) { m_objDialog = od; m_editDialog = ed; }
	static std::pair<int, ObjType> GetInfoFromSTR(CString s);
	void onSave();
	void onOpen();



	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

