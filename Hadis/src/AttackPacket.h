#pragma once

class Attack {
public:
	enum class AttackStatus {Critical, None, Parry, Block, Resist, Normal};
public:
	unsigned int targetid;
	int damage;
	AttackStatus type;
};

class AttackPacket {
public:
	enum class AttackPacketType { SpellCast, StatusUpdate, NormalAttack };
public:
	AttackPacketType type;
	unsigned int objectid;
	unsigned short spellid;
	unsigned long long timestamp;
	std::vector<Attack> hits = std::vector<Attack>();
};