// WinDV.h : main header file for the WinDV application
//

#if !defined(AFX_WINDV_H__233DAD68_8B5D_4596_8330_07B05049E9F4__INCLUDED_)
#define AFX_WINDV_H__233DAD68_8B5D_4596_8330_07B05049E9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

void SelectFile(BOOL open, CWnd *ctrl);

/////////////////////////////////////////////////////////////////////////////
// CWinDVApp:
// See WinDV.cpp for the implementation of this class
//

class CWinDVApp : public CWinApp
{
public:
	CWinDVApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinDVApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinDVApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDV_H__233DAD68_8B5D_4596_8330_07B05049E9F4__INCLUDED_)
