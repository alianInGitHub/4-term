#include "stdafx.h"
#include "OpenGLControl.h"
#include <glm\gtc\matrix_transform.hpp>
#include <string>
#include "loader.h"


COpenGLControl::COpenGLControl()
{
	m_fPos.x = 3.0f;
	m_fPos.y = 4.0f;
	m_fPos.z = 2.0f;
	m_fZoom = 45.0f;
	m_fRotX = 1.0f;
	m_fRotY = 1.0f;
	Model = glm::mat4(1.0f);

	placement.x = placement.y = placement.z = 0.0;
}


COpenGLControl::~COpenGLControl()
{
}

void COpenGLControl::Create(CRect rect, CWnd * parent)
{
	LPCTSTR className = AfxRegisterWndClass(CS_HREDRAW |
		CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, (LPCTSTR)"OpenGL", WS_CHILD | WS_VISIBLE |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	oldWindow = rect;
	orinalRect = rect;
	hWnd = parent;
}

void COpenGLControl::Initialize(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16, //z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;

	// Pixel format.
	pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Set color to use when clearing the background.
	glClearColor(0.1333f, 0.1255f, 0.1255f, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glewExperimental = GL_TRUE;
	glewInit();

	glRotatef(90, 1.0, 0.0, 0.0);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	addObject(SPHERE);

	OnDraw(NULL);
}

void COpenGLControl::DrawScene(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex3f(placement.x, placement.y, placement.z);
	glEnd();
	if (selectedItem != -1)
	{
		if (m_editDialog->xoyProjection.GetCheck() == BST_CHECKED)
		{
			objects[selectedItem].RenderProjection(MVP, XOY);
		}
		if (m_editDialog->xozProjection.GetCheck() == BST_CHECKED)
		{
			objects[selectedItem].RenderProjection(MVP, XOZ);
		}
		if (m_editDialog->yozProjection.GetCheck() == BST_CHECKED)
		{
			objects[selectedItem].RenderProjection(MVP, YOZ);
		}
	}
	glBegin(GL_LINES);
	for (int i = -5; i < 6; i++)
	{
		if (i == 0)
			glColor3d(1.0, 0.0, 0.0);
		else
			glColor3d(0.6549, 0.5961, 0.5451);
		glVertex3d(-5, 0, i);
		glVertex3d(5, 0, i);
	}

	for (int i = -5; i < 6; i++)
	{
		if (i == 0)
			glColor3d(0.0, 1.0, 0.0);
		else
			glColor3d(0.6549, 0.5961, 0.5451);
		glVertex3d(i, 0, -5);
		glVertex3d(i, 0, 5);
	}
	glEnd();
	
	for (auto i : objects)
	{
		i.Render(MVP);
	}
	
}

void COpenGLControl::addObject(ObjType type)
{
	Object newObj(type, placement);
	objects.push_back(newObj);
}



void COpenGLControl::CalculateCameraMatrices()
{
	glm::vec3 position(m_fPos);
	glm::vec3 direction(0.0, 0.0, 0.0);
	glm::vec3 up(0, 1, 0);
	glm::mat4 Rotation = glm::mat4(1.0f);
	Rotation[0][0] = m_fRotX;
	Rotation[1][1] = m_fRotY;
	glm::vec4 temp = Rotation * glm::vec4(position, 1);
	position.x = temp.x;
	position.y = temp.y;
	position.z = temp.z;
	glm::mat4 Projection = glm::perspective((float)m_fZoom, (float)(WND_Width) / (float)WND_Height, 0.01f, 2000.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		position,           // Camera is here
		direction,			// and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model;
}
void COpenGLControl::PositionControls()
{
	CString s;
	m_editDialog->xMoveEdit->GetWindowTextW(s);
	placement.x = _tstof(s);
	int i = _tstof(s);
	m_editDialog->yMoveEdit->GetWindowTextW(s);
	placement.y = _tstof(s);
	m_editDialog->zMoveEdit->GetWindowTextW(s);
	placement.z = _tstof(s);
}
void COpenGLControl::ObjectControls(std::pair<unsigned, ObjType> obj)
{
	unsigned i = 0;
	switch (obj.second)
	{
	case SPHERE:
	{
		unsigned count = -1;
		do
		{
			while (objects[i].type != SPHERE)
				i++;
			count++;
		} while (count != obj.first);
		break;
	}
	case PIRAMID:
	{
		unsigned count = -1;
		do
		{
			while (objects[i].type != PIRAMID)
				i++;
			count++;
		} while (count != obj.first);
		break;
	}
	default:
		break;
	}
	selectedItem = i;
	glm::vec3 vect;
	CString s;
	m_editDialog->xRotateEdit->GetWindowTextW(s);
	vect.x = _tstof(s);
	m_editDialog->yRotateEdit->GetWindowTextW(s);
	vect.y = _tstof(s);
	m_editDialog->zRotateEdit->GetWindowTextW(s);
	vect.z = _tstof(s);
	objects[i].SetRotation(vect);

	m_editDialog->xMoveEdit->GetWindowTextW(s);
	vect.x = _tstof(s);
	m_editDialog->yMoveEdit->GetWindowTextW(s);
	vect.y = _tstof(s);
	m_editDialog->zMoveEdit->GetWindowTextW(s);
	vect.z = _tstof(s);
	objects[i].SetPlacement(vect);

	m_editDialog->scaleEdit->GetWindowTextW(s);
	objects[i].SetScaling(_tstof(s));
}
std::vector<std::pair<unsigned, ObjType>> COpenGLControl::getRange()
{
	std::vector<std::pair<unsigned, ObjType>>objs;
	std::pair<unsigned, ObjType> temp;
	temp.first = 0;
	temp.second = POS;
	objs.push_back(temp);
	unsigned pcount = 0, scount = 0;
	for (auto i : objects)
	{
		switch (i.type)
		{
		case PIRAMID:
		{
			temp.first = pcount;
			pcount++;
			temp.second = PIRAMID;
			objs.push_back(temp);
			break;
		}
		case SPHERE:
		{
			temp.first = scount;
			scount++;
			temp.second = SPHERE;
			objs.push_back(temp);
			break;
		}
		default:
			break;
		}
	}
	return objs;
}
BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


void COpenGLControl::OnPaint()
{
	ValidateRect(NULL);
}


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	Initialize();

	return 0;
}

void COpenGLControl::OnDraw(CDC * pDC)
{
	glLoadIdentity();
}


std::pair<int, ObjType> COpenGLControl::GetInfoFromSTR(CString s)
{
	std::pair<int, ObjType> res;
	if (s.IsEmpty())
	{
		res.first = -1;
		return res;
	}
	if (s[0] == 'P')
	{
		if (s[1] == 'o')
			res.second = POS;
		else
			res.second = PIRAMID;
	}
	else
		res.second = SPHERE;
	if (res.second != POS)
	{
		int num = s[s.GetLength() - 1] - '0';
		if (s[s.GetLength() - 2] != '0')
			num += (s[s.GetLength() - 2] - '0') * 10;
		res.first = num;
	}
	res.first = 0;
	return res;
}

void COpenGLControl::onSave()
{
	if (objects.size() == 0)
		return;
	std::string s;
	for (Object i : objects)
	{
		std::string sql = "INSERT INTO objects (Type, PosX, PosY, PosZ, RotX, RotY, RotZ, Scale) VALUES ('"
			+ std::to_string(i.type) + "', '"
			+ std::to_string(i.GetPosition().x) + "', '"
			+ std::to_string(i.GetPosition().y) + "', '"
			+ std::to_string(i.GetPosition().z) + "', '"
			+ std::to_string(i.GetRotation().x) + "', '"
			+ std::to_string(i.GetRotation().y) + "', '"
			+ std::to_string(i.GetRotation().z) + "', '"
			+ std::to_string(i.GetScaling()) + "');";
		mysql(sql.c_str(), false, 9);
	}
}

void COpenGLControl::onOpen()
{
	std::vector<std::vector<std::string>> records = mysql("SELECT * FROM objects;", true, 9);

	objects.clear();

	float temp[9];
	for (int j = 0; j < records.size(); j++)
	{
		for (int i = 0; i < 9; i++) {
			temp[i] = stof(records[j][i], 0);
		}
		ObjType type;
		if ((int)temp[1] == SPHERE)
			type = SPHERE;
		else
		{
			if ((int)temp[1] == PIRAMID)
				type = PIRAMID;
			else
			{
				type = POS;
			}
		}
		addObject(type); 
		glm::vec3 v1(temp[2], temp[3], temp[4]);
		objects.back().SetPlacement(v1);
		glm::vec3 v2(temp[5], temp[6], temp[7]);
		objects.back().SetRotation(v2);
		objects.back().SetScaling(temp[8]);
	}
}


void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		CString s;
		m_objDialog->selection.GetWindowTextW(s);
		std::pair<int, ObjType> obj = GetInfoFromSTR(s);
		selectedItem = -1;
		if (obj.first > -1)
		{
			switch (obj.second)
			{
			case POS:
			{
				PositionControls();
				break;
			}
			case PIRAMID:
				ObjectControls(obj);
				break;
			case SPHERE:
				ObjectControls(obj);
				break;
			default:
				break;
			}
		}
		s = m_objDialog->delItem;
		obj = GetInfoFromSTR(s);
		if ((obj.first != -1) && (obj.second != POS))
		{
			deleteObject(obj.first);
			m_objDialog->delItem = "";
			m_objDialog->SetRange(getRange());
			selectedItem = -1;
		}
		
		// Clear color and depth buffer bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Draw OpenGL scene
		DrawScene();

		// Swap buffers
		SwapBuffers(hdc);
		break;
	}
	default:
		break;
	}
	CWnd::OnTimer(nIDEvent);
}


