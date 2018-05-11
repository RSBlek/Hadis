#include "stdafx.h"
#include "NetDevice.h"



System::Collections::Generic::List<NetDevice^>^ NetDevice::getDevices() {
	System::Collections::Generic::List<NetDevice^>^ devices = gcnew System::Collections::Generic::List<NetDevice^>();
	cli::array <System::Net::NetworkInformation::NetworkInterface^>^ interfaces = System::Net::NetworkInformation::NetworkInterface::GetAllNetworkInterfaces();
	for each (System::Net::NetworkInformation::NetworkInterface^ adapter in interfaces)
	{
		if (adapter->NetworkInterfaceType != System::Net::NetworkInformation::NetworkInterfaceType::Ethernet && adapter->NetworkInterfaceType != System::Net::NetworkInformation::NetworkInterfaceType::Wireless80211) continue;
		int ipint;
		System::Net::NetworkInformation::IPInterfaceProperties^ ipProps = adapter->GetIPProperties();

		for each(System::Net::NetworkInformation::UnicastIPAddressInformation^ ip in ipProps->UnicastAddresses)
		{
			if ((adapter->OperationalStatus == System::Net::NetworkInformation::OperationalStatus::Up) && (ip->Address->AddressFamily == System::Net::Sockets::AddressFamily::InterNetwork))
			{
				ipint = BitConverter::ToInt32(ip->Address->GetAddressBytes(), 0);
				NetDevice^ dev = gcnew NetDevice(adapter->Id, adapter->Name, ipint);
				devices->Add(dev);
			}
		}
		
	}
	return devices;
}