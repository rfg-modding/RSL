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
		""
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

