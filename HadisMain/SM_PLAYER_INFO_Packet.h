#pragma once
#include <string>
#include <sstream>

class SM_PLAYER_INFO_Packet {
public:
	float x;
	float y;
	float z;
	unsigned int objectid;
	unsigned char raceid;
	unsigned char classid;
	unsigned char genderid;
	std::wstring name;
	unsigned int legionid;
	std::wstring legionname;
	std::wstring note;
	unsigned short level;

	SM_PLAYER_INFO_Packet(char* p) {
		size_t c = 5; //2 Bytes for opcode and 3 for checksum
		x = *((float*)(p + c)); c += (sizeof(x));
		y = *((float*)(p + c)); c += (sizeof(x));
		z = *((float*)(p + c)); c += (sizeof(x));
		objectid = *((unsigned int*)(p + c)); c += (sizeof(objectid));
		c = c + 37; //37 Bytes useless information
		raceid = *((unsigned char*)(p + c)); c += (sizeof(raceid));
		classid = *((unsigned char*)(p + c)); c += (sizeof(classid));
		genderid = *((unsigned char*)(p + c)); c += (sizeof(genderid));
		c = c + 11; //11 Bytes useless information

		name = std::wstring((wchar_t*)(p + c)); c = c + (name.length()+1)*2;
		size_t minuspos = name.find_last_of('-');
		if (minuspos != std::wstring::npos) {
			name = name.substr(0, minuspos);
		}
		size_t spacepos = name.find_last_of(' ');
		if (spacepos != std::wstring::npos) {
			name = name.substr(spacepos + 1, std::wstring::npos);
		}

		c = c + 6; //6 Bytes useless information
		legionid = *((unsigned int*)(p + c)); c += (sizeof(legionid));
		if (legionid == 0) {
			c = c + 8;
		}
		else {
			c = c + 6; //Useless legion information
			legionname = std::wstring((wchar_t*)(p + c)); c = c + (legionname.length() + 1) * 2;
		}
		c = c + 4; //4 Bytes useless information
		unsigned int tmp = *((unsigned int*)(p + c)); c += (sizeof(tmp));
		unsigned short itemcount = 0;
		for (int i = 0; i < sizeof(tmp) * 8; i++) {
			if ((tmp & 1) == 1) itemcount++;
			tmp = tmp >> 1;
		}
		c = c + (itemcount * 16); //Every item is represented by 16 bytes
		c = c + 99;
		std::wstring tmpwstring = std::wstring((wchar_t*)(p + c)); c = c + (tmpwstring.length() + 1) * 2;
		c = c + 26;
		note = std::wstring((wchar_t*)(p + c)); c = c + (note.length() + 1) * 2;
		level = *((unsigned short*)(p + c)); c += (sizeof(level));
	}
};