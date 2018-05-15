#pragma once

#define MAXPLAYERIDLE 3000

struct PlayerAttackDuration {
	unsigned long long lasthittimestamp = 0;
	unsigned long long attackduration = 0;
};

class PlayerStatInfo {

public:
	enum PlayerStatInfoType { Damage, Heal, Dps };

	std::wstring player;
	unsigned long long playerid;
	unsigned int value;
	short percentage;
	unsigned char classid;
	PlayerStatInfoType type;

	bool operator < (const PlayerStatInfo& str) const
	{
		return (value > str.value);
	}

};


class Hds {
private:
	PacketBuffer* serverpackets = new PacketBuffer();
	PacketBuffer* clientpackets = new PacketBuffer();
	PacketHandler* packethandler = new PacketHandler();
	Sniffer* sniffer = new Sniffer();
	Decryptor* decryptor = new Decryptor();
	unsigned int srcxdstport = 0;
	void sortclientserverpackets();
	void sortpacketsbysequence(PacketBuffer* pb);
	void readpacketdata(PacketBuffer* pb);
	void processbuffer(PacketBuffer* pb, bool isclient);
	unsigned char getUIClassID(unsigned char classid);
	void calculateDpsForAttack(std::unordered_map<unsigned int, PlayerAttackDuration>* playerdpsinfomap, AttackPacket* currentAttackPacket, unsigned int objectid);
	Hds() {}
public:
	std::vector<PlayerStatInfo>* getPlayerStatInfo(unsigned int targetid, PlayerStatInfo::PlayerStatInfoType type);

public:
	void init();
	void process();
	void reset();
	static DWORD WINAPI processStart(void* data);
	static Hds& getInstance() {
		static Hds instance;
		return instance;
	}
};