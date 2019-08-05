.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


World
********************************************************
The rfg world structure. Contains the global list of all objects in the game and info about each of the world zones.

Variables
========================================================

**MissionObjectCreationMode** (`bool`_)
    Unknown value.

**LevelAmbient** (`Vector`_)
    The ambient light color of the environment.

**LevelBackAmbient** (`Vector`_)
    A secondary ambient light color of the environment.

**LastLoadedTerritory** (`char[64]`_)
    Unknown value.

**MaxWorldObjects** (`int`_)
    The maximum number of objects the game world can support.

**AllObjects** (`BaseArray<Object*>`_)
    An array containing all of the objects in the game world. You can iterate through this and filter objects by type to interact with the game world. When iterating through the list be sure to check if each object is ``nil`` before accessing it to avoid errors.

**TechLevel** (`float`_)
    The current tech level, used to determine the weapons used by NPCs.

**TechLevelMax** (`float`_)
    The maximum tech level possible.

**FlaggedObjects** (`Object*`_)
    Unknown value. Possibly an array of flagged objects that the game uses. May be ``nil``.

**CurrentFlaggedObject** (`Object*`_)
    Unknown value. May be ``nil``.

**CurrentFlaggedMode** (`char`_)
    Unknown value. Likely related to the previous two variables.

**DeserializeList** (`char[144]`_)
    Unknown value.

**CurWorldState** (`WorldStateModes`_)
    Unknown value.

**SlFlags** (`SaveLoadInfo`_)
     Flags used by the game to determine the right behavior when loading/saving the game. Such as if it should use the reset destruction feature on next load.

**PendingGameSaveSlot** (`GameSaveInfo*`_)
    Info about the game state which would be stored in a save game if you save. Things like the number of missions completed or hours played. May be ``nil``.

**DlcBundleId** (`int`_)
    Unknown value.

**PendingFilename** (`char[64]`_)
    Unknown value.

**PendingGameLoadWarpToPos** (`Vector`_)
    Unknown value.

**PendingGameLoadWarpToOrient** (`Matrix`_)
    Unknown value.

**StreamPos** (`Vector`_)
    Unknown value.

**NumTerritoryZones** (`int`_)
    Unknown value.

**GlobalZoneGrid** (`WorldZone*[257]`_)
    Unknown value. May be ``nil``.

**IsTerritory** (`bool`_)
    Unknown value.

**TerritoryName[128]** (`char`_)
    Unknown value.

**NumStreamingObjects** (`int`_)
    The number of objects currently being streamed in by the game.

**StubSerializationInProgress** (`bool`_)
    Unknown value.

.. _`bool`: ./PrimitiveTypes.html
.. _`Vector`: ./Vector.html
.. _`char`: ./PrimitiveTypes.html
.. _`char[64]`: ./PrimitiveTypes.html
.. _`char[144]`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`BaseArray<Object*>`: ./BaseArray.html
.. _`float`: ./PrimitiveTypes.html
.. _`Object*`: ./Object.html
.. _`WorldStateModes`: ./WorldStateModes.html
.. _`SaveLoadInfo`: ./SaveLoadInfo.html
.. _`GameSaveInfo*`: ./GameSaveInfo.html
.. _`Matrix`: ./Matrix.html
.. _`StreamGrid*`: ./StreamGrid.html
.. _`WorldZone*`: ./WorldZone.html
.. _`WorldZone*[257]`: ./WorldZone.html