
// EyeCare.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CEyeCareApp:
// See EyeCare.cpp for the implementation of this class
//

class CEyeCareApp : public CWinApp
{
public:
	CEyeCareApp();

// Overrides
public:
	virtual BOOL InitInstance();

	BOOL ExitInstance() override;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CEyeCareApp theApp;
