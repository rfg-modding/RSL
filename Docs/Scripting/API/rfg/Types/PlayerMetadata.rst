
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


PlayerMetadata
********************************************************
Metadata about the `player's`_ activities in game such as play time and supply crates destroyed.

Variables
========================================================

**Salvage** (`int`_)
    The players current salvage amount. Useable to buy weapon upgrades at the upgrade table.

**MiningCount** (`int`_)
    The amount of ore deposits the player has mined.

**SupplyCrateCount** (`int`_)
    The amount of supply crates the player has destroyed.

**DistrictHash** (`unsigned int`_)
    The hash for the current world district the player is in.

**DistrictTime** (`int`_)
    The time in the players current district.

**Upgrades[128]** (`UpgradeItem`_)
    An array of upgrades and their states. Each individual value may be ``nil``, so be sure to check them before accessing them.

**PlayTime** (`int`_)
    The players play time.

**LastDeathTime** (`int`_)
    The players last death time.

.. _`unsigned int`: ./PrimitiveTypes.html
.. _`UpgradeItem`: ./UpgradeItem.html
.. _`int`: ./PrimitiveTypes.html
.. _`player's`: ./Player.html
