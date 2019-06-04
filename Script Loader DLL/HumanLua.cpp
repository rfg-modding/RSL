#include "HumanLua.h"
#include "Functions.h"

void Lua::BindIKJoint(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<IK_Joint>();
	Utype.set("AnchorTag", &IK_Joint::anchor_tag);
	Utype.set("JointTag", &IK_Joint::joint_tag);
	Utype.set("IkTag", &IK_Joint::ik_tag);
	Utype.set("IkStrength", &IK_Joint::ik_strength);
	Utype.set("IkRateOfChange", &IK_Joint::ik_rate_of_change);
	Utype.set("FreezeObjHandle", &IK_Joint::freeze_obj_handle);
	Utype.set("FreezeOffsetPos", &IK_Joint::freeze_offset_pos);
	Utype.set("Location", &IK_Joint::location);
	RfgTable.set_usertype("IKJoint", Utype);
}

void Lua::BindWeaponAnimationFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<WeaponAnimationFlags>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Prone", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 0>, itsy_bitsy::write<WeaponAnimationFlags, 0>)); //uint32 - 1
	Utype.set("Crouch", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 1>, itsy_bitsy::write<WeaponAnimationFlags, 1>)); //uint32 - 1
	Utype.set("DownReady", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 2>, itsy_bitsy::write<WeaponAnimationFlags, 2>)); //uint32 - 1
	Utype.set("Ready", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 3>, itsy_bitsy::write<WeaponAnimationFlags, 3>)); //uint32 - 1
	Utype.set("Aim", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 4>, itsy_bitsy::write<WeaponAnimationFlags, 4>)); //uint32 - 1
	Utype.set("FineAim", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 5>, itsy_bitsy::write<WeaponAnimationFlags, 5>)); //uint32 - 1
	Utype.set("NoAmmo", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 6>, itsy_bitsy::write<WeaponAnimationFlags, 6>)); //uint32 - 1
	Utype.set("Walk", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 7>, itsy_bitsy::write<WeaponAnimationFlags, 7>)); //uint32 - 1
	Utype.set("Run", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 8>, itsy_bitsy::write<WeaponAnimationFlags, 8>)); //uint32 - 1
	Utype.set("Left", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 9>, itsy_bitsy::write<WeaponAnimationFlags, 9>)); //uint32 - 1
	Utype.set("Right", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 10>, itsy_bitsy::write<WeaponAnimationFlags, 10>)); //uint32 - 1
	Utype.set("Back", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 11>, itsy_bitsy::write<WeaponAnimationFlags, 11>)); //uint32 - 1
	Utype.set("Backpedal", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 12>, itsy_bitsy::write<WeaponAnimationFlags, 12>)); //uint32 - 1
	Utype.set("Switching", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 13>, itsy_bitsy::write<WeaponAnimationFlags, 13>)); //uint32 - 1
	Utype.set("Drive", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 14>, itsy_bitsy::write<WeaponAnimationFlags, 14>)); //uint32 - 1
	Utype.set("Ride", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 15>, itsy_bitsy::write<WeaponAnimationFlags, 15>)); //uint32 - 1
	Utype.set("RideLeft", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 16>, itsy_bitsy::write<WeaponAnimationFlags, 16>)); //uint32 - 1
	RfgTable.set_usertype("WeaponAnimationFlags", Utype);
}