void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
		return;

	// map the opengl coords
	glViewport(0, 0, cx, cy);
	WND_Width = cx;
	WND_Height = cy;
	CalculateCameraMatrices();
	// Model view
	glMatrixMode(GL_MODELVIEW); 
}


void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX = (float)point.x;
	m_fLastY = (float)point.y;

	// Left mouse button
	if (nFlags & MK_LBUTTON)
	{
		m_fRotX += (float)0.05f * diffY;

		if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
		{
			m_fRotX = 0.0f;
		}

		m_fRotY += (float)0.05f * diffX;

		if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
		{
			m_fRotY = 0.0f;
		}
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
		m_fZoom -= (float)0.01f * diffY;
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
		m_fPos.x += (float)0.05f * diffX;
		m_fPos.z -= (float)0.05f * diffY;
	}

	CalculateCameraMatrices();

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}


void COpenGLControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar & VK_NUMPAD1)
	{
		m_fPos.x = 0.0;
		m_fPos.y = 0.0;
		m_fPos.z = 3.0;
		CalculateCameraMatrices();
	}
	else
		if (nChar & VK_NUMPAD2)
		{
			m_fPos.x = 3.0;
			m_fPos.y = 0.0;
			m_fPos.z = 0.0;
			CalculateCameraMatrices();
		}
		else
			if (nChar & VK_NUMPAD3)
			{
				m_fPos.x = 0.0;
				m_fPos.y = 3.0;
				m_fPos.z = 0.0;
				CalculateCameraMatrices();
			}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}



