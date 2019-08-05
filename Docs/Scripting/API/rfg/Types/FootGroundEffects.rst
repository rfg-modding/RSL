
FootGroundEffects
********************************************************
Has variables for a humans footsteps and walking.

Variables
========================================================

**Name** (`char[20]`_)
    Name of the effect.

**WalkFoley** (`int`_)
    Walk sound effect id.

**RunFoley** (`int`_)
    Run sound effect id.

**JumpFoley** (`int`_)
    Jump sound effect id.

**LandFoley** (`int`_)
    Landing / ground impact sound effect id.

.. _`bool`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`char[20]`: ./PrimitiveTypes.html

struct human_info_flags //19
{
	__int8 female : 1;
	__int8 coin : 1;
	__int8 preload : 1;
	__int8 officer : 1;
	__int8 unarmed : 1;
	__int8 vip : 1;
	__int8 use_tech_level : 1;
	__int8 sniper : 1;
	__int8 elite_dodge : 1;
	__int8 riot_shield : 1;
	__int8 body_armor : 1;
	__int8 nonflammable : 1;
	__int8 no_attaching_projectiles : 1;
	__int8 guerrilla_tech : 1;
	__int8 guerrilla_rfc : 1;
	__int8 old_coot : 1;
	__int8 dan : 1;
	__int8 jenkins : 1;
	bool driverless_exit_only;
};