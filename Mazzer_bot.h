#pragma once

#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_agent.h"
#include "sc2api/sc2_map_info.h"
#include "sc2lib/sc2_lib.h"
#include "Strategys.h"

#define DllExport   __declspec( dllexport )  
using namespace sc2;

#define BO_SIZE 57
#define MAX_GEASER_DISTANCE 200
#define BATTLEGROUP_SIZE 3
#define CANNONS_PER_PYLON 4

typedef struct BattleGroup_s
{
	UNIT_TYPEID UnitType;
	std::vector<int64_t> Members;
	bool Attacking;
	uint64_t engaged_tag;
	Point2D ScoutingTarget;

} BattleGroup;

struct Mz_Order{
	Mz_Order(UNIT_TYPEID Type, ABILITY_ID c, int32_t mineralN, int32_t VespenN,UNIT_TYPEID needed = UNIT_TYPEID::TERRAN_SCV) :
		UnitType(Type), command(c), mineralNeed(mineralN), vespenNeed(VespenN), Unit_need(needed){}

	UNIT_TYPEID UnitType;
	ABILITY_ID command;
	int32_t mineralNeed;
	int32_t vespenNeed;
	UNIT_TYPEID Unit_need;
};

struct Mz_BuildOrder {
	Mz_BuildOrder(std::vector<Mz_Order> Order,std::vector<int32_t> nb_w) :
		UnitOrder(Order),nb_worker(nb_w) {}

	std::vector<Mz_Order> UnitOrder;
	std::vector<int32_t> nb_worker;
};
static const float PI = 3.1415927f;

enum QueryType
{
	None,
	MinXMinY,
	MinXMaxY,
	MaxXMinY,
	MaxXMaxY
};

class Mazzer_bot : public Agent
{
public:
	Point2D GetRandomBuildableLocationFor(sc2::ABILITY_ID Structure, sc2::Point2D Location, QueryType QType, sc2::search::ExpansionParameters parameters = sc2::search::ExpansionParameters());
	Point2D GetNearestBuildableLocationFor(sc2::ABILITY_ID Structure, sc2::Point2D Location, QueryType QType, sc2::search::ExpansionParameters parameters = sc2::search::ExpansionParameters());
	Mazzer_bot();
	virtual void OnStep() override;
	virtual void OnGameStart() override;
	virtual void OnUnitDestroyed(const Unit *unit) override;
	virtual void OnUnitIdle(const Unit *unit) override;
	virtual void OnUnitCreated(const Unit *unit) override;
	virtual void OnUnitEnterVision(const Unit *unit) override;
	virtual void OnUpgradeCompleted(UpgradeID) {};
	void OnBuildingConstructionComplete(const Unit * unit);
	void BuildVespeneG();
	void Follow_BO(Mz_BuildOrder);
	void Build_Any(Mz_Order);
	void Fill_refinery(const Unit * unit);
	Tag GetNearestVG(sc2::Point2D Location, const ObservationInterface *observation);
	Tag GetNearestWorker(sc2::Point2D Location, const ObservationInterface *observation);
	Point2D GetNearestVGPos(sc2::Point2D Location, const ObservationInterface *observation);
	void SetupRushLocation(const ObservationInterface *observation);
	bool FindNearestMineralPatch(const Point2D& start, uint64_t& target);
private:
	sc2::Point3D *StartPosition;
	sc2::Point2D RushLocation;
	GameInfo *game_info_;
	sc2::search::ExpansionParameters SearchParams;
	sc2::search::ExpansionParameters SearchParamsA;
	int step;
	bool Construct;
	int32_t W_inTraining;
	std::vector<Point3D> expansions_;
};


void DllExport *CreateNewAgent();

int DllExport GetAgentRace();

const char DllExport *GetAgentName();

