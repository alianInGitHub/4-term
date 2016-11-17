
// 3DFigures.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy3DFiguresApp:
// See 3DFigures.cpp for the implementation of this class
//

class CMy3DFiguresApp : public CWinApp
{
public:
	CMy3DFiguresApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy3DFiguresApp theApp;