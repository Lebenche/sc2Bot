﻿#include <iostream>

#include "Mazzer_bot.h"
#include "sc2api/sc2_api.h"
#include "Strategys.h"

//FILTRES ET FONCTIONS POUR IDENTIFIER DES UNITS OU DES ABILITY
struct IsVespeneGeyser {
	bool operator()(const Unit& unit) {
		switch (unit.unit_type.ToType()) {
		case UNIT_TYPEID::NEUTRAL_VESPENEGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER: return true;
		default: return false;
		}
	}
};

struct IsWorker {
	bool operator()(const Unit& unit) {
		switch (unit.unit_type.ToType()) {
		case UNIT_TYPEID::PROTOSS_PROBE: return true;
		case UNIT_TYPEID::ZERG_DRONE: return true;
		case UNIT_TYPEID::TERRAN_SCV: return true;
		default: return false;
		}
	}
};

struct IsFlying {
	bool operator()(const Unit& unit) {
		switch (unit.unit_type.ToType()) {
		case UNIT_TYPEID::TERRAN_BARRACKSFLYING: return true;
		case UNIT_TYPEID::TERRAN_FACTORYFLYING: return true;
		case UNIT_TYPEID::TERRAN_STARPORTFLYING: return true;
		default: return false;
		}
	}
};

struct IsTownHall {
	bool operator()(const Unit& unit) {
		switch (unit.unit_type.ToType()) {
		case UNIT_TYPEID::ZERG_HATCHERY: return true;
		case UNIT_TYPEID::ZERG_LAIR: return true;
		case UNIT_TYPEID::ZERG_HIVE: return true;
		case UNIT_TYPEID::TERRAN_COMMANDCENTER: return true;
		case UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING: return true;
		case UNIT_TYPEID::TERRAN_ORBITALCOMMAND: return true;
		case UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
		case UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
		case UNIT_TYPEID::PROTOSS_NEXUS: return true;
		default: return false;
		}
	}
};

struct IsArmy {
	bool operator()(const sc2::Unit & unit)
	{
		switch (unit.unit_type.ToType())
		{
		case UNIT_TYPEID::TERRAN_BANSHEE: return true;
		case UNIT_TYPEID::TERRAN_BATTLECRUISER: return true;
		case UNIT_TYPEID::TERRAN_CYCLONE: return true;
		case UNIT_TYPEID::TERRAN_GHOST: return true;
		case UNIT_TYPEID::TERRAN_HELLION: return true;
		case UNIT_TYPEID::TERRAN_HELLIONTANK: return true;
		case UNIT_TYPEID::TERRAN_LIBERATOR: return true;
		case UNIT_TYPEID::TERRAN_LIBERATORAG: return true;
		case UNIT_TYPEID::TERRAN_MARAUDER: return true;
		case UNIT_TYPEID::TERRAN_MARINE: return true;
		case UNIT_TYPEID::TERRAN_MEDIVAC: return true;
		case UNIT_TYPEID::TERRAN_MULE: return true;
		case UNIT_TYPEID::TERRAN_RAVEN: return true;
		case UNIT_TYPEID::TERRAN_REAPER: return true;
		//case UNIT_TYPEID::TERRAN_SCV: return true;
		case UNIT_TYPEID::TERRAN_SIEGETANK: return true;
		case UNIT_TYPEID::TERRAN_SIEGETANKSIEGED: return true;
		case UNIT_TYPEID::TERRAN_THOR: return true;
		case UNIT_TYPEID::TERRAN_THORAP: return true;
		case UNIT_TYPEID::TERRAN_VIKINGASSAULT: return true;
		case UNIT_TYPEID::TERRAN_VIKINGFIGHTER: return true;
		case UNIT_TYPEID::ZERG_BANELING: return true;
		case UNIT_TYPEID::ZERG_BROODLING: return true;
		case UNIT_TYPEID::ZERG_BROODLORD: return true;
		case UNIT_TYPEID::ZERG_BROODLORDCOCOON: return true;
		case UNIT_TYPEID::ZERG_CHANGELING: return true;
		case UNIT_TYPEID::ZERG_CHANGELINGMARINE: return true;
		case UNIT_TYPEID::ZERG_CHANGELINGMARINESHIELD: return true;
		case UNIT_TYPEID::ZERG_CHANGELINGZEALOT: return true;
		case UNIT_TYPEID::ZERG_CHANGELINGZERGLING: return true;
		case UNIT_TYPEID::ZERG_CHANGELINGZERGLINGWINGS: return true;
		case UNIT_TYPEID::ZERG_CORRUPTOR: return true;
		case UNIT_TYPEID::ZERG_DRONE: return true;
		case UNIT_TYPEID::ZERG_HYDRALISK: return true;
		case UNIT_TYPEID::ZERG_INFESTEDTERRANSEGG: return true;
		case UNIT_TYPEID::ZERG_INFESTOR: return true;
		case UNIT_TYPEID::ZERG_INFESTORTERRAN: return true;
		case UNIT_TYPEID::ZERG_LOCUSTMP: return true;
		case UNIT_TYPEID::ZERG_LOCUSTMPFLYING: return true;
		case UNIT_TYPEID::ZERG_LURKERMP: return true;
		case UNIT_TYPEID::ZERG_MUTALISK: return true;
		case UNIT_TYPEID::ZERG_OVERLORD: return true;
		case UNIT_TYPEID::ZERG_OVERLORDTRANSPORT: return true;
		case UNIT_TYPEID::ZERG_OVERSEER: return true;
		case UNIT_TYPEID::ZERG_QUEEN: return true;
		case UNIT_TYPEID::ZERG_RAVAGER: return true;
		case UNIT_TYPEID::ZERG_ROACH: return true;
		case UNIT_TYPEID::ZERG_SPINECRAWLERUPROOTED: return true;
		case UNIT_TYPEID::ZERG_SPORECRAWLERUPROOTED: return true;
		case UNIT_TYPEID::ZERG_SWARMHOSTBURROWEDMP: return true;
		case UNIT_TYPEID::ZERG_SWARMHOSTMP: return true;
		case UNIT_TYPEID::ZERG_TRANSPORTOVERLORDCOCOON: return true;
		case UNIT_TYPEID::ZERG_ULTRALISK: return true;
		case UNIT_TYPEID::ZERG_VIPER: return true;
		case UNIT_TYPEID::ZERG_ZERGLING: return true;
		case UNIT_TYPEID::PROTOSS_ADEPT: return true;
		case UNIT_TYPEID::PROTOSS_ARCHON: return true;
		case UNIT_TYPEID::PROTOSS_CARRIER: return true;
		case UNIT_TYPEID::PROTOSS_COLOSSUS: return true;
		case UNIT_TYPEID::PROTOSS_DARKTEMPLAR: return true;
		case UNIT_TYPEID::PROTOSS_DISRUPTOR: return true;
		case UNIT_TYPEID::PROTOSS_HIGHTEMPLAR: return true;
		case UNIT_TYPEID::PROTOSS_IMMORTAL: return true;
		case UNIT_TYPEID::PROTOSS_INTERCEPTOR: return true;
		case UNIT_TYPEID::PROTOSS_MOTHERSHIP: return true;
		case UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE: return true;
		case UNIT_TYPEID::PROTOSS_OBSERVER: return true;
		case UNIT_TYPEID::PROTOSS_ORACLE: return true;
		case UNIT_TYPEID::PROTOSS_PHOENIX: return true;
		case UNIT_TYPEID::PROTOSS_PROBE: return true;
		case UNIT_TYPEID::PROTOSS_SENTRY: return true;
		case UNIT_TYPEID::PROTOSS_STALKER: return true;
		case UNIT_TYPEID::PROTOSS_TEMPEST: return true;
		case UNIT_TYPEID::PROTOSS_VOIDRAY: return true;
		case UNIT_TYPEID::PROTOSS_WARPPRISM: return true;
		case UNIT_TYPEID::PROTOSS_ZEALOT: return true;
		default: return false;
		}
	}
};

struct IsBuilding {
	bool operator()(const sc2::Unit & unit)
	{
		switch (unit.unit_type.ToType())
		{
		case sc2::UNIT_TYPEID::TERRAN_ARMORY:           return true;
		case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:     return true;
		case sc2::UNIT_TYPEID::ZERG_BANELINGNEST:       return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKS:         return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR:  return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB:  return true;
		case sc2::UNIT_TYPEID::TERRAN_BUNKER:           return true;
		case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:    return true;
		case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE: return true;
		case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:      return true;
		case sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY:   return true;
		case sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER:   return true;
		case sc2::UNIT_TYPEID::ZERG_EXTRACTOR:          return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORY:          return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR:   return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB:   return true;
		case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:     return true;
		case sc2::UNIT_TYPEID::PROTOSS_FORGE:           return true;
		case sc2::UNIT_TYPEID::TERRAN_FUSIONCORE:       return true;
		case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:         return true;
		case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:        return true;
		case sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY:     return true;
		case sc2::UNIT_TYPEID::ZERG_HATCHERY:           return true;
		case sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN:       return true;
		case sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT:     return true;
		case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:    return true;
		case sc2::UNIT_TYPEID::PROTOSS_NEXUS:           return true;
		case sc2::UNIT_TYPEID::ZERG_NYDUSCANAL:         return true;
		case sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK:       return true;
		case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:    return true;
		case sc2::UNIT_TYPEID::PROTOSS_PYLON:           return true;
		case sc2::UNIT_TYPEID::TERRAN_REFINERY:         return true;
		case sc2::UNIT_TYPEID::ZERG_ROACHWARREN:        return true;
		case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:     return true;
		case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY: return true;
		case sc2::UNIT_TYPEID::TERRAN_SENSORTOWER:      return true;
		case sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL:       return true;
		case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:       return true;
		case sc2::UNIT_TYPEID::ZERG_SPIRE:              return true;
		case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:       return true;
		case sc2::UNIT_TYPEID::PROTOSS_STARGATE:        return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORT:         return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR:  return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB:  return true;
		case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT:      return true;
		case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:  return true;
		case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL: return true;
		case sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN:    return true;
		case sc2::UNIT_TYPEID::ZERG_HIVE:               return true;
		case sc2::UNIT_TYPEID::ZERG_LAIR:               return true;
		case sc2::UNIT_TYPEID::ZERG_GREATERSPIRE:       return true;
		case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:   return true;
		case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
		case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED: return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING:	return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING:	return true;
		case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING: return true;
		case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING:	return true;
		case sc2::UNIT_TYPEID::TERRAN_TECHLAB:			return true;

		default: return false;
		}
	}
};

