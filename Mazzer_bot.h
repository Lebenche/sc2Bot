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

typedef struct BattleGroup_u
{
	UNIT_TYPEID UnitType;
	std::vector<int64_t> Members;
	bool Attacking;
	uint64_t engaged_tag;
	float health;

} BattleGroup_Unit_type;

typedef struct Building_ennemy
{

	std::vector<int64_t> Members;
	std::vector<Point2D> Pos;
	
};

typedef struct BattleGroup_b
{
	UNIT_TYPEID UnitType;
	std::vector<int64_t> Members;
	float health;

} BattleGroup_Building_type;

typedef struct BattleGroup_a
{
	ATTACK_TYPE AttackType;
	std::vector<int64_t> Members;
	bool Attacking;
	uint64_t engaged_tag;
	float health;

} BattleGroup_Attack_type;

struct Mz_Order {
	Mz_Order(UNIT_TYPEID Type, ABILITY_ID c, int32_t mineralN, int32_t VespenN, UNIT_TYPEID needed = UNIT_TYPEID::TERRAN_SCV) :
		UnitType(Type), command(c), mineralNeed(mineralN), vespenNeed(VespenN), Unit_need(needed) {}

	UNIT_TYPEID UnitType;
	ABILITY_ID command;
	int32_t mineralNeed;
	int32_t vespenNeed;
	UNIT_TYPEID Unit_need;
};

struct Mz_BuildOrder {
	Mz_BuildOrder(std::vector<Mz_Order> Order, std::vector<int32_t> nb_w,bool isA = false) :
		UnitOrder(Order), nb_worker(nb_w), isArmy(isA) {}

	std::vector<Mz_Order> UnitOrder;
	std::vector<int32_t> nb_worker;
	bool isArmy;
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
	void AttackBase(const ObservationInterface* observation);
	void Mazzer_bot::CheckSupply(const ObservationInterface* observation);
	void Mazzer_bot::TrainArmy(const ObservationInterface* observation);
	void Mazzer_bot::CheckSCV(const ObservationInterface* observation);
	void Follow_BO(Mz_BuildOrder);
	bool Build_Any(Mz_Order);
	void Fill_refinery(const Unit * unit);
	void Fill_All_Refinery();
	Tag GetNearestVG(sc2::Point2D Location, const ObservationInterface *observation);
	Tag GetNearestWorker(sc2::Point2D Location, const ObservationInterface *observation);
	Point2D GetNearestVGPos(sc2::Point2D Location, const ObservationInterface *observation);
	void SetupRushLocation(const ObservationInterface *observation);
	bool FindNearestMineralPatch(const Point2D& start, uint64_t& target);
	bool CheckStep(Mz_Order toCheck,Mz_Order prev,bool isArmy = false, int32_t nb_army = 0);

	bool isSurrounded(const Unit * unit);
	Point2D getCloseBase(const Unit * unit);

	void CreateBG(const Unit * unit, bool attack_type = false, bool isBuilding = false); //set to unit type by default
	void AddToBG(const Unit * unit, bool attack_type = false, bool isBuilding = false); // Add to a unit type BG by default
	BattleGroup_Unit_type GetUnitTypeBG(UNIT_TYPEID unit_type); //Use only if BG exist
	BattleGroup_Building_type GetBuildingTypeBG(UNIT_TYPEID unit_type); //Use only if BG exist
	BattleGroup_Attack_type GetAttackTypeBG(ATTACK_TYPE attack_type); //Use only if BG exist
	void MakeAttackBGAttack(ATTACK_TYPE attack_type, Point2D pos); 
	void MakeAttackBGAttack(BattleGroup_Attack_type &BG, Point2D pos);
	void MakeUnitBGAttack(UNIT_TYPEID unit_type, Point2D pos);
	void MakeUnitBGAttack(BattleGroup_Unit_type &BG, Point2D pos);
	float GetBGHealth(std::vector<int64_t> Members);
	bool AllInAttack(Point2D pos);
	bool ShouldRetreat(BattleGroup_Unit_type &BG);
	void GeneralRetreat();
	bool UnitTypeBGExisting(UNIT_TYPEID unit_type);
	bool BuildingTypeBGExisting(UNIT_TYPEID unit_type);
	bool AttackTypeBGExisting(ATTACK_TYPE attack_type);
	void MakeAttackBGRetreat(BattleGroup_Attack_type &BG, Point2D pos);
	void MakeUnitBGRetreat(BattleGroup_Unit_type &BG, Point2D pos);
	void Flee();
	bool IsInBG(const Unit * unit);
	void DeleteDeadfromBG(const Unit * unit, bool attack_type = false);
	void CheckAddBG(UNIT_TYPEID unit_type);
	bool ShouldGO(const Unit * unit);
	void CheckAddBG(ATTACK_TYPE attack_type);

	void AddEnnemyBuilding(const Unit * unit);
	void DeleteEnnemyBuilding(const Unit * unit);

private:
	sc2::Point3D *StartPosition;
	sc2::Point2D RushLocation;
	GameInfo *game_info_;
	sc2::search::ExpansionParameters SearchParams;
	sc2::search::ExpansionParameters SearchParamsA;
	sc2::search::ExpansionParameters SearchParamsB;
	int32_t Mazzer_bot::GetCurrentMaxSupply();
	int step;
	int check_prev_step;
	int command_to_count;
	int nb_vespene;
	int nb_building_suround;
	int base_step_vespenes;
	int base_step_building;
	bool Construct_check_decrease;
	bool switchbo;
	bool allIn;
	bool dont_attack;
	const Unit *isBuild_same;
	int32_t W_inTraining;
	std::vector<Point3D> expansions_;

	std::vector<BattleGroup_Unit_type>  PerUnitsBG;
	std::vector<BattleGroup_Attack_type>  PerAttackBG;
	std::vector<BattleGroup_Building_type>  PerBuildingBG;
	Building_ennemy  Ennemy_Buildings;
};


void DllExport *CreateNewAgent();

int DllExport GetAgentRace();

const char DllExport *GetAgentName();
