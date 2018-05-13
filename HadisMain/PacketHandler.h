#pragma once

using namespace std::chrono;
class PacketHandler{
	void rcv_sm_key(char* data, unsigned int size, Decryptor* decryptor);
	void rcv_sm_stats_info(char* data, unsigned int size);
	void rcv_sm_player_info(char* data, unsigned int size);
	void rcv_sm_castspell_end(char* data, unsigned int size, unsigned long long timestamp);
	void rcv_sm_attack_status(char* data, unsigned int size, unsigned long long timestamp);
	void rcv_sm_attack(char* data, unsigned int size, unsigned long long timestamp);
	void rcv_sm_move(char* data, unsigned int size, unsigned long long timestamp);
	void addAttackPacketToLists(AttackPacket* attackpacket);
public:
	std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*> playerlist = std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*>();
	std::list<AttackPacket*> attacklist = std::list<AttackPacket*>();
	std::list<SM_MOVE_Packet*> movelist = std::list<SM_MOVE_Packet*>();
	std::unordered_map<unsigned int, list<AttackPacket*>> attacksByObjectID = std::unordered_map<unsigned int, list<AttackPacket*>>();
	std::unordered_map<unsigned int, list<AttackPacket*>> attacksByTargetID = std::unordered_map<unsigned int, list<AttackPacket*>>();
	SM_STATS_INFO_Packet* playerstats = nullptr;
public: 
	void handlepacket(char* data, unsigned short size, Decryptor* decryptor, bool isclient);
	void reset();
	void resetcastsandattacks();
};