bool IsUpgrade(sc2::ABILITY_ID ab) {

	switch (ab)
	{
	case ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD:return true;
	case ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1:return true;
	case ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2:return true;
	case ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1:return true;
	case ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2:return true;
	case ABILITY_ID::RESEARCH_DRILLINGCLAWS:return true;
	default:
		return false;
	}

}

bool IsABuilding(UNIT_TYPEID Uid) {
	
		switch (Uid)
		{
		case sc2::UNIT_TYPEID::TERRAN_ARMORY:           return true;
		case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:     return true;
		case sc2::UNIT_TYPEID::ZERG_BANELINGNEST:       return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKS:         return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR:  return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB:  return true;
		case sc2::UNIT_TYPEID::TERRAN_BUNKER:           return true;
		case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:    return true;
		case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE: return true;
		case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:      return true;
		case sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY:   return true;
		case sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER:   return true;
		case sc2::UNIT_TYPEID::ZERG_EXTRACTOR:          return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORY:          return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR:   return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB:   return true;
		case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:     return true;
		case sc2::UNIT_TYPEID::PROTOSS_FORGE:           return true;
		case sc2::UNIT_TYPEID::TERRAN_FUSIONCORE:       return true;
		case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:         return true;
		case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:        return true;
		case sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY:     return true;
		case sc2::UNIT_TYPEID::ZERG_HATCHERY:           return true;
		case sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN:       return true;
		case sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT:     return true;
		case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:    return true;
		case sc2::UNIT_TYPEID::PROTOSS_NEXUS:           return true;
		case sc2::UNIT_TYPEID::ZERG_NYDUSCANAL:         return true;
		case sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK:       return true;
		case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:    return true;
		case sc2::UNIT_TYPEID::PROTOSS_PYLON:           return true;
		case sc2::UNIT_TYPEID::TERRAN_REFINERY:         return true;
		case sc2::UNIT_TYPEID::ZERG_ROACHWARREN:        return true;
		case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:     return true;
		case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY: return true;
		case sc2::UNIT_TYPEID::TERRAN_SENSORTOWER:      return true;
		case sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL:       return true;
		case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:       return true;
		case sc2::UNIT_TYPEID::ZERG_SPIRE:              return true;
		case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:       return true;
		case sc2::UNIT_TYPEID::PROTOSS_STARGATE:        return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORT:         return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR:  return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB:  return true;
		case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT:      return true;
		case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:  return true;
		case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL: return true;
		case sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN:    return true;
		case sc2::UNIT_TYPEID::ZERG_HIVE:               return true;
		case sc2::UNIT_TYPEID::ZERG_LAIR:               return true;
		case sc2::UNIT_TYPEID::ZERG_GREATERSPIRE:       return true;
		case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:   return true;
		case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
		case sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED: return true;
		case sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING:	return true;
		case sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING:	return true;
		case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING: return true;
		case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
		case sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING:	return true;
		case sc2::UNIT_TYPEID::TERRAN_TECHLAB:			return true;

		default: return false;
		}
	
};

bool IsAnArmy(UNIT_TYPEID unit_type) {
	switch (unit_type)
	{
	case UNIT_TYPEID::TERRAN_BANSHEE: return true;
	case UNIT_TYPEID::TERRAN_BATTLECRUISER: return true;
	case UNIT_TYPEID::TERRAN_CYCLONE: return true;
	case UNIT_TYPEID::TERRAN_GHOST: return true;
	case UNIT_TYPEID::TERRAN_HELLION: return true;
	case UNIT_TYPEID::TERRAN_HELLIONTANK: return true;
	case UNIT_TYPEID::TERRAN_LIBERATOR: return true;
	case UNIT_TYPEID::TERRAN_LIBERATORAG: return true;
	case UNIT_TYPEID::TERRAN_MARAUDER: return true;
	case UNIT_TYPEID::TERRAN_MARINE: return true;
	case UNIT_TYPEID::TERRAN_MEDIVAC: return true;
	case UNIT_TYPEID::TERRAN_MULE: return true;
	case UNIT_TYPEID::TERRAN_RAVEN: return true;
	case UNIT_TYPEID::TERRAN_REAPER: return true;
	case UNIT_TYPEID::TERRAN_SIEGETANK: return true;
	case UNIT_TYPEID::TERRAN_SIEGETANKSIEGED: return true;
	case UNIT_TYPEID::TERRAN_THOR: return true;
	case UNIT_TYPEID::TERRAN_THORAP: return true;
	case UNIT_TYPEID::TERRAN_VIKINGASSAULT: return true;
	case UNIT_TYPEID::TERRAN_VIKINGFIGHTER: return true;
	case UNIT_TYPEID::ZERG_BANELING: return true;
	case UNIT_TYPEID::ZERG_BROODLING: return true;
	case UNIT_TYPEID::ZERG_BROODLORD: return true;
	case UNIT_TYPEID::ZERG_BROODLORDCOCOON: return true;
	case UNIT_TYPEID::ZERG_CHANGELING: return true;
	case UNIT_TYPEID::ZERG_CHANGELINGMARINE: return true;
	case UNIT_TYPEID::ZERG_CHANGELINGMARINESHIELD: return true;
	case UNIT_TYPEID::ZERG_CHANGELINGZEALOT: return true;
	case UNIT_TYPEID::ZERG_CHANGELINGZERGLING: return true;
	case UNIT_TYPEID::ZERG_CHANGELINGZERGLINGWINGS: return true;
	case UNIT_TYPEID::ZERG_CORRUPTOR: return true;
	case UNIT_TYPEID::ZERG_DRONE: return true;
	case UNIT_TYPEID::ZERG_HYDRALISK: return true;
	case UNIT_TYPEID::ZERG_INFESTEDTERRANSEGG: return true;
	case UNIT_TYPEID::ZERG_INFESTOR: return true;
	case UNIT_TYPEID::ZERG_INFESTORTERRAN: return true;
	case UNIT_TYPEID::ZERG_LOCUSTMP: return true;
	case UNIT_TYPEID::ZERG_LOCUSTMPFLYING: return true;
	case UNIT_TYPEID::ZERG_LURKERMP: return true;
	case UNIT_TYPEID::ZERG_MUTALISK: return true;
	case UNIT_TYPEID::ZERG_OVERLORD: return true;
	case UNIT_TYPEID::ZERG_OVERLORDTRANSPORT: return true;
	case UNIT_TYPEID::ZERG_OVERSEER: return true;
	case UNIT_TYPEID::ZERG_QUEEN: return true;
	case UNIT_TYPEID::ZERG_RAVAGER: return true;
	case UNIT_TYPEID::ZERG_ROACH: return true;
	case UNIT_TYPEID::ZERG_SPINECRAWLERUPROOTED: return true;
	case UNIT_TYPEID::ZERG_SPORECRAWLERUPROOTED: return true;
	case UNIT_TYPEID::ZERG_SWARMHOSTBURROWEDMP: return true;
	case UNIT_TYPEID::ZERG_SWARMHOSTMP: return true;
	case UNIT_TYPEID::ZERG_TRANSPORTOVERLORDCOCOON: return true;
	case UNIT_TYPEID::ZERG_ULTRALISK: return true;
	case UNIT_TYPEID::ZERG_VIPER: return true;
	case UNIT_TYPEID::ZERG_ZERGLING: return true;
	case UNIT_TYPEID::PROTOSS_ADEPT: return true;
	case UNIT_TYPEID::PROTOSS_ARCHON: return true;
	case UNIT_TYPEID::PROTOSS_CARRIER: return true;
	case UNIT_TYPEID::PROTOSS_COLOSSUS: return true;
	case UNIT_TYPEID::PROTOSS_DARKTEMPLAR: return true;
	case UNIT_TYPEID::PROTOSS_DISRUPTOR: return true;
	case UNIT_TYPEID::PROTOSS_HIGHTEMPLAR: return true;
	case UNIT_TYPEID::PROTOSS_IMMORTAL: return true;
	case UNIT_TYPEID::PROTOSS_INTERCEPTOR: return true;
	case UNIT_TYPEID::PROTOSS_MOTHERSHIP: return true;
	case UNIT_TYPEID::PROTOSS_MOTHERSHIPCORE: return true;
	case UNIT_TYPEID::PROTOSS_OBSERVER: return true;
	case UNIT_TYPEID::PROTOSS_ORACLE: return true;
	case UNIT_TYPEID::PROTOSS_PHOENIX: return true;
	case UNIT_TYPEID::PROTOSS_PROBE: return true;
	case UNIT_TYPEID::PROTOSS_SENTRY: return true;
	case UNIT_TYPEID::PROTOSS_STALKER: return true;
	case UNIT_TYPEID::PROTOSS_TEMPEST: return true;
	case UNIT_TYPEID::PROTOSS_VOIDRAY: return true;
	case UNIT_TYPEID::PROTOSS_WARPPRISM: return true;
	case UNIT_TYPEID::PROTOSS_ZEALOT: return true;
	default: return false;
	}
}

bool IsExtandable(sc2::ABILITY_ID ab) {

	switch (ab)
	{
	case ABILITY_ID::BUILD_BARRACKS:return true;
	case ABILITY_ID::BUILD_FACTORY:return true;
	case ABILITY_ID::BUILD_STARPORT:return true;
	default:
		return false;
	}

}

bool IsAWorker(UNIT_TYPEID ID) {
	switch (ID) {
	case UNIT_TYPEID::PROTOSS_PROBE: return true;
	case UNIT_TYPEID::ZERG_DRONE: return true;
	case UNIT_TYPEID::TERRAN_SCV: return true;
	default: return false;
	}
}

