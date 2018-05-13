#include "stdafx.h"
#include "PacketHandler.h"
#include <sstream>

void PacketHandler::reset() {
	for (std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*>::iterator it = playerlist.begin(); it != playerlist.end(); it++)
		delete(it->second);
	playerlist.clear();
	resetcastsandattacks();
}

void PacketHandler::resetcastsandattacks() {
	attacksByObjectID.clear();
	attacksByTargetID.clear();
	for (std::list<AttackPacket*>::iterator i = attacklist.begin(); i != attacklist.end(); i++) //Free memory of all attacks
		delete(*i);
	attacklist.clear();
}

void PacketHandler::handlepacket(char* data, unsigned short size, Decryptor* decryptor, bool isclient) {
	if (isclient == false) {

		if (size == 9) {
			short* opcode = (short*)data;
			short origopcode = *opcode;
			decryptor->decodeOpCode(opcode);
			if (*opcode == SM_KEY) {
				rcv_sm_key(data, size, decryptor);
				return;
			}
			else
				*opcode = origopcode;
		}
		if (decryptor->haskey()) {
			decryptor->decodePacket(data, size, isclient);
			decryptor->decodeOpCode((short*)data);
			unsigned long long timestamp = (unsigned long)(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
			short opcode = *((short*)data);
			if (opcode == SM_STATS_INFO) {
				rcv_sm_stats_info(data, size);
			}
			else if (opcode == SM_MOVE) {
				rcv_sm_move(data, size, timestamp);
			}
			else if (opcode == SM_PLAYER_INFO) {
				rcv_sm_player_info(data, size);
			}
			else if (opcode == SM_CASTSPELL_END) {
				rcv_sm_castspell_end(data, size, timestamp);
			}
			else if (opcode == SM_ATTACK_STATUS) {
				rcv_sm_attack_status(data, size, timestamp);
			}
			else if (opcode == SM_ATTACK) {
				rcv_sm_attack(data, size, timestamp);
			}
		}
	}
}

void PacketHandler::rcv_sm_move(char* data, unsigned int size, unsigned long long timestamp) {
	//SM_MOVE_Packet* smp = new SM_MOVE_Packet(data, timestamp);
	//movelist.push_back(smp);
}

void PacketHandler::rcv_sm_player_info(char* data, unsigned int size) {
	SM_PLAYER_INFO_Packet* sspip = new SM_PLAYER_INFO_Packet(data);

	if (playerlist.find(sspip->objectid) == playerlist.end()) {
		playerlist.insert({ sspip->objectid , sspip });
	}
	else {
		delete(playerlist.at(sspip->objectid));
		playerlist.erase(sspip->objectid);
		playerlist.insert({ sspip->objectid , sspip });
	}
}

void PacketHandler::addAttackPacketToLists(AttackPacket* attackpacket) {
	attacklist.push_back(attackpacket);
	attacksByObjectID[attackpacket->objectid].push_back(attackpacket);

	if (attackpacket->hits.size() == 1) { //Because >90% of hits are single hits, a check for this case is useful to prevent the overhead of checking if the attackpacket was already added
		attacksByTargetID[attackpacket->hits[0].targetid].push_back(attackpacket);
	}
	else {
		for (size_t i = 0; i < attackpacket->hits.size(); i++) { //For each hit 
			unsigned int targetid = attackpacket->hits[i].targetid;  //TargetID of this hit 
			list<AttackPacket*>* attacksOnTargetID = &attacksByTargetID[targetid]; //Get list of all attacks on this target
			bool found = (std::find(attacksOnTargetID->begin(), attacksOnTargetID->end(), attackpacket) != attacksOnTargetID->end()); //True if this attack is already in the list of attacks on the target
			if (found == false)
				attacksOnTargetID->push_back(attackpacket);
		}
	}
}

void PacketHandler::rcv_sm_castspell_end(char* data, unsigned int size, unsigned long long timestamp) {
	SM_CAST_SPELL_END_Packet* castspellendpacket = new SM_CAST_SPELL_END_Packet(data, timestamp);
	addAttackPacketToLists(castspellendpacket->toAttackPacket());
	delete(castspellendpacket);
}

void PacketHandler::rcv_sm_attack(char* data, unsigned int size, unsigned long long timestamp) {
	SM_ATTACK_Packet* attackpacket = new SM_ATTACK_Packet(data, timestamp);
	addAttackPacketToLists(attackpacket->toAttackPacket());
	delete(attackpacket);
}

void PacketHandler::rcv_sm_attack_status(char* data, unsigned int size, unsigned long long timestamp) {
	SM_ATTACK_STATUS_Packet* attackstatuspacket = new SM_ATTACK_STATUS_Packet(data, timestamp);
	addAttackPacketToLists(attackstatuspacket->toAttackPacket());
}

void PacketHandler::rcv_sm_stats_info(char* data, unsigned int size) {
	SM_STATS_INFO_Packet* ssip = new SM_STATS_INFO_Packet(data);
	if (playerstats != nullptr) delete(playerstats);
	playerstats = ssip;
}

void PacketHandler::rcv_sm_key(char* data, unsigned int size, Decryptor* decryptor) {
	reset();
	SM_KEY_Packet smk = SM_KEY_Packet(data);
	decryptor->setKeys((char*)smk.key);
}



