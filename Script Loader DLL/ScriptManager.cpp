#include "ScriptManager.h"

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

const char* TestFunc()
{
	return "Test";
}

void ScriptManager::Initialize()
{
	//See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	//and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	//Excluded the ffi lib for now. Current goal is to sandbox lua for user
	//safety. Might change this later on.
	LuaState.open_libraries
	(
		sol::lib::base,
		sol::lib::package,
		sol::lib::coroutine,
		sol::lib::string,
		sol::lib::os,
		sol::lib::math,
		sol::lib::table,
		sol::lib::debug,
		sol::lib::bit32,
		sol::lib::io,
		sol::lib::ffi,
		sol::lib::jit
	);
	SetupLua();
	//RunMainLua();
}

void ScriptManager::SetupLua()
{
	RunScript(GetEXEPath(false) + "RFGR Script Loader/Core/CoreInit.lua");

	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	auto RslTable = LuaState["rsl"].get_or_create<sol::table>();
	RslTable["GetScriptLoaderVersion"] = GetScriptLoaderVersion;

	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;
	RfgTable["SetFarClipDistance"] = game_render_set_far_clip_distance;

	//LogType enums defined in lua
	auto LoggerTable = LuaState["Logger"].get_or_create<sol::table>(); //Todo: Add to RSL table.
	LoggerTable["OpenLogFile"] = Logger::OpenLogFile;
	LoggerTable["CloseLogFile"] = Logger::CloseLogFile;
	LoggerTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles;
	LoggerTable["Log"] = Logger::Log;
	LoggerTable["LogFlagWithColor"] = Logger::LogFlagWithColor;
	LoggerTable["GetFlagString"] = Logger::GetFlagString;
	LoggerTable["LogToFile"] = Logger::LogToFile;
	LoggerTable["GetTimeString"] = Logger::GetTimeString;
	
	RfgTable.new_usertype<vector>
	(
		"vector",
		"new", sol::constructors<vector(), vector(const vector&), vector(float), vector(float, float, float)>(),
		sol::meta_function::addition, &vector::operator+,
		sol::meta_function::subtraction, &vector::operator-,
		sol::meta_function::multiplication, &vector::operator*,
		sol::meta_function::equal_to, &vector::operator==,
		"Cross", &vector::Cross,
		"Magnitude", &vector::Magnitude,
		"SetAll", &vector::SetAll,
		"x", &vector::x,
		"y", &vector::y,
		"z", &vector::z
	);
	RfgTable.new_usertype<matrix>
	(
		"matrix",
		"new", sol::constructors<matrix(), matrix(const matrix&), matrix(float), matrix(vector, vector, vector)>(),
		sol::meta_function::addition, &matrix::operator+,
		sol::meta_function::subtraction, &matrix::operator-,
		sol::meta_function::equal_to, &matrix::operator==,
		"SetAll", &matrix::SetAll,
		"rvec", &matrix::rvec,
		"uvec", &matrix::uvec,
		"fvec", &matrix::fvec
	);	
	RfgTable.new_usertype<matrix43>
	(
		"matrix43",
		"new", sol::constructors<matrix43(), matrix43(const matrix43&), matrix43(float), matrix43(matrix, vector)>(),
		sol::meta_function::addition, &matrix43::operator+,
		sol::meta_function::subtraction, &matrix43::operator-,
		sol::meta_function::equal_to, &matrix43::operator==,
		"SetAll", &matrix43::SetAll,
		"Rotation", &matrix43::m_rotation,
		"Translation", &matrix43::m_translation
	);
	RfgTable.new_usertype<AttachInfoData> //Note: I have no idea if the last 3 vars are correct. Bit fields are odd with sol2.
	(
		"AttachInfoData",
		"new", sol::constructors<AttachInfoData(), AttachInfoData(const AttachInfoData&)>(),
		"ParentHandle", &AttachInfoData::parent_handle,
		"ParentPropPoint", &AttachInfoData::parent_prop_point,
		"ChildPropPoint", &AttachInfoData::child_prop_point,
		"RelativeTransform", &AttachInfoData::relative_transform,
		"UseRelativeTransform", sol::property(itsy_bitsy::read<AttachInfoData, 60>, itsy_bitsy::write<AttachInfoData, 60>), //uint32 - 1
		"UpdatePhysics", sol::property(itsy_bitsy::read<AttachInfoData, 61>, itsy_bitsy::write<AttachInfoData, 61>),//uint32 - 1 
		"Updated", sol::property(itsy_bitsy::read<AttachInfoData, 62>, itsy_bitsy::write<AttachInfoData, 62>) //uint32 - 1
	);
	RfgTable.new_usertype<ContactNode>
	(
		"ContactNode",
		"new", sol::constructors<ContactNode(), ContactNode(const ContactNode&)>(),
		"ContactedObject", &ContactNode::m_contacted_object,
		"NumberOfContacts", &ContactNode::m_num_contacts,
		"Previous", &ContactNode::prev,
		"Next", &ContactNode::next
	);
	RfgTable.new_usertype<ObjectContactInfo>
	(
		"ObjectContactInfo",
		"new", sol::constructors<ObjectContactInfo(), ObjectContactInfo(const ObjectContactInfo&)>(),
		"ContactList", &ObjectContactInfo::m_contact_list
	);
	RfgTable.new_usertype<ObjectFlags>
	(
		"ObjectFlags",
		"new", sol::constructors<ObjectFlags(), ObjectFlags(const ObjectFlags&)>(),
		"FlaggedListState", sol::property(itsy_bitsy::read<ObjectFlags, 0>, itsy_bitsy::write<ObjectFlags, 0>), //int8 - 3
		"LightingSetOnce", sol::property(itsy_bitsy::read<ObjectFlags, 3>, itsy_bitsy::write<ObjectFlags, 3>), //int8 - 1
		"Destroyed", sol::property(itsy_bitsy::read<ObjectFlags, 4>, itsy_bitsy::write<ObjectFlags, 4>), //int8 - 1
		"NoSave", sol::property(itsy_bitsy::read<ObjectFlags, 5>, itsy_bitsy::write<ObjectFlags, 5>), //int8 - 1
		"ForceFullSave", sol::property(itsy_bitsy::read<ObjectFlags, 6>, itsy_bitsy::write<ObjectFlags, 6>), //int8 - 1
		"DestroyOnSave", sol::property(itsy_bitsy::read<ObjectFlags, 7>, itsy_bitsy::write<ObjectFlags, 7>), //int8 - 1
		"CreatedByMissionOrActivity", sol::property(itsy_bitsy::read<ObjectFlags, 8>, itsy_bitsy::write<ObjectFlags, 8>), //int8 - 1
		"DontTransform", sol::property(itsy_bitsy::read<ObjectFlags, 9>, itsy_bitsy::write<ObjectFlags, 9>), //int8 - 1
		"WorldFree", sol::property(itsy_bitsy::read<ObjectFlags, 10>, itsy_bitsy::write<ObjectFlags, 10>), //int8 - 1
		"Streaming", sol::property(itsy_bitsy::read<ObjectFlags, 11>, itsy_bitsy::write<ObjectFlags, 11>), //int8 - 1
		"Streamed", sol::property(itsy_bitsy::read<ObjectFlags, 12>, itsy_bitsy::write<ObjectFlags, 12>), //int8 - 1
		"Persistent", sol::property(itsy_bitsy::read<ObjectFlags, 13>, itsy_bitsy::write<ObjectFlags, 13>), //int8 - 1
		"Original", sol::property(itsy_bitsy::read<ObjectFlags, 14>, itsy_bitsy::write<ObjectFlags, 14>), //int8 - 1
		"Stub", sol::property(itsy_bitsy::read<ObjectFlags, 15>, itsy_bitsy::write<ObjectFlags, 15>), //int8 - 1
		"PreserveHandle", sol::property(itsy_bitsy::read<ObjectFlags, 16>, itsy_bitsy::write<ObjectFlags, 16>), //int8 - 1
		"BpoIndex", sol::property(itsy_bitsy::read<ObjectFlags, 17>, itsy_bitsy::write<ObjectFlags, 17>), //int8 - 2
		"IsDependent", sol::property(itsy_bitsy::read<ObjectFlags, 19>, itsy_bitsy::write<ObjectFlags, 19>), //int8 - 1
		"Visited", sol::property(itsy_bitsy::read<ObjectFlags, 20>, itsy_bitsy::write<ObjectFlags, 20>), //int8 - 1
		"SpecialLifetime", sol::property(itsy_bitsy::read<ObjectFlags, 21>, itsy_bitsy::write<ObjectFlags, 21>), //int8 - 1
		"SerializeProtected", sol::property(itsy_bitsy::read<ObjectFlags, 22>, itsy_bitsy::write<ObjectFlags, 22>), //int8 - 1
		"DontUseMe", sol::property(itsy_bitsy::read<ObjectFlags, 23>, itsy_bitsy::write<ObjectFlags, 23>),//int8 - 1
		"StreamingFixed", sol::property(itsy_bitsy::read<ObjectFlags, 24>, itsy_bitsy::write<ObjectFlags, 24>), //int8 - 1
		"RenderFlags", sol::property(itsy_bitsy::read<ObjectFlags, 25>, itsy_bitsy::write<ObjectFlags, 25>) //int8 - 4 
	);
	/*RfgTable.new_usertype<RemoteObjectFlags>
	(
		"RemoteObjectFlags",
		"new", sol::constructors<sol::types<const RemoteObjectFlags&>>(),	
	);*/
	RfgTable.new_usertype<HavokBPO>
	(
		"HavokBPO",
		"new", sol::constructors<HavokBPO(), HavokBPO(const HavokBPO&)>(),
		"Flags", &HavokBPO::flags,
		"State", &HavokBPO::state,
		"BpoIndex", &HavokBPO::bpo_index,
		"StateIndex", &HavokBPO::state_index,
		"Owner", &HavokBPO::owner,
		"Next", &HavokBPO::next,
		"Prev", &HavokBPO::prev
		//"Userdata", &HavokBPO::user_data
	);
	RfgTable.new_usertype<HumanFlags>
	(
		"HumanFlags",
		"new", sol::constructors<HumanFlags(), HumanFlags(const HumanFlags&)>(),
		"BoredHeadtrackDisabled", sol::property(itsy_bitsy::read<HumanFlags, 0>, itsy_bitsy::write<HumanFlags, 0>), //int32 - 1
		"Hidden", sol::property(itsy_bitsy::read<HumanFlags, 1>, itsy_bitsy::write<HumanFlags, 1>), //int32 - 1
		"CapSpeed", sol::property(itsy_bitsy::read<HumanFlags, 2>, itsy_bitsy::write<HumanFlags, 2>), //int32 - 1
		"WasRendered", sol::property(itsy_bitsy::read<HumanFlags, 3>, itsy_bitsy::write<HumanFlags, 3>), //int32 - 1
		"LockedController", sol::property(itsy_bitsy::read<HumanFlags, 4>, itsy_bitsy::write<HumanFlags, 4>), //int32 - 1
		"Invulnerable", sol::property(itsy_bitsy::read<HumanFlags, 5>, itsy_bitsy::write<HumanFlags, 5>), //int32 - 1
		"MissionInvulnerable", sol::property(itsy_bitsy::read<HumanFlags, 6>, itsy_bitsy::write<HumanFlags, 6>), //int32 - 1
		"NoDamage", sol::property(itsy_bitsy::read<HumanFlags, 7>, itsy_bitsy::write<HumanFlags, 7>), //int32 - 1
		"ActivityEngage", sol::property(itsy_bitsy::read<HumanFlags, 8>, itsy_bitsy::write<HumanFlags, 8>), //int32 - 1
		"ConsideredArmed", sol::property(itsy_bitsy::read<HumanFlags, 9>, itsy_bitsy::write<HumanFlags, 9>), //int32 - 1
		"RiotShield", sol::property(itsy_bitsy::read<HumanFlags, 10>, itsy_bitsy::write<HumanFlags, 10>), //int32 - 1
		"SafehouseVIP", sol::property(itsy_bitsy::read<HumanFlags, 11>, itsy_bitsy::write<HumanFlags, 11>), //int32 - 1
		"RadioOperator", sol::property(itsy_bitsy::read<HumanFlags, 12>, itsy_bitsy::write<HumanFlags, 12>), //int32 - 1
		"ActivityRaidRequired", sol::property(itsy_bitsy::read<HumanFlags, 13>, itsy_bitsy::write<HumanFlags, 13>), //int32 - 1
		"ActivityRaidOptional", sol::property(itsy_bitsy::read<HumanFlags, 14>, itsy_bitsy::write<HumanFlags, 14>), //int32 - 1
		"ActivateHouseArrestHostage", sol::property(itsy_bitsy::read<HumanFlags, 15>, itsy_bitsy::write<HumanFlags, 15>), //int32 - 1
		"RaidIntroductionLines", sol::property(itsy_bitsy::read<HumanFlags, 16>, itsy_bitsy::write<HumanFlags, 16>), //int32 - 1
		"MinerPersonaLines", sol::property(itsy_bitsy::read<HumanFlags, 17>, itsy_bitsy::write<HumanFlags, 17>), //int32 - 1
		"DamagedByPlayer", sol::property(itsy_bitsy::read<HumanFlags, 18>, itsy_bitsy::write<HumanFlags, 18>), //int32 - 1
		"AiIgnore", sol::property(itsy_bitsy::read<HumanFlags, 19>, itsy_bitsy::write<HumanFlags, 19>), //int32 - 1
		"CastsShadows", sol::property(itsy_bitsy::read<HumanFlags, 20>, itsy_bitsy::write<HumanFlags, 20>),//int32 - 1
		"CastsDropShadows", sol::property(itsy_bitsy::read<HumanFlags, 21>, itsy_bitsy::write<HumanFlags, 21>), //int32 - 1
		"IsTurning", sol::property(itsy_bitsy::read<HumanFlags, 22>, itsy_bitsy::write<HumanFlags, 22>), //int32 - 1 
		"IsFalling", sol::property(itsy_bitsy::read<HumanFlags, 23>, itsy_bitsy::write<HumanFlags, 23>), //int32 - 1 
		"DontDeformBones", sol::property(itsy_bitsy::read<HumanFlags, 24>, itsy_bitsy::write<HumanFlags, 24>), //int32 - 1 
		"DontLodBones", sol::property(itsy_bitsy::read<HumanFlags, 25>, itsy_bitsy::write<HumanFlags, 25>), //int32 - 1 
		"PlayingEquipAnim", sol::property(itsy_bitsy::read<HumanFlags, 26>, itsy_bitsy::write<HumanFlags, 26>), //int32 - 1 
		"PlayingUnequipAnim", sol::property(itsy_bitsy::read<HumanFlags, 27>, itsy_bitsy::write<HumanFlags, 27>), //int32 - 1 
		"DoInstantEquip", sol::property(itsy_bitsy::read<HumanFlags, 28>, itsy_bitsy::write<HumanFlags, 28>), //int32 - 1 
		"AnimDirectBlend", sol::property(itsy_bitsy::read<HumanFlags, 29>, itsy_bitsy::write<HumanFlags, 29>), //int32 - 1 
		"StartJump", sol::property(itsy_bitsy::read<HumanFlags, 30>, itsy_bitsy::write<HumanFlags, 30>), //int32 - 1 
		"SuperJump", sol::property(itsy_bitsy::read<HumanFlags, 31>, itsy_bitsy::write<HumanFlags, 31>), //int32 - 1 
		"ProcessedThisFrame", sol::property(itsy_bitsy::read<HumanFlags, 32>, itsy_bitsy::write<HumanFlags, 32>), //int32 - 1 
		"SilentVehicleStart", sol::property(itsy_bitsy::read<HumanFlags, 33>, itsy_bitsy::write<HumanFlags, 33>), //int32 - 1 
		"SupressFleeOnVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 34>, itsy_bitsy::write<HumanFlags, 34>), //int32 - 1 
		"DeathFunctionDone", sol::property(itsy_bitsy::read<HumanFlags, 35>, itsy_bitsy::write<HumanFlags, 35>), //int32 - 1 
		"FadingIn", sol::property(itsy_bitsy::read<HumanFlags, 36>, itsy_bitsy::write<HumanFlags, 36>), //int32 - 1 
		"FadingOut", sol::property(itsy_bitsy::read<HumanFlags, 37>, itsy_bitsy::write<HumanFlags, 37>), //int32 - 1 
		"FadingOutFromNano", sol::property(itsy_bitsy::read<HumanFlags, 38>, itsy_bitsy::write<HumanFlags, 38>), //int32 - 1 
		"IsNanoEffectCurrentlyApplied", sol::property(itsy_bitsy::read<HumanFlags, 39>, itsy_bitsy::write<HumanFlags, 39>), //int32 - 1 
		"OnFire", sol::property(itsy_bitsy::read<HumanFlags, 40>, itsy_bitsy::write<HumanFlags, 40>), //int32 - 1 
		"DroppedCash", sol::property(itsy_bitsy::read<HumanFlags, 41>, itsy_bitsy::write<HumanFlags, 41>), //int32 - 1 
		"OnMover", sol::property(itsy_bitsy::read<HumanFlags, 42>, itsy_bitsy::write<HumanFlags, 42>), //int32 - 1 
		"RecalculateAtNode", sol::property(itsy_bitsy::read<HumanFlags, 43>, itsy_bitsy::write<HumanFlags, 43>), //int32 - 1 
		"SpinebendingDone", sol::property(itsy_bitsy::read<HumanFlags, 44>, itsy_bitsy::write<HumanFlags, 44>), //int32 - 1 
		"LastDestinationInRepulsor", sol::property(itsy_bitsy::read<HumanFlags, 45>, itsy_bitsy::write<HumanFlags, 45>), //int32 - 1 
		"JumpingFromBuilding", sol::property(itsy_bitsy::read<HumanFlags, 46>, itsy_bitsy::write<HumanFlags, 46>), //int32 - 1 
		"IsOnLadder", sol::property(itsy_bitsy::read<HumanFlags, 47>, itsy_bitsy::write<HumanFlags, 47>), //int32 - 1 
		"LadderForceSlide", sol::property(itsy_bitsy::read<HumanFlags, 48>, itsy_bitsy::write<HumanFlags, 48>), //int32 - 1 
		"LadderForceExit", sol::property(itsy_bitsy::read<HumanFlags, 49>, itsy_bitsy::write<HumanFlags, 49>), //int32 - 1 
		"LadderReEquipWeapon", sol::property(itsy_bitsy::read<HumanFlags, 50>, itsy_bitsy::write<HumanFlags, 50>), //int32 - 1 
		"AllowFlyingEquips", sol::property(itsy_bitsy::read<HumanFlags, 51>, itsy_bitsy::write<HumanFlags, 51>), //int32 - 1 
		"CorpseSpotted", sol::property(itsy_bitsy::read<HumanFlags, 52>, itsy_bitsy::write<HumanFlags, 52>), //int32 - 1 
		"CorpseSpottedByEnemy", sol::property(itsy_bitsy::read<HumanFlags, 53>, itsy_bitsy::write<HumanFlags, 53>), //int32 - 1 
		"DeathReported", sol::property(itsy_bitsy::read<HumanFlags, 54>, itsy_bitsy::write<HumanFlags, 54>), //int32 - 1 
		"RaidDeathAck", sol::property(itsy_bitsy::read<HumanFlags, 55>, itsy_bitsy::write<HumanFlags, 55>), //int32 - 1 
		"AnchorOrient", sol::property(itsy_bitsy::read<HumanFlags, 56>, itsy_bitsy::write<HumanFlags, 56>), //int32 - 1 
		"BonesTransformedThisFrame", sol::property(itsy_bitsy::read<HumanFlags, 57>, itsy_bitsy::write<HumanFlags, 57>), //int32 - 1 
		"UseCurrentVelocity", sol::property(itsy_bitsy::read<HumanFlags, 58>, itsy_bitsy::write<HumanFlags, 58>), //int32 - 1 
		"UseAsFinalVelocity", sol::property(itsy_bitsy::read<HumanFlags, 59>, itsy_bitsy::write<HumanFlags, 59>), //int32 - 1 
		"AimAtPos", sol::property(itsy_bitsy::read<HumanFlags, 60>, itsy_bitsy::write<HumanFlags, 60>), //int32 - 1 
		"BlockForcedMovement", sol::property(itsy_bitsy::read<HumanFlags, 61>, itsy_bitsy::write<HumanFlags, 61>), //int32 - 1 
		"CancellingMeleeAttack", sol::property(itsy_bitsy::read<HumanFlags, 62>, itsy_bitsy::write<HumanFlags, 62>), //int32 - 1 
		"DoContinuousMeleeDamage", sol::property(itsy_bitsy::read<HumanFlags, 63>, itsy_bitsy::write<HumanFlags, 63>), //int32 - 1 
		"InAirMelee", sol::property(itsy_bitsy::read<HumanFlags, 64>, itsy_bitsy::write<HumanFlags, 64>), //int32 - 1 
		"CantHitWithMelee", sol::property(itsy_bitsy::read<HumanFlags, 65>, itsy_bitsy::write<HumanFlags, 65>), //int32 - 1 
		"InvulnerableToDebris", sol::property(itsy_bitsy::read<HumanFlags, 66>, itsy_bitsy::write<HumanFlags, 66>), //int32 - 1 
		"OverrideDefaultAnimState", sol::property(itsy_bitsy::read<HumanFlags, 67>, itsy_bitsy::write<HumanFlags, 67>), //int32 - 1 
		"OverrideDefaultFireAnim", sol::property(itsy_bitsy::read<HumanFlags, 68>, itsy_bitsy::write<HumanFlags, 68>), //int32 - 1 
		"MovingAndTransitioningStates", sol::property(itsy_bitsy::read<HumanFlags, 69>, itsy_bitsy::write<HumanFlags, 69>), //int32 - 1 
		"CheckForCover", sol::property(itsy_bitsy::read<HumanFlags, 70>, itsy_bitsy::write<HumanFlags, 70>), //int32 - 1 
		"JumpTakeOff", sol::property(itsy_bitsy::read<HumanFlags, 71>, itsy_bitsy::write<HumanFlags, 71>), //int32 - 1 
		"RotateInternalHeadingUpdated", sol::property(itsy_bitsy::read<HumanFlags, 72>, itsy_bitsy::write<HumanFlags, 72>), //int32 - 1 
		"CrouchCover", sol::property(itsy_bitsy::read<HumanFlags, 73>, itsy_bitsy::write<HumanFlags, 73>), //int32 - 1 
		"CoverCrouchHighOnly", sol::property(itsy_bitsy::read<HumanFlags, 74>, itsy_bitsy::write<HumanFlags, 74>), //int32 - 1 
		"CoverCrouchNoLean", sol::property(itsy_bitsy::read<HumanFlags, 75>, itsy_bitsy::write<HumanFlags, 75>), //int32 - 1 
		"SideFiring", sol::property(itsy_bitsy::read<HumanFlags, 76>, itsy_bitsy::write<HumanFlags, 76>), //int32 - 1 
		"SideFiringWalkBack", sol::property(itsy_bitsy::read<HumanFlags, 77>, itsy_bitsy::write<HumanFlags, 77>), //int32 - 1 
		"RagdollOnImpactAllCollisions", sol::property(itsy_bitsy::read<HumanFlags, 78>, itsy_bitsy::write<HumanFlags, 78>), //int32 - 1 
		"RagdollOnImpactUseRagdollPos", sol::property(itsy_bitsy::read<HumanFlags, 79>, itsy_bitsy::write<HumanFlags, 79>), //int32 - 1 
		"DiveCapsule", sol::property(itsy_bitsy::read<HumanFlags, 80>, itsy_bitsy::write<HumanFlags, 80>), //int32 - 1 
		"MaintainAmbientProps", sol::property(itsy_bitsy::read<HumanFlags, 81>, itsy_bitsy::write<HumanFlags, 81>), //int32 - 1 
		"LeaningDisabled", sol::property(itsy_bitsy::read<HumanFlags, 82>, itsy_bitsy::write<HumanFlags, 82>), //int32 - 1 
		"OverrideSterringHeadingOffset", sol::property(itsy_bitsy::read<HumanFlags, 83>, itsy_bitsy::write<HumanFlags, 83>), //int32 - 1 
		"PushesOtherHumans", sol::property(itsy_bitsy::read<HumanFlags, 84>, itsy_bitsy::write<HumanFlags, 84>), //int32 - 1 
		"PushesDebrisScripted", sol::property(itsy_bitsy::read<HumanFlags, 85>, itsy_bitsy::write<HumanFlags, 85>), //int32 - 1 
		"AllowSteepSlopes", sol::property(itsy_bitsy::read<HumanFlags, 86>, itsy_bitsy::write<HumanFlags, 86>), //int32 - 1 
		"ExternalForceApplied", sol::property(itsy_bitsy::read<HumanFlags, 87>, itsy_bitsy::write<HumanFlags, 87>), //int32 - 1 
		"RagdollShot", sol::property(itsy_bitsy::read<HumanFlags, 88>, itsy_bitsy::write<HumanFlags, 88>), //int32 - 1 
		"SavedPushesDebrisScripted", sol::property(itsy_bitsy::read<HumanFlags, 89>, itsy_bitsy::write<HumanFlags, 89>), //int32 - 1 
		"FilterHandleValid", sol::property(itsy_bitsy::read<HumanFlags, 90>, itsy_bitsy::write<HumanFlags, 90>), //int32 - 1 
		"JustGotUpFromRagdoll", sol::property(itsy_bitsy::read<HumanFlags, 91>, itsy_bitsy::write<HumanFlags, 91>), //int32 - 1 
		"DisablePathSmoothingForRequest", sol::property(itsy_bitsy::read<HumanFlags, 92>, itsy_bitsy::write<HumanFlags, 92>), //int32 - 1 
		"DisableAllPathSmoothing", sol::property(itsy_bitsy::read<HumanFlags, 93>, itsy_bitsy::write<HumanFlags, 93>), //int32 - 1 
		"InFetalPosition", sol::property(itsy_bitsy::read<HumanFlags, 94>, itsy_bitsy::write<HumanFlags, 94>), //int32 - 1 
		"DisallowVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 95>, itsy_bitsy::write<HumanFlags, 95>), //int32 - 1 
		"LimitedVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 96>, itsy_bitsy::write<HumanFlags, 96>), //int32 - 1 
		"DriverlessExitOnly", sol::property(itsy_bitsy::read<HumanFlags, 97>, itsy_bitsy::write<HumanFlags, 97>), //int32 - 1 
		"StuckInVehicle", sol::property(itsy_bitsy::read<HumanFlags, 98>, itsy_bitsy::write<HumanFlags, 98>), //int32 - 1 
		"ConvoyVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 99>, itsy_bitsy::write<HumanFlags, 99>), //int32 - 1 
		"DisallowVehicleEntry", sol::property(itsy_bitsy::read<HumanFlags, 100>, itsy_bitsy::write<HumanFlags, 100>), //int32 - 1 
		"DisallowVehicleDrive", sol::property(itsy_bitsy::read<HumanFlags, 101>, itsy_bitsy::write<HumanFlags, 101>), //int32 - 1 
		"AmbientEDF", sol::property(itsy_bitsy::read<HumanFlags, 102>, itsy_bitsy::write<HumanFlags, 102>), //int32 - 1 
		"BashedCharacterController", sol::property(itsy_bitsy::read<HumanFlags, 103>, itsy_bitsy::write<HumanFlags, 103>), //int32 - 1 
		"HeadLoaded", sol::property(itsy_bitsy::read<HumanFlags, 104>, itsy_bitsy::write<HumanFlags, 104>), //int32 - 1 
		"LodHeadLoaded", sol::property(itsy_bitsy::read<HumanFlags, 105>, itsy_bitsy::write<HumanFlags, 105>), //int32 - 1 
		"InVehicleInvisible", sol::property(itsy_bitsy::read<HumanFlags, 106>, itsy_bitsy::write<HumanFlags, 106>), //int32 - 1 
		"HighPriorityTarget", sol::property(itsy_bitsy::read<HumanFlags, 107>, itsy_bitsy::write<HumanFlags, 107>), //int32 - 1 
		"HealthChangeWasNegative", sol::property(itsy_bitsy::read<HumanFlags, 108>, itsy_bitsy::write<HumanFlags, 108>), //int32 - 1 
		"VoiceLinePlay2D", sol::property(itsy_bitsy::read<HumanFlags, 109>, itsy_bitsy::write<HumanFlags, 109>), //int32 - 1 
		"VoiceLinePainOnly", sol::property(itsy_bitsy::read<HumanFlags, 110>, itsy_bitsy::write<HumanFlags, 110>), //int32 - 1 
		"KilledByKillzone", sol::property(itsy_bitsy::read<HumanFlags, 111>, itsy_bitsy::write<HumanFlags, 111>), //int32 - 1 
		"FirstTimeStreamed", sol::property(itsy_bitsy::read<HumanFlags, 112>, itsy_bitsy::write<HumanFlags, 112>), //int32 - 1 
		"Tired", sol::property(itsy_bitsy::read<HumanFlags, 113>, itsy_bitsy::write<HumanFlags, 113>), //int32 - 1 
		"UseBigsteps", sol::property(itsy_bitsy::read<HumanFlags, 114>, itsy_bitsy::write<HumanFlags, 114>), //int32 - 1 
		"Stuck", sol::property(itsy_bitsy::read<HumanFlags, 115>, itsy_bitsy::write<HumanFlags, 115>), //int32 - 1 
		"LastPfFailed", sol::property(itsy_bitsy::read<HumanFlags, 116>, itsy_bitsy::write<HumanFlags, 116>), //int32 - 1 
		"ExtendedStuck", sol::property(itsy_bitsy::read<HumanFlags, 117>, itsy_bitsy::write<HumanFlags, 117>), //int32 - 1 
		"XrayVisible", sol::property(itsy_bitsy::read<HumanFlags, 118>, itsy_bitsy::write<HumanFlags, 118>), //int32 - 1 
		"WasGibbed", sol::property(itsy_bitsy::read<HumanFlags, 119>, itsy_bitsy::write<HumanFlags, 119>), //int32 - 1 
		"PreventRagdollSfx", sol::property(itsy_bitsy::read<HumanFlags, 120>, itsy_bitsy::write<HumanFlags, 120>), //int32 - 1 
		"AlwaysShowOnMinimap", sol::property(itsy_bitsy::read<HumanFlags, 121>, itsy_bitsy::write<HumanFlags, 121>), //int32 - 1 
		"UsedDeathBuffer", sol::property(itsy_bitsy::read<HumanFlags, 122>, itsy_bitsy::write<HumanFlags, 122>), //int32 - 1 
		"DoNotConvertToGuerrilla", sol::property(itsy_bitsy::read<HumanFlags, 123>, itsy_bitsy::write<HumanFlags, 123>), //int32 - 1 
		"DoNotPlayAmbientOrGreetLines", sol::property(itsy_bitsy::read<HumanFlags, 124>, itsy_bitsy::write<HumanFlags, 124>), //int32 - 1 
		"DisallowFlinchesAndRagdolls", sol::property(itsy_bitsy::read<HumanFlags, 125>, itsy_bitsy::write<HumanFlags, 125>), //int32 - 1 
		"OnlyUseActionNodes", sol::property(itsy_bitsy::read<HumanFlags, 126>, itsy_bitsy::write<HumanFlags, 126>), //int32 - 1 
		"ComplainWhenShot", sol::property(itsy_bitsy::read<HumanFlags, 127>, itsy_bitsy::write<HumanFlags, 127>) //int32 - 1 
	);
	RfgTable.new_usertype<HumanMPFlags>
	(
		"HumanMPFlags",
		"new", sol::constructors<HumanMPFlags(), HumanMPFlags(const HumanMPFlags&)>(),
		"IsMultiplayer", sol::property(itsy_bitsy::read<ObjectFlags, 0>, itsy_bitsy::write<ObjectFlags, 0>), //int32 - 1
		"MeleePrimaryID", sol::property(itsy_bitsy::read<ObjectFlags, 1>, itsy_bitsy::write<ObjectFlags, 1>), //int32 - 2
		"MeleeSecondaryID", sol::property(itsy_bitsy::read<ObjectFlags, 3>, itsy_bitsy::write<ObjectFlags, 3>), //int32 - 2
		"MeleeTertiaryID", sol::property(itsy_bitsy::read<ObjectFlags, 5>, itsy_bitsy::write<ObjectFlags, 5>), //int32 - 2
		"MeleeFirearmID", sol::property(itsy_bitsy::read<ObjectFlags, 7>, itsy_bitsy::write<ObjectFlags, 7>), //int32 - 2
		"JumpID", sol::property(itsy_bitsy::read<ObjectFlags, 9>, itsy_bitsy::write<ObjectFlags, 9>), //int32 - 2
		"Vehicle", sol::property(itsy_bitsy::read<ObjectFlags, 11>, itsy_bitsy::write<ObjectFlags, 11>), //int32 - 1
		"Turret", sol::property(itsy_bitsy::read<ObjectFlags, 12>, itsy_bitsy::write<ObjectFlags, 12>), //int32 - 1
		"SwapWeapon", sol::property(itsy_bitsy::read<ObjectFlags, 13>, itsy_bitsy::write<ObjectFlags, 13>), //int32 - 1
		"FirearmTriggerDownID", sol::property(itsy_bitsy::read<ObjectFlags, 14>, itsy_bitsy::write<ObjectFlags, 14>), //int32 - 2
		"FirearmTriggerUpID", sol::property(itsy_bitsy::read<ObjectFlags, 16>, itsy_bitsy::write<ObjectFlags, 16>), //int32 - 2
		"ThrowAttackID", sol::property(itsy_bitsy::read<ObjectFlags, 18>, itsy_bitsy::write<ObjectFlags, 18>), //int32 - 2
		"ChargeWeapon", sol::property(itsy_bitsy::read<ObjectFlags, 20>, itsy_bitsy::write<ObjectFlags, 20>), //int32 - 2
		"RunningAttack", sol::property(itsy_bitsy::read<ObjectFlags, 22>, itsy_bitsy::write<ObjectFlags, 22>), //int32 - 1
		"InAirDetonate", sol::property(itsy_bitsy::read<ObjectFlags, 23>, itsy_bitsy::write<ObjectFlags, 23>), //int32 - 1
		"DetonatedCharges", sol::property(itsy_bitsy::read<ObjectFlags, 24>, itsy_bitsy::write<ObjectFlags, 24>), //int32 - 1
		"Jetpack", sol::property(itsy_bitsy::read<ObjectFlags, 25>, itsy_bitsy::write<ObjectFlags, 25>) //int32 - 1
	);
	RfgTable.new_usertype<Object>
	(
		"Object",
		"new", sol::constructors<Object(), Object(const Object&)>(),
		"Position", &Object::Position,
		"ChildPtr", &Object::ChildPtr,
		"ChildNext", &Object::ChildNext,
		"ChildPrevious", &Object::ChildPrevious,
		"AttachInfo", &Object::AttachInfo,
		"HavokHandle", &Object::HavokHandle,
		"ContactInfo", &Object::ContactInfo,
		"ObjFlags", &Object::ObjFlags,
		//"RemoteObjFlags", &Object::RemoteObjFlags,
		//"MPDcmoIndex", &Object::MPDcmoIndex,
		"CheckingReset", &Object::CheckingReset,
		"NameIndex", &Object::NameIndex,
		"FlaggedNext", &Object::FlaggedNext,
		"FlaggedPrevious", &Object::FlaggedPrevious,
		"Handle", &Object::Handle,
		"Parent", &Object::Parent,
		"BPOHandle", &Object::BPOHandle,
		"AllIndex", &Object::AllIndex,
		"TypeIndex", &Object::TypeIndex,
		"SubtypeIndex", &Object::SubtypeIndex,
		"ObjectType", &Object::ObjectType,
		"SubType", &Object::SubType,
		"LastKnownBMin", &Object::LastKnownBMin,
		"LastKnownBMax", &Object::LastKnownBMax,
		"SRID", &Object::SRID
	);
	RfgTable.new_usertype<Human>
	(
		"Human",
		"new", sol::constructors<Human(), Human(const Human&)>(),
		//"ResourceDependentData", &Human::ResourceDependentData,
		"Flags", &Human::Flags,
		"MPFlags", &Human::MPFlags,
		"LastTriggerDownFrame", &Human::LastTriggerDownFrame,
		"Info", &Human::Info,
		"RenderDistance", &Human::render_distance,
		"XRayMaterial", &Human::XRayMaterial,
		"XrayRenderAlpha", &Human::XrayRenderAlpha,
		"Rank", &Human::Rank,
		"ApproxLocalBmin", &Human::ApproxLocalBmin,
		"ApproxLocalBmax", &Human::ApproxLocalBmax,
		"LastPosition", &Human::LastPosition,
		"PathData", &Human::PathData,
		"TurnToTarget", &Human::TurnToTarget,
		"NavCellDetourRequestHandle", &Human::NavCellDetourRequestHandle,
		"RaycastHitInfo", &Human::RaycastHitInfo,
		"Velocity", &Human::Velocity,
		"ActualVelocity", &Human::ActualVelocity,
		"TransformFramesSkipped", &Human::TransformFramesSkipped,
		"SteeringVector", &Human::SteeringVector,
		"MoveSpeed", &Human::MoveSpeed,
		"SteeringHeadingOffset", &Human::SteeringHeadingOffset,
		"RotateDirection", &Human::RotateDirection,
		"StateSpeedThrottle", &Human::StateSpeedThrottle,
		"RotateHeadingLeft", &Human::RotateHeadingLeft,
		"RotateHeadingRight", &Human::RotateHeadingRight,
		"RotateInternalHeading", &Human::RotateInternalHeading,
		"InertialMotion", &Human::InertialMotion,
		"GroundObjectHandle", &Human::GroundObjectHandle,
		"GroundObjectContactPos", &Human::GroundObjectContactPos,
		"GroundObjectAltBodyIDX", &Human::GroundObjectAltBodyIDX,
		"GroundObjectShapeKey", &Human::GroundObjectShapeKey,
		"GroundObjectNormal", &Human::GroundObjectNormal,
		"ObjectFilterHandle", &Human::ObjectFilterHandle,
		"BlockMovementAnimation", &Human::BlockMovementAnimation,
		"BlockSteeringVector", &Human::BlockSteeringVector,
		"BlockMovementType", &Human::BlockMovementType,
		"BlockSteeringHeadingOffset", &Human::BlockSteeringHeadingOffset,
		"ReleasedMovementAnim", &Human::ReleasedMovementAnim,
		"ReleasedMovementType", &Human::ReleasedMovementType,
		"CurrentState", &Human::CurrentState,
		"CurrentMovementState", &Human::CurrentMovementState,
		"CurrentStance", &Human::CurrentStance,
		"LastStance", &Human::LastStance,
		"MovementMode", &Human::MovementMode,
		"MovementSubmode", &Human::MovementSubmode,
		"PreviousMovementMode", &Human::PreviousMovementMode,
		"CustomFireAnimation", &Human::CustomFireAnimation,
		"WalkAnimationSpeedPercentage", &Human::WalkAnimationSpeedPercentage,
		"FrametimeTally", &Human::FrametimeTally,
		"ActualVelocityMagnitude", &Human::ActualVelocityMagnitude,
		"MaxSpeed", &Human::MaxSpeed,
		"FallingVelocityMagnitude", &Human::FallingVelocityMagnitude,
		"NotMovingUpdate", &Human::NotMovingUpdate,
		"CharInstance", &Human::CharInstance,
		//"ClothSim", &Human::ClothSim,
		"BoneLODLevel", &Human::BoneLODLevel,
		"WepAnimationFlags", &Human::WepAnimationFlags,
		"RagdollState", &Human::RagdollState,
		"RagdollSourceHumanHandle", &Human::RagdollSourceHumanHandle,
		"RagdollIDX", &Human::RagdollIDX,
		"RagdollBlendPercentage", &Human::RagdollBlendPercentage,
		"RagdollLastFrameVelocity", &Human::RagdollLastFrameVelocity,
		"RagdollOnImpactTime", &Human::RagdollOnImpactTime,
		"RagdollOnImpactMinVelocity", &Human::RagdollOnImpactMinVelocity,
		"RagdollDamaged", &Human::RagdollDamaged,
		"RootBoneOffset", &Human::RootBoneOffset,
		"NanoMaterialFX", &Human::NanoMaterialFX, //16 element c-array or uints
		"MaterialFXHandleForHeadSkin", &Human::MaterialFXHandleForHeadSkin,
		"LastValidPositionBeforeRagdoll", &Human::LastValidPositionBeforeRagdoll, //16 element c-array of vectors
		"RagdollNumCollisionWithWalker", &Human::RagdollNumCollisionsWithWalker,
		"IK_Joints", &Human::IK_Joints, //4 size array of IK_Joint
		"SpinebendData", &Human::SpinebendData,
		"HeadMorphs", &Human::HeadMorphs,
		"InitialMaxHitPoints", &Human::InitialMaxHitPoints,
		"MaxHitPoints", &Human::MaxHitPoints,
		"HitPoints", &Human::HitPoints,
		"MaxKnockdownHits", &Human::MaxKnockdownHits,
		"KnockdownHits", &Human::KnockdownHits,
		"KnockdownTimestamp", &Human::KnockdownTimestamp,
		"KnockdownTimeoutTimestamp", &Human::KnockdownTimeoutTimestamp,
		"Combat", &Human::Combat,
		"CollisionDamageTimer", &Human::CollisionDamageTimer,
		"CurrentCollisionDamage", &Human::CurrentCollisionDamage,
		"DoRagdollTimestamp", &Human::DoRagdollTimestamp,
		"FacialPoseTimestamp", &Human::FacialPoseTimestamp,
		"TurretHoldAnimations", &Human::TurretHoldAnimations,
		"Cash", &Human::Cash,
		"Inventory", &Human::Inventory,
		"DesiredEquippedInvItem", &Human::DesiredEquippedInvItem,
		"LastEquippedWeapon", &Human::LastEquippedWeapon,
		"SecondLastEquippedWeapon", &Human::SecondLastEquippedWeapon,
		"GrenadeWeapon", &Human::GrenadeWeapon,
		//"AnimationPropInfo", &Human::AnimationPropInfo,
		"OffhandProjectileHandle", &Human::OffhandProjectileHandle,
		"ShieldHandle", &Human::ShieldHandle,
		"ReloadTimer", &Human::ReloadTimer,
		"EquipTagIndex", &Human::EquipTagIndex,
		"EquipOffhandTagIndex", &Human::EquipOffhandTagIndex,
		"RootBoneIndex", &Human::RootBoneIndex,
		"LeftFootBoneIndex", &Human::LeftFootBoneIndex,
		"RightFootBoneIndex", &Human::RightFootBoneIndex,
		"LeftShoulderBoneIndex", &Human::LeftShoulderBoneIndex,
		"RightShoulderBoneIndex", &Human::RightShoulderBoneIndex,
		"LeftHandBoneIndex", &Human::LeftHandBoneIndex,
		"RightHandBoneIndex", &Human::RightHandBoneIndex,
		"LeftHipBoneIndex", &Human::LeftFootBoneIndex,
		"RightHipBoneIndex", &Human::RightHipBoneIndex,
		"RunStandBlendPoseWeight", &Human::RunStandBlendPoseWeight,
		"LeanWeight", &Human::LeanWeight,
		"LeanDirection", &Human::LeanDirection,
		"LeanDisabled", &Human::LeanDisabled,
		"LeanLastSteeringVector", &Human::LeanLastSteeringVector,
		"FootPlanted", &Human::FootPlanted,
		"FootPlantTime", &Human::FootPlantTime,
		"IsTurning", &Human::IsTurning,
		"StartingTurn", &Human::StartingTurn,
		"RenderAlpha", &Human::RenderAlpha,
		"CameraAlphaOverride", &Human::CameraAlphaOverride,
		"CastsTransparentShadows", &Human::CastsTransparentShadows,
		"FadeTimer", &Human::FadeTimer,
		"FadeTime", &Human::FadeTime,
		"StealthPercent", &Human::StealthPercent,
		"VehicleHandle", &Human::VehicleHandle,
		"ReservedVehicleHandle", &Human::ReservedVehicleHandle,
		"VehicleSeatIDX", &Human::VehicleSeatIDX,
		"BoredIdleTimestamp", &Human::BoredIdleTimestamp,
		"CorpseCleanupTimer", &Human::CorpseCleanupTimer,
		"TurnOffFireTimestamp", &Human::TurnOffFireTimestamp,
		"HealthRestoreTimestamp", &Human::HealthRestoreTimestamp,
		"HealthRestoreHitPoints", &Human::HealthRestoreHitPoints,
		"HealthRestoreMinimumHitPoints", &Human::HealthRestoreMinimumHitPoints,
		"LookAtPos", &Human::LookAtPos,
		"LookAtHandle", &Human::LookAtHandle,
		"LookAtSpeed", &Human::LookAtSpeed,
		"AimOverrideDirection", &Human::AimOverrideDirection,
		"DamagePercent", &Human::DamagePercent,
		"DamageFunctionHandle", &Human::DamageFunctionHandle,
		"DeathFunctionHandle", &Human::DeathFunctionHandle,
		"BreathTimer", &Human::BreathTimer,
		"CrouchToStandTestTimestamp", &Human::CrouchToStandTestTimestamp,
		"LadderHandle", &Human::LadderHandle,
		"LadderSlideSpeed", &Human::LadderSlideSpeed,
		"LadderGrabRung", &Human::LadderGrabRung,
		"LadderSlidePlayID", &Human::LadderSlidePlayID,
		"CodeDrivenStartJump", &Human::CodeDrivenStartJump,
		"CodeDrivenJumpTimer", &Human::CodeDrivenJumpTimer,
		"CodeDrivenJumpHeight", &Human::CodeDrivenJumpHeight,
		"JumpStateTimer", &Human::JumpStateTimer,
		"LastSupported", &Human::LastSupported,
		"AirTime", &Human::AirTime,
		"UpdateTimer", &Human::UpdateTimer,
		"ImportanceLevel", &Human::ImportanceLevel,
		"ScriptedActionNodeHandle", &Human::ScriptedActionNodeHandle,
		"NanoCBInfo", &Human::NanoCBInfo,
		"NanoIndex", &Human::NanoIndex,
		"ActionNodeData", &Human::ActionNodeData,
		"LightEffects", &Human::LightEffects,
		"LightTags", &Human::LightTags,
		"AvoidanceCheckTimer", &Human::AvoidanceCheckTimer,
		"AvoidanceRequestTimer", &Human::AvoidanceRequestTimer,
		"AvoidanceRequestHuman", &Human::AvoidanceRequestHuman,
		"AvoidanceMoveDirection", &Human::AvoidanceMoveDirection,
		"AvoidanceHintDirection", &Human::AvoidanceHintDirection,
		"AvoidancePauseTimer", &Human::AvoidancePauseTimer,
		"AvoidanceOriginalMovementState", &Human::AvoidanceOriginalMovementState,
		"MinimapFlags", &Human::MinimapFlags,
		//"AmpPropInfo", &Human::AmpPropInfo,
		"EquippedInventoryItemLastFrame", &Human::EquippedInventoryItemLastFrame,
		"EquippedInventoryItem", &Human::EquippedInventoryItem,
		//"Voice", &Human::Voice,
		"CurrentTeam", &Human::CurrentTeam,
		"UndercoverTeam", &Human::UndercoverTeam,
		"DialogueFoleyInfo", &Human::DialogueFoleyInfo,
		"QueuedVoiceLine", &Human::QueuedVoiceLine,
		"SituationalVoiceLine", &Human::SituationalVoiceLine,
		"VoicePriority", &Human::VoicePriority,
		"VoiceCuePriority", &Human::VoiceCuePriority,
		"RadioInstance", &Human::RadioInstance,
		"VoiceInstance", &Human::VoiceInstance,
		"VoiceTimeSinceFinish", &Human::VoiceTimeSinceFinish,
		"LipsyncHandle", &Human::LipsyncHandle,
		"VoiceDelayTime", &Human::voice_delay_time,
		//"UnimVoiceDelayCBCallback", &Human::Unim_VoiceDelayCBCallback,
		//"VoiceDelayCBData", &Human::VoiceDelayCBData,
		"AcknowledgedTime", &Human::AcknowledgedTime,
		"ReportedTimer", &Human::ReportedTimer,
		"Lifetime", &Human::Lifetime
	);
}

