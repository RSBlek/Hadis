#pragma once
#pragma comment( lib, "ws2_32.lib" ) // linker must use this lib for sockets

using namespace std;

#ifndef SIO_RCVALL
#  define SIO_RCVALL    _WSAIOW(IOC_VENDOR,1)
#endif
#define LS_MAX_PACKET_SIZE 65535
#define LS_HI_PART(x)  ((x>>4) & 0x0F)
#define LS_LO_PART(x)  ((x) & 0x0F)


class Sniffer {
public:
	static DWORD WINAPI sniffStart(void* data);
	void setIp(int ip);
private:
	void sniff();
	int devip;
	bool exited;
};