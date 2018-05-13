#include "stdafx.h"
#include "Hadis.h"
#include <algorithm>


void Hds::reset() {
	srcxdstport = 0;
	serverpackets->reset();
	PacketBuffer::packetmutex.lock();
	for (std::list<TCPPacket*>::iterator i = PacketBuffer::allpackets.begin(); i != PacketBuffer::allpackets.end(); i++)
		delete(*i);
	PacketBuffer::allpackets.clear();
	PacketBuffer::packetmutex.unlock();
	packethandler->reset();
}

unsigned char Hds::getUIClassID(unsigned char classid) {
	if (classid >= 0 && classid <= 2) return 0;
	if (classid >= 3 && classid <= 5) return 1;
	if (classid >= 6 && classid <= 8) return 2;
	if (classid >= 9 && classid <= 11) return 3;
	if (classid >= 12 && classid <= 14) return 4;
	if (classid >= 15 && classid <= 16) return 5;
	return 6;
}


void Hds::calculateDpsForAttack(std::unordered_map<unsigned int, PlayerAttackDuration>* playerattackdurationmap, AttackPacket* currentAttackPacket, unsigned int objectid) {
	PlayerAttackDuration playerdpsinfo = (*playerattackdurationmap)[objectid]; //Get players lasthittimestamp and cumulated attackduration
	if (playerdpsinfo.lasthittimestamp < (currentAttackPacket->timestamp - MAXPLAYERIDLE)) //If his last hit is longer ago than the maximum idle time
		(*playerattackdurationmap)[objectid].attackduration += MAXPLAYERIDLE; //Add maximum idle time to his attack duration
	else //If the player did two hits within the maximum idle time
		(*playerattackdurationmap)[objectid].attackduration += (currentAttackPacket->timestamp - playerdpsinfo.lasthittimestamp); //Add the time difference between his last two hits
	(*playerattackdurationmap)[objectid].lasthittimestamp = currentAttackPacket->timestamp; //Set the players last hit timestamp to the current timestamp
}



std::vector<PlayerStatInfo>* Hds::getPlayerStatInfo(unsigned int targetid, PlayerStatInfo::PlayerStatInfoType type) {

	std::unordered_map<unsigned int, unsigned int> damagedonemap = std::unordered_map<unsigned int, unsigned int>(); //Hashmap with player objectid as key and his overall damage/heal done as value
	std::unordered_map<unsigned int, PlayerAttackDuration> playerattackdurationmap = std::unordered_map<unsigned int, PlayerAttackDuration>(); //Hashmap with player objectid as key and a struct where his lasthit and the cumulated attack duration as value
	std::unordered_map<unsigned int, list<AttackPacket*>>::iterator attacksByObjIdIt;
	std::list<AttackPacket*>::iterator attackPacketListIt;
	SM_PLAYER_INFO_Packet* currentPlayer;
	AttackPacket* currentAttackPacket;
	std::vector<PlayerStatInfo>* psivector = new std::vector<PlayerStatInfo>();

	for (attacksByObjIdIt = packethandler->attacksByObjectID.begin(); attacksByObjIdIt != packethandler->attacksByObjectID.end(); attacksByObjIdIt++) {
		if (packethandler->playerlist.find(attacksByObjIdIt->first) == packethandler->playerlist.end()) continue; //If the casting objectid is not found in the playerlist continue
		currentPlayer = packethandler->playerlist.find(attacksByObjIdIt->first)->second;
		for (attackPacketListIt = attacksByObjIdIt->second.begin(); attackPacketListIt != attacksByObjIdIt->second.end(); attackPacketListIt++) { //For each attack of the player
			currentAttackPacket = *attackPacketListIt;
			for (size_t i = 0; i < currentAttackPacket->hits.size(); i++) { //For each hit of the attack
				Attack* currentHit = &(currentAttackPacket->hits[i]);
				if (type == PlayerStatInfo::PlayerStatInfoType::Heal) { //If the function was called with Heal as type parameter
					if (currentHit->damage < 0) 
						damagedonemap[currentPlayer->objectid] += (currentHit->damage * -1); //If the hit value is negative then it is a heal and will be added to the calculation
				}
				else { //If it is not called with Heal as type parameter
					if (currentHit->damage > 0) //If the damage is positive, it is damage
						damagedonemap[currentPlayer->objectid] += currentHit->damage;
				}
			}

			if (type == PlayerStatInfo::PlayerStatInfoType::Dps)
				calculateDpsForAttack(&playerattackdurationmap, currentAttackPacket, currentPlayer->objectid);
		}

		if (damagedonemap[currentPlayer->objectid] == 0) 
			continue;

		PlayerStatInfo psi = PlayerStatInfo(); 
		psi.player = currentPlayer->name;
		psi.playerid = Security::getUIObjectID(currentPlayer->objectid);
		psi.value = damagedonemap[currentPlayer->objectid];
		psi.classid = getUIClassID(currentPlayer->classid);
		if (type == PlayerStatInfo::PlayerStatInfoType::Dps) 
			psi.value = psi.value / ((unsigned int)(playerattackdurationmap[currentPlayer->objectid].attackduration / 1000));

		psivector->push_back(psi);

	}

	std::sort(psivector->begin(), psivector->end());

	int maxdamage = 0;
	for (size_t i = 0; i < psivector->size(); i++) {
		if (i == 0) {
			maxdamage = (*psivector)[i].value;
			(*psivector)[i].percentage = 100;
		}
		else {
			(*psivector)[i].percentage = ((*psivector)[i].value * 100) / maxdamage;
		}
	}

	return psivector;
}



