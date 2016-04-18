
#include "stdafx.h"
#include "resource.h"
#include "ResizableGrip.h"
#include "WebBrowserAxDialog.h"
#include "Exdispid.h" // platform SDK header


	// IUnknown methods
HRESULT __stdcall DWebBrowserEventsImpl::QueryInterface(REFIID riid, LPVOID* ppv)
{
	*ppv = NULL;

	if (IID_IUnknown == riid || __uuidof(SHDocVw::DWebBrowserEventsPtr) == riid)
	{
		*ppv = (LPUNKNOWN)(SHDocVw::DWebBrowserEventsPtr*)this;
		AddRef();
		return NOERROR;
	}
	else if (IID_IOleClientSite == riid)
	{
		*ppv = (IOleClientSite*)this;
		AddRef();
		return NOERROR;
	}
	else if (IID_IDispatch == riid)
	{
		*ppv = (IDispatch*)this;
		AddRef();
		return NOERROR;
	}
	else
	{
		return E_NOTIMPL;
	}
}

ULONG __stdcall DWebBrowserEventsImpl::AddRef() { return 1;}
ULONG __stdcall DWebBrowserEventsImpl::Release() { return 0;}

// IDispatch methods
HRESULT __stdcall DWebBrowserEventsImpl::GetTypeInfoCount(UINT* pctinfo)
{ 
	return E_NOTIMPL; 
}

HRESULT __stdcall DWebBrowserEventsImpl::GetTypeInfo(UINT iTInfo,
            LCID lcid,
            ITypeInfo** ppTInfo)
{ 
	return E_NOTIMPL; 
}

HRESULT __stdcall DWebBrowserEventsImpl::GetIDsOfNames(REFIID riid,
            LPOLESTR* rgszNames,
            UINT cNames,
            LCID lcid,
            DISPID* rgDispId)
{ 
	return E_NOTIMPL; 
}
        
HRESULT __stdcall DWebBrowserEventsImpl::Invoke(DISPID dispIdMember,
            REFIID riid,
            LCID lcid,
            WORD wFlags,
            DISPPARAMS __RPC_FAR *pDispParams,
            VARIANT __RPC_FAR *pVarResult,
            EXCEPINFO __RPC_FAR *pExcepInfo,
            UINT __RPC_FAR *puArgErr)
{ 
	// proces OnBeforeNavigate
	if (dispIdMember == DISPID_BEFORENAVIGATE)
	{
		BeforeNavigate( _bstr_t( pDispParams->rgvarg[5].bstrVal ),
						0,
						_bstr_t( pDispParams->rgvarg[3].bstrVal ),
						NULL,
						_bstr_t(""),
						NULL);
		
	}
	else if (dispIdMember == DISPID_NAVIGATECOMPLETE)
	{
		NavigateComplete( _bstr_t( pDispParams->rgvarg[0].bstrVal ) );
	}

	return NOERROR;
}


// Methods:
HRESULT DWebBrowserEventsImpl::BeforeNavigate (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Cancel )
	{
		::MessageBox(NULL,(char*)URL,"BeforeNavigate message box",MB_OK);
		return S_OK;
	}

    HRESULT DWebBrowserEventsImpl::NavigateComplete ( _bstr_t URL ) 
	{ 
/* example code
		SHDocVw::IWebBrowserAppPtr pWebBrowser = NULL;
		HRESULT hr = m_cpParent->GetDlgControl(IDC_EXPLORER1, 
						__uuidof(SHDocVw::IWebBrowserAppPtr), 
						(void**)&pWebBrowser);

		// get the html document
		MSHTML::IHTMLDocument2Ptr doc( pWebBrowser->Document );
		MSHTML::IHTMLElementPtr htmlbody( doc->body );

		BSTR content = NULL;
		htmlbody->get_innerHTML(&content);
		_bstr_t bcontent(content);
*/
		return S_OK; 
	}
    HRESULT DWebBrowserEventsImpl::StatusTextChange ( _bstr_t Text ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::ProgressChange (
        long Progress,
        long ProgressMax )  { return S_OK; }
    HRESULT DWebBrowserEventsImpl::DownloadComplete()  { return S_OK; }
    HRESULT DWebBrowserEventsImpl::CommandStateChange (
        long Command,
        VARIANT_BOOL Enable ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::DownloadBegin () { return S_OK; }
    HRESULT DWebBrowserEventsImpl::NewWindow (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Processed ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::TitleChange ( _bstr_t Text ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::FrameBeforeNavigate (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Cancel ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::FrameNavigateComplete (
        _bstr_t URL ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::FrameNewWindow (
        _bstr_t URL,
        long Flags,
        _bstr_t TargetFrameName,
        VARIANT * PostData,
        _bstr_t Headers,
        VARIANT_BOOL * Processed ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::Quit (
        VARIANT_BOOL * Cancel ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::WindowMove ( ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::WindowResize ( ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::WindowActivate ( ) { return S_OK; }
    HRESULT DWebBrowserEventsImpl::PropertyChange (
        _bstr_t Property ) { return S_OK; }

