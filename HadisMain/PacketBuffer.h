#pragma once

#define BUFFERSIZE 0x500000

class PacketBuffer {
public:
	static std::mutex packetmutex;
	static std::list<TCPPacket*> allpackets;
	std::list<TCPPacket*> unorderedpackets = std::list<TCPPacket*>();
	std::list<TCPPacket*> orderedpackets = std::list<TCPPacket*>();
	char* bytebuffer = (char*)malloc(BUFFERSIZE);
	unsigned int bytebuffercount = 0;
	unsigned int nextsequence = 0;
	void reset();

	void lshiftbuffer(unsigned int n);

};