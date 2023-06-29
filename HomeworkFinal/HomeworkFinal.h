
// HomeworkFinal.h : main header file for the HomeworkFinal application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHomeworkFinalApp:
// See HomeworkFinal.cpp for the implementation of this class
//

class CHomeworkFinalApp : public CWinApp
{
public:
	CHomeworkFinalApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHomeworkFinalApp theApp;
