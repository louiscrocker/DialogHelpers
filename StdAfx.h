// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <atlbase.h>
extern CComModule _Module;
#include <atlwin.h>

#include <atlcom.h>
#include <atlhost.h>

#include <commctrl.h>

#include "Templates.h" // collections
#include "ResizableGrip.h"

#pragma warning( disable : 4192 ) 

// windows media player type-library 
#import "c:\winnt\system32\msdxm.ocx"

// web browser type libraries
#import "c:\winnt\system32\shdocvw.dll" // web browser control
#import "c:\winnt\system32\mshtml.tlb" // web browser dom


#define RX 1
#define RY 2
#define RXY RX | RY
#define MX 4
#define MY 8
#define MXY MX | MY

#define BEGIN_SIZINGRULES(grip, hParent) \
	grip.InitGrip( hParent ); \
	grip.ShowSizeGrip();

#define ADDRULE(grip, item, rule) \
	{ \
	HWND hObject##item = GetDlgItem( item ); \
	if ( hObject##item ) \
	{ \
		CResizableControl *pListDynamics = grip.AddDynamicControls(); \
		if (pListDynamics) \
		{ \
			pListDynamics->Init(hObject##item); \
			if ((rule)&RX) pListDynamics->AllowResizeXOnResize(); \
			if ((rule)&RY) pListDynamics->AllowResizeYOnResize(); \
			if ((rule)&MX) pListDynamics->AllowMoveXOnResize(); \
			if ((rule)&MY) pListDynamics->AllowMoveYOnResize(); \
		} \
	} \
	}


#define END_SIZINGRULES

#define DORESIZE(grip) \
	if (grip.GetSafeHwnd()) \
	{ \
		grip.UpdateGripPos(); \
		grip.MoveAndResize(); \
	}

#define MINMAX(x,y) \
    LPRECT pRect = (LPRECT) lParam; \
	\
    int nWidth = pRect->right - pRect->left; \
    if (nWidth<x) pRect->right = pRect->left + x; \
	\
    int nHeight = pRect->bottom - pRect->top; \
    if (nHeight<y) pRect->bottom = pRect->top + y;


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
