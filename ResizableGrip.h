// ResizableGrip.h: interface for the CResizableGrip class.
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2001 by Paolo Messina
// (http://www.geocities.com/ppescher - ppescher@yahoo.com)
//
// The contents of this file are subject to the Artistic License (the "License").
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.opensource.org/licenses/artistic-license.html
//
// If you find this code useful, credits would be nice!
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define WS_EX_LAYOUT_RTL	0x00400000


class CRect
{
};



class CResizableControl
{
	// Members
protected:
	HWND m_hCtrl; // copy ptr to actual control
	RECT m_rect, m_parentrect; // initial window rect
	BOOL m_bAllowMoveX, m_bAllowMoveY, m_bAllowResizeX, m_bAllowResizeY;

	// Constructor
public:
	CResizableControl();

	// Methods
	void AllowMoveOnResize(BOOL bAllow=TRUE); // allow the pointed control to be moved in both directions when the parent is resized
	void AllowMoveXOnResize(); // allow the pointed control to be moved in the X direction when the parent is resized
	void AllowMoveYOnResize(); // allow the pointed control to be moved when the parent is resized
	void AllowResizeOnResize(BOOL bAllow=TRUE); // allow the pointed control to be resized in both directions when the parent is resized
	void AllowResizeXOnResize(); // allow the pointed control to be resized in the X direction when the parent is resized
	void AllowResizeYOnResize(); // allow the pointed control to be resized when the parent is resized

	void Init(HWND hCtrl);
	void MoveAndResize();
};




class CResizableGrip  
{

	// Members
protected:
	HWND m_hParent;
	SIZE m_sizeGrip; // holds grip size
	HWND m_wndGrip;	// grip control
	CPtrArray m_wndControls; // controls allowed to dynamically move and resize
	
	RECT m_initialrect;
	BOOL m_binitialrect;

	// Constructor
public:
	CResizableGrip();
	virtual ~CResizableGrip();


	// Methods
public:
	BOOL InitGrip(HWND hParent);
	void UpdateGripPos();
	void ShowSizeGrip(BOOL bShow = TRUE);	// show or hide the size grip

	HWND GetSafeHwnd();
	CResizableControl *AddDynamicControls();
	void RemoveDynamicControls(CResizableControl *p);
	void MoveAndResize();

	void SetInitialRect(RECT *rect) { m_initialrect = *rect; m_binitialrect = TRUE;}
	BOOL IsRectInitialized() { return m_binitialrect; }
	RECT GetFinalRect() { return m_initialrect; }



	// Helpers
protected:
	static BOOL IsRTL(HWND hwnd) {
		DWORD dwExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);
		return (dwExStyle & WS_EX_LAYOUT_RTL);
	}

	static LRESULT CALLBACK GripWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};


