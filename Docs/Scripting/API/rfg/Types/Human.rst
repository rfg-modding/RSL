
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.

Human
********************************************************
Has all the data representing a human such as health, jump height, move speed, and more.

Inherits `Object`_

Variables
========================================================

**Flags** (`HumanFlags`_)
    A set of `bool`_ values which determine the behavior of the human.

**LastTriggerDownFrame** (`int`_)
    The last frame the humans weapon was fired.

**Info** (`HumanInfo`_)
    More human specific data. May be ``nil``.

**RenderDistance** (`ObjectRenderDistance`_)
    THe humans render distance.

**XRayMaterial** (`char`_)
    The xray material of this human. They may or may not be visible via xray depending on their material.

**XrayRenderAlpha** (`char`_)
    The transparency of this human in xray mode.

**Rank** (`int`_)
    Unknown value.

**ApproxLocalBmin** (`Vector`_)
    The minimum point of this humans bounding box.

**ApproxLocalBmax** (`Vector`_)
    The maximum point of this humans bounding box.

**LastPosition** (`Vector`_)
    The last x, y, z position.

**TurnToTarget** (`Vector`_)
    Point that the human is turning towards.

**NavCellDetourRequestHandle** (`unsigned int`_)
    Unknown value.

**RaycastHitInfo** (`HumanRaycastHitInfo`_)
    Info about a raycast starting point and result. Unknown if this is just cast from the humans position or if it's from the weapon if they possess one.

**Velocity** (`Vector`_)
    The humans velocity.

**ActualVelocity** (`Vector`_)
    Difference from previous value unknown.

**TransformFramesSkipped** (`int`_)
    Unknown value.

**SteeringVector** (`Vector`_)
    Unknown value.

**MoveSpeed** (`float`_)
    Move speed when walking and running.

**SteeringHeadingOffset** (`float`_)
    Unknown value. Possibly an angle offset from 0 degrees.

**RotateDirection** (`HumanRotateDirections`_)
    Determines which direction (clockwise, counter-clockwise) the human will rotate in.

**StateSpeedThrottle** (`float`_)
    Unknown value.

**RotateHeadingLeft** (`float`_)
    Unknown value.

**RotateHeadingRight** (`float`_)
    Unknown value.

**RotateInternalHeading** (`float`_)
    Unknown value.

**InertialMotion** (`Vector`_)
    Unknown value.

**GroundObjectHandle** (`unsigned int`_)
    Unknown value. Possibly the object handle of the ground.

**GroundObjectContactPos** (`Vector`_)
    The point that the human is in contact with the ground.

**GroundObjectAltBodyIDX** (`int`_)
    Unknown value.

**GroundObjectShapeKey** (`int`_)
    Unknown value. Likely related to havok physics.

**GroundObjectNormal** (`float`_)
    The normal vector of the point that the human is in contact with the ground.

**ObjectFilterHandle** (`unsigned int`_)
    Unknown value.

**BlockMovementAnimation** (`int`_)
    Unknown value.

**BlockSteeringVector** (`Vector`_)
    Unknown value.

**BlockMovementType** (`BlockMovementTypes`_)
    Unknown value.

**BlockSteeringHeadingOffset** (`float`_)
    Unknown value.

**ReleasedMovementAnim** (`int`_)
    Unknown value.

**ReleasedMovementType** (`BlockMovementTypes`_)
    Unknown value.

**CurrentState** (`HumanStates`_)
    The state of the human. Jumping, falling, in turret, etc. See `HumanStates`_ for more info.

**CurrentMovementState** (`HumanMovementStates`_)
    Running, walking, idle, etc.

**CurrentStance** (`HumanStances`_)
    Current stance. Standing, prone, crouching, etc.

**LastStance** (`HumanStances`_)
    Last stance.

**MovementMode** (`HumanMoveModes`_)
    The current movement mode. Pathfinding, pathfinding to vehicle, etc.

**MovementSubmode** (`HumanMoveSubmodes`_)
    Movement submodes. Jump start, jump pre, jump mid, etc.

**PreviousMovementMode** (`HumanMoveModes`_)
    The previous movement mode.

**CustomFireAnimation** (`AnimationActions`_)
    Fire animation info.

**WalkAnimationSpeedPercentage** (`float`_)
    Unknown value.

**FrametimeTally** (`float`_)
    Unknown value.

**ActualVelocityMagnitude** (`float`_)
    Magnitude of ActualVelocity.

