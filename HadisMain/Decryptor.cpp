#include "stdafx.h"
#include "Decryptor.h"

char Decryptor::statickey[] = { 110, 75, 79, 47, 87, 99, 116, 81, 48, 65, 86, 76, 98, 112, 122, 102, 66,
107, 83, 54, 78, 101, 118, 68, 89, 84, 56, 111, 117, 114, 71, 53, 67, 82,
108, 109, 100, 106, 121, 74, 55, 50, 97, 115, 119, 120, 52, 69, 80, 113,
49, 85, 103, 90, 104, 70, 77, 88, 72, 63, 51, 105, 73, 57 };

void Decryptor::setKeys(char* rawkey) {
	int* key = (int*)rawkey;
	*key = (*key - 0x3FF2CCD7) ^ 0xCD92E4D5;
	clientkey[0] = *((char*)key + 0x0);
	clientkey[1] = *((char*)key + 0x1);
	clientkey[2] = *((char*)key + 0x2);
	clientkey[3] = *((char*)key + 0x3);
	clientkey[4] = (char)0xA1;
	clientkey[5] = (char)0x6C;
	clientkey[6] = (char)0x54;
	clientkey[7] = (char)0x87;
	for (int i = 0; i < 8; i++) serverkey[i] = clientkey[i];
	keyavailable = true;
}

short Decryptor::decodeOpCode(short* opcode) {
	*opcode = (*opcode ^ 0xD5) - 0xD4;
	return *opcode;
}

void Decryptor::decodePacket(char* data, unsigned short datalength, bool isclient) {
	char* key;
	if (isclient == false) {
		key = serverkey;
	}
	else {
		key = clientkey;
	}
	char* bytes = data;
	char previous = bytes[0];
	bytes[0] = bytes[0] ^ (*key);

	for (unsigned int i = 1; i < datalength; i++) {
		char current = bytes[i];
		bytes[i] = current ^ Decryptor::statickey[i & 0x3F] ^ key[i & 0x7] ^ previous;
		previous = current;
	}

	long long *longkey = (long long*)key;
	*longkey = *longkey + datalength;
}

bool Decryptor::haskey() {
	return keyavailable;
}