bool IsAnExtension(UNIT_TYPEID ID) {
	switch (ID) {
	case UNIT_TYPEID::TERRAN_REACTOR: return true;
	case UNIT_TYPEID::TERRAN_TECHLAB: return true;
	default: return false;
	}
}

bool IsATownHall(UNIT_TYPEID ID) {
	switch (ID) {
	case UNIT_TYPEID::ZERG_HATCHERY: return true;
	case UNIT_TYPEID::ZERG_LAIR: return true;
	case UNIT_TYPEID::ZERG_HIVE: return true;
	case UNIT_TYPEID::TERRAN_COMMANDCENTER: return true;
	case UNIT_TYPEID::TERRAN_ORBITALCOMMAND: return true;
	case UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
	case UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
	case UNIT_TYPEID::PROTOSS_NEXUS: return true;
	default: return false;
	
	}
}
//

//BUILDINGS

Mz_Order CommandCenter(UNIT_TYPEID::TERRAN_COMMANDCENTER, ABILITY_ID::BUILD_COMMANDCENTER, 400, 0);
Mz_Order OrbitalCommand(UNIT_TYPEID::TERRAN_ORBITALCOMMAND, ABILITY_ID::MORPH_ORBITALCOMMAND, 150, 0, UNIT_TYPEID::TERRAN_COMMANDCENTER);
Mz_Order PlanetaryFortress(UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, ABILITY_ID::MORPH_PLANETARYFORTRESS, 150, 150);
Mz_Order SupplyDepot(UNIT_TYPEID::TERRAN_SUPPLYDEPOT, ABILITY_ID::BUILD_SUPPLYDEPOT, 100, 0);
Mz_Order Refinery(UNIT_TYPEID::TERRAN_REFINERY, ABILITY_ID::BUILD_REFINERY, 75, 0);
Mz_Order Barracks(UNIT_TYPEID::TERRAN_BARRACKS, ABILITY_ID::BUILD_BARRACKS, 150, 0);
Mz_Order EngineeringBay(UNIT_TYPEID::TERRAN_ENGINEERINGBAY, ABILITY_ID::BUILD_ENGINEERINGBAY, 125, 0);
Mz_Order Bunker(UNIT_TYPEID::TERRAN_BUNKER, ABILITY_ID::BUILD_BUNKER, 100, 0);
Mz_Order MissileTurret(UNIT_TYPEID::TERRAN_MISSILETURRET, ABILITY_ID::BUILD_MISSILETURRET, 100, 0);
Mz_Order SensorTower(UNIT_TYPEID::TERRAN_SENSORTOWER, ABILITY_ID::BUILD_SENSORTOWER, 125, 100);
Mz_Order Factory(UNIT_TYPEID::TERRAN_FACTORY, ABILITY_ID::BUILD_FACTORY, 150, 100);
Mz_Order GhostAcademy(UNIT_TYPEID::TERRAN_GHOSTACADEMY, ABILITY_ID::BUILD_GHOSTACADEMY, 150, 50);
Mz_Order Armory(UNIT_TYPEID::TERRAN_ARMORY, ABILITY_ID::BUILD_ARMORY, 150, 100);
Mz_Order Starport(UNIT_TYPEID::TERRAN_STARPORT, ABILITY_ID::BUILD_STARPORT, 150, 100);
Mz_Order FusionCore(UNIT_TYPEID::TERRAN_FUSIONCORE, ABILITY_ID::BUILD_FUSIONCORE, 150, 150);
Mz_Order BTechLab(UNIT_TYPEID::TERRAN_TECHLAB, ABILITY_ID::BUILD_TECHLAB, 50, 25, UNIT_TYPEID::TERRAN_BARRACKS);
Mz_Order STechLab(UNIT_TYPEID::TERRAN_TECHLAB, ABILITY_ID::BUILD_TECHLAB, 50, 25, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order FTechLab(UNIT_TYPEID::TERRAN_TECHLAB, ABILITY_ID::BUILD_TECHLAB, 50, 25, UNIT_TYPEID::TERRAN_FACTORY);
Mz_Order BReactor(UNIT_TYPEID::TERRAN_REACTOR, ABILITY_ID::BUILD_REACTOR, 50, 50, UNIT_TYPEID::TERRAN_BARRACKS);
Mz_Order SReactor(UNIT_TYPEID::TERRAN_REACTOR, ABILITY_ID::BUILD_REACTOR, 50, 50, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order FReactor(UNIT_TYPEID::TERRAN_REACTOR, ABILITY_ID::BUILD_REACTOR, 50, 50, UNIT_TYPEID::TERRAN_FACTORY);

//UNITS

Mz_Order SCV(UNIT_TYPEID::TERRAN_SCV, ABILITY_ID::TRAIN_SCV, 50, 0, UNIT_TYPEID::TERRAN_COMMANDCENTER);
Mz_Order MULE(UNIT_TYPEID::TERRAN_MULE, ABILITY_ID::EFFECT_CALLDOWNMULE, 0, 0);
Mz_Order Marine(UNIT_TYPEID::TERRAN_MARINE, ABILITY_ID::TRAIN_MARINE, 50, 0, UNIT_TYPEID::TERRAN_BARRACKS);
Mz_Order Marauder(UNIT_TYPEID::TERRAN_MARAUDER, ABILITY_ID::TRAIN_MARAUDER, 100, 25, UNIT_TYPEID::TERRAN_BARRACKS);
Mz_Order Reaper(UNIT_TYPEID::TERRAN_REAPER, ABILITY_ID::TRAIN_REAPER, 50, 50, UNIT_TYPEID::TERRAN_BARRACKS);
Mz_Order Ghost(UNIT_TYPEID::TERRAN_GHOST, ABILITY_ID::TRAIN_GHOST, 150, 125, UNIT_TYPEID::TERRAN_BARRACKS);
Mz_Order Hellion(UNIT_TYPEID::TERRAN_HELLION, ABILITY_ID::TRAIN_HELLION, 100, 0, UNIT_TYPEID::TERRAN_FACTORY);
Mz_Order WidowMine(UNIT_TYPEID::TERRAN_WIDOWMINE, ABILITY_ID::TRAIN_WIDOWMINE, 75, 25, UNIT_TYPEID::TERRAN_FACTORY);
Mz_Order SiegeTank(UNIT_TYPEID::TERRAN_SIEGETANK, ABILITY_ID::TRAIN_SIEGETANK, 150, 125, UNIT_TYPEID::TERRAN_FACTORY);
Mz_Order Cyclone(UNIT_TYPEID::TERRAN_CYCLONE, ABILITY_ID::TRAIN_CYCLONE, 150, 100, UNIT_TYPEID::TERRAN_FACTORY);
Mz_Order Thor(UNIT_TYPEID::TERRAN_THOR, ABILITY_ID::TRAIN_THOR, 300, 200, UNIT_TYPEID::TERRAN_FACTORY);
Mz_Order Viking(UNIT_TYPEID::TERRAN_VIKINGFIGHTER, ABILITY_ID::TRAIN_VIKINGFIGHTER, 150, 75, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order Medivac(UNIT_TYPEID::TERRAN_MEDIVAC, ABILITY_ID::TRAIN_MEDIVAC, 100, 100, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order Liberator(UNIT_TYPEID::TERRAN_LIBERATOR, ABILITY_ID::TRAIN_LIBERATOR, 150, 150, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order Banshee(UNIT_TYPEID::TERRAN_BANSHEE, ABILITY_ID::TRAIN_BANSHEE, 150, 100, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order Raven(UNIT_TYPEID::TERRAN_RAVEN, ABILITY_ID::TRAIN_RAVEN, 100, 200, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order Battlecruiser(UNIT_TYPEID::TERRAN_BATTLECRUISER, ABILITY_ID::TRAIN_BATTLECRUISER, 400, 300, UNIT_TYPEID::TERRAN_STARPORT);
Mz_Order PlaneterayFortress(UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, ABILITY_ID::MORPH_PLANETARYFORTRESS, 150, 150);
Mz_Order AutoTurret(UNIT_TYPEID::TERRAN_AUTOTURRET, ABILITY_ID::EFFECT_AUTOTURRET, 0, 0);
Mz_Order PointDefenseDrone(UNIT_TYPEID::TERRAN_POINTDEFENSEDRONE, ABILITY_ID::EFFECT_POINTDEFENSEDRONE, 0, 0);

//Ability upgrade

Mz_Order CloakingField(UNIT_TYPEID::TERRAN_STARPORTTECHLAB, ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD, 100, 100, UNIT_TYPEID::TERRAN_STARPORTTECHLAB);
Mz_Order VnSLvL1(UNIT_TYPEID::TERRAN_ARMORY, ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL1, 100, 100, UNIT_TYPEID::TERRAN_ARMORY);
Mz_Order VnSLvL2(UNIT_TYPEID::TERRAN_ARMORY, ABILITY_ID::RESEARCH_TERRANVEHICLEANDSHIPPLATINGLEVEL2, 100, 100, UNIT_TYPEID::TERRAN_ARMORY);
Mz_Order VWLvL1(UNIT_TYPEID::TERRAN_ARMORY, ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL1, 100, 100, UNIT_TYPEID::TERRAN_ARMORY);
Mz_Order VWLvL2(UNIT_TYPEID::TERRAN_ARMORY, ABILITY_ID::RESEARCH_TERRANVEHICLEWEAPONSLEVEL2, 100, 100, UNIT_TYPEID::TERRAN_ARMORY);
Mz_Order DrillingClaws(UNIT_TYPEID::TERRAN_FACTORYTECHLAB, ABILITY_ID::RESEARCH_DRILLINGCLAWS, 100, 100);



//Les Build Order à suivre

//le secours
std::vector<Mz_Order> UnitOrdersAfterFlee = {SupplyDepot,Refinery,Barracks,SupplyDepot};
std::vector<int32_t> nb_worker = { 14,15,16,19,19,20,20,20,20,20,20,20,21,22,23,25,26,27,28,28,30,32,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };

std::vector<Mz_Order> UnitOrdersArmyAfterFlee = { Marine,Marine }; //BO spécial armé pour construire en continu (il boucle sur lui même)
std::vector<int32_t> nb_ArmyAfterFlee = {10,2};


Mz_BuildOrder BOFlee = Mz_BuildOrder(UnitOrdersAfterFlee, nb_worker);
Mz_BuildOrder BOAFlee = Mz_BuildOrder(UnitOrdersArmyAfterFlee, nb_ArmyAfterFlee, true);

//le main
std::vector<Mz_Order> UnitOrders = { SupplyDepot,Refinery,Barracks,Refinery,BReactor,SupplyDepot,Marine,Marine,Marine,Marine,CommandCenter,Bunker,EngineeringBay,Refinery,Factory,FTechLab,SupplyDepot,Starport,STechLab,CloakingField,SupplyDepot,Marine };

std::vector<Mz_Order> UnitOrdersArmy = { Marine,SiegeTank,Banshee,Marine};//BO Spécial armée de secours
std::vector<int32_t> nb_Army = { 5,2,3,1 };

Mz_BuildOrder BOA = Mz_BuildOrder(UnitOrdersArmy, nb_Army,true);
Mz_BuildOrder BO = Mz_BuildOrder(UnitOrders, nb_worker);






bool islift = false;
bool ismoving = false;
bool unload = false;
bool Fleeing = false;


Mazzer_bot::Mazzer_bot()
{
	SearchParams.radiuses_ = { 5.3f,6.4f,9.5f,7.0f};
	SearchParams.circle_step_size_ = 0.5f;
	SearchParams.cluster_distance_ = 15.0f;

	SearchParamsA.radiuses_ = {13.2f,15.0f,15.5f,16.3f,16.7f };
	SearchParamsA.circle_step_size_ = 10.0f;
	SearchParamsA.cluster_distance_ = 15.0f;

	SearchParamsB.radiuses_ = { 17.0f };
	SearchParamsB.circle_step_size_ = 20.0f;
	SearchParamsB.cluster_distance_ = 25.0f;

	//Les différents suivis initialisé
	step = 0;
	W_inTraining = 0;
	Construct_check_decrease = false;
	nb_vespene = 0;
	nb_building_suround = 0;
	base_step_vespenes = 0;
	base_step_building = 0;
	check_prev_step = 0;
	command_to_count = 0;
	switchbo = false;
	allIn = true;
	startBot = false;
	onload = false;
	Bo_secours = false;

}
void Mazzer_bot::OnGameStart()

{
	expansions_ = search::CalculateExpansionLocations(Observation(), Query());
	
	//Pour le suivi du nombre de worker en création (à perfectionner)
	W_inTraining = Observation()->GetFoodWorkers();

	StartPosition = new sc2::Point3D(Observation()->GetStartLocation());
	game_info_ = new sc2::GameInfo(Observation()->GetGameInfo());

	SetupRushLocation(Observation());

	//Ajout de la 1ère base au groupe correspondant
	Units Base = Observation()->GetUnits(Unit::Alliance::Self, IsTownHall());
	AddToBG(Base[0], false, true);

	//On regarde où on commence
	if(Observation()->GetStartLocation().x - game_info_->enemy_start_locations.front().x>0) startBot = true;

	//Parametres pour placer les batiments avec add-on, afin d'avoir le plus de chance de ne pas rater l'ajout de l'add-on
	if (startBot) {
		SearchParamsA.radiuses_ = { 13.2f,15.0f,15.5f,16.3f,16.7f };
		SearchParamsA.circle_step_size_ = 10.0f;
		SearchParamsA.cluster_distance_ = 15.0f;

	}
	else {
		SearchParamsA.radiuses_ = {13.2f,14.3f,15.4f,15.6f,15.6f };
		SearchParamsA.circle_step_size_ = 10.0f;
		SearchParamsA.cluster_distance_ = 15.0f;
	}

	/*const Units NewUnits = Observation()->GetUnits(sc2::Unit::Alliance::Self);
	for (auto &u : NewUnits)
	{
		if (u->unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER)
		{
			Actions()->UnitCommand(u, ABILITY_ID::TRAIN_SCV);
			break;
		}
	}
	*/
}

void Mazzer_bot::OnStep() {
	//BuildVespeneG();
	const ObservationInterface* observation = Observation();
	//CheckSupply(observation);
	//CheckSCV(observation);
	//TrainArmy(observation);
	int frames_to_skip = 4;
	if (observation->GetGameLoop() % frames_to_skip != 0) {
		return;
	}
	if (allIn) {
		AttackBase(observation);
	}
	else {

		for (auto& ThisBG : PerUnitsBG)
		{
			if (ShouldRetreat(ThisBG) && ThisBG.Attacking) {
				MakeUnitBGRetreat(ThisBG,*StartPosition);
			}
		}
	}
	
	if (Fleeing) {
		Flee();
		step = 0;
		switchbo = false;
		
		SearchParamsA.radiuses_ = { 5.3f,6.4f,9.5f,7.0f };
		SearchParamsA.circle_step_size_ = 0.5f;
		SearchParamsA.cluster_distance_ = 15.0f;

		 
	}
	else {
		if (!Bo_secours) {
			if (!switchbo) {
				if (step < BO.UnitOrder.size() - 1) {

					Follow_BO(BO);

				}
				else {
					switchbo = !switchbo;
					step = 0;
					return;
				}
			}
			else {
				CheckSupply(Observation());
				if (step < BOA.UnitOrder.size() - 1) {
					Follow_BO(BOA);
					CheckSCV(Observation());
				}
				else {

					step = 0;
					return;
				}

			}
		}
		else {
			if (!switchbo) {
				if (step < BOFlee.UnitOrder.size() - 1) {

					Follow_BO(BOFlee);

				}
				else {
					switchbo = !switchbo;
					step = 0;
					return;
				}
			}
			else {
				CheckSupply(Observation());
				if (step < BOAFlee.UnitOrder.size() - 1) {
					Follow_BO(BOAFlee);
					CheckSCV(Observation());
				}
				else {

					step = 0;
					return;
				}

			}

		}
	}
	
	

	



}



// On r�cup�re le Max supply actuel en comptant ne nombre de depots et de command centers construits 
int32_t Mazzer_bot::GetCurrentMaxSupply()
{
	int32_t MaxSupply = 0;
	const Units NewUnits = Observation()->GetUnits();
	for (auto &u : NewUnits)
	{
		if (u->unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER && u->build_progress == 1.0f)
		{
			MaxSupply += 15;
		}
		else if (u->unit_type == UNIT_TYPEID::TERRAN_SUPPLYDEPOT && u->build_progress == 1.0f)
		{
			MaxSupply += 8;
		}
		else if (u->unit_type == UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED && u->build_progress == 1.0f)
		{
			MaxSupply += 8;
		}

	}
	return MaxSupply;
}

// Permet de reconstruire des SCV si ces derniers sont d�truits 
void Mazzer_bot::CheckSCV(const ObservationInterface* observation) {
	Units SCV = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_SCV));
	Units bases = observation->GetUnits(Unit::Alliance::Self, IsTownHall());


	for (auto& b : bases) {
		bool ok = false;
		if (b->assigned_harvesters  < b->ideal_harvesters) {
			for (auto &order : b->orders) {
				if (order.ability_id == ABILITY_ID::TRAIN_SCV) ok = true;
			}
		if(!ok)
			Actions()->UnitCommand(b, ABILITY_ID::TRAIN_SCV);

		}
	}

}

// Fonction qui g�re les attaques sur la base ennemie
void Mazzer_bot::AttackBase(const ObservationInterface* observation) {
	const GameInfo& game_info = Observation()->GetGameInfo();
	//AllInAttack(game_info.enemy_start_locations.front());
	Observation();
	Units all = observation->GetUnits(Unit::Alliance::Self, IsArmy());
	//Units bunker = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BUNKER));
	Units banshee = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BANSHEE));
	if (UnitTypeBGExisting(UNIT_TYPEID::TERRAN_MARINE)) {
	BattleGroup_Unit_type BG = GetUnitTypeBG(UNIT_TYPEID::TERRAN_MARINE);
	if (BG.Members.size() >= 4/* && bunker.size()>=1*/)
	{
		if (BuildingTypeBGExisting(UNIT_TYPEID::TERRAN_BUNKER)) {
			BattleGroup_Building_type BGB = GetBuildingTypeBG(UNIT_TYPEID::TERRAN_BUNKER);
			const Unit* bunker = Observation()->GetUnit(BGB.Members[0]);
			
			if (bunker->passengers.size() < 4) {
				onload = true;
				for (auto& m : BG.Members)
				{
					const Unit * marine = Observation()->GetUnit(m);
					
					DeleteDeadfromBG(marine);
					Actions()->UnitCommand(bunker, ABILITY_ID::LOAD_BUNKER, marine);
					
				}
			}
			else { onload = false; }
			//allIn = AllInAttack(game_info.enemy_start_locations.front());
			//Actions()->UnitCommand(marine, ABILITY_ID::ATTACK, game_info.enemy_start_locations.front());
			//Actions()->UnitCommand(marine, ABILITY_ID::RALLY_BUILDING, bunker.front());
		}
	
	}

}	
	if (UnitTypeBGExisting(UNIT_TYPEID::TERRAN_BANSHEE)) {
		BattleGroup_Unit_type BG2 = GetUnitTypeBG(UNIT_TYPEID::TERRAN_BANSHEE);

		if (BG2.Members.size() >= 3)
		{
			MakeUnitBGAttack(UNIT_TYPEID::TERRAN_BANSHEE, game_info.enemy_start_locations.front());
			//Actions()->UnitCommand(marine, ABILITY_ID::RALLY_BUILDING, bunker.front() );

		}
	}
	if (all.size() >= 15) {
		allIn = AllInAttack(game_info.enemy_start_locations.front());
	}
}

// Ici on voudrait construire des depot si on est en manque de supply
void Mazzer_bot::CheckSupply(const ObservationInterface* observation) {
	Units depot = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_SUPPLYDEPOT));
	if (observation->GetFoodUsed() >= GetCurrentMaxSupply() - 4 ) {
		Units Workers = observation->GetUnits(Unit::Alliance::Self, IsUnit(SupplyDepot.Unit_need));
		bool ok = false;
		for (auto &worker : Workers) {

			for (auto &order : worker->orders) {
				if (order.ability_id == SupplyDepot.command) {
					ok = true;

				}
			}

		}
		if (!ok) {
			Build_Any(SupplyDepot);
			
		}
	
	}
}

// Fonction qui applique le Build order
void Mazzer_bot::Follow_BO(Mz_BuildOrder Bo) {

	const ObservationInterface* observation = Observation();
	Units depot = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_SUPPLYDEPOT));


	
	if (Bo.isArmy) {
		
		CheckStep(Bo.UnitOrder[step], Bo.UnitOrder[step], Bo.isArmy, Bo.nb_worker[step]);
		Build_Any(Bo.UnitOrder[step]);
	}
	else {
		if ((W_inTraining) < Bo.nb_worker[step]) {
			Units CC = observation->GetUnits(Unit::Alliance::Self, IsTownHall());
			for (auto &TH : CC)
			{
			
				if (observation->GetMinerals() >= 50) {
					Actions()->UnitCommand(TH, ABILITY_ID::TRAIN_SCV);
					W_inTraining += 1;
					break;
				}
			}
		}
		else {
			
			if (step > 0) {
				CheckStep(Bo.UnitOrder[step], Bo.UnitOrder[step - 1]);
				Build_Any(Bo.UnitOrder[step]);
			}
			else {
				CheckStep(Bo.UnitOrder[step], Bo.UnitOrder[step]);
				Build_Any(Bo.UnitOrder[step]);
			}
		}
	}

}

