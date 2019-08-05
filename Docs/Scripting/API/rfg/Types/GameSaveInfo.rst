
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


GameSaveInfo
********************************************************
Additional info about the current save game.

Variables
========================================================

**NumMissionsCompleted** (`int`_)
    The number of missions completed in this save.

**NumActivitiesCompleted** (`int`_)
    The number of activities completed in this save game.

**DistrictsLiberated** (`int`_)
    The number of districts liberated in this save game.

**TerritoryIndex** (`int`_)
    The current territory index of the player in this save game.

**DistrictIndex** (`int`_)
    The current district index of the player in this save game.

**Day** (`int`_)
    The real world day at the time this game was saved.

**Month** (`int`_)
    The real world month at the time this game was saved.

**Year** (`int`_)
    The real world year at the time this game was saved.

**Hours** (`int`_)
    The number of hours played in this save.

**Minutes** (`int`_)
    The number of minutes played in this save.

**Seconds** (`int`_)
    The number of seconds played in this save.

**AutoSave** (`bool`_)
    Whether or not autosave is enabled.

**UsedSlot** (`bool`_)
    Unknown value.

**DlcId** (`int`_)
    Unknown value.

**SaveSlotIndex** (`unsigned int`_)
    The index of this save game. The game supports 10 saves and an autosave.

**HammersUnlocked** (`char`_)
    Determines whether MP hammers are unlocked.

**GoldenHammerDesired** (`bool`_)
    Unknown value.

**NewData** (`GameSaveInfoNewData`_)
    More save data that is for some reason placed in it's own type. 

**Padding** (`char[117]`_)
    Padding. Likely placed in by the compiler or to allow future expansion of the save file format without changing it.

.. _`int`: ./PrimitiveTypes.html
.. _`bool`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`char`: ./PrimitiveTypes.html
.. _`char[117]`: ./PrimitiveTypes.html
.. _`GameSaveInfoNewData`: ./GameSaveInfoNewData.html