**MaxSpeed** (`float`_)
    Max speed enforced on human.

**FallingVelocityMagnitude** (`float`_)
    Magnitude of falling velocity.

**NotMovingUpdate** (`Timestamp`_)
    Desc... Can be ``nil``.

**CharInstance** (`CharacterInstance`_)
    Character instance info. May be ``nil``.

**BoneLODLevel** (`int`_)
    Unknown value.

**WepAnimationFlags** (`WeaponAnimationFlags`_)
    Weapon animation flags.

**RagdollState** (`HumanRagdollStates`_)
    Ragdoll state. Flinch, active, blend out, etc.

**RagdollSourceHumanHandle** (`unsigned int`_)
    Unknown value.

**RagdollIDX** (`int`_)
    Unknown value.

**RagdollBlendPercentage** (`float`_)
    Unknown value.

**RagdollLastFrameVelocity** (`Vector`_)
    Unknown value.

**RagdollOnImpactTime** (`float`_)
    Unknown value.

**RagdollOnImpactMinVelocity** (`float`_)
    Unknown value.

**RagdollDamaged** (`Timestamp`_)
    Unknown value.

**RootBoneOffset** (`float`_)
    Unknown value.

**NanoMaterialFX** (`unsigned int[16]`_)
    Unknown value.

**MaterialFXHandleForHeadSkin** (`unsigned int`_)
    Unknown value.

**LastValidPositionBeforeRagdollIndex** (`unsigned int`_)
    Unknown value.

**RagdollNumCollisionsWithWalker** (`int`_)
    Unknown value.

**IK_Joints** (`IkJoint[4]`_)
    Inverse kinematics joints of the humans body.

**InitialMaxHitPoints** (`int`_)
    Initial max hit points.

**MaxHitPoints** (`int`_)
    Current max hit points.

**HitPoints** (`float`_)
    Hit points.

**MaxKnockdownHits** (`int`_)
    Unknown value.

**KnockdownHits** (`float`_)
    Unknown value.

**KnockdownTimestamp** (`Timestamp`_)
    Unknown value.

**KnockdownTimeoutTimestamp** (`Timestamp`_)
    Unknown value.

**CollisionDamageTimer** (`Timestamp`_)
    Unknown value.

**CurrentCollisionDamage** (`float`_)
    Unknown value.

**DoRagdollTimestamp** (`Timestamp`_)
    Unknown value.

**FacialPoseTimestamp** (`Timestamp`_)
    Unknown value.

**TurretHoldAnimations** (`Timestamp`_)
    Unknown value.

**Cash** (`float`_)
    Not used by the game. Likely a remnant of Saints Row 1.

**Inventory** (`InventoryItem`_)
    Desc... Can be ``nil``.

**DesiredEquippedInvItem** (`InventoryItem`_)
    Desc... Can be ``nil``.

**LastEquippedWeapon** (`InventoryItem`_)
    Desc... Can be ``nil``.

**SecondLastEquippedWeapon** (`InventoryItem`_)
    Desc... Can be ``nil``.

**GrenadeWeapon** (`InventoryItem`_)
    Desc... Can be ``nil``.

**OffhandProjectileHandle** (`unsigned int`_)
    Unknown value.

**ShieldHandle** (`unsigned int`_)
    Object handle of the humans shield if they have one.

**ReloadTimer** (`Timestamp`_)
    Timer used for weapon reload.

**EquipTagIndex** (`int`_)
    Unknown value.

**EquipOffhandTagIndex** (`int`_)
    Unknown value.

**RootBoneIndex** (`int`_)
    Root bone index.

**LeftFootBoneIndex** (`int`_)
    Left foot bone index.

**RightFootBoneIndex** (`int`_)
    Right foot bone index.

**LeftShoulderBoneIndex** (`int`_)
    Left shoulder bone index.

**RightShoulderBoneIndex** (`int`_)
    Right shoulder bone index.

**LeftHandBoneIndex** (`int`_)
    Left hand bone index.

**RightHandBoneIndex** (`int`_)
    Right hand bone index.

**LeftHipBoneIndex** (`int`_)
    Left hip bone index.

**RightHipBoneIndex** (`int`_)
    Right hip bone index.

**RunStandBlendPoseWeight** (`float`_)
    Unknown value. Likely used when blending run and stand animations when switching between the two.