void ScriptManager::ScanScriptsFolder()
{
	try 
	{
		Scripts.clear();
		std::string ScriptFolderPath(GetEXEPath(false) + "RFGR Script Loader/Scripts/");

		std::string ThisScriptPath;
		std::string ThisScriptFolderPath;
		std::string ThisScriptName;

		for (auto& i : fs::directory_iterator(ScriptFolderPath))
		{
			if (IsValidScriptExtensionFromPath(i.path().string()))
			{
				ThisScriptPath = i.path().string();
				ThisScriptFolderPath = GetScriptFolderFromPath(i.path().string());
				ThisScriptName = GetScriptNameFromPath(i.path().string());
				Scripts.push_back(Script(ThisScriptPath, ThisScriptFolderPath, ThisScriptName));

				//Logger::Log(i.path().string(), LogInfo);
				//Logger::Log("Script Name: " + ThisScriptName, LogInfo);
				//Logger::Log("Script Folder: " + ThisScriptFolderPath, LogInfo);
			}
		}
	}
	catch(std::exception& Ex)
	{
		std::string ExceptionInfo = Ex.what();
		ExceptionInfo += " \nstd::exception when scanning scripts folder, Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogFatalError, true, true);
		//strcpy(Ex.what, ExceptionInfo.c_str());
		//throw(Ex);
	}
}

