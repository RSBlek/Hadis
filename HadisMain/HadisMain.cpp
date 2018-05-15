// HadisMain.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include <thread>
#include <string>

HANDLE sniffthread = nullptr;
HANDLE proccessthread = nullptr;

vector<PlayerStatInfo>* lastPlayerStatInfoPointer = nullptr;

extern  __declspec(dllexport) void start(int ip) {
	Sniffer* sniffer = new Sniffer();
	sniffer->setIp(ip);
	HANDLE hCurrentProcess = GetCurrentProcess(); //Get Handle of current process
	wchar_t executablePath[512]; 
	GetModuleFileNameEx(hCurrentProcess, NULL, executablePath, 512); //Get path by process handle
	wchar_t FirewallRuleName[] = L"Hadis";
	Firewall::addFirewallApp(executablePath, FirewallRuleName);
	Hds::getInstance().reset();
	PacketBuffer::packetmutex.lock();
	if (sniffthread != nullptr) {
		SuspendThread(sniffthread);
	}
	sniffthread = CreateThread(NULL, 0, Sniffer::sniffStart, sniffer, 0L, NULL);
	PacketBuffer::packetmutex.unlock();
	if(proccessthread == nullptr)
		proccessthread = CreateThread(NULL, 0, Hds::processStart , &Hds::getInstance(), 0L, NULL);
}


extern __declspec(dllexport) vector<PlayerStatInfo>* getPlayerStatInfo(unsigned int target, PlayerStatInfo::PlayerStatInfoType type) {
	if (lastPlayerStatInfoPointer != nullptr) free(lastPlayerStatInfoPointer);
	lastPlayerStatInfoPointer = Hds::getInstance().getPlayerStatInfo(target, type);
	return lastPlayerStatInfoPointer;
}