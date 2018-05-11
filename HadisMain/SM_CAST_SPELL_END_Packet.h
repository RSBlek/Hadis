#pragma once
#include "GamePacket.h"

class SpellHit {
public:
	unsigned int targetid;
	char targethp;
	char attackerhp;
	int damage;
	char attackstatus;
	char shielddefence;
};

class SM_CAST_SPELL_END_Packet : GamePacket {
public:
	unsigned int objectid;
	unsigned char targettype;
	unsigned int targetid;
	unsigned short spellid;
	unsigned char level;
	int cooldown;
	unsigned short time;
	std::vector<SpellHit> spellhitlist;

	AttackPacket* toAttackPacket() {
		AttackPacket* attackpacket = new AttackPacket();
		attackpacket->type = AttackPacket::AttackPacketType::SpellCast;
		attackpacket->objectid = objectid;
		attackpacket->spellid = spellid;
		attackpacket->timestamp = timestamp;
		
		for (size_t i = 0; i < spellhitlist.size(); i++) {
			Attack attack = Attack();
			attack.damage = spellhitlist[i].damage;
			attack.targetid = spellhitlist[i].targetid;
			attack.type = (Attack::AttackStatus)spellhitlist[i].attackstatus;
			attackpacket->hits.push_back(attack);
		}

		return attackpacket;
	}

	SM_CAST_SPELL_END_Packet(char* p, unsigned long long timestamp) {
		this->timestamp = timestamp;
		size_t c = 5; //2 Bytes for opcode and 3 for checksum
		objectid = *((unsigned int*)(p + c)); c += (sizeof(objectid));
		targettype = *((unsigned char*)(p + c)); c += (sizeof(targettype));

		if (targettype == 0x0) {
			targetid = *((unsigned int*)(p + c)); c += (sizeof(targetid));
		}
		else if (targettype == 0x1) {
			c = c + 12; //AoE Coordinates 12 Bytes
		}
		else if (targettype == 0x3) {
			c = c + 4; //Unknown 4 bytes
		}
		spellid = *((unsigned short*)(p + c)); c += (sizeof(spellid));
		level = *((unsigned char*)(p + c)); c += (sizeof(level));
		cooldown = *((int*)(p + c)); c += (sizeof(cooldown));
		time = *((unsigned short*)(p + c)); c += (sizeof(time));
		c = c + 3;//1 Byte unknown and 2 Bytes spelleffect
		unsigned char dashtype = *((unsigned char*)(p + c)); c += (sizeof(dashtype));
		if (dashtype >= 0x01 && dashtype <= 4) {
			c = c + 13;
		}
		c = c + 2; //Unknown 2 Bytes
		unsigned short effectsize = *((unsigned short*)(p + c)); c += (sizeof(effectsize));


		for (int i = 0; i < effectsize; i++) {
			SpellHit hit = SpellHit();
			hit.targetid = *((unsigned int*)(p + c)); c += (sizeof(hit.targetid));
			c = c + 1; //Unknown byte
			hit.targethp = *((char*)(p + c)); c += (sizeof(hit.targethp));
			hit.attackerhp = *((char*)(p + c)); c += (sizeof(hit.attackerhp));
			char spellstatus = *((char*)(p + c)); c += (sizeof(spellstatus));
			char skillmovetype = *((char*)(p + c)); c += (sizeof(skillmovetype));
			c = c + 3;//Unknown 2 bytes and 1 byte currentrunecount

			switch (spellstatus) {
			case 1: //Stumble
				c = c + 12;//12 Bytes x y z
				break;
			case 2: //Knockback
				c = c + 12;//12 Bytes x y z
				break;
			case 4: //Open Aerial
				c = c + 12;//12 Bytes x y z
				break;
			case 8://Close Aerial
				c = c + 12;//12 Bytes x y z
				break;
			case 16:
				c = c + 1;//1 Byte heading
				break;
			default:
				if (skillmovetype == 54) {
					c = c + 12; // 12 Bytes x y z
				}
				else if (skillmovetype == 50) {
					c = c + 12; // 12 Bytes x y z
				}
				break;
			}

			c = c + 2; // 1 unknown byte and 1 byte ismpheal
			hit.damage = *((int*)(p + c)); c += (sizeof(hit.damage));
			hit.attackstatus = *((char*)(p + c)); c += (sizeof(hit.attackstatus));
			hit.shielddefence = *((char*)(p + c)); c += (sizeof(hit.shielddefence));

			if (hit.shielddefence == 0x1) {
				c = c + 20; //12 Bytes unknown and 4 bytes reflectdamage and 4 bytes skillid
			}
			else if (hit.shielddefence == 8) {
				c = c + 12; // 4 Bytes protector id and 4 bytes damage and 2 bytes skillid und 2 bytes unknown
			}
			spellhitlist.push_back(hit);
		}

	}

};