//Regarde si la step du bo est accomplie et passe à la suivante
bool Mazzer_bot::CheckStep(Mz_Order toCheck, Mz_Order prev, bool isArmy, int32_t nb_army) {
	const ObservationInterface* observation = Observation();
	int counted = 0;
	if (!isArmy){
		if (toCheck.UnitType == prev.UnitType) {    //look if the current order is the same as the previou sone
			if (step != check_prev_step && step != 0) {
				command_to_count++;           //the number of construction in progress we will check to pass step;
				check_prev_step = step;       //So it won't increment commmand_to_check each time it looks
			}

		}
		else {
			command_to_count = 0;
		}
	}
	else {
		
		command_to_count = nb_army+1;
	}
	//look if the order is already in progress
	Units Workers = observation->GetUnits(Unit::Alliance::Self, IsUnit(toCheck.Unit_need));
	
	for (auto &worker : Workers) {
		
			for (auto &order : worker->orders) {
				if (order.ability_id == toCheck.command) {
					counted++;
				
				}
			}
		
	}
	if (counted > command_to_count) {
		step++;
		
		return true;
	}
	else {
		return false;
	}
	
}

//Construit tout (Terran focus pour le moment)
bool Mazzer_bot::Build_Any(Mz_Order toBuild) {

	const ObservationInterface* observation = Observation();
	Units Workers = observation->GetUnits(Unit::Alliance::Self, IsUnit(toBuild.Unit_need));

	
	if (observation->GetMinerals() >= toBuild.mineralNeed && observation->GetVespene() >= toBuild.vespenNeed) {

		if (IsUpgrade(toBuild.command)) {   //Gestion des améliorations
			Units Upgrader = observation->GetUnits(Unit::Alliance::Self, IsUnit(toBuild.UnitType));
			for (auto &Upgrade : Upgrader) {
				Actions()->UnitCommand(Upgrade, toBuild.command);

			}
		}
		else {


			if (toBuild.UnitType == UNIT_TYPEID::TERRAN_REFINERY) {
				BuildVespeneG();

			}
			else if (!IsAWorker(toBuild.Unit_need)) {
				if (IsAnExtension(toBuild.UnitType)) {

					Point2D pos;
					Point2D loc;

					const Units NewUnits = Observation()->GetUnits(sc2::Unit::Alliance::Self, IsUnit(toBuild.Unit_need));
					for (auto &u : NewUnits)
					{
						pos = u->pos;
						
							Actions()->UnitCommand(u, toBuild.command, pos);
							Actions()->UnitCommand(u, ABILITY_ID::LIFT);
						
						 
						break;
					}
					const Units Flys = Observation()->GetUnits(sc2::Unit::Alliance::Self,IsFlying()); //Permet de detecter quand le BO a eu un soucis sur les Add-on
					if (Flys.size() > 0)Fleeing = true;
					
					

				}

				else {
					for (auto &worker : Workers) {

						Actions()->UnitCommand(worker, toBuild.command); //Construit la partie armée du BO

						

					}
				}
			}
			else if (toBuild.UnitType == UNIT_TYPEID::TERRAN_COMMANDCENTER) { //pour Extansion du territoire
				float minimum_distance = std::numeric_limits<float>::max();
				Point3D closest_expansion;
				for (const auto& expansion : expansions_) {
					float current_distance = Distance3D(*StartPosition, expansion);
					if (current_distance < .01f) {
						continue;
					}

					if (current_distance < minimum_distance) {
						if (Query()->Placement(toBuild.command, expansion)) {
							closest_expansion = expansion;
							minimum_distance = current_distance;
						}
					}
				}


				Units Workers = observation->GetUnits(Unit::Alliance::Self, IsUnit(toBuild.Unit_need));
				for (auto &worker : Workers) {
					const Unit * target = observation->GetUnit(worker->orders.back().target_unit_tag); //Pour que les vespene ne se vide pas
					if (target == nullptr || target->unit_type == UNIT_TYPEID::NEUTRAL_MINERALFIELD) {

						Actions()->UnitCommand(worker, toBuild.command, closest_expansion);

						break;
					}
				}
			}
			else {
				Point2D pos;

				


				const ObservationInterface* observation = Observation();

				Point2D loc;
				if (IsExtandable(toBuild.command)) { //Pour les batiments pouvant abriter des Add-on

					BattleGroup_Building_type Bases = GetBuildingTypeBG(UNIT_TYPEID::TERRAN_COMMANDCENTER);
					if (!Bo_secours) {
						const Unit * b = Observation()->GetUnit(Bases.Members[base_step_building]); 
						pos = b->pos;
					}
					else { 
						
						const Unit * b = Observation()->GetUnit(Bases.Members[Bases.Members.size() - 1]);
						pos = b->pos;
					}
					
					
					loc = GetRandomBuildableLocationFor(toBuild.command, pos, QueryType::None, SearchParamsA);
					
				}
				else if(toBuild.command == ABILITY_ID::BUILD_BUNKER){ //Spécial pour notre strat
					BattleGroup_Building_type Bases = GetBuildingTypeBG(UNIT_TYPEID::TERRAN_COMMANDCENTER);
					
					const Unit * b = Observation()->GetUnit(Bases.Members[Bases.Members.size()-1]);
					pos = b->pos;
					if (startBot)loc = pos - Point2D(10,0);  
					else loc = pos + Point2D(10, 0);

			
				}
				else { //Pour les batiment normaux
					BattleGroup_Building_type Bases = GetBuildingTypeBG(UNIT_TYPEID::TERRAN_COMMANDCENTER);  
					
					
						const Unit * b = Observation()->GetUnit(Bases.Members[Bases.Members.size() - 1]);
						pos = b->pos;
					
					loc = GetRandomBuildableLocationFor(toBuild.command, pos, QueryType::None, SearchParams);
				}
				Point2D cl = GetNearestVGPos(loc, observation);

				Tag closestWorker = GetNearestWorker(cl, observation);
				Actions()->UnitCommand(observation->GetUnit(closestWorker), toBuild.command, loc); //Construit autour d'une commandecenter




			}

		}

	}


	return true;
};

