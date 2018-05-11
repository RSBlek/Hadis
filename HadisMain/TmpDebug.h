//#pragma once
//#include <string>
//#include <vector>
//#include <list>
//
//class Player {
//public:
//	unsigned int objectid;
//	std::wstring playername;
//	unsigned char classid;
//	unsigned short level;
//};
//
//
//class Spellcast {
//public:
//	unsigned short spellid;
//	unsigned int caster;
//	unsigned int targetid;
//	char attackstatus;
//	int damage;
//};
//
//class Attackstatus {
//public:
//	unsigned int targetid;
//	unsigned int casterid;
//	int value;
//	char type;
//	unsigned short skillid;
//	char type2;
//	char type3;
//};
//
//class AutoAttack {
//public:
//	unsigned int attacker;
//	unsigned char attackno;
//	int damage;
//	char type;
//	unsigned int targetid;
//	int attackstatus;
//	char attackstatus2;
//	char shieldtype;
//};
//
//std::vector<Player> getPlayerList() {
//	std::vector<Player> pl = std::vector<Player>();
//
//	std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*>::iterator current = packethandler->playerlist->begin();
//	std::unordered_map<unsigned int, SM_PLAYER_INFO_Packet*>::iterator next;
//	Player p;
//	while (current != packethandler->playerlist->end()) {
//		next = std::next(current, 1);
//		p = Player();
//		p.objectid = current->second->objectid;
//		p.playername = current->second->name;
//		p.level = current->second->level;
//		p.classid = current->second->classid;
//		pl.push_back(p);
//		current = next;
//	}
//	return pl;
//}
//
//std::vector<Spellcast> getSpellcastList() {
//	std::vector<Spellcast> scl = std::vector<Spellcast>();
//	Spellcast sc;
//	for (std::list<SM_CAST_SPELL_END_Packet*>::iterator current = packethandler->castspelllist->begin(); current != packethandler->castspelllist->end(); current++) {
//		std::vector<SpellHit> hl = (*current)->spellhitlist;
//		for (size_t i = 0; i < hl.size(); i++) {
//			sc = Spellcast();
//			sc.damage = hl[i].damage;
//			sc.caster = (*current)->objectid;
//			sc.attackstatus = hl[i].attackstatus;
//			sc.spellid = (*current)->spellid;
//			sc.targetid = hl[i].targetid;
//			scl.push_back(sc);
//		}
//
//	}
//	return scl;
//}
//
//std::vector<AutoAttack> getAttackList() {
//	std::vector<AutoAttack> scl = std::vector<AutoAttack>();
//	AutoAttack sc;
//	for (std::list<SM_ATTACK_Packet*>::iterator current = packethandler->normalattacklist->begin(); current != packethandler->normalattacklist->end(); current++) {
//		std::vector<AttackHit> hl = (*current)->attacklist;
//		for (size_t i = 0; i < hl.size(); i++) {
//			sc = AutoAttack();
//			sc.damage = hl[i].damage;
//			sc.attacker = (*current)->attackerid;
//			sc.attackstatus = (*current)->attackstatus;
//			sc.attackstatus2 = hl[i].attackstatus;
//			sc.attackno = (*current)->attackno;
//			sc.targetid = (*current)->targetid;
//			scl.push_back(sc);
//		}
//
//	}
//	return scl;
//}
//
//
//
//std::vector<Attackstatus> getAttackStatusList() {
//	std::vector<Attackstatus> asl = std::vector<Attackstatus>();
//	Attackstatus as;
//	for (std::list<SM_ATTACK_STATUS_Packet*>::iterator current = packethandler->attackstatuslist->begin(); current != packethandler->attackstatuslist->end(); current++) {
//		as = Attackstatus();
//		as.casterid = (*current)->casterid;
//		as.skillid = (*current)->skillid;
//		as.targetid = (*current)->targetid;
//		as.type = (*current)->type;
//		as.type2 = (*current)->type2;
//		as.type3 = (*current)->type3;
//		as.value = (*current)->value;
//		asl.push_back(as);
//	}
//	return asl;
//}





//for (std::list<SM_CAST_SPELL_END_Packet*>::iterator i = castspelllist->begin(); i != castspelllist->end(); i++)
//delete(*i);
//castspelllist->clear();
//
//for (std::list<SM_ATTACK_STATUS_Packet*>::iterator i = attackstatuslist->begin(); i != attackstatuslist->end(); i++)
//delete(*i);
//attackstatuslist->clear();
//
//for (std::list<SM_ATTACK_Packet*>::iterator i = normalattacklist->begin(); i != normalattacklist->end(); i++)
//delete(*i);
//normalattacklist->clear();