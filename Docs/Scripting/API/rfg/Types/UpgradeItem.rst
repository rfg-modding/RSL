
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


UpgradeItem
********************************************************
An entry for an upgrade which can be accessed at an upgrade table at any safehouse.

Variables
========================================================

**CurrentLevel** (`char`_)
    The upgrades current level.

**AvailabilityBitfield** (`unsigned __int16`_)
    Whether or not the upgrade is available.

**UnlockedNotifiedBitfield** (`unsigned __int16`_)
    Unknown value.

**NewNotifiedBitfield** (`unsigned __int16`_)
    Unknown value.

.. _`unsigned __int16`: ./PrimitiveTypes.html
.. _`char`: ./PrimitiveTypes.html

	char current_level; //1
	unsigned __int16 availability_bitfield; //2
	unsigned __int16 unlocked_notified_bitfield; //2
	unsigned __int16 new_notified_bitfield; //2