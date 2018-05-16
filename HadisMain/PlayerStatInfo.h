#pragma once

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