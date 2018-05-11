#include "stdafx.h"
#include "PacketBuffer.h"

std::list<TCPPacket*> PacketBuffer::allpackets = std::list<TCPPacket*>();
std::mutex PacketBuffer::packetmutex;

void PacketBuffer::reset() {
	nextsequence = 0;

	for(std::list<TCPPacket*>::iterator it = unorderedpackets.begin(); it!=unorderedpackets.end(); it++)
		delete(*it);
	unorderedpackets.clear();
	for (std::list<TCPPacket*>::iterator it = orderedpackets.begin(); it !=orderedpackets.end(); it++)
		delete(*it);
	orderedpackets.clear();

	bytebuffercount = 0;
	memset(bytebuffer, 0x0, BUFFERSIZE);
}


void PacketBuffer::lshiftbuffer(unsigned int n) {
	for (unsigned int i = n; i < bytebuffercount; i++) {
		bytebuffer[i - n] = bytebuffer[i];
	}
	for (unsigned int i = bytebuffercount - n; i < bytebuffercount; i++) {
		bytebuffer[i] = 0x0;
	}
	bytebuffercount = bytebuffercount - n;
}