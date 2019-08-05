
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


Player
********************************************************
Holds the variables representing a player. You can use ``rfg.ActivePlayer`` to easily access the current player. This only becomes available after a save is loaded. This type is an `Object`_ since it inherits `Human`_ which inherits `Object`_.

Inherits `Human`_, which inherits `Object`_

Variables
========================================================

**FrametimeMultiplier** (`float`_)
    Unknown value.

**ActionObject** (`UseableObject`_)
    Unknown value.

**ActionObjectTimestamp** (`Timestamp`_)
    Unknown value.

**LastFireTime** (`Timestamp`_)
    Unknown value.

**RadioId** (`int`_)
    Unknown value.

**TagTrigger** (`int`_)
    Unknown value.

**TagSeq** (`TaggingSequences`_)
    Unknown value.

**TagTimer** (`Timestamp`_)
    Unknown value.

**TagEffect** (`int`_)
    Unknown value.

**HudMessage** (`HudMessageHandle`_)
    Unknown value.

**HavokFilterGroup** (`unsigned int`_)
    Unknown value.

**AimTarget** (`unsigned int`_)
    Unknown value.

**PenetratingAimTarget** (`unsigned int`_)
    Unknown value.

**PenetratingAimPos** (`Vector`_)
    Unknown value.

**AimTargetDuration** (`Timestamp`_)
    Unknown value.

**HeatSeekingTarget** (`unsigned int`_)
    Unknown value.

**AimPos** (`Vector`_)
    Unknown value.

**CombatTargetUpdateTime** (`Timestamp`_)
    Unknown value.

**RemoteChargeTime** (`float`_)
    Unknown value.

**DoingRemoteCharge** (`bool`_)
    Unknown value.

**ZoomState** (`PlayerZoomState`_)
    Unknown value.

**PreviousZoomState** (`PlayerZoomState`_)
    Unknown value.

**CoverVector** (`Vector`_)
    Unknown value.

**CoverVectorRight** (`Vector`_)
    Unknown value.

**EnteringCover** (`Timestamp`_)
    Unknown value.

**ExitingCover** (`Timestamp`_)
    Unknown value.

**CoverMoveVel** (`float`_)
    Unknown value.

**CoverApproachingEdge** (`bool`_)
    Unknown value.

**CoverApproachingEdgeTs** (`Timestamp`_)
    Unknown value.

**CoverEdgeHitPos** (`Vector`_)
    Unknown value.

**CoverEdgeMissPos** (`Vector`_)
    Unknown value.

**ThrownWeaponCheckPos** (`Vector`_)
    Unknown value.

**CombatMoveQueue** (`int`_)
    Unknown value.

**PreviousBulletHit** (`TimestampPercent`_)
    Unknown value.

**JetpackFuelPercent** (`float`_)
    Unknown value.

**JetpackFoley** (`int`_)
    Unknown value.

**JetpackEffect** (`unsigned int`_)
    Unknown value.

**AllowRagdoll** (`bool`_)
    Unknown value.

**PFlags** (`PlayerFlags`_)
    Unknown value.

**HoldObjectAvailable** (`bool`_)
    Unknown value.

**HoldObjectHandle** (`unsigned int`_)
    Unknown value.

**NumAbandonedVehicles** (`int`_)
    Unknown value.

**DeadTimestamp** (`TimestampPercent`_)
    Unknown value.

**MatFxHandle[16]** (`unsigned int`_)
    Unknown value.

**CurrentMatFx** (`unsigned int`_)
    Unknown value.

**ScriptMode** (`PlayerScriptMode`_)
    Unknown value.

**ScriptData** (`ScriptSpecificData`_)
    Unknown value.

**JetpackUseLogHandle** (`int`_)
    Unknown value.

**BackpackEquipLogHandle** (`int`_)
    Unknown value.

**DistrictLogHandle** (`int`_)
    Unknown value.

**CameraBoneTransform** (`Matrix43`_)
    Unknown value.

**MovementVelocity** (`Vector`_)
    Unknown value.

**DirectControlDir** (`Vector2`_)
    Unknown value.

**DirectControlVel** (`Vector`_)
    Unknown value.

**CoverCollisionNormal** (`Vector`_)
    Unknown value.

**LastFrameCoverCollisionNormal** (`Vector`_)
    Unknown value.

**CoverTestQueue** (`PlayerCoverTest`_)
    Unknown value.

**CoverDelayTs** (`Timestamp`_)
    Unknown value.

**CoverEnterTs** (`Timestamp`_)
    Unknown value.

**CoverExitDelayTs** (`Timestamp`_)
    Unknown value.

**CoverDiveCapsule** (`Timestamp`_)
    Unknown value.

**CoverLeanDelay** (`Timestamp`_)
    Unknown value.

**CoverRootOffset** (`float`_)
    Unknown value.

**SpinebendRootOffset** (`float`_)
    Unknown value.

**FacialIdle** (`Timestamp`_)
    Unknown value.

**FootstepPropagateTime** (`Timestamp`_)
    Unknown value.

