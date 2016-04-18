// main.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "ResizableGrip.h"
#include "AboutDialog.h"
#include "SampleDialog.h"
#include "SampleAxDialog.h"
#include "WindowsMediaAxDialog.h"
#include "WebBrowserAxDialog.h"

CComModule _Module;


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwICC = ICC_LISTVIEW_CLASSES;
    InitCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
    BOOL bRet = InitCommonControlsEx(&InitCtrls);


    _Module.Init(NULL, hInstance, &LIBID_ATLLib);

	// CAboutDialog dlg; // about box
	// CSampleDialog dlg; // resizable dialog
	// CSampleAxDialog dlg; // sample dialog
	// CWindowsMediaAxDialog dlg; // windows media player
	CWebBrowserAxDialog dlg; // web browser
	dlg.DoModal();



 	// TODO: Place code here.

    _Module.Term();

	return 0;
}



