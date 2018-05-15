#include "stdafx.h"
#include "Firewall.h"


HRESULT Firewall::WindowsFirewallInitialize(OUT INetFwProfile** fwProfile)
{
	HRESULT hr = S_OK;
	INetFwMgr* fwMgr = NULL;
	INetFwPolicy* fwPolicy = NULL;

	_ASSERT(fwProfile != NULL);

	*fwProfile = NULL;

	// Create an instance of the firewall settings manager.
	hr = CoCreateInstance(
		__uuidof(NetFwMgr),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwMgr),
		(void**)&fwMgr
	);
	if (FAILED(hr))
	{
		////printf("CoCreateInstance failed: 0x%08lx\n", hr);
		goto error;
	}

	// Retrieve the local firewall policy.
	hr = fwMgr->get_LocalPolicy(&fwPolicy);
	if (FAILED(hr))
	{
		////printf("get_LocalPolicy failed: 0x%08lx\n", hr);
		goto error;
	}

	// Retrieve the firewall profile currently in effect.
	hr = fwPolicy->get_CurrentProfile(fwProfile);
	if (FAILED(hr))
	{
		////printf("get_CurrentProfile failed: 0x%08lx\n", hr);
		goto error;
	}

error:

	// Release the local firewall policy.
	if (fwPolicy != NULL)
	{
		fwPolicy->Release();
	}

	// Release the firewall settings manager.
	if (fwMgr != NULL)
	{
		fwMgr->Release();
	}

	return hr;
}

HRESULT Firewall::WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2)
{
	HRESULT hr = S_OK;

	hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)ppNetFwPolicy2);

	if (FAILED(hr))
	{
		//w//printf(L"CoCreateInstance for INetFwPolicy2 failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

Cleanup:
	return hr;
}

void Firewall::WindowsFirewallCleanup(IN INetFwProfile* fwProfile)
{
	// Release the firewall profile.
	if (fwProfile != NULL)
	{
		fwProfile->Release();
	}
}

HRESULT Firewall::WindowsFirewallRemoveApp(
	IN INetFwProfile* fwProfile,
	IN const wchar_t* fwProcessImageFileName
)
{
	HRESULT hr = S_OK;
	BOOL fwAppEnabled;
	BSTR fwBstrName = NULL;
	BSTR fwBstrProcessImageFileName = NULL;
	INetFwAuthorizedApplications* fwApps = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwProcessImageFileName != NULL);

	// First check to see if the application is already authorized.
	hr = WindowsFirewallAppIsEnabled(
		fwProfile,
		fwProcessImageFileName,
		&fwAppEnabled
	);
	if (FAILED(hr))
	{
		////printf("WindowsFirewallAppIsEnabled failed: 0x%08lx\n", hr);
		goto error;
	}

	// Only add the application if it isn't already authorized.
	if (fwAppEnabled)
	{
		// Retrieve the authorized application collection.
		hr = fwProfile->get_AuthorizedApplications(&fwApps);
		if (FAILED(hr))
		{
			////printf("get_AuthorizedApplications failed: 0x%08lx\n", hr);
			goto error;
		}


		// Allocate a BSTR for the process image file name.
		fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
		if (fwBstrProcessImageFileName == NULL)
		{
			hr = E_OUTOFMEMORY;
			////printf("SysAllocString failed: 0x%08lx\n", hr);
			goto error;
		}

		// Add the application to the collection.
		hr = fwApps->Remove(fwBstrProcessImageFileName);
		if (FAILED(hr))
		{
			//printf("Remove failed: 0x%08lx\n", hr);
			goto error;
		}

		////printf("Authorized application %lS is now enabled in the firewall.\n",fwProcessImageFileName);
	}

error:

	// Free the BSTRs.
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	return hr;
}

