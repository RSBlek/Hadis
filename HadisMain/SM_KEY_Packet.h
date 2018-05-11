#pragma once



class SM_KEY_Packet {
public:
	char key[4];
	SM_KEY_Packet(char* p) {
		unsigned short c = 5; //2 Bytes for opcode and 3 for checksum
		key[0] =  *((char*)(p + c)); c += (sizeof(char));
		key[1] = *((char*)(p + c)); c += (sizeof(char));
		key[2] = *((char*)(p + c)); c += (sizeof(char));
		key[3] = *((char*)(p + c)); c += (sizeof(char));
	}
};