//Constuit une Raffinerie
void Mazzer_bot::BuildVespeneG() {
	const ObservationInterface* observation = Observation();

	Units Bases = observation->GetUnits(Unit::Alliance::Self, IsTownHall());
	Units VG = observation->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_REFINERY));


	for (auto &Base : Bases)
	{


		if (observation->GetMinerals() > 75) {
			Tag closestGeyster = GetNearestVG(Base->pos, observation);
			Point2D cl = GetNearestVGPos(Base->pos, observation);

			Tag closestWorker = GetNearestWorker(cl, observation);

			Actions()->UnitCommand(observation->GetUnit(closestWorker), ABILITY_ID::BUILD_REFINERY, observation->GetUnit(closestGeyster));
			break;
		}

	}

}

//Trouve le Geyser vespene le plus proche d'une position (tag)
Tag Mazzer_bot::GetNearestVG(sc2::Point2D Location, const ObservationInterface *observation) {

	Units geysers = observation->GetUnits(Unit::Alliance::Neutral, IsVespeneGeyser());


	//only search within this radius
	float minimum_distance = 15.0f;
	Tag closestGeyster = 0;

	for (const auto& geyser : geysers) {
		float current_distance = Distance2D(Location, geyser->pos);
		if (current_distance < minimum_distance) {
			if (Query()->Placement(ABILITY_ID::BUILD_REFINERY, geyser->pos)) {
				minimum_distance = current_distance;
				closestGeyster = geyser->tag;

			}
		}
	}
	return closestGeyster;

}

//Trouve le Geyser vespene le plus proche d'une position (pos)
Point2D Mazzer_bot::GetNearestVGPos(sc2::Point2D Location, const ObservationInterface *observation) {

	Units geysers = observation->GetUnits(Unit::Alliance::Neutral, IsVespeneGeyser());


	//only search within this radius
	float minimum_distance = 15.0f;
	Point2D closestGeyster = Point2D(0, 0);

	for (const auto& geyser : geysers) {
		float current_distance = Distance2D(Location, geyser->pos);
		if (current_distance < minimum_distance) {
			if (Query()->Placement(ABILITY_ID::BUILD_REFINERY, geyser->pos)) {
				minimum_distance = current_distance;
				closestGeyster = geyser->pos;

			}
		}
	}
	return closestGeyster;

}

