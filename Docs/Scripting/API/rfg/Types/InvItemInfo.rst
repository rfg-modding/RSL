.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.

InvItemInfo
********************************************************
Holds data defining the behavior of an inventory item such as remote charges or the nanorifle. A variable containing weapon info has not been bound to lua yet due to time constraints and so is unlisted here.

Variables
========================================================

**Name** (`char*`_)
    Name of the inventory item.

**NameChecksum** (`ChecksumStri`_)
    Checksum of the items name.

**DisplayName** (`char*`_)
    Name used in menus and the hud.

**Cost** (`int`_)
    Unknown value. 

**DefaultCount** (`int`_)
    Default amount of this item to be carried by the player.

**MaxItem** (`int`_)
    Max amount of this item the player can carry.

**Description** (`char*`_)
    Description of the items behavior and appearance.

**ItemOrder** (`char`_)
    Unknown value.

.. _`bool`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`char*`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`int16`: ./PrimitiveTypes.html
.. _`ChecksumStri`: ./ChecksumStri.html