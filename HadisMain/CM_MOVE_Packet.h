#pragma once
#include "GamePacket.h"

class CM_MOVE_Packet : GamePacket {
public:
	float x;
	float y;
	float z;
	unsigned char heading;
	char movementtypeid;
	float x2;
	float y2;
	float z2;
	char glideflag;

	CM_MOVE_Packet(char* p, unsigned long long timestamp) {
		this->timestamp = timestamp;
		size_t c = 5;
		x = *((float*)(p + c)); c += (sizeof(x));
		y = *((float*)(p + c)); c += (sizeof(y));
		z = *((float*)(p + c)); c += (sizeof(z));
		heading = *((char*)(p + c)); c += (sizeof(heading));
		movementtypeid = *((char*)(p + c)); c += (sizeof(movementtypeid));
		if (movementtypeid == -32 || movementtypeid == -64 || movementtypeid == -60 || movementtypeid == -28) {
			x2 = *((float*)(p + c)); c += (sizeof(x2));
			y2 = *((float*)(p + c)); c += (sizeof(y2));
			z2 = *((float*)(p + c)); c += (sizeof(z2));
		}
		else if (movementtypeid == -124 || movementtypeid == -92) {
			glideflag = *((char*)(p + c)); c += (sizeof(glideflag));
		}
	}

};