void Lua::BindHuman(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Human>();
	Utype.set("new", sol::constructors<Human(), Human(const Human&)>());
	Utype.set(sol::base_classes, sol::bases<Object>());
	//Utype.set("ResourceDependentData", &Human::ResourceDependentData);
	Utype.set("Flags", &Human::Flags);
	//Utype.set("MPFlags", &Human::MPFlags);
	Utype.set("LastTriggerDownFrame", &Human::LastTriggerDownFrame);
	Utype.set("Info", &Human::Info);
	Utype.set("RenderDistance", &Human::render_distance);
	Utype.set("XRayMaterial", &Human::XRayMaterial);
	Utype.set("XrayRenderAlpha", &Human::XrayRenderAlpha);
	Utype.set("Rank", &Human::Rank);
	Utype.set("ApproxLocalBmin", &Human::ApproxLocalBmin);
	Utype.set("ApproxLocalBmax", &Human::ApproxLocalBmax);
	Utype.set("LastPosition", &Human::LastPosition);
	//Utype.set("PathData", &Human::PathData);
	Utype.set("TurnToTarget", &Human::TurnToTarget);
	Utype.set("NavCellDetourRequestHandle", &Human::NavCellDetourRequestHandle);
	Utype.set("RaycastHitInfo", &Human::RaycastHitInfo);
	Utype.set("Velocity", &Human::Velocity);
	Utype.set("ActualVelocity", &Human::ActualVelocity);
	Utype.set("TransformFramesSkipped", &Human::TransformFramesSkipped);
	Utype.set("SteeringVector", &Human::SteeringVector);
	Utype.set("MoveSpeed", &Human::MoveSpeed);
	Utype.set("SteeringHeadingOffset", &Human::SteeringHeadingOffset);
	Utype.set("RotateDirection", &Human::RotateDirection);
	Utype.set("StateSpeedThrottle", &Human::StateSpeedThrottle);
	Utype.set("RotateHeadingLeft", &Human::RotateHeadingLeft);
	Utype.set("RotateHeadingRight", &Human::RotateHeadingRight);
	Utype.set("RotateInternalHeading", &Human::RotateInternalHeading);
	Utype.set("InertialMotion", &Human::InertialMotion);
	Utype.set("GroundObjectHandle", &Human::GroundObjectHandle);
	Utype.set("GroundObjectContactPos", &Human::GroundObjectContactPos);
	Utype.set("GroundObjectAltBodyIDX", &Human::GroundObjectAltBodyIDX);
	Utype.set("GroundObjectShapeKey", &Human::GroundObjectShapeKey);
	Utype.set("GroundObjectNormal", &Human::GroundObjectNormal);
	Utype.set("ObjectFilterHandle", &Human::ObjectFilterHandle);
	Utype.set("BlockMovementAnimation", &Human::BlockMovementAnimation);
	Utype.set("BlockSteeringVector", &Human::BlockSteeringVector);
	Utype.set("BlockMovementType", &Human::BlockMovementType);
	Utype.set("BlockSteeringHeadingOffset", &Human::BlockSteeringHeadingOffset);
	Utype.set("ReleasedMovementAnim", &Human::ReleasedMovementAnim);
	Utype.set("ReleasedMovementType", &Human::ReleasedMovementType);
	Utype.set("CurrentState", &Human::CurrentState);
	Utype.set("CurrentMovementState", &Human::CurrentMovementState);
	Utype.set("CurrentStance", &Human::CurrentStance);
	Utype.set("LastStance", &Human::LastStance);
	Utype.set("MovementMode", &Human::MovementMode);
	Utype.set("MovementSubmode", &Human::MovementSubmode);
	Utype.set("PreviousMovementMode", &Human::PreviousMovementMode);
	Utype.set("CustomFireAnimation", &Human::CustomFireAnimation);
	Utype.set("WalkAnimationSpeedPercentage", &Human::WalkAnimationSpeedPercentage);
	Utype.set("FrametimeTally", &Human::FrametimeTally);
	Utype.set("ActualVelocityMagnitude", &Human::ActualVelocityMagnitude);
	Utype.set("MaxSpeed", &Human::MaxSpeed);
	Utype.set("FallingVelocityMagnitude", &Human::FallingVelocityMagnitude);
	Utype.set("NotMovingUpdate", &Human::NotMovingUpdate);
	Utype.set("CharInstance", &Human::CharInstance);
	//Utype.set("ClothSim", &Human::ClothSim);
	Utype.set("BoneLODLevel", &Human::BoneLODLevel);
	Utype.set("WepAnimationFlags", &Human::WepAnimationFlags);
	Utype.set("RagdollState", &Human::RagdollState);
	Utype.set("RagdollSourceHumanHandle", &Human::RagdollSourceHumanHandle);
	Utype.set("RagdollIDX", &Human::RagdollIDX);
	Utype.set("RagdollBlendPercentage", &Human::RagdollBlendPercentage);
	Utype.set("RagdollLastFrameVelocity", &Human::RagdollLastFrameVelocity);
	Utype.set("RagdollOnImpactTime", &Human::RagdollOnImpactTime);
	Utype.set("RagdollOnImpactMinVelocity", &Human::RagdollOnImpactMinVelocity);
	Utype.set("RagdollDamaged", &Human::RagdollDamaged);
	Utype.set("RootBoneOffset", &Human::RootBoneOffset);
	Utype.set("NanoMaterialFX", sol::property([](Human& Self) { return std::ref(Self.NanoMaterialFX); })); //16 element c-array or uints
	Utype.set("MaterialFXHandleForHeadSkin", &Human::MaterialFXHandleForHeadSkin);
    //Utype.set("LastValidPositionBeforeRagdoll", sol::property([](Human& Self) { return std::ref(Self.LastValidPositionBeforeRagdoll); })); //vector[3]
	Utype.set("RagdollNumCollisionWithWalker", &Human::RagdollNumCollisionsWithWalker);
	Utype.set("IK_Joints", sol::property([](Human& Self) { return std::ref(Self.IK_Joints); })); //4 size array of IK_Joint
	//Utype.set("SpinebendData", &Human::SpinebendData);
	//Utype.set("HeadMorphs", &Human::HeadMorphs);
	Utype.set("InitialMaxHitPoints", &Human::InitialMaxHitPoints);
	Utype.set("MaxHitPoints", &Human::MaxHitPoints);
	Utype.set("HitPoints", &Human::HitPoints);
	Utype.set("MaxKnockdownHits", &Human::MaxKnockdownHits);
	Utype.set("KnockdownHits", &Human::KnockdownHits);
	Utype.set("KnockdownTimestamp", &Human::KnockdownTimestamp);
	Utype.set("KnockdownTimeoutTimestamp", &Human::KnockdownTimeoutTimestamp);
	//Utype.set("Combat", &Human::Combat);
	Utype.set("CollisionDamageTimer", &Human::CollisionDamageTimer);
	Utype.set("CurrentCollisionDamage", &Human::CurrentCollisionDamage);
	Utype.set("DoRagdollTimestamp", &Human::DoRagdollTimestamp);
	Utype.set("FacialPoseTimestamp", &Human::FacialPoseTimestamp);
	Utype.set("TurretHoldAnimations", &Human::TurretHoldAnimations);
	Utype.set("Cash", &Human::Cash);
	Utype.set("Inventory", &Human::Inventory);
	Utype.set("DesiredEquippedInvItem", &Human::DesiredEquippedInvItem);
	Utype.set("LastEquippedWeapon", &Human::LastEquippedWeapon);
	Utype.set("SecondLastEquippedWeapon", &Human::SecondLastEquippedWeapon);
	Utype.set("GrenadeWeapon", &Human::GrenadeWeapon);
	//Utype.set("AnimationPropInfo", &Human::AnimationPropInfo);
	Utype.set("OffhandProjectileHandle", &Human::OffhandProjectileHandle);
	Utype.set("ShieldHandle", &Human::ShieldHandle);
	Utype.set("ReloadTimer", &Human::ReloadTimer);
	Utype.set("EquipTagIndex", &Human::EquipTagIndex);
	Utype.set("EquipOffhandTagIndex", &Human::EquipOffhandTagIndex);
	Utype.set("RootBoneIndex", &Human::RootBoneIndex);
	Utype.set("LeftFootBoneIndex", &Human::LeftFootBoneIndex);
	Utype.set("RightFootBoneIndex", &Human::RightFootBoneIndex);
	Utype.set("LeftShoulderBoneIndex", &Human::LeftShoulderBoneIndex);
	Utype.set("RightShoulderBoneIndex", &Human::RightShoulderBoneIndex);
	Utype.set("LeftHandBoneIndex", &Human::LeftHandBoneIndex);
	Utype.set("RightHandBoneIndex", &Human::RightHandBoneIndex);
	Utype.set("LeftHipBoneIndex", &Human::LeftFootBoneIndex);
	Utype.set("RightHipBoneIndex", &Human::RightHipBoneIndex);
	Utype.set("RunStandBlendPoseWeight", &Human::RunStandBlendPoseWeight);
	Utype.set("LeanWeight", &Human::LeanWeight);
	Utype.set("LeanDirection", &Human::LeanDirection);
	Utype.set("LeanDisabled", &Human::LeanDisabled);
	Utype.set("LeanLastSteeringVector", &Human::LeanLastSteeringVector);
	Utype.set("FootPlanted", &Human::FootPlanted);
	Utype.set("FootPlantTime", &Human::FootPlantTime);
	Utype.set("IsTurning", &Human::IsTurning);
	Utype.set("StartingTurn", &Human::StartingTurn);
	Utype.set("RenderAlpha", &Human::RenderAlpha);
	Utype.set("CameraAlphaOverride", &Human::CameraAlphaOverride);
	Utype.set("CastsTransparentShadows", &Human::CastsTransparentShadows);
	Utype.set("FadeTimer", &Human::FadeTimer);
	Utype.set("FadeTime", &Human::FadeTime);
	Utype.set("StealthPercent", &Human::StealthPercent);
	Utype.set("VehicleHandle", &Human::VehicleHandle);
	Utype.set("ReservedVehicleHandle", &Human::ReservedVehicleHandle);
	Utype.set("VehicleSeatIDX", &Human::VehicleSeatIDX);
	Utype.set("BoredIdleTimestamp", &Human::BoredIdleTimestamp);
	Utype.set("CorpseCleanupTimer", &Human::CorpseCleanupTimer);
	Utype.set("TurnOffFireTimestamp", &Human::TurnOffFireTimestamp);
	Utype.set("HealthRestoreTimestamp", &Human::HealthRestoreTimestamp);
	Utype.set("HealthRestoreHitPoints", &Human::HealthRestoreHitPoints);
	Utype.set("HealthRestoreMinimumHitPoints", &Human::HealthRestoreMinimumHitPoints);
	Utype.set("LookAtPos", &Human::LookAtPos);
	Utype.set("LookAtHandle", &Human::LookAtHandle);
	Utype.set("LookAtSpeed", &Human::LookAtSpeed);
	Utype.set("AimOverrideDirection", &Human::AimOverrideDirection);
	Utype.set("DamagePercent", &Human::DamagePercent);
	Utype.set("DamageFunctionHandle", &Human::DamageFunctionHandle);
	Utype.set("DeathFunctionHandle", &Human::DeathFunctionHandle);
	Utype.set("BreathTimer", &Human::BreathTimer);
	Utype.set("CrouchToStandTestTimestamp", &Human::CrouchToStandTestTimestamp);
	Utype.set("LadderHandle", &Human::LadderHandle);
	Utype.set("LadderSlideSpeed", &Human::LadderSlideSpeed);
	Utype.set("LadderGrabRung", &Human::LadderGrabRung);
	Utype.set("LadderSlidePlayID", &Human::LadderSlidePlayID);
	Utype.set("CodeDrivenStartJump", &Human::CodeDrivenStartJump);
	Utype.set("CodeDrivenJumpTimer", &Human::CodeDrivenJumpTimer);
	Utype.set("CodeDrivenJumpHeight", &Human::CodeDrivenJumpHeight);
	Utype.set("JumpStateTimer", &Human::JumpStateTimer);
	Utype.set("LastSupported", &Human::LastSupported);
	Utype.set("AirTime", &Human::AirTime);
	Utype.set("UpdateTimer", &Human::UpdateTimer);
	Utype.set("ImportanceLevel", &Human::ImportanceLevel);
	Utype.set("ScriptedActionNodeHandle", &Human::ScriptedActionNodeHandle);
	Utype.set("NanoCBInfo", sol::property([](Human& Self) { return std::ref(Self.NanoCBInfo); })); //size 16 array of nano_callback_info[16]
	Utype.set("NanoIndex", &Human::NanoIndex);
	//Utype.set("ActionNodeData", &Human::ActionNodeData);
	Utype.set("LightEffects", sol::property([](Human& Self) { return std::ref(Self.LightEffects); })); //uint[2]
	Utype.set("LightTags", sol::property([](Human& Self) { return std::ref(Self.LightTags); })); //int[2]
	Utype.set("AvoidanceCheckTimer", &Human::AvoidanceCheckTimer);
	Utype.set("AvoidanceRequestTimer", &Human::AvoidanceRequestTimer);
	Utype.set("AvoidanceRequestHuman", &Human::AvoidanceRequestHuman);
	Utype.set("AvoidanceMoveDirection", &Human::AvoidanceMoveDirection);
	Utype.set("AvoidanceHintDirection", &Human::AvoidanceHintDirection);
	Utype.set("AvoidancePauseTimer", &Human::AvoidancePauseTimer);
	Utype.set("AvoidanceOriginalMovementState", &Human::AvoidanceOriginalMovementState);
	Utype.set("MinimapFlags", &Human::MinimapFlags);
	//Utype.set("AmpPropInfo", &Human::AmpPropInfo);
	Utype.set("EquippedInventoryItemLastFrame", &Human::EquippedInventoryItemLastFrame);
	Utype.set("EquippedInventoryItem", &Human::EquippedInventoryItem);
	//Utype.set("Voice", &Human::Voice);
	Utype.set("CurrentTeam", &Human::CurrentTeam);
	Utype.set("UndercoverTeam", &Human::UndercoverTeam);
	Utype.set("DialogueFoleyInfo", &Human::DialogueFoleyInfo);
	Utype.set("QueuedVoiceLine", &Human::QueuedVoiceLine); //enum
	Utype.set("SituationalVoiceLine", &Human::SituationalVoiceLine); //enum
	Utype.set("VoicePriority", &Human::VoicePriority); //enum
	Utype.set("VoiceCuePriority", &Human::VoiceCuePriority); //enum
	Utype.set("RadioInstance", &Human::RadioInstance);
	Utype.set("VoiceInstance", &Human::VoiceInstance);
	Utype.set("VoiceTimeSinceFinish", &Human::VoiceTimeSinceFinish);
	Utype.set("LipsyncHandle", &Human::LipsyncHandle); //enum
	Utype.set("VoiceDelayTime", &Human::voice_delay_time);
	//Utype.set("UnimVoiceDelayCBCallback", &Human::Unim_VoiceDelayCBCallback);
	//Utype.set("VoiceDelayCBData", &Human::VoiceDelayCBData);
	Utype.set("AcknowledgedTime", &Human::AcknowledgedTime);
	Utype.set("ReportedTimer", &Human::ReportedTimer);
	Utype.set("Lifetime", &Human::Lifetime);
	RfgTable.set_usertype("Human", Utype);

	/*RfgTable.new_usertype<Human>
	(
		"Human",
		"new", sol::constructors<Human(), Human(const Human&)>(),
		//"ResourceDependentData", &Human::ResourceDependentData,
		"Flags", &Human::Flags,
		//"MPFlags", &Human::MPFlags,
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
		//"NanoMaterialFX", &Human::NanoMaterialFX, //16 element c-array or uints
		"MaterialFXHandleForHeadSkin", &Human::MaterialFXHandleForHeadSkin,
		//"LastValidPositionBeforeRagdoll", &Human::LastValidPositionBeforeRagdoll, //16 element c-array of vectors
		"RagdollNumCollisionWithWalker", &Human::RagdollNumCollisionsWithWalker,
		//"IK_Joints", &Human::IK_Joints, //4 size array of IK_Joint
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
		//"NanoCBInfo", &Human::NanoCBInfo,
		"NanoIndex", &Human::NanoIndex,
		"ActionNodeData", &Human::ActionNodeData,
		//"LightEffects", &Human::LightEffects,
		//"LightTags", &Human::LightTags,
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
	);*/
}