**BumpIntoPropagateTime** (`Timestamp`_)
    Unknown value.

**AmmoBoxHandle** (`unsigned int`_)
    Unknown value.

**PathfindTimeOut** (`Timestamp`_)
    Unknown value.

**CurrentInterfaceMode** (`InterfaceModes`_)
    Unknown value.

**CommonControlsAllowed** (`unsigned int`_)
    Unknown value.

**ControlsGeneralAllowed** (`unsigned int`_)
    Unknown value.

**ControlsOnFootAllowed** (`unsigned int`_)
    Unknown value.

**ControlsDrivingAllowed** (`unsigned int`_)
    Unknown value.

**GeneralActionsAllowed** (`unsigned int`_)
    Unknown value.

**WeaponSwapTimestamp** (`Timestamp`_)
    Unknown value.

**SprintDelayTimestamp** (`Timestamp`_)
    Unknown value.

**SprintStartTimestamp** (`Timestamp`_)
    Unknown value.

**JumpRefreshTimestamp** (`Timestamp`_)
    Unknown value.

**AllySquadHandle** (`unsigned int`_)
    Unknown value.

**EscortSquadHandle** (`unsigned int`_)
    Unknown value.

**CheckSquadsTimer** (`Timestamp`_)
    Unknown value.

**PathfindInfo** (`PathfindNavInfo`_)
    Unknown value.

**BloodDecalsFadeIndex** (`int`_)
    Unknown value.

**ActivityInventoryBuffer[1024]** (`char`_)
    Unknown value.

**ZoomCancelTimestamp** (`Timestamp`_)
    Unknown value.

**NonInventoryItemHandle** (`unsigned int`_)
    Unknown value.

**LastVehicleDriven** (`unsigned int`_)
    Unknown value.

**QuickTurnOrient** (`Matrix`_)
    Unknown value.

**QuickTurnSpeed** (`float`_)
    Unknown value.

**Metadata** (`PlayerMetadata`_)
    Unknown value.

**RadiationTimestamp** (`Timestamp`_)
    Unknown value.

**RadiationDamage** (`float`_)
    Unknown value.

**RadiationFoley** (`int`_)
    Unknown value.

**IsStuckTimer** (`Timestamp`_)
    Unknown value.

**LastStuckPos** (`Vector`_)
    Unknown value.

**RagdollOverrideGetUpTime** (`int`_)
    Unknown value.

**FadeBackpackTime** (`TimestampPercent`_)
    Unknown value.

**CommTowerCheckPeriod** (`Timestamp`_)
    Unknown value.

**NextRecord** (`int`_)
    Unknown value.

**PositionalRecords[8]** (`PlayerPositionalRecord`_)
    Unknown value.

**TrackingPeriod** (`Timestamp`_)
    Unknown value.

.. _`float`: ./PrimitiveTypes.html
.. _`UseableObject`: ./UseableObject.html
.. _`Timestamp`: ./Timestamp.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`TaggingSequences`: ./TaggingSequences.html
.. _`TaggingSequence`: ./TaggingSequences.html
.. _`HudMessageHandle`: ./HudMessageHandle.html
.. _`Vector`: ./Vector.html
.. _`bool`: ./PrimitiveTypes.html
.. _`PlayerZoomState`: ./PlayerZoomState.html
.. _`TimestampPercent`: ./TimestampPercent.html
.. _`PlayerFlags`: ./PlayerFlags.html
.. _`CustomVehicle`: ./CustomVehicle.html
.. _`CustomVehicle*`: ./CustomVehicle*.html
.. _`PlayerScriptMode`: ./PlayerScriptMode.html
.. _`ScriptSpecificData`: ./ScriptSpecificData.html
.. _`void*`: ./PrimitiveTypes.html
.. _`GameCommand`: ./GameCommand.html
.. _`Matrix`: ./Matrix.html
.. _`Vector2`: ./Vector2.html
.. _`MultiSimStateMp`: ./MultiSimStateMp.html
.. _`MultiTimestamp`: ./MultiTimestamp.html
.. _`MultiTimestampPercent`: ./MultiTimestampPercent.html
.. _`PlayerLadderState`: ./PlayerLadderState.html
.. _`MultiplayerEdgeCorrectionInfo`: ./MultiplayerEdgeCorrectionInfo.html
.. _`MultiplayerBlockedInfo`: ./MultiplayerBlockedInfo.html
.. _`Matrix43`: ./Matrix43.html
.. _`PlayerCoverTest`: ./PlayerCoverTest.html
.. _`InterfaceModes`: ./InterfaceModes.html
.. _`PathfindNavInfo`: ./PathfindNavInfo.html
.. _`DecalCircArrayQueue10`: ./DecalCircArrayQueue10.html
.. _`FileObject*`: ./FileObject*.html
.. _`char`: ./PrimitiveTypes.html
.. _`PlayerMetadata`: ./PlayerMetadata.html
.. _`PlayerPositionalRecord`: ./PlayerPositionalRecord.html
.. _`Human`: ./Human.html
.. _`Object`: ./Object.html