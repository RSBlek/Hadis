#pragma once

class Decryptor {

public:
	char clientkey[8];
	char serverkey[8];
	bool keyavailable = false;
public:
	static char statickey[];
	void setKeys(char* rawkey);
	short decodeOpCode(short* opcode);
	bool haskey();
	void decodePacket(char* data, unsigned short datalength, bool isclient);
};