void Hds::sortclientserverpackets() {
	PacketBuffer::packetmutex.lock();
	std::list<TCPPacket*>::iterator current = PacketBuffer::allpackets.begin();
	std::list<TCPPacket*>::iterator next;
	while (current != PacketBuffer::allpackets.end()) {
		next = std::next(current, 1);
		if ((*current)->clientpacket == false) { //If current packet is a server packet
			unsigned int currentsrcxdstport = (*current)->tcp_port_src * (*current)->tcp_port_dst; //Get session id of current packet
			if (currentsrcxdstport != srcxdstport) {//If the session id is an other than the previous
				srcxdstport = currentsrcxdstport; //Set new session id
				serverpackets->nextsequence = 0; //Reset sequence number
				serverpackets->reset(); //Delete all received packets except the unprocessed
				clientpackets->nextsequence = 0; //Reset sequence number
				clientpackets->reset(); //Delete all received packets except the unprocessed
			}
			serverpackets->unorderedpackets.push_back(*current); //Add this packet to the list of serverpackets
		}
		else { //If the current packet is a client packet
			clientpackets->unorderedpackets.push_back(*current); //Add this packet to the list of clientpackets
		}
		PacketBuffer::allpackets.erase(current); //Remove this packet from the list of unprocessed packets
		current = next;
	}
	PacketBuffer::packetmutex.unlock();
}

void Hds::sortpacketsbysequence(PacketBuffer* pb) {
	std::list<TCPPacket*>::iterator current;
	std::list<TCPPacket*>::iterator next;
	bool added = false;
	unsigned long long timestamplimit = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - 30000; //All packets that are older than 30 seconds will be deleted
	do {
		added = false; //Initialize flag that no packets were ordered
		current = pb->unorderedpackets.begin(); //First unprocessed packet
		while (current != pb->unorderedpackets.end()) { //While the end of the packet list was not reached
			next = std::next(current, 1); //Save the iterator to the next packet
			if (pb->nextsequence == 0) { //If no packets were sorted before
				if ((*current)->tcp_syn == 0) { //If the synchronisation is completed and it is a data packet
					pb->nextsequence = (*current)->tcp_sequence; //Set next sequence number
				}
				else { //If it is a syn packet
					delete(*current); //Free memory of tcp packet
					pb->unorderedpackets.erase(current); //Remove tcp packet from list
					current = next; //Increment iterator
					continue;
				}
			}
			if (pb->nextsequence == (*current)->tcp_sequence) {//If the sequence number matches the next sequence number
				pb->nextsequence += (*current)->data_size; //Increment the next sequence by the number of received bytes
				if ((*current)->data_size > 0) { //If the packet has data 
					pb->orderedpackets.push_back(*current); //Add current packet to the list of ordered packets
				}
				else {
					delete(*current); //Free Packet memory
				}
				pb->unorderedpackets.erase(current); //Remove from unordered packet list
				added = true; //Set the added flag to true. All packets have to be analyzed from the beginning because the next packet could be before the current packet
			}
			else if ((*current)->timestamp < timestamplimit) { //If packet is too old
				delete(*current); //Free Packet memory
				pb->unorderedpackets.erase(current); //Remove from unordered packet list
			}
			current = next;
		}
	} while (added == true);
}

void Hds::readpacketdata(PacketBuffer* pb) {
	std::list<TCPPacket*>::iterator current = pb->orderedpackets.begin();
	std::list<TCPPacket*>::iterator next;

	while (current != pb->orderedpackets.end()) { //While the end of the list was not reached
		next = std::next(current, 1); //Increment iterator
		for (unsigned short i = 0; i < (*current)->data_size; i++) { //Copy data into buffer
			pb->bytebuffer[pb->bytebuffercount + i] = (*current)->data[i];
		}
		pb->bytebuffercount += (*current)->data_size; //Increase the number of buffered bytes
		delete(*current); //Free Packet Memory
		pb->orderedpackets.erase(current); //Remove Packet from the list
		current = next;
	}
}

void Hds::processbuffer(PacketBuffer* pb, bool isclient) {
	unsigned int currpos = 0;
	unsigned short packetsize = 0;
	char* p;
	while (currpos < pb->bytebuffercount) {
		packetsize = *(unsigned short*)(pb->bytebuffer + currpos);
		if (packetsize > pb->bytebuffercount) break;
		p = (char*)malloc(packetsize - 2);
		for (unsigned short i = 2; i < packetsize; i++) {
			p[i - 2] = pb->bytebuffer[currpos + i];
		}
		packethandler->handlepacket(p, packetsize - 2, decryptor, isclient);
		free(p);
		currpos += packetsize;
	}
	pb->lshiftbuffer(currpos);
}

void Hds::process() {
	while (1) {
		sortclientserverpackets();

		sortpacketsbysequence(serverpackets);
		readpacketdata(serverpackets);
		processbuffer(serverpackets, false);

		sortpacketsbysequence(clientpackets);
		readpacketdata(clientpackets);
		processbuffer(clientpackets, true);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

DWORD WINAPI Hds::processStart(void* data) {
	Hds* This = (Hds*)data;
	This->process();
	return 0;
}