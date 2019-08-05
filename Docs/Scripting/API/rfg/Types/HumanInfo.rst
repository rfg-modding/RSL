.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.

HumanInfo
********************************************************
Contains additional information about a human. Each human has their own unique copy of this type.

Variables
========================================================

**MaxHitPoints** (`int`_)
    Max hit points this human can have.

**MaxKnockdownHits** (`int`_)
    The maximum number of melee hits before this human will be knocked over.

**MaxSpeed** (`float`_)
    Max speed in m/s of this human.

**DefaultEquipItem** (`InvItemInfo`_)
    The default item that this human has equipped.

**DefaultLastEquipItem** (`InvItemInfo`_)
    The last item equipped.

**Name** (`char*`_)
    The humans name.

**NameCrc** (`unsigned int`_)
    The names crc hash.

**ModelName** (`char*`_)
    This humans 3D model filename.

**AnimSetName** (`char*`_)
    This humans animation set filename.

**AnimSetNameCrc** (`unsigned int`_)
    The anim set filename's crc hash.

**RigName** (`char*`_)
    This humans rigging filename.

**SRID** (`int`_)
    Likely a unique identifier for this human. Not confirmed.

**SlotID** (`int`_)
    Unknown value.

**DefaultHeightScale** (`float`_)
    The height scale of this human. With 1.0 being no scaling, 0.5 being half size, 2.0 being double the size, etc. Testing with this did not result in an immediate height change. A way to force rescaling may need to be found.

**HeightScaleVariation** (`float`_)
    Unknown value.

**DefaultTeam** (`HumanTeams`_)
    The team this human is on (EDF, Marauders, etc).

**HurtThreshold** (`int16`_)
    Unknown value.

**HomeDistrict** (`int`_)
    Unknown value.

**AimErrorPercent** (`float`_)
    Unknown value.

**FootEffects** (`FootGroundEffects`_)
    Unknown value.

**NumHeads** (`int`_)
    Unknown value.

**Heads** (`CharDefHead*[4]`_)
    Unknown value.

**NumGeneralProps** (`int`_)
    The number of props this human has. The actual prop data has not yet been bound to lua.

**LowerSpineBoneIndex** (`int`_)
    Unknown value.

**UpperSpineBoneIndex** (`int`_)
    Unknown value.

**PelvisBoneIndex** (`int`_)
    Unknown value.

**HeadBoneIndex** (`int`_)
    Unknown value.

**NeckBoneIndex** (`int`_)
    Unknown value.

**EyeLeftBoneIndex** (`int`_)
    Unknown value.

**EyeRightBoneIndex** (`int`_)
    Unknown value.

**CalfLeftBoneIndex** (`int`_)
    Unknown value.

**CalfRightBoneIndex** (`int`_)
    Unknown value.

**CameraBoneIndex** (`int`_)
    Unknown value.

**DropCashMin** (`int`_)
    Unknown value.

**DropCashMax** (`int`_)
    Unknown value.

**LightEffectHandle** (`unsigned int`_)
    Unknown value.

**LightTagNames** (`char*[2]`_)
    Unknown value.

**Flags** (`HumanInfoFlags`_)
    More flags used to describe this humans behavior.

.. _`bool`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`char*`: ./PrimitiveTypes.html
.. _`char*[2]`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`int16`: ./PrimitiveTypes.html
.. _`HumanTeams`: ./HumanTeams.html
.. _`InvItemInfo`: ./InvItemInfo.html
.. _`FootGroundEffects`: ./FootGroundEffects.html
.. _`CharDefHead*[4]`: ./CharDefHead.html
.. _`HumanInfoFlags`: ./HumanInfoFlags.html