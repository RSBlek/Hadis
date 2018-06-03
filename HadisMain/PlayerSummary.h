#pragma once

class SpellSummary {
public:
	std::string spellname;
	unsigned int normalhits;
	unsigned int criticalhits;
	unsigned int evadedhits;
	unsigned int totaldamage;
	unsigned int criticaldamage;
	unsigned int mindamage;
	unsigned int maxdamage;
	unsigned int avgdamage;

	bool operator < (const SpellSummary& str) const
	{
		return (totaldamage > str.totaldamage);
	}

};

class PlayerSummary {
public:
	enum class PlayerSummaryType { Damage, Heal };
	unsigned long long objectid;
	std::wstring playername;
	std::vector<SpellSummary> spells;
};