//Trouve le worker le plus proche d'un position
Tag Mazzer_bot::GetNearestWorker(sc2::Point2D Location, const ObservationInterface *observation) {

	Units Workers = observation->GetUnits(Unit::Alliance::Self, IsWorker());


	//only search within this radius
	float minimum_distance = 100.0f;
	Tag closestWorker = 0;

	for (const auto& worker : Workers) {
		float current_distance = Distance2D(Location, worker->pos);
		if (current_distance < minimum_distance && !worker->orders.empty()) {
			const Unit * target = observation->GetUnit(worker->orders.back().target_unit_tag); //so vespene geyser don't get empty
			if (worker->orders.back().ability_id == ABILITY_ID::HARVEST_GATHER) {
				minimum_distance = current_distance;
				closestWorker = worker->tag;

			}
		}
	}
	return closestWorker;

}

void Mazzer_bot::OnBuildingConstructionComplete(const Unit* unit)
{

	if (unit->unit_type == sc2::UNIT_TYPEID::TERRAN_REFINERY)
	{
		Fill_refinery(unit);
	}
	if (IsABuilding(unit->unit_type) && step == check_prev_step) {
		Construct_check_decrease = true;      //so it won't try to find a order that is finnish in checkStep()
		isBuild_same = unit;
	}
	if (unit->unit_type == UNIT_TYPEID::TERRAN_BUNKER) {
		AddToBG(unit, false, true);
	}
	if (unit->unit_type == UNIT_TYPEID::TERRAN_SUPPLYDEPOT) {
		Actions()->UnitCommand(unit,ABILITY_ID::MORPH_SUPPLYDEPOT_LOWER);
	}
}

//Fill une raffinerie
void Mazzer_bot::Fill_refinery(const Unit* unit) {
	const ObservationInterface* observation = Observation();
	Units Workers = observation->GetUnits(Unit::Alliance::Self, IsWorker());
	if (unit->assigned_harvesters < unit->ideal_harvesters-1) {
		for (const auto& probe : Workers)
		{


			if (probe->orders.empty())
			{
				Actions()->UnitCommand(probe, ABILITY_ID::HARVEST_GATHER, unit);
				break;
			}
			UnitOrder CurrentOrder = probe->orders.back();
			if (CurrentOrder.ability_id == ABILITY_ID::HARVEST_GATHER)
			{
				if (CurrentOrder.target_unit_tag == 0)
				{
					Actions()->UnitCommand(probe, ABILITY_ID::HARVEST_GATHER, unit);
					break;
				}
				const Unit *TargetUnit = observation->GetUnit(CurrentOrder.target_unit_tag);
				if (TargetUnit == nullptr || TargetUnit->unit_type == UNIT_TYPEID::NEUTRAL_MINERALFIELD)
				{
					Actions()->UnitCommand(probe, ABILITY_ID::HARVEST_GATHER, unit);
					break;
				}

			}

		}
	}

}

//Fill toute les raffinerie
void Mazzer_bot::Fill_All_Refinery() {
	Units Ref = Observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_REFINERY));
	for (auto& r : Ref) {
		Fill_refinery(r);
	}
}

//Fonctions de gestion des events de l'api
void Mazzer_bot::OnUnitDestroyed(const Unit *unit) {
	if (unit->alliance == Unit::Alliance::Enemy) {  //Gestion des batiment ennemy detruit (découvert avant obligé)(la gestion entière des attaque basées la dessus n'a pas pu être implémentée 
		if (IsABuilding(unit->unit_type)) {
			DeleteEnnemyBuilding(unit);
		}
	}
	if (unit->alliance == Unit::Alliance::Self) { //Suppression des batiments detruit du suivi de batiments (les notres)
		if (IsABuilding(unit->unit_type)) {
			DeleteDestroyBuildingfromBG(unit);
		}
	}
	if (IsAnArmy(unit->unit_type) && unit->alliance == Unit::Alliance::Self) //Suppression unité morte du suivi
		DeleteDeadfromBG(unit);
	if (IsAWorker(unit->unit_type) && unit->alliance == Unit::Alliance::Self) { //Déclencheur de fuite
		W_inTraining--;
		Units w = Observation()->GetUnits(Unit::Alliance::Self, IsWorker());
		Units a = Observation()->GetUnits(Unit::Alliance::Self, IsArmy());
		if (a.size() < 3 && w.size() < 8)Fleeing = true;
	}
};

void Mazzer_bot::OnUnitIdle(const Unit *unit) {
	if (unit->unit_type == UNIT_TYPEID::TERRAN_SCV) {
		uint64_t valid_mineral_patch;
		Point2D BasePos = getCloseBase(unit);
		FindNearestMineralPatch(BasePos, valid_mineral_patch);
		Actions()->UnitCommand(unit, ABILITY_ID::HARVEST_GATHER, Observation()->GetUnit(valid_mineral_patch));
		if (Construct_check_decrease) {
			command_to_count--;
			Construct_check_decrease = false;
		}
	}
	if (IsAnArmy(unit->unit_type)) {
		if (UnitTypeBGExisting(unit->unit_type)) {
			BattleGroup_Unit_type BG = GetUnitTypeBG(unit->unit_type);
			if (!BG.Attacking && ShouldGO(unit))allIn = true;
		
		}
	}
};

void Mazzer_bot::OnUnitCreated(const Unit *unit) {
	if (unit->unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER)
		expansions_ = search::CalculateExpansionLocations(Observation(), Query());
	if (IsAnArmy(unit->unit_type)) {
		if (BuildingTypeBGExisting(UNIT_TYPEID::TERRAN_BUNKER)) {
			BattleGroup_Building_type BG = GetBuildingTypeBG(UNIT_TYPEID::TERRAN_BUNKER);
			const Unit * bunker = Observation()->GetUnit(BG.Members[0]);
			Actions()->UnitCommand(unit, ABILITY_ID::MOVE, bunker->pos);
		}
		else {
			Actions()->UnitCommand(unit, ABILITY_ID::MOVE, *StartPosition);
		}
		AddToBG(unit);
		
	}
	if (IsABuilding(unit->unit_type)) {
		Fill_All_Refinery();
		if(unit->unit_type!=UNIT_TYPEID::TERRAN_BUNKER)
		AddToBG(unit, false, true);
	}
}

void OnUpgradeCompleted(UpgradeID) {

}

void Mazzer_bot::OnUnitEnterVision(const Unit *unit) {
	if (IsABuilding(unit->unit_type)) {
		AddEnnemyBuilding(unit);
	}
};
//

//Trouve les minerai les plus proches d'une position donnée
bool Mazzer_bot::FindNearestMineralPatch(const Point2D& start, uint64_t& target) {
	Units units = Observation()->GetUnits(Unit::Alliance::Neutral);
	float distance = std::numeric_limits<float>::max();
	for (const auto& u : units) {
		if (u->unit_type == UNIT_TYPEID::NEUTRAL_MINERALFIELD) {
			float d = DistanceSquared2D(u->pos, start);
			if (d < distance) {
				distance = d;
				target = u->tag;
			}
		}
	}

	if (distance == std::numeric_limits<float>::max()) {
		return false;
	}

	return true;
}

