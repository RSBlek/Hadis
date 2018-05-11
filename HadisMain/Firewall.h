#pragma once
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>

class Firewall {
	static HRESULT WindowsFirewallAppIsEnabled(
		IN INetFwProfile* fwProfile,
		IN const wchar_t* fwProcessImageFileName,
		OUT BOOL* fwAppEnabled
	);
	static HRESULT WindowsFirewallAddApp(
		IN INetFwProfile* fwProfile,
		IN const wchar_t* fwProcessImageFileName,
		IN const wchar_t* fwName
	);
	static HRESULT WindowsFirewallInitialize(OUT INetFwProfile** fwProfile);
	static void WindowsFirewallCleanup(IN INetFwProfile* fwProfile);
	static HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);
public:
	static bool addFirewallApp(wchar_t* FileName, wchar_t* AppName);
	static bool isFirewallRule(wchar_t* Name, wchar_t* Path);

};
