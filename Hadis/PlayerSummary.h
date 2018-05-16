#pragma once
class SpellSummary {
public:
	std::string spellname;
	unsigned int normalhits;
	unsigned int criticalhits;
	unsigned int evadedhits;
	unsigned int totaldamage;
	unsigned int criticaldamage;
};

class PlayerSummary {
public:
	enum class PlayerSummaryType { Damage, Heal };
	unsigned long long objectid;
	std::wstring playername;
	std::vector<SpellSummary> spells;
};