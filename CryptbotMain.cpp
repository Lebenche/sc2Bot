#include <iostream>
#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"
#include "sc2utils/sc2_arg_parser.h"

#include "Mazzer_bot.h"
#include "LadderInterface.h"

#ifdef DEBUG
int main(int argc, char* argv[])
{
	Mazzer_bot Mz_bot;	sc2::Coordinator coordinator;
	if (!coordinator.LoadSettings(argc, argv))
	{
		std::cout << "Unable to find or parse settings." << std::endl;
		return 1;
	}
	coordinator.SetStepSize(1);
	coordinator.SetRealtime(false);
	coordinator.SetMultithreaded(true);
	coordinator.SetParticipants({
		CreateParticipant(sc2::Race::Terran, &Mz_bot),
		//sc2::PlayerSetup(sc2::PlayerType::Observer,Util::GetRaceFromString(enemyRaceString)),
		CreateComputer(sc2::Race::Terran, sc2::Difficulty::VeryEasy)
	});
	// Start the game.
	coordinator.LaunchStarcraft();
	coordinator.StartGame("C:/ProgramData/Blizzard Entertainment/StarCraft II/Maps/InterloperLE.SC2Map");
	//coordinator.StartGame("Interloper LE");


	// Step forward the game simulation.
	while (coordinator.Update())
	{
	}
}
#else

//*************************************************************************************************
int main(int argc, char* argv[]) 
{

	RunBot(argc, argv, new CryptBot(), sc2::Race::Protoss);

	return 0;
}
#endif

/*
std::vector<Mz_Order> UnitOrders = { SupplyDepot,Refinery,Barracks,BReactor,Refinery,SupplyDepot,Barracks,BReactor,EngineeringBay,CommandCenter,MissileTurret,Bunker,Refinery,Refinery,Factory,FTechLab,SupplyDepot,Starport,STechLab,SupplyDepot,SupplyDepot };
			Actions()->UnitCommand(marine[0], ABILITY_ID::LOAD_BUNKER, Point2D(bunker[0]->pos.x, bunker[0]->pos.y));

*/