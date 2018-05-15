// HadisMain.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include <thread>
#include <string>

HANDLE sniffthread = nullptr;

vector<PlayerStatInfo>* lastPlayerStatInfoPointer = nullptr;

extern  __declspec(dllexport) void start(int ip) {
	Sniffer* sniffer = new Sniffer();
	sniffer->setIp(ip);
	
	Hds::getInstance().reset();
	PacketBuffer::packetmutex.lock();
	if (sniffthread != nullptr) {
		SuspendThread(sniffthread);
	}
	sniffthread = CreateThread(NULL, 0, Sniffer::sniffStart, sniffer, 0L, NULL);
	PacketBuffer::packetmutex.unlock();

}


extern __declspec(dllexport) vector<PlayerStatInfo>* getPlayerStatInfo(unsigned int target, PlayerStatInfo::PlayerStatInfoType type) {
	if (lastPlayerStatInfoPointer != nullptr) free(lastPlayerStatInfoPointer);
	lastPlayerStatInfoPointer = Hds::getInstance().getPlayerStatInfo(target, type);
	return lastPlayerStatInfoPointer;
}