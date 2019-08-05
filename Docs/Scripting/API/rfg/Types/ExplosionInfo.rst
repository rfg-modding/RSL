
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


ExplosionInfo
********************************************************
Information about an explosion. Used when spawning an explosion. You can use ``rfg.GetExplosionInfo()`` to get an explosion of the specified name, or you can iterate the games explosion preset list directly. If you'd like to make a custom explosion, using an existing one as a template you can make a copy of it and modify it from there. See the examples section for a more detailed explanation of this. Note that many of these variable descriptions were pulled from explosions.xtbl and slightly modified.

Variables
========================================================

**Name** (`String`_)
    The explosions name. Probably shouldn't change this in case the game expects certain named explosions to exist. Note: is really a char[32], behaves like a string.

**UniqueId** (`int`_)
    A unique Id used to identify an explosion preset.

**NameCrcStr** (`unsigned int`_)
    CRC hash on the explosions name string.

**Flags** (`unsigned int`_)
    Flags representing behavior about the explosion. The purpose of each bit/value is currently unknown. Should be easy enough to determine these by looking at the flags var description in explosions.xtbl.

**Radius** (`float`_)
    The explosion radius.

**SecondaryRadius** (`float`_)
    The secondary explosion radius. Equivalent to ``<CrumbleRadius>`` in ``explosions.xtbl``.

**KnockdownRadius** (`float`_)
    The knockdown radius in meters for humans. Also the distance at which the damage to humans falls off to 0 (from explosions.xtbl).

**FlinchRadius** (`float`_)
    The flinch radius in meters for humans.

**AiSoundRadius** (`float`_)
    The maximum distance in meters, that humans/ai can hear the sound of this explosion.

**HumanMinDamageHitpoints** (`unsigned int`_)
    Amount of hitpoints to do at the Blast Radius of the explosion to humans.

**HumanMaxDamageHitpoints** (`unsigned int`_)
    Amount of hitpoints to do at the exact center of the explosion to humans.

**VehicleMinDamageHitpoints** (`unsigned int`_)
    Minimum amount of hitpoints to do at the Secondary Radius to vehicles and oridinary objects (not human or destroyable). Often will be much less than Max Vehicle Damage.

**VehicleMaxDamageHitpoints** (`unsigned int`_)
    Amount of hitpoints to do at the exact center of the explosion to vehicles and oridinary objects (not human or destroyable).

**PlayerDamageMult** (`float`_)
    Multiplier applied to damage calculation for players.

**PlayerVehDamageMult** (`float`_)
    This is a multiplier applied to the damage calculation to the player's vehicle.  It is used instead of the Player multiplier - they are not multiplied together.

**PlayerVehicleImpulseMult** (`float`_)
    Impulse multiplier for when the player's vehicle is hit with this explosion.

**ImpulseMagnitude** (`float`_)
    Maximum impulse to apply at the center of the explosion in kg * m/s. This is interpolated to 0 at the explosion edge.

**StructuralDamage** (`int`_)
    Damage amount to be applied to destroyable objects. Damage to destroyable objects is computed entirely different then normal objects, so this value has little relevence compared to human or vehicle damage.

**ExpandingExplosionDuration** (`unsigned int`_)
    This is used to control how long (in milliseconds) it takes an expanding explosion to reach the full radius.

**ExpandingExplosionDelay** (`unsigned int`_)
    This controls how long to delay (in milliseconds) before starting to delete pieces, the effect(s) start immediately

**NumEffects** (`unsigned int`_)
    The number of effects the explosion plays.

**Effects** (`unsigned int[4]`_)
    An array of effects that the explosion plays. Up to 4 effects can be used. Zero based array.

**NumMaterialEffects** (`unsigned int`_)
    The number of material effects the explosion has.

**MaterialEffects** (`unsigned int[8]`_)
    An array of material effects that the explosion plays. Up to 8 material effects can be used. Zero based array.

**MaterialReference** (`char[8]`_)
    Unknown value. Zero based array with 8 elements.

**SalvageMaterial** (`SalvageMaterialTypes`_)
    Salvage material used by the explosion.

**SalvageMaxPieces** (`int`_)
    Max number of salvage pieces dropped by the explosion.

**SalvageProbability** (`float`_)
    The probability that the explosion will drop salvage. 1.0 is a 100% probability and 0.0 is a 0% probability.

**TimeBetweenBreaks** (`int`_)
    Time between each destruction frame of breaking links. This might only be valid if another variable is set. Explosions.xtbl defines a parent variable to this one called ``Break_off_pieces`` with the following description: "*Set this to make the explosion behave like a nano-rifle (breaking off pieces from objects)*".

**HalfAngleDot** (`float`_)
    When specified it defines half angle (in degrees) for a cone around the fvec of the explosion orient, things outside that cone are not damaged.

**BlastDecalRadius** (`float`_)
    The radius of the sphere used to place blast decals.

**CameraShakeType** (`String`_)
    The camera shake type. Can be one of several preset values: ``explosion_small``, ``explosion_large``, ``explosion_quake``, ``explosion_very_large``, ``explosion_smash``.

**CameraShakeMultiplier** (`float`_)
    Base multiplier of the camera shake. Values greater than 1.0 will make the shaking effect more intense than usual.

**CameraShakeFalloff** (`float`_)
    The distance from the explosion at which the camera doesn't shake at all.

**IgnoreOrientation** (`bool`_)
    Whether the orientation of the explosion should be ignored. Unknown what it does when this is true. Perhaps uses some default orientation, like directly upwards in the y direction.

**AlwaysRagdoll** (`bool`_)
    Always ragdoll instead of playing knockdown animations.

.. _`String`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`unsigned int[4]`: ./Unsigned Int[4].html
.. _`unsigned int[8]`: ./Unsigned Int[8].html
.. _`char[8]`: ./Char[8].html
.. _`SalvageMaterialTypes`: ./Salvagematerialtypes.html
.. _`char[32]`: ./Char[32].html
.. _`bool`: ./PrimitiveTypes.html
