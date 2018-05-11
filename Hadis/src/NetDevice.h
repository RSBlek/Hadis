#pragma once

using namespace System;
using namespace std;

public ref class NetDevice {
public:
	String^ name;
	String^ id;
	int ip;
	static System::Collections::Generic::List<NetDevice^>^ getDevices();
	NetDevice(String^ i, String^ n, int ipint) {
		name = n;
		id = i;
		ip = ipint;
	}
	virtual System::String^ ToString() override
	{
		return name;
	}
};
