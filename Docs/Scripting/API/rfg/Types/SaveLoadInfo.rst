
SaveLoadInfo
********************************************************
Flags used by the game to determine the right behavior during saving and loading. Seen in `World`_. 

Variables
========================================================

**PendingNewGame** (`Bitfield`_)
    Equal 1 if a new game operation is pending. ``Range: 0 to 1``

**ResetDestruction** (`Bitfield`_)
    Equal to 1 if destruction should be reset on next load. ``Range: 0 to 1``

**PendingSaveGame** (`Bitfield`_)
    Equal to 1 if a save game operation is pending. ``Range: 0 to 1``

**PerformingSaveGame** (`Bitfield`_)
    Equal to 1 if a save game operation is occurring. ``Range: 0 to 1``

**PendingSaveState** (`Bitfield`_)
    Unknown value. ``Range: 0 to 1``

**PerformingSaveState** (`Bitfield`_)
    Unknown value. ``Range: 0 to 1``

**PendingSingleZone** (`Bitfield`_)
    Unknown value. ``Range: 0 to 1``

**SaveGameWarp** (`Bitfield`_)
    Unknown value. ``Range: 0 to 1``

**GameSaveCheckpoint** (`Bitfield`_)
    Unknown value.  ``Range: 0 to 1``

**GameSaveToDisk** (`Bitfield`_)
    Equal to 1 if the game is being saved to the hard drive. ``Range: 0 to 1``

**PendingLoadGameFromMemory** (`Bitfield`_)
    Equal to 1 if an operation to load the game from memory (RAM) is pending. ``Range: 0 to 1``

**AutoSaveGame** (`Bitfield`_)
    Equal to 1 if the game is auto saving. ``Range: 0 to 1``

**SavingStateData** (`Bitfield`_)
    Unknown value. ``Range: 0 to 1``

**PlayerStateAtSafehouse** (`Bitfield`_)
    Unknown value. ``Range: 0 to 1``

**PlayerStartPos** (`Vector`_)
    The players start position for this save game. ``Range: 0 to 1``

**PlayerStartOrient** (`Matrix`_)
    The players starting orientation for this save game. ``Range: 0 to 1``

.. _`World`: ./World.html
.. _`Vector`: ./Vector.html
.. _`Matrix`: ./Matrix.html
.. _`Bitfield`: ./PrimitiveTypes.html