**LeanWeight** (`float`_)
    Unknown value.

**LeanDirection** (`Vector`_)
    Direction the human is leaning in.

**LeanDisabled** (`Timestamp`_)
    Unknown value.

**LeanLastSteeringVector** (`Vector`_)
    Unknown value.

**FootPlanted** (`FootPlant`_)
    Information about where and how the foot is planted.

**FootPlantTime** (`Timestamp`_)
    Unknown value.

**IsTurning** (`bool`_)
    Is ``true`` if turning.

**StartingTurn** (`bool`_)
    Is ``true`` if starting to turn.

**RenderAlpha** (`float`_)
    The humans render opacity.

**CameraAlphaOverride** (`float`_)
    Unknown value.

**CastsTransparentShadows** (`bool`_)
    Is ``true`` if it casts transparent shadows.

**FadeTimer** (`Timestamp`_)
    Unknown value.

**FadeTime** (`int`_)
    Unknown value.

**StealthPercent** (`float`_)
    If set to ``1.0`` the human will have the stealth jetpack "invisible" effect on their body.

**VehicleHandle** (`unsigned int`_)
    The object handle of the humans vehicle if they are in one.

**ReservedVehicleHandle** (`unsigned int`_)
    Unknown value.

**VehicleSeatIDX** (`VehicleSeatIndex`_)
    Unknown value.

**BoredIdleTimestamp** (`Timestamp`_)
    Unknown value.

**CorpseCleanupTimer** (`Timestamp`_)
    Unknown value.

**TurnOffFireTimestamp** (`Timestamp`_)
    Unknown value.

**HealthRestoreTimestamp** (`Timestamp`_)
    Unknown value.

**HealthRestoreHitPoints** (`float`_)
    How many hitpoints to restore each healing tick.

**HealthRestoreMinimumHitPoints** (`float`_)
    Unknown value.

**LookAtPos** (`Vector`_)
    Unknown value.

**LookAtHandle** (`unsigned int`_)
    Unknown value.

**LookAtSpeed** (`float`_)
    The speed at which the human looks at things.

**AimOverrideDirection** (`Vector`_)
    Unknown value.

**DamagePercent** (`float`_)
    Percent of damage to hitpoints. A value of ``1.0`` is equal to 100%.

**DamageFunctionHandle** (`unsigned int16`_)
    Unknown value.

**DeathFunctionHandle** (`unsigned int16`_)
    Unknown value.

**BreathTimer** (`Timestamp`_)
    Unknown value.

**CrouchToStandTestTimestamp** (`Timestamp`_)
    Unknown value.

**LadderHandle** (`unsigned int`_)
    The object handle of the ladder the human is attached to if they are attached to one.

**LadderSlideSpeed** (`float`_)
    The speed at which the human slides down ladders.

**LadderGrabRung** (`int`_)
    Unknown value.

**LadderSlidePlayID** (`int`_)
    Unknown value.

**CodeDrivenStartJump** (`bool`_)
    Unknown value.

**CodeDrivenJumpTimer** (`float`_)
    Unknown value.

**CodeDrivenJumpHeight** (`float`_)
    The humans jump height.

**JumpStateTimer** (`Timestamp`_)
    Unknown value.

**LastSupported** (`Timestamp`_)
    Unknown value.

**AirTime** (`Timestamp`_)
    Unknown value.

**UpdateTimer** (`Timestamp`_)
    Unknown value.

**ImportanceLevel** (`ObjectImportanceLevels`_)
    Unknown value.

**ScriptedActionNodeHandle** (`unsigned int`_)
    Unknown value.

**NanoCBInfo** (`NanoCallbackInfo[16]`_)
    Unknown value.

**NanoIndex** (`int`_)
    Unknown value.

**LightEffects** (`unsigned int[2]`_)
    Unknown value.

**LightTags** (`int[2]`_)
    Unknown value.

**AvoidanceCheckTimer** (`Timestamp`_)
    Unknown value.

**AvoidanceRequestTimer** (`Timestamp`_)
    Unknown value.

**AvoidanceRequestHuman** (`unsigned int`_)
    Unknown value.

**AvoidanceMoveDirection** (`Vector`_)
    Unknown value.

**AvoidanceHintDirection** (`Vector`_)
    Unknown value.

**AvoidancePauseTimer** (`Timestamp`_)
    Unknown value.

**AvoidanceOriginalMovementState** (`HumanMovementStates`_)
    Unknown value.