//Fonctions pour trouver un emplacements de batiments
size_t CalculateQueriess(float radius, float step_size, const Point2D& center, sc2::ABILITY_ID Structure, QueryType QType, std::vector<QueryInterface::PlacementQuery>& queries) {
	Point2D current_grid, previous_grid(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	size_t valid_queries = 0;
	// Find a buildable location on the circumference of the sphere
	float loc = 0.0f;
	while (loc < 360.0f) {
		Point2D point = Point2D(
			(radius * std::cos((loc * PI) / 180.0f)) + center.x,
			(radius * std::sin((loc * PI) / 180.0f)) + center.y);
		switch (QType)
		{

		case MaxXMinY:
			if (point.x > center.x || point.y < center.y)
			{
				loc += step_size;
				continue;
			}
			break;
		case MaxXMaxY:
			if (point.x > center.x || point.y > center.y)
			{
				loc += step_size;
				continue;
			}
			break;
		case MinXMinY:
			if (point.x > center.x || point.y > center.y)
			{
				loc += step_size;
				continue;
			}
			break;
		case MinXMaxY:
			if (point.x < center.x || point.y > center.y)
			{
				loc += step_size;
				continue;
			}
			break;

		}
		QueryInterface::PlacementQuery query(Structure, point);

		current_grid = Point2D(floor(point.x), floor(point.y));

		if (previous_grid != current_grid) {
			queries.push_back(query);
			++valid_queries;
		}

		previous_grid = current_grid;
		loc += step_size;
	}

	return valid_queries;
}

Point2D Mazzer_bot::GetRandomBuildableLocationFor(sc2::ABILITY_ID Structure, sc2::Point2D Location, QueryType QType, sc2::search::ExpansionParameters parameters)
{



	// Get the required queries for this cluster.
	std::vector<QueryInterface::PlacementQuery> queries;

	size_t query_count = 0;
	for (auto r : parameters.radiuses_) {
		query_count += CalculateQueriess(r, parameters.circle_step_size_, Location, Structure, QType, queries);
	}
	float distance = std::numeric_limits<float>::max();
	std::vector<bool> results = Query()->Placement(queries);
	std::vector<QueryInterface::PlacementQuery> validqueries;
	for (size_t j = 0; j < results.size(); ++j)
	{
		if (!results[j]) {
			continue;
		}
		validqueries.push_back(queries[j]);
	}
	Point2D place = Point2D(0,0);
	srand(time(0));
	if (validqueries.size() < 1)
	{
		std::cout << "No valid placement locations \n";
		Expand();
	}
	else {
		const QueryInterface::PlacementQuery& random_location = GetRandomEntry(validqueries);

		place = random_location.target_pos;
	}
	
	return place;
}

Point2D Mazzer_bot::GetNearestBuildableLocationFor(sc2::ABILITY_ID Structure, sc2::Point2D Location, QueryType QType, sc2::search::ExpansionParameters parameters)
{
	// Get the required queries for this cluster.
	std::vector<QueryInterface::PlacementQuery> queries;

	size_t query_count = 0;
	for (auto r : parameters.radiuses_) {
		query_count += CalculateQueriess(r, parameters.circle_step_size_, Location, Structure, QType, queries);
	}
	float distance = std::numeric_limits<float>::max();
	Point2D closest;
	std::vector<bool> results = Query()->Placement(queries);
	for (size_t j = 0; j < results.size(); ++j)
	{
		if (!results[j]) {
			continue;
		}

		Point2D& p = queries[j].target_pos;

		float d = Distance2D(p, Location);
		if (d < distance)
		{
			distance = d;
			closest = p;
		}
	}
	return closest;
}
//


//Regarde si un batiment est entouré d'autre batiment
bool Mazzer_bot::isSurrounded(const Unit* unit) {
	uint64_t valid_mineral_patch;
	
	FindNearestMineralPatch(unit->pos, valid_mineral_patch);
	Point2D VG = GetNearestVGPos(unit->pos, Observation());
	Units buildings = Observation()->GetUnits(Unit::Alliance::Self, IsBuilding());
	if (Distance2D(Observation()->GetUnit(valid_mineral_patch)->pos, unit->pos) < 5) {
		return true;

	}
	if (Distance2D(VG, unit->pos) < 5) {
		return true;
	}
	for (auto &b : buildings) {
		if (Distance2D(b->pos, unit->pos) < 5 && Distance2D(b->pos, unit->pos) > 0) {
			return true;
		}

	}
	return false;
}

bool Mazzer_bot::isSurrounded(Point2D pos) {
	uint64_t valid_mineral_patch;

	FindNearestMineralPatch(pos, valid_mineral_patch);
	Point2D VG = GetNearestVGPos(pos, Observation());
	Units buildings = Observation()->GetUnits(Unit::Alliance::Self, IsBuilding());
	if (Distance2D(Observation()->GetUnit(valid_mineral_patch)->pos, pos) < 4) {
		return true;

	}
	if (Distance2D(VG, pos) < 4) {
		return true;
	}
	for (auto &b : buildings) {
		if (Distance2D(b->pos, pos) < 4 && Distance2D(b->pos, pos) > 0) {
			return true;
		}

	}
	return false;
}
//

//Trouve la base la plus proche
Point2D Mazzer_bot::getCloseBase(const Unit * unit) {

	Units Bases = Observation()->GetUnits(Unit::Alliance::Self, IsTownHall());
	float minimum_distance = 100.0f;
	Point2D closestBase;
	for (auto &base : Bases) {



		float current_distance = Distance2D(unit->pos, base->pos);
		if (current_distance < minimum_distance) {

			minimum_distance = current_distance;
			closestBase = base->pos;


		}

		return closestBase;
	}
}

//Inutilisée
void Mazzer_bot::SetupRushLocation(const ObservationInterface *observation) {

	if (StartPosition == nullptr || (StartPosition->x == 0 && StartPosition->y == 0 && StartPosition->z == 0))
	{
		return;
	}
	Point2D Point1;
	Point2D Point2;
	if (game_info_->map_name.compare("Ascension to Aiur LE") == 0)
	{
		Point1 = Point2D(33.397f, 119.001f);//, 10.0061f);
		Point2 = Point2D(142.58f, 32.9744f);//, 10.0032f);
	}
	else if (game_info_->map_name.compare("Proxima Station LE") == 0)
	{
		Point1 = Point2D(55.5349f, 45.8899f);//, 12.0083f);
		Point2 = Point2D(144.946f, 119.996f);//, 12.0068f);
	}
	else if (game_info_->map_name.compare("Mech Depot LE") == 0)
	{
		Point1 = Point2D(144.891f, 126.548f);//, 9.99219f);
		Point2 = Point2D(38.4912f, 36.8269f);//, 10.0034f);
	}
	else if (game_info_->map_name.compare("Odyssey LE") == 0)
	{
		Point1 = Point2D(140.301f, 46.1042f);//, 10.0193f);
		Point2 = Point2D(29.7517f, 123.95f);//, 9.99219f);
	}
	else if (game_info_->map_name.compare("Abyssal Reef LE") == 0)
	{
		Point1 = Point2D(51.3499f, 119.31f);//, 9.98828f);
		Point2 = Point2D(148.648f, 24.686f);//, 9.98828f);
	}
	else if (game_info_->map_name.compare("Interloper LE") == 0)
	{
		Point1 = Point2D(113.626f, 43.3684f);
		Point2 = Point2D(40.6443f, 130.659f);
	}
	else if (game_info_->map_name.compare("Blackpink LE") == 0)
	{
		Point1 = Point2D(144.061f, 122.754f);
		Point2 = Point2D(24.4409f, 37.0681f);
	}
	else if (game_info_->map_name.compare("Acolyte LE") == 0)
	{
		Point1 = Point2D(123.395f, 160.331f);
		Point2 = Point2D(48.7954f, 23.0759f);
	}
	else
	{
		return;
	}
	if (Distance2D(*StartPosition, Point1) > Distance2D(*StartPosition, Point2))
	{
		RushLocation = Point1;
	}
	else
	{
	}
}
//

//Fonctions pour manager les Groupes de Bataille (BG)

void Mazzer_bot::CreateBG(const Unit *unit, bool attack_type , bool isBuilding) {
	if (!attack_type) {
		if (!isBuilding) {
			BattleGroup_Unit_type BG;
			BG.Attacking = false;
			BG.engaged_tag = 0;
			BG.UnitType = unit->unit_type.ToType();
			BG.Members.push_back(unit->tag);
			BG.health = GetBGHealth(BG.Members);
			PerUnitsBG.push_back(BG);
		}
		else {
			BattleGroup_Building_type BG;
			BG.UnitType = unit->unit_type.ToType();
			BG.Members.push_back(unit->tag);
			BG.health = GetBGHealth(BG.Members);
			PerBuildingBG.push_back(BG);
		}
	}
	else {
		BattleGroup_Attack_type BG;
		BG.Attacking = false;
		BG.engaged_tag = 0;
		BG.AttackType = Strategy::CanAttack(unit->unit_type.ToType());
		BG.Members.push_back(unit->tag);
		BG.health = GetBGHealth(BG.Members);
		PerAttackBG.push_back(BG);
	}
	
}

void Mazzer_bot::AddToBG(const Unit * unit, bool attack_type, bool isBuilding) {
	if (!attack_type) {
		if (!isBuilding) {
			if (UnitTypeBGExisting(unit->unit_type.ToType())) {

				for (auto& ThisBG : PerUnitsBG)
				{
					if (ThisBG.UnitType == unit->unit_type)
					{
						if (!ThisBG.Attacking)
						{

							ThisBG.Members.push_back(unit->tag);
							ThisBG.health = GetBGHealth(ThisBG.Members);

						}
					}
				}

			}
			else {
				CreateBG(unit, attack_type, isBuilding);
			}
		}
		else {
			if (BuildingTypeBGExisting(unit->unit_type.ToType())) {

				for (auto& ThisBG : PerBuildingBG)
				{
					if (ThisBG.UnitType == unit->unit_type)
					{

							ThisBG.Members.push_back(unit->tag);
							ThisBG.health = GetBGHealth(ThisBG.Members);

					}
				}
			}
			else {
				CreateBG(unit, attack_type, isBuilding);
			}
		}
	}
	else {

		ATTACK_TYPE AttackType = Strategy::CanAttack(unit->unit_type.ToType());
		if (AttackTypeBGExisting(AttackType)) {
			for (auto& ThisBG : PerAttackBG)
			{
				if (ThisBG.AttackType == AttackType)
				{

					if (!ThisBG.Attacking)
					{
						ThisBG.Members.push_back(unit->tag);
						ThisBG.health = GetBGHealth(ThisBG.Members);

					}
				}
			}

			
		}
		else {
			CreateBG(unit, attack_type, isBuilding);
		}
	}
}

 BattleGroup_Unit_type  Mazzer_bot::GetUnitTypeBG(UNIT_TYPEID unit_type) {

	for (auto& ThisBG : PerUnitsBG)
	{
		if (ThisBG.UnitType == unit_type)
		{
			return ThisBG;
		
		}

	}
	
}

 BattleGroup_Building_type  Mazzer_bot::GetBuildingTypeBG(UNIT_TYPEID unit_type) {

	 for (auto& ThisBG : PerBuildingBG)
	 {
		 if (ThisBG.UnitType == unit_type)
		 {
			 return ThisBG;

		 }

	 }

 }


BattleGroup_Attack_type Mazzer_bot::GetAttackTypeBG(ATTACK_TYPE attack_type) {

	
		for (auto& ThisBG : PerAttackBG)
		{
			if (ThisBG.AttackType == attack_type)
			{
				return ThisBG;
			}

		}
		

}

void Mazzer_bot::MakeAttackBGAttack(ATTACK_TYPE attack_type, Point2D pos) {
	if (AttackTypeBGExisting(attack_type)) {
		for (auto& BG : PerAttackBG)
		{
			if (BG.AttackType == attack_type)
			{
				BG.Attacking = true;
				for (auto &member : BG.Members) {
					const Unit * u = Observation()->GetUnit(member);
					Actions()->UnitCommand(u, ABILITY_ID::ATTACK, pos);
				}
			}
		}
	}

}

void Mazzer_bot::MakeAttackBGAttack(BattleGroup_Attack_type &BG, Point2D pos) {
	
		BG.Attacking = true;
		for (auto &member : BG.Members) {
			const Unit * u = Observation()->GetUnit(member);
			Actions()->UnitCommand(u, ABILITY_ID::ATTACK, pos);
		}
	}

void Mazzer_bot::MakeUnitBGAttack(UNIT_TYPEID unit_type, Point2D pos) {
	if (UnitTypeBGExisting(unit_type)) {
		for (auto& BG : PerUnitsBG)
		{
			if (BG.UnitType == unit_type)
			{
				BG.Attacking = true;
				for (auto &member : BG.Members) {
					const Unit * u = Observation()->GetUnit(member);
					if (u->unit_type == UNIT_TYPEID::TERRAN_BANSHEE) {
						Actions()->UnitCommand(u, ABILITY_ID::BEHAVIOR_CLOAKON_BANSHEE);

					}
					Actions()->UnitCommand(u, ABILITY_ID::ATTACK, pos);
				}
			}
		}
	}
}

void Mazzer_bot::MakeUnitBGAttack(BattleGroup_Unit_type &BG, Point2D pos) {
	
		BG.Attacking = true;
		for (auto &member : BG.Members) {
			const Unit * u = Observation()->GetUnit(member);
			Actions()->UnitCommand(u, ABILITY_ID::ATTACK, pos);
		}
	
}

float Mazzer_bot::GetBGHealth(std::vector<int64_t> Members) {

	float hp = 0;
	for (auto &member : Members) {
		const Unit * u = Observation()->GetUnit(member);
		hp += u->health;
	}
	return hp;
}

bool Mazzer_bot::AllInAttack(Point2D pos) {

	for (auto& ThisBG : PerUnitsBG)
	{
		if (!ThisBG.Attacking) {
			MakeUnitBGAttack(ThisBG, pos);
		}

	}
	for (auto& ThisBG : PerAttackBG)
	{
		if (!ThisBG.Attacking) {
			MakeAttackBGAttack(ThisBG, pos);
		}

	}
	return false;
}

void Mazzer_bot::GeneralRetreat() {
	for (auto& ThisBG : PerUnitsBG)
	{
		if (!ThisBG.Attacking) {
			MakeUnitBGRetreat(ThisBG, Observation()->GetStartLocation());
		}

	}
	for (auto& ThisBG : PerAttackBG)
	{
		if (!ThisBG.Attacking) {
			MakeAttackBGRetreat(ThisBG, Observation()->GetStartLocation());
		}

	}
}

bool  Mazzer_bot::UnitTypeBGExisting(UNIT_TYPEID unit_type){
	for (auto& ThisBG : PerUnitsBG)
	{
		if (ThisBG.UnitType == unit_type)
		{
			return true;

		}

	}
	return false;
}

bool  Mazzer_bot::BuildingTypeBGExisting(UNIT_TYPEID unit_type) {
	for (auto& ThisBG : PerBuildingBG)
	{
		if (ThisBG.UnitType == unit_type)
		{
			return true;

		}

	}
	return false;
}

bool  Mazzer_bot::AttackTypeBGExisting(ATTACK_TYPE attack_type) {
	for (auto& ThisBG : PerAttackBG)
	{
		if (ThisBG.AttackType == attack_type)
		{
			return true;
		}

	}
	return false;
}

void  Mazzer_bot::MakeAttackBGRetreat(BattleGroup_Attack_type &BG, Point2D pos){
	BG.Attacking = false;
	for (auto &member : BG.Members) {
		const Unit * u = Observation()->GetUnit(member);
		Actions()->UnitCommand(u, ABILITY_ID::RALLY_UNITS, pos);
	}
}

void  Mazzer_bot::MakeUnitBGRetreat(BattleGroup_Unit_type &BG, Point2D pos){
	BG.Attacking = false
;
	for (auto &member : BG.Members) {
		const Unit * u = Observation()->GetUnit(member);
		Actions()->UnitCommand(u, ABILITY_ID::MOVE, pos);
	}
	CheckAddBG(BG.UnitType);
	
}

void Mazzer_bot::DeleteDeadfromBG(const Unit * unit, bool attack_type) {
	if (!attack_type) {
		if (UnitTypeBGExisting(unit->unit_type.ToType())) {

			for (auto& ThisBG : PerUnitsBG)
			{
				if (ThisBG.UnitType == unit->unit_type)
				{
					int thisMember = 0;
					for (auto& ThisUnit : ThisBG.Members)
					{
						if (ThisUnit == unit->tag)
						{
							ThisBG.Members.erase(ThisBG.Members.begin() + thisMember);
							
							if (ThisBG.Members.size() < 1) { 
								ThisBG.Attacking = false;
								if (!onload) {
									CheckAddBG(unit->unit_type);
									
								}
							}
							break;
						}
						thisMember++;
					}
				

				}
			}


		}


	}
	else {

		ATTACK_TYPE AttackType = Strategy::CanAttack(unit->unit_type.ToType());
		if (AttackTypeBGExisting(AttackType)) {
			for (auto& ThisBG : PerAttackBG)
			{
				if (ThisBG.AttackType == AttackType)
				{
					int thisMember = 0;
					for (auto& ThisUnit : ThisBG.Members)
					{
						if (ThisUnit == unit->tag)
						{
							ThisBG.Members.erase(ThisBG.Members.begin() + thisMember);
							if (ThisBG.Members.size() < 1)ThisBG.Attacking = false;
							break;
						}
						thisMember++;
					}
				}
			}


		}
		
	}
}

void Mazzer_bot::DeleteDestroyBuildingfromBG(const Unit * unit) {
	if (BuildingTypeBGExisting(unit->unit_type)) {
		for (auto& ThisBG : PerBuildingBG)
		{
			if (ThisBG.UnitType == unit->unit_type)
			{
				int thisMember = 0;
				for (auto& ThisUnit : ThisBG.Members)
				{
					if (ThisUnit == unit->tag)
					{
						ThisBG.Members.erase(ThisBG.Members.begin() + thisMember);
						
						break;
					}
					thisMember++;
				}
			}
		}


	}
}

void Mazzer_bot::CheckAddBG(UNIT_TYPEID unit_type) {

	Units units = Observation()->GetUnits(Unit::Alliance::Self, IsUnit(unit_type));
		if (UnitTypeBGExisting(unit_type)) {

			for (auto& ThisBG : PerUnitsBG)
			{
				if (ThisBG.UnitType == unit_type)
				{
					
						for (auto& u : units)
						{
							if(!IsInBG(u))
							AddToBG(u);
						}
					
				}
			}


		}
	
}

void Mazzer_bot::CheckAddBG(ATTACK_TYPE attack_type) {

	/*Units units = Observation()->GetUnits(Unit::Alliance::Self, Strategy::CanAttack(attack_type));
	if (AttackTypeBGExisting(attack_type)) {

		for (auto& ThisBG : PerAttackBG)
		{
			if (ThisBG.AttackType == attack_type)
			{
				if (ThisBG.Members.size() < 1) {
					for (auto& u : units)
					{
						AddToBG(u,true);
					}
				}
			}
		}


	}*/

}

bool Mazzer_bot::ShouldRetreat(BattleGroup_Unit_type &BG) {

	
		float hp = GetBGHealth(BG.Members);
		if (hp < 0.3*BG.health) {
			
			return true;
		}
	
	return false;
}

bool  Mazzer_bot::ShouldGO(const Unit * unit) {
	BattleGroup_Unit_type BG = GetUnitTypeBG(unit->unit_type);
	
	for (auto& m : BG.Members) {
		if (Distance2D(unit->pos, Observation()->GetUnit(m)->pos) > 10)return false;
	}
	return true;
}

bool Mazzer_bot::IsInBG(const Unit * unit) {
	if (UnitTypeBGExisting(unit->unit_type)) {
		BattleGroup_Unit_type BG = GetUnitTypeBG(unit->unit_type);
		for (auto& m : BG.Members) {
			if (m == unit->tag)return true;
		}
	}
	return false;
}

//


//Fait fuire un commandCenter (spéciale terran)
void Mazzer_bot::Flee() {
	Units units = Observation()->GetUnits(Unit::Alliance::Self, IsTownHall());
	if (units.size() > 1) {
		Fleeing = false;
		Bo_secours = true;
		step = 0;
		switchbo = false;
	}
	else
	{
		for (auto &u : units) {
			
			if (u->unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER) {

				if (!islift) {
					Actions()->UnitCommand(u, ABILITY_ID::LOADALL_COMMANDCENTER);
					Actions()->UnitCommand(u, ABILITY_ID::LIFT_COMMANDCENTER);
					islift = true;

					break;
				}
				if (unload) {
					Actions()->UnitCommand(u, ABILITY_ID::UNLOADALL);
					unload = false;
					Fleeing = false;
					islift = false;
					ismoving = false;
					Bo_secours = true;
					*StartPosition = u->pos;
					AddToBG(u, false, true);
					Units workers = Observation()->GetUnits(Unit::Alliance::Self, IsWorker());
					for (auto& w : workers) {
						Actions()->UnitCommand(w, ABILITY_ID::MOVE, *StartPosition);
					}

				}
			}
			if (u->unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING) {
				PerUnitsBG = {};
				PerAttackBG = {};
				PerBuildingBG = {};
				if (!ismoving) {
					float minimum_distance = std::numeric_limits<float>::max();
					Point3D closest_expansion;
					for (const auto& expansion : expansions_) {
						float current_distance = Distance3D(*StartPosition, expansion);
						if (current_distance < .01f) {
							continue;
						}

						if (current_distance < minimum_distance && current_distance > 100) {
							if (Query()->Placement(ABILITY_ID::LAND_COMMANDCENTER, expansion)) {
								closest_expansion = expansion;
								minimum_distance = current_distance;
							}
						}
						Actions()->UnitCommand(u, ABILITY_ID::LAND, closest_expansion);
						ismoving = true;
						unload = true;
					}
				}
			}

	}	}
}

//Expansion
void Mazzer_bot::Expand() {
	Build_Any(CommandCenter);
}

//Batiments Ennemi

void Mazzer_bot::AddEnnemyBuilding(const Unit * unit) {
	Ennemy_Buildings.Members.push_back(unit->tag);
	Ennemy_Buildings.Pos.push_back(unit->pos);
}

void Mazzer_bot::DeleteEnnemyBuilding(const Unit * unit) {
	int thisMember = 0;
	for (auto& ThisUnit : Ennemy_Buildings.Members)
	{
		if (ThisUnit == unit->tag)
		{
			Ennemy_Buildings.Members.erase(Ennemy_Buildings.Members.begin() + thisMember);
			Ennemy_Buildings.Pos.erase(Ennemy_Buildings.Pos.begin() + thisMember);
			
			
			break;
		}
		thisMember++;
	}
}
