
#pragma once



// CSampleAxDialog : sample resizable dialog implementation
//

class CSampleAxDialog : public CAxDialogImpl<CSampleAxDialog>
{
protected:
	HICON			m_hIcon;
	CResizableGrip	m_grip;

public:
    enum { IDD = IDD_SAMPLEACTIVEXDIALOG };

    BEGIN_MSG_MAP(CSampleAxDialog)
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

		m_grip.InitGrip( m_hWnd );
		m_grip.ShowSizeGrip();

		HWND hMediaPlayer = GetDlgItem(IDC_MEDIAPLAYER1);
		{
			CResizableControl *pListDynamics = m_grip.AddDynamicControls();
			if (pListDynamics)
			{
				pListDynamics->Init(hMediaPlayer);
				pListDynamics->AllowResizeOnResize();
			}
		}

		HWND hOk = GetDlgItem(IDOK);
		{
			CResizableControl *pListDynamics = m_grip.AddDynamicControls();
			if (pListDynamics)
			{
				pListDynamics->Init(hOk);
				pListDynamics->AllowMoveXOnResize();
			}
		}

		HWND hCancel = GetDlgItem(IDCANCEL);
		{
			CResizableControl *pListDynamics = m_grip.AddDynamicControls();
			if (pListDynamics)
			{
				pListDynamics->Init(hCancel);
				pListDynamics->AllowMoveXOnResize();
			}
		}

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