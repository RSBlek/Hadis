// stdafx.h: Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur in unregelmäßigen Abständen geändert werden.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Komponenten aus Windows-Headern ausschließen
// Windows-Headerdateien:
#include <windows.h>
#include <WinSock2.h>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
#include <atlcomcli.h>
#include <psapi.h>
#include <unordered_map>
#include <sstream>
#include <string>

// TODO: Hier auf zusätzliche Header, die das Programm erfordert, verweisen.
#include "Firewall.h"
#include "Spells.h"
#include "TCPPacket.h"
#include "OpCodes.h"
#include "PacketBuffer.h"
#include "Sniffer.h"
#include "AttackPacket.h"
#include "SM_MOVE_Packet.h"
#include "CM_MOVE_Packet.h"
#include "SM_CAST_SPELL_END_Packet.h"
#include "SM_PLAYER_INFO_Packet.h" 
#include "SM_ATTACK_STATUS_Packet.h"
#include "SM_ATTACK_Packet.h"
#include "SM_KEY_Packet.h"
#include "SM_L2AUTH_LOGIN_CHECK_Packet.h"
#include "SM_STATS_INFO_Packet.h"
#include "Security.h"
#include "Decryptor.h"
#include "PacketHandler.h"
#include "PlayerStatInfo.h"
#include "PlayerSummary.h"
#include "Hadis.h"