**MinimapFlags** (`int`_)
    Unknown value.

**EquippedInventoryItemLastFrame** (`InventoryItem`_)
    Unknown value. May be ``nil``.

**EquippedInventoryItem** (`InventoryItem`_)
    Unknown value. May be  ``nil``.

**CurrentTeam** (`HumanTeams`_)
    The humans team. EDF, Guerrilla, etc.

**UndercoverTeam** (`HumanTeams`_)
    Unknown value.

**DialogueFoleyInfo** (`int`_)
    Unknown value.

**QueuedVoiceLine** (`VoiceLineHandle`_)
    Unknown value.

**SituationalVoiceLine** (`VoiceLines`_)
    Unknown value.

**VoicePriority** (`VoiceLinePriorities`_)
    Unknown value.

**VoiceCuePriority** (`AudiolibCuePriorities`_)
    Unknown value.

**RadioInstance** (`unsigned int16`_)
    Unknown value.

**VoiceInstance** (`int`_)
    Unknown value.

**VoiceTimeSinceFinish** (`Timestamp`_)
    Unknown value.

**LipsyncHandle** (`LipsyncDataHandle`_)
    Unknown value.

**VoiceDelayTime** (`Timestamp`_)
    Unknown value.

**AcknowledgedTime** (`Timestamp`_)
    Unknown value.

**ReportedTimer** (`Timestamp`_)
    Unknown value.

**Lifetime** (`Timestamp`_)
    The time the human has been in existance.

.. _`Object`: ./Object.html
.. _`Vector`: ./Vector.html
.. _`Matrix`: ./Matrix.html
.. _`AttachInfoData`: ./AttachInfoData.html
.. _`ObjectContactInfo`: ./ObjectContactInfo.html
.. _`ObjectFlags`: ./ObjectFlags.html
.. _`Human`: ./Human.html
.. _`HumanFlags`: ./HumanFlags.html
.. _`HumanInfo`: ./HumanInfo.html
.. _`Player`: ./Player.html
.. _`WorldZone`: ./WorldZone.html
.. _`District`: ./District.html
.. _`HavokBPO`: ./HavokBPO.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`unsigned int16`: ./PrimitiveTypes.html
.. _`int16`: ./PrimitiveTypes.html
.. _`char`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`bool`: ./PrimitiveTypes.html
.. _`int[2]`: ./PrimitiveTypes.html
.. _`unsigned int[2]`: ./PrimitiveTypes.html
.. _`unsigned int[16]`: ./PrimitiveTypes.html
.. _`ObjectRenderDistance`: ./ObjectRenderDistance.html
.. _`HumanRaycastHitInfo`: ./HumanRaycastHitInfo.html
.. _`HumanRotateDirections`: ./HumanRotateDirections.html
.. _`BlockMovementTypes`: ./BlockMovementTypes.html
.. _`HumanStates`: ./HumanStates.html
.. _`HumanMovementStates`: ./HumanMovementStates.html
.. _`HumanStances`: ./HumanStances.html
.. _`HumanMoveModes`: ./HumanMoveModes.html
.. _`HumanMoveSubmodes`: ./HumanMoveSubmodes.html
.. _`AnimationActions`: ./AnimationActions.html
.. _`Timestamp`: ./Timestamp.html
.. _`CharacterInstance`: ./CharacterInstance.html
.. _`WeaponAnimationFlags`: ./WeaponAnimationFlags.html
.. _`HumanRagdollStates`: ./HumanRagdollStates.html
.. _`ObjectImportanceLevels`: ./ObjectImportanceLevels.html
.. _`VehicleSeatIndex`: ./VehicleSeatIndex.html
.. _`IkJoint`: ./IkJoint.html
.. _`IkJoint[4]`: ./IkJoint.html
.. _`InventoryItem`: ./InventoryItem.html
.. _`NanoCallbackInfo[16]`: ./NanoCallbackInfo.html
.. _`HumanTeams`: ./HumanTeams.html
.. _`FootPlant`: ./FootPlant.html
.. _`VoiceLineHandle`: ./VoiceLineHandle.html
.. _`VoiceLines`: ./VoiceLines.html
.. _`VoiceLinePriorities`: ./VoiceLinePriorities.html
.. _`AudiolibCuePriorities`: ./AudiolibCuePriorities.html
.. _`LipsyncDataHandle`: ./LipsyncDataHandle.html