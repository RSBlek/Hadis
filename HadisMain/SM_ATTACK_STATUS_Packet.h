#pragma once
#include "GamePacket.h"

class SM_ATTACK_STATUS_Packet : GamePacket{
public:
	unsigned int targetid;
	unsigned int casterid;
	int value;
	char type;
	unsigned short skillid;
	char type2;
	char type3;

	AttackPacket* toAttackPacket() {
		AttackPacket* attackpacket = new AttackPacket();
		attackpacket->type = AttackPacket::AttackPacketType::StatusUpdate;
		attackpacket->objectid = casterid;
		attackpacket->spellid = skillid;
		attackpacket->timestamp = timestamp;
		Attack attack = Attack();
		attack.damage = value * -1;
		attack.targetid = targetid;
		if (type3 == 12) {
			attack.type = Attack::AttackStatus::Critical;
		}
		else {
			attack.type = Attack::AttackStatus::Normal;
		}
		attackpacket->hits.push_back(attack);
		return attackpacket;
	}


	SM_ATTACK_STATUS_Packet(char* p, unsigned long long timestamp) {
		this->timestamp = timestamp;
		size_t c = 5; //2 Bytes for opcode and 3 for checksum
		targetid = *((unsigned int*)(p + c)); c += (sizeof(targetid));
		casterid = *((unsigned int*)(p + c)); c += (sizeof(casterid));
		value = *((int*)(p + c)); c += (sizeof(value));
		type = *((char*)(p + c)); c += (sizeof(type));
		c = c + 1;//1 Byte hp
		skillid = *((unsigned short*)(p + c)); c += (sizeof(skillid));
		c = c + 2;//2 Bytes logid
		type2 = *((char*)(p + c)); c += (sizeof(type2));
		type3 = *((char*)(p + c)); c += (sizeof(type3));
	}

};