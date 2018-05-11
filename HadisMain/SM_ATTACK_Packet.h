#pragma once
#include "GamePacket.h"

class AttackHit {
public:
	int damage;
	char attackstatus;
	char shieldtype;
	int reflectdamage;
	int reflectskillid;
};

class SM_ATTACK_Packet : GamePacket{
public:
	unsigned int attackerid;
	unsigned char attackno;
	short time;
	char type;
	unsigned int targetid;
	char targethp;
	int attackstatus;
	unsigned char attacklistsize;
	std::vector<AttackHit> attacklist = std::vector<AttackHit>();

	AttackPacket* toAttackPacket() {
		AttackPacket* attackpacket = new AttackPacket();
		attackpacket->type = AttackPacket::AttackPacketType::NormalAttack;
		attackpacket->objectid = this->attackerid;
		attackpacket->spellid = 1;
		attackpacket->timestamp = timestamp;
		for (size_t i = 0; i < attacklist.size(); i++) {
			Attack attack = Attack();
			attack.damage = attacklist[i].damage;
			attack.targetid = targetid;
			attack.type = (Attack::AttackStatus)attacklist[i].attackstatus;
			attackpacket->hits.push_back(attack);
		}
		return attackpacket;
	}

	SM_ATTACK_Packet(char* p, unsigned long long timestamp) {
		this->timestamp = timestamp;
		size_t c = 5; //2 Bytes for opcode and 3 for checksum
		this->attackerid = *((unsigned int*)(p + c)); c += (sizeof(attackerid));
		this->attackno = *((unsigned char*)(p + c)); c += (sizeof(attackno));
		this->time = *((short*)(p + c)); c += (sizeof(this->time));
		c = c + 1; // 1 Unknown Byte
		this->type = *((char*)(p + c)); c += (sizeof(this->type));
		this->targetid = *((unsigned int*)(p + c)); c += (sizeof(this->targetid));
		this->targethp = *((char*)(p + c)); c += (sizeof(this->targethp));
		c = c + 1; //Attacker hp
		this->attackstatus = *((int*)(p + c)); c += (sizeof(this->attackstatus));
		switch (this->attackstatus) {
		case 0x10A0F:
			c = c + 12; // 12 Bytes x y z
			break;
		case 0x10010:
			c = c + 1; //Unknown
			break;
		case 0x10000:
			c = c + 8; // Unknown
			break;
		}
		this->attacklistsize= *((unsigned char*)(p + c)); c += (sizeof(this->attacklistsize));
		if (this->attacklistsize > 255) this->attacklistsize = 0;

		for (int i = 0; i < this->attacklistsize; i++) {
			AttackHit ah = AttackHit();
			ah.damage = *((int*)(p + c)); c += (sizeof(ah.damage));
			ah.attackstatus = *((char*)(p + c)); c += (sizeof(ah.attackstatus));
			ah.shieldtype = *((char*)(p + c)); c += (sizeof(ah.shieldtype));
			switch (ah.shieldtype) {
			case 0x5:
				c = c + 12; // 12 Bytes unknown
				ah.reflectdamage = *((int*)(p + c)); c += (sizeof(ah.reflectdamage));
				ah.reflectskillid = *((int*)(p + c)); c += (sizeof(ah.reflectskillid));
				break;
			case 0x8:
				c = c + 12; // Unknown
				break;
			}
			attacklist.push_back(ah);
		}

	}
};