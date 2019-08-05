
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


WorldZone
********************************************************
Represents a cube of the game world. The game world is split up into zones and loaded/unloaded as you move around in this. This generally isn't visible unless you maximize the far clip distance, disable fog, and move to a higher altitude where you'll see the individual zones as square region that load in as you move around.

Variables
========================================================

**Bmin** (`Vector`_)
    One "minimum" corner of the zones cube.

**Bmax** (`Vector`_)
    The "maximum" corner of the zones cube.

**Name** (`char[64]`_)
    The name of the zone. 

**State** (`WorldZoneStates`_)
    The state of the zone.

**DeserializeHeader** (`ZoneHeader*`_)
    The header data from the zones rfgzone_pc file. May be ``nil``.

**StoredZoneState** (`WorldStateBuf`_)
    Info about the players movements through this zone.

**Srid** (`unsigned int`_)
    Unknown value.

**IsBorderZone** (`bool`_)
    Set to ``True`` if the zone is a border zone. On the edge of the game world.

**Gid** (`unsigned int16`_)
    Unknown value.

.. _`Vector`: ./Vector.html
.. _`char[64]`: ./PrimitiveTypes.html
.. _`WorldZoneStates`: ./WorldZoneStates.html
.. _`ZoneHeader*`: ./ZoneHeader.html
.. _`WorldStateBuf`: ./WorldStateBuf.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`bool`: ./PrimitiveTypes.html
.. _`unsigned int16`: ./PrimitiveTypes.html