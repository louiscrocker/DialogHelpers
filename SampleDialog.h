
#pragma once

// CSampleDialog : sample resizable dialog implementation
//

class CSampleDialog : public CDialogImpl<CSampleDialog>
{
protected:
	HICON			m_hIcon;
	CResizableGrip	m_grip;

public:
    enum { IDD = IDD_SAMPLEDIALOG };

    BEGIN_MSG_MAP(CSampleDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_SIZING, OnSizing)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CenterWindow();

		m_hIcon = ::LoadIcon(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDI_APPICON));
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon

		BEGIN_SIZINGRULES(m_grip, m_hWnd)
			ADDRULE(m_grip, IDC_TREE1, RXY)
			ADDRULE(m_grip, IDOK, MX)
			ADDRULE(m_grip, IDCANCEL, MX)
		END_SIZINGRULES

        return TRUE;    // let the system set the focus
    }

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        EndDialog(IDCANCEL);
        return 0;
    }

	// called by framework while resizing
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
		DORESIZE(m_grip)
	    return 0;
    }

	// called by framework while resizing, to allow min max bound adjustement
	LRESULT OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		MINMAX(150,150)
		return 0;
	}



    LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        EndDialog(IDOK);
        return 0;
    }

    LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        EndDialog(IDCANCEL);
        return 0;
    }

};