HRESULT Firewall::WindowsFirewallAddApp(
	IN INetFwProfile* fwProfile,
	IN const wchar_t* fwProcessImageFileName,
	IN const wchar_t* fwName
)
{
	HRESULT hr = S_OK;
	BOOL fwAppEnabled;
	BSTR fwBstrName = NULL;
	BSTR fwBstrProcessImageFileName = NULL;
	INetFwAuthorizedApplication* fwApp = NULL;
	INetFwAuthorizedApplications* fwApps = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwProcessImageFileName != NULL);
	_ASSERT(fwName != NULL);

	// First check to see if the application is already authorized.
	hr = WindowsFirewallAppIsEnabled(
		fwProfile,
		fwProcessImageFileName,
		&fwAppEnabled
	);
	if (FAILED(hr))
	{
		////printf("WindowsFirewallAppIsEnabled failed: 0x%08lx\n", hr);
		goto error;
	}

	// Only add the application if it isn't already authorized.
	if (!fwAppEnabled)
	{
		// Retrieve the authorized application collection.
		hr = fwProfile->get_AuthorizedApplications(&fwApps);
		if (FAILED(hr))
		{
			////printf("get_AuthorizedApplications failed: 0x%08lx\n", hr);
			goto error;
		}

		// Create an instance of an authorized application.
		hr = CoCreateInstance(
			__uuidof(NetFwAuthorizedApplication),
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(INetFwAuthorizedApplication),
			(void**)&fwApp
		);
		if (FAILED(hr))
		{
			////printf("CoCreateInstance failed: 0x%08lx\n", hr);
			goto error;
		}

		// Allocate a BSTR for the process image file name.
		fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
		if (fwBstrProcessImageFileName == NULL)
		{
			hr = E_OUTOFMEMORY;
			////printf("SysAllocString failed: 0x%08lx\n", hr);
			goto error;
		}

		// Set the process image file name.
		hr = fwApp->put_ProcessImageFileName(fwBstrProcessImageFileName);
		if (FAILED(hr))
		{
			////printf("put_ProcessImageFileName failed: 0x%08lx\n", hr);
			goto error;
		}

		// Allocate a BSTR for the application friendly name.
		fwBstrName = SysAllocString(fwName);
		if (SysStringLen(fwBstrName) == 0)
		{
			hr = E_OUTOFMEMORY;
			//printf("SysAllocString failed: 0x%08lx\n", hr);
			goto error;
		}

		// Set the application friendly name.
		hr = fwApp->put_Name(fwBstrName);
		if (FAILED(hr))
		{
			//printf("put_Name failed: 0x%08lx\n", hr);
			goto error;
		}

		// Add the application to the collection.
		hr = fwApps->Add(fwApp);
		if (FAILED(hr))
		{
			//printf("Add failed: 0x%08lx\n", hr);
			goto error;
		}

		////printf("Authorized application %lS is now enabled in the firewall.\n",fwProcessImageFileName);
	}

error:

	// Free the BSTRs.
	SysFreeString(fwBstrName);
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application instance.
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	return hr;
}

HRESULT Firewall::WindowsFirewallAppIsEnabled(
	IN INetFwProfile* fwProfile,
	IN const wchar_t* fwProcessImageFileName,
	OUT BOOL* fwAppEnabled
)
{
	HRESULT hr = S_OK;
	BSTR fwBstrProcessImageFileName = NULL;
	VARIANT_BOOL fwEnabled;
	INetFwAuthorizedApplication* fwApp = NULL;
	INetFwAuthorizedApplications* fwApps = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwProcessImageFileName != NULL);
	_ASSERT(fwAppEnabled != NULL);

	*fwAppEnabled = FALSE;

	// Retrieve the authorized application collection.
	hr = fwProfile->get_AuthorizedApplications(&fwApps);
	if (FAILED(hr))
	{
		//printf("get_AuthorizedApplications failed: 0x%08lx\n", hr);
		goto error;
	}

	// Allocate a BSTR for the process image file name.
	fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
	if (fwBstrProcessImageFileName == NULL)
	{
		hr = E_OUTOFMEMORY;
		//printf("SysAllocString failed: 0x%08lx\n", hr);
		goto error;
	}

	// Attempt to retrieve the authorized application.
	hr = fwApps->Item(fwBstrProcessImageFileName, &fwApp);
	if (SUCCEEDED(hr))
	{
		// Find out if the authorized application is enabled.
		hr = fwApp->get_Enabled(&fwEnabled);
		if (FAILED(hr))
		{
			//printf("get_Enabled failed: 0x%08lx\n", hr);
			goto error;
		}

		if (fwEnabled != VARIANT_FALSE)
		{
			// The authorized application is enabled.
			*fwAppEnabled = TRUE;

			//printf("Authorized application %lS is enabled in the firewall.\n",fwProcessImageFileName);
		}
		else
		{
			//printf("Authorized application %lS is disabled in the firewall.\n",fwProcessImageFileName);
		}
	}
	else
	{
		// The authorized application was not in the collection.
		hr = S_OK;

		//printf("Authorized application %lS is disabled in the firewall.\n",fwProcessImageFileName);
	}

error:

	// Free the BSTR.
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application instance.
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	return hr;
}

bool Firewall::addFirewallApp(wchar_t* FileName, wchar_t* AppName) {

	HRESULT hr = S_OK;
	INetFwProfile* fwProfile = NULL;
	HRESULT comInit = E_FAIL;

	comInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
	);
	if (comInit != RPC_E_CHANGED_MODE)
	{
		hr = comInit;
		if (FAILED(hr)) return false;
	}

	hr = WindowsFirewallInitialize(&fwProfile);
	if (FAILED(hr)) return false;

	hr = WindowsFirewallAddApp(
		fwProfile,
		FileName,
		AppName
	);
	if (FAILED(hr)) return false;
	return true;
}

bool Firewall::removeFirewallApp(wchar_t* FileName) {

	HRESULT hr = S_OK;
	INetFwProfile* fwProfile = NULL;
	HRESULT comInit = E_FAIL;

	comInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
	);
	if (comInit != RPC_E_CHANGED_MODE)
	{
		hr = comInit;
		if (FAILED(hr)) return false;
	}

	hr = WindowsFirewallInitialize(&fwProfile);
	if (FAILED(hr)) return false;

	hr = WindowsFirewallRemoveApp(
		fwProfile,
		FileName
	);
	if (FAILED(hr)) return false;
	return true;
}

bool Firewall::isFirewallRule(wchar_t* Name, wchar_t* Path) {
	HRESULT hrComInit = S_OK;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	INetFwRules *pFwRules = NULL;
	INetFwRule *pFwRule = NULL;
	HRESULT hr = S_OK;
	IEnumVARIANT* pVariant = NULL;
	IUnknown *pEnumerator;
	CComVariant var;
	ULONG cFetched = 0;
	bool ret = false;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
	);
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			//wprintf(L"CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	hr = WFCOMInitialize(&pNetFwPolicy2);

	long fwRuleCount;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
	);

	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			//wprintf(L"CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		//wprintf(L"get_Rules failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Obtain the number of Firewall rules
	hr = pFwRules->get_Count(&fwRuleCount);
	if (FAILED(hr))
	{
		//wprintf(L"get_Count failed: 0x%08lx\n", hr);
		goto Cleanup;

	}

	//wprintf(L"The number of rules in the Windows Firewall are %d\n", fwRuleCount);


	pFwRules->get__NewEnum(&pEnumerator);

	if (pEnumerator)
	{
		hr = pEnumerator->QueryInterface(__uuidof(IEnumVARIANT), (void **)&pVariant);
		goto Cleanup;
	}

	while (SUCCEEDED(hr) && hr != S_FALSE)
	{
		var.Clear();
		hr = pVariant->Next(1, &var, &cFetched);

		if (S_FALSE != hr)
		{
			if (SUCCEEDED(hr))
			{
				hr = var.ChangeType(VT_DISPATCH);
			}
			if (SUCCEEDED(hr))
			{
				hr = (V_DISPATCH(&var))->QueryInterface(__uuidof(INetFwRule), reinterpret_cast<void**>(&pFwRule));
			}

			if (SUCCEEDED(hr))
			{
				BSTR bstrVal;
				pFwRule->get_Name(&bstrVal);
				wchar_t* RuleName = bstrVal;
				pFwRule->get_ApplicationName(&bstrVal);
				wchar_t* RulePath = bstrVal;
				if (wcscmp(RuleName, Name) == 0) {
					if (wcscmp(RulePath, Path) == 0) {
						if (pFwRule != NULL) pFwRule->Release();
						if (pNetFwPolicy2 != NULL) pNetFwPolicy2->Release();
						if (SUCCEEDED(hrComInit)) CoUninitialize();
						return true;
					}
				}
				// Output the properties of this rule
				//DumpFWRulesInCollection(pFwRule);
			}
		}
	}
	if (pFwRule != NULL) pFwRule->Release();
	if (pNetFwPolicy2 != NULL) pNetFwPolicy2->Release();
	if (SUCCEEDED(hrComInit)) CoUninitialize();
	return false;
	//hr = WFCOMInitialize(&pNetFwPolicy2);
Cleanup:

	// Release pFwRule
	if (pFwRule != NULL)
	{
		pFwRule->Release();
	}

	// Release INetFwPolicy2
	if (pNetFwPolicy2 != NULL)
	{
		pNetFwPolicy2->Release();
	}

	// Uninitialize COM.
	if (SUCCEEDED(hrComInit))
	{
		CoUninitialize();
	}

	return false;
}