
// CurrencyInspectionSystem.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCurrencyInspectionSystemApp:
// See CurrencyInspectionSystem.cpp for the implementation of this class
//

class CCurrencyInspectionSystemApp : public CWinApp
{
public:
	CCurrencyInspectionSystemApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCurrencyInspectionSystemApp theApp;