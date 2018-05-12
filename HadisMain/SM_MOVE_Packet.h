#pragma once
#include "GamePacket.h"

class SM_MOVE_Packet : GamePacket {
public:
	unsigned int objectid;
	float x;
	float y;
	float z;
	unsigned char heading;
	unsigned char movementtypeid;
	float x2;
	float y2;
	float z2;

	SM_MOVE_Packet(char* p, unsigned long long timestamp) {
		this->timestamp = timestamp;
		size_t c = 5;
		objectid = *((unsigned int*)(p + c)); c += (sizeof(objectid));
		x = *((float*)(p + c)); c += (sizeof(x));
		y = *((float*)(p + c)); c += (sizeof(y));
		z = *((float*)(p + c)); c += (sizeof(z));
		heading = *((char*)(p + c)); c += (sizeof(heading));
		movementtypeid = *((char*)(p + c)); c += (sizeof(movementtypeid));
		if (movementtypeid != 0) {
			x2 = *((float*)(p + c)); c += (sizeof(x2));
			y2 = *((float*)(p + c)); c += (sizeof(y2));
			z2 = *((float*)(p + c)); c += (sizeof(z2));
		}
	}

};