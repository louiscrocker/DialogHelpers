
#pragma once



// CWebBrowserAxDialog : windows media player hosted dialog
//

class CWebBrowserAxDialog; // forward declaration


class DWebBrowserEventsImpl : public DWebBrowserEvents
{

	// IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID* ppv);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

	// IDispatch methods
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo);
	STDMETHOD(GetTypeInfo)(UINT iTInfo,
            LCID lcid,
            ITypeInfo** ppTInfo);
	STDMETHOD(GetIDsOfNames)(REFIID riid,
            LPOLESTR* rgszNames,
            UINT cNames,
            LCID lcid,
            DISPID* rgDispId);
	STDMETHOD(Invoke)(DISPID dispIdMember,
            REFIID riid,
            LCID lcid,
            WORD wFlags,
            DISPPARAMS __RPC_FAR *pDispParams,
            VARIANT __RPC_FAR *pVarResult,
            EXCEPINFO __RPC_FAR *pExcepInfo,
            UINT __RPC_FAR *puArgErr);

    // Methods:
    HRESULT BeforeNavigate (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Cancel );

    HRESULT NavigateComplete ( _bstr_t URL );
    HRESULT StatusTextChange ( _bstr_t Text );
    HRESULT ProgressChange (
        long Progress,
        long ProgressMax );
    HRESULT DownloadComplete();
    HRESULT CommandStateChange (
        long Command,
        VARIANT_BOOL Enable );
    HRESULT DownloadBegin ();
    HRESULT NewWindow (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Processed );
    HRESULT TitleChange ( _bstr_t Text );
    HRESULT FrameBeforeNavigate (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Cancel );
    HRESULT FrameNavigateComplete (
        _bstr_t URL );
    HRESULT FrameNewWindow (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Processed );
    HRESULT Quit (
        VARIANT_BOOL * Cancel );
    HRESULT WindowMove ( );
    HRESULT WindowResize ( );
    HRESULT WindowActivate ( );
    HRESULT PropertyChange (
        _bstr_t Property );


	// members
	CWebBrowserAxDialog *m_cpParent; // any time a IWebBrowser instance is needed

public:
	void SetParent(CWebBrowserAxDialog *pParent) { m_cpParent = pParent; }

};

class CWebBrowserAxDialog : public CAxDialogImpl<CWebBrowserAxDialog>
{
protected:
	HICON			m_hIcon;
	CResizableGrip	m_grip;
	DWebBrowserEventsImpl m_events;

public:
    enum { IDD = IDD_WEBBROWSERAXDIALOG };

    BEGIN_MSG_MAP(CWebBrowserAxDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_SIZING, OnSizing)
        COMMAND_ID_HANDLER(IDC_NAVIGATE, OnNavigate)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CenterWindow();

		m_hIcon = ::LoadIcon(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDI_APPICON));
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon


		BEGIN_SIZINGRULES(m_grip, m_hWnd)
			ADDRULE(m_grip, IDC_EXPLORER1, RXY)
			ADDRULE(m_grip, IDC_EDITURL, RX)
			ADDRULE(m_grip, IDC_NAVIGATE, MX)
		END_SIZINGRULES


		// Web browser specific code
	
		m_events.SetParent(this);

		SHDocVw::IWebBrowserAppPtr pWebBrowser = NULL;
		HRESULT hr = GetDlgControl(IDC_EXPLORER1, __uuidof(SHDocVw::IWebBrowserAppPtr), (void**)&pWebBrowser);

		// subscribe for the web browse event source
		LPCONNECTIONPOINTCONTAINER pCPC = NULL;
		LPCONNECTIONPOINT pCP = NULL;
		pWebBrowser->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pCPC);
		pCPC->FindConnectionPoint(__uuidof(SHDocVw::DWebBrowserEventsPtr), &pCP);
		DWORD dwCookie;
		pCP->Advise((LPUNKNOWN)&m_events, &dwCookie);


		pWebBrowser->Navigate( _bstr_t("http://www.codeproject.com") );




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



    LRESULT OnNavigate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {

		// Web browser specific code
		SHDocVw::IWebBrowserAppPtr pWebBrowser = NULL;
		HRESULT hr = GetDlgControl(IDC_EXPLORER1, __uuidof(SHDocVw::IWebBrowserAppPtr), (void**)&pWebBrowser);

		TCHAR szUrl[2048]="";
		::GetWindowText(GetDlgItem(IDC_EDITURL), szUrl, 2048);

		pWebBrowser->Navigate( _bstr_t(szUrl) );

        return 0;
    }


};