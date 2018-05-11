#include "stdafx.h"
#include "PacketHandler.h"
#include <sstream>

void PacketHandler::reset() {
	std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*>::iterator current = playerlist->begin();
	std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*>::iterator next;

	while (current != playerlist->end()) {
		next = std::next(current, 1);
		delete(current->second);
		playerlist->erase(current);
		current = next;
	}
	resetcastsandattacks();
}

void PacketHandler::resetcastsandattacks() {
	for (std::list<SM_CAST_SPELL_END_Packet*>::iterator i = castspelllist->begin(); i != castspelllist->end(); i++) {
		delete(*i);
	}
	castspelllist->clear();

	for (std::list<SM_ATTACK_STATUS_Packet*>::iterator i = attackstatuslist->begin(); i != attackstatuslist->end(); i++) {
		delete(*i);
	}
	attackstatuslist->clear();

	for (std::list<SM_ATTACK_Packet*>::iterator i = normalattacklist->begin(); i != normalattacklist->end(); i++) {
		delete(*i);
	}
	normalattacklist->clear();

	for (std::list<AttackPacket*>::iterator i = attacklist.begin(); i != attacklist.end(); i++) {
		delete(*i);
	}
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
		if(decryptor->haskey()){
			decryptor->decodePacket(data, size, isclient);
			decryptor->decodeOpCode((short*)data);
			unsigned long long timestamp = (unsigned long)(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
			short opcode = *((short*)data);
			if (opcode == SM_STATS_INFO) {
				rcv_sm_stats_info(data, size);
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

void PacketHandler::rcv_sm_player_info(char* data, unsigned int size) {
	SM_PLAYER_INFO_Packet* sspip = new SM_PLAYER_INFO_Packet(data);

	if ( playerlist->find(sspip->objectid) == playerlist->end()) {
		playerlist->insert({ sspip->objectid , sspip });
	}
	else {
		delete(playerlist->at(sspip->objectid));
		playerlist->erase(sspip->objectid);
		playerlist->insert({ sspip->objectid , sspip });
	}
}


void PacketHandler::rcv_sm_castspell_end(char* data, unsigned int size, unsigned long long timestamp) {
	SM_CAST_SPELL_END_Packet* scep = new SM_CAST_SPELL_END_Packet(data, timestamp);
	attacklist.push_back(scep->toAttackPacket());
	castspelllist->push_back(scep);
}

void PacketHandler::rcv_sm_attack(char* data, unsigned int size, unsigned long long timestamp) {
	SM_ATTACK_Packet* sap = new SM_ATTACK_Packet(data, timestamp);
	attacklist.push_back(sap->toAttackPacket());
	normalattacklist->push_back(sap);
}

void PacketHandler::rcv_sm_attack_status(char* data, unsigned int size, unsigned long long timestamp) {
	SM_ATTACK_STATUS_Packet* sasp = new SM_ATTACK_STATUS_Packet(data, timestamp);
	attackstatuslist->push_back(sasp);
	if (sasp->casterid != 0) {
		attacklist.push_back(sasp->toAttackPacket());
	}
}

void PacketHandler::rcv_sm_stats_info(char* data, unsigned int size) {
	SM_STATS_INFO_Packet* ssip = new SM_STATS_INFO_Packet(data);
}

void PacketHandler::rcv_sm_key(char* data, unsigned int size, Decryptor* decryptor) {
	reset();
	SM_KEY_Packet smk = SM_KEY_Packet(data);
	decryptor->setKeys((char*)smk.key);
}



