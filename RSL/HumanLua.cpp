#include "HumanLua.h"
#include "Functions.h"

void Lua::BindIKJoint(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<IK_Joint>
    (
        "IkJoint",
        "AnchorTag", &IK_Joint::anchor_tag,
        "JointTag", &IK_Joint::joint_tag,
        "IkTag", &IK_Joint::ik_tag,
        "IkStrength", &IK_Joint::ik_strength,
        "IkRateOfChange", &IK_Joint::ik_rate_of_change,
        "FreezeObjHandle", &IK_Joint::freeze_obj_handle,
        "FreezeOffsetPos", &IK_Joint::freeze_offset_pos,
        "Location", &IK_Joint::location
    );
}

void Lua::BindWeaponAnimationFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<WeaponAnimationFlags>
    (
        "WeaponAnimationFlags",
        "new", sol::no_constructor,
        "Prone", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 0>, itsy_bitsy::write<WeaponAnimationFlags, 0>), //uint32 - 1
        "Crouch", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 1>, itsy_bitsy::write<WeaponAnimationFlags, 1>), //uint32 - 1
        "DownReady", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 2>, itsy_bitsy::write<WeaponAnimationFlags, 2>), //uint32 - 1
        "Ready", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 3>, itsy_bitsy::write<WeaponAnimationFlags, 3>), //uint32 - 1
        "Aim", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 4>, itsy_bitsy::write<WeaponAnimationFlags, 4>), //uint32 - 1
        "FineAim", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 5>, itsy_bitsy::write<WeaponAnimationFlags, 5>), //uint32 - 1
        "NoAmmo", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 6>, itsy_bitsy::write<WeaponAnimationFlags, 6>), //uint32 - 1
        "Walk", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 7>, itsy_bitsy::write<WeaponAnimationFlags, 7>), //uint32 - 1
        "Run", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 8>, itsy_bitsy::write<WeaponAnimationFlags, 8>), //uint32 - 1
        "Left", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 9>, itsy_bitsy::write<WeaponAnimationFlags, 9>), //uint32 - 1
        "Right", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 10>, itsy_bitsy::write<WeaponAnimationFlags, 10>), //uint32 - 1
        "Back", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 11>, itsy_bitsy::write<WeaponAnimationFlags, 11>), //uint32 - 1
        "Backpedal", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 12>, itsy_bitsy::write<WeaponAnimationFlags, 12>), //uint32 - 1
        "Switching", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 13>, itsy_bitsy::write<WeaponAnimationFlags, 13>), //uint32 - 1
        "Drive", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 14>, itsy_bitsy::write<WeaponAnimationFlags, 14>), //uint32 - 1
        "Ride", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 15>, itsy_bitsy::write<WeaponAnimationFlags, 15>), //uint32 - 1
        "RideLeft", sol::property(itsy_bitsy::read<WeaponAnimationFlags, 16>, itsy_bitsy::write<WeaponAnimationFlags, 16>) //uint32 - 1
    );
}

void Lua::BindHuman(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<Human>
    (
        "Human",
        "new", sol::constructors<Human(), Human(const Human&)>(),
        sol::base_classes, sol::bases<Object>(),
        //"ResourceDependentData", &Human::ResourceDependentData,
        "Flags", &Human::Flags,
        //"MPFlags", &Human::MPFlags,
        "LastTriggerDownFrame", &Human::LastTriggerDownFrame,
        "Info", &Human::Info,
        "RenderDistance", &Human::render_distance,
        "XRayMaterial", sol::property([](Human& Self) -> int {return static_cast<int>(Self.XRayMaterial); }, [](Human& Self, int Value) {Self.XRayMaterial = static_cast<char>(Value); }),
        "XrayRenderAlpha", sol::property([](Human& Self) -> int {return static_cast<int>(Self.XrayRenderAlpha); }, [](Human& Self, int Value) {Self.XrayRenderAlpha = static_cast<char>(Value); }),
        "Rank", &Human::Rank,
        "ApproxLocalBmin", &Human::ApproxLocalBmin,
        "ApproxLocalBmax", &Human::ApproxLocalBmax,
        "LastPosition", &Human::LastPosition,
        //"PathData", &Human::PathData,
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
        "NanoMaterialFX", sol::property([](Human& Self) { return std::ref(Self.NanoMaterialFX); }), //16 element c-array or uints
        "MaterialFXHandleForHeadSkin", &Human::MaterialFXHandleForHeadSkin,
        //"LastValidPositionBeforeRagdoll", sol::property([](Human& Self) { return std::ref(Self.LastValidPositionBeforeRagdoll); }), //vector[3]
        "RagdollNumCollisionWithWalker", &Human::RagdollNumCollisionsWithWalker,
        "IK_Joints", sol::property([](Human& Self) { return std::ref(Self.IK_Joints); }), //4 size array of IK_Joint
        //"SpinebendData", &Human::SpinebendData,
        //"HeadMorphs", &Human::HeadMorphs,
        "InitialMaxHitPoints", &Human::InitialMaxHitPoints,
        "MaxHitPoints", &Human::MaxHitPoints,
        "HitPoints", &Human::HitPoints,
        "MaxKnockdownHits", &Human::MaxKnockdownHits,
        "KnockdownHits", &Human::KnockdownHits,
        "KnockdownTimestamp", &Human::KnockdownTimestamp,
        "KnockdownTimeoutTimestamp", &Human::KnockdownTimeoutTimestamp,
        //"Combat", &Human::Combat,
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
        "NanoCBInfo", sol::property([](Human& Self) { return std::ref(Self.NanoCBInfo); }), //size 16 array of nano_callback_info[16]
        "NanoIndex", &Human::NanoIndex,
        //"ActionNodeData", &Human::ActionNodeData,
        "LightEffects", sol::property([](Human& Self) { return std::ref(Self.LightEffects); }), //uint[2]
        "LightTags", sol::property([](Human& Self) { return std::ref(Self.LightTags); }), //int[2]
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
        "QueuedVoiceLine", &Human::QueuedVoiceLine, //enum
        "SituationalVoiceLine", &Human::SituationalVoiceLine, //enum
        "VoicePriority", &Human::VoicePriority, //enum
        "VoiceCuePriority", &Human::VoiceCuePriority, //enum
        "RadioInstance", &Human::RadioInstance,
        "VoiceInstance", &Human::VoiceInstance,
        "VoiceTimeSinceFinish", &Human::VoiceTimeSinceFinish,
        "LipsyncHandle", &Human::LipsyncHandle, //enum
        "VoiceDelayTime", &Human::voice_delay_time,
        //"UnimVoiceDelayCBCallback", &Human::Unim_VoiceDelayCBCallback,
        //"VoiceDelayCBData", &Human::VoiceDelayCBData,
        "AcknowledgedTime", &Human::AcknowledgedTime,
        "ReportedTimer", &Human::ReportedTimer,
        "Lifetime", &Human::Lifetime
    );
}
