#pragma once

class Attack {
public:
	enum class AttackStatus : char {Critical = -54, None = 0, Parry = 2, Block = 4, Resist = 6, Normal = 10};
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