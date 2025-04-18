#pragma once
#include <adecc_Scholar/MFC/framework.h>
#include "resource.h"		// main symbols

class CAuswertungApp : public CWinApp
{
public:
	CAuswertungApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAuswertungApp theApp;