void ScriptManager::ScanScriptsSubFolders()
{

}

bool ScriptManager::RunScript(std::string FullPath)
{
	if (IsValidScriptExtensionFromPath(FullPath))
	{
		try
		{
			auto CodeResult = LuaState.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
			{
				return pfr;
			}, sol::load_mode::text);

			if (!CodeResult.valid())
			{
				sol::error ScriptError = CodeResult;
				std::exception ScriptException(ScriptError.what());
				throw(ScriptException);
			}
			return true;
		}
		catch (std::exception& Exception)
		{
			Logger::Log(std::string("Exception caught when running " + GetScriptNameFromPath(FullPath) + std::string(Exception.what())), LogLua | LogError);
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ScriptManager::RunScript(size_t Index)
{
	std::string FullPath = Scripts[Index].FullPath;
	try
	{
		auto CodeResult = LuaState.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		}, sol::load_mode::text);

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Scripts[Index].Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

bool ScriptManager::RunStringAsScript(std::string Buffer, std::string Name)
{
	try
	{
		auto CodeResult = LuaState.script(Buffer, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		});

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

std::string ScriptManager::GetScriptNameFromPath(std::string FullPath)
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(i + 1, FullPath.length() - i);
			}
		}
	}
	return std::string();
}

std::string ScriptManager::GetScriptFolderFromPath(std::string FullPath)
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(0, i + 1);
			}
		}
	}
	return std::string();
}

std::string ScriptManager::GetScriptExtensionFromPath(std::string FullPath)
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (FullPath.compare(i, 1, ".") == 0)
		{
			return FullPath.substr(i + 1, FullPath.length() - i);
		}
	}
	return std::string();
}

bool ScriptManager::IsValidScriptExtensionFromPath(std::string FullPath)
{
	if (IsValidScriptExtension(GetScriptExtensionFromPath(FullPath)))
	{
		return true;
	}
	return false;
}

bool ScriptManager::IsValidScriptExtension(std::string Extension)
{
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
	if (Extension == "lua")
	{
		return true;
	}
	return false;
}

