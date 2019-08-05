
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.

ObjectFlags
********************************************************
A set of flags used to describe an objects state and determines how the game treats it. 

.. Note:: The names of these variables are the same names the game uses for them and they may not all have an obvious or immediate effect. You may also find that one of the descriptions here in innaccurate. Feel free to update the page with more accurate info.

Variables
========================================================

**FlaggedListState** (`Bitfield`_)
    ``Range: -4 to 3``

**LightingSetOnce** (`Bitfield`_)
    ``Range: 0 to 1``

**Destroyed** (`Bitfield`_)
    Set to 1 if the object has been destroyed. ``Range: 0 to 1``

**NoSave** (`Bitfield`_)
    ``Range: 0 to 1``

**ForceFullSave** (`Bitfield`_)
    ``Range: 0 to 1``

**DestroyOnStream** (`Bitfield`_)
    Unconfirmed behavior. Based on the name the object is likely destroyed and set to defaults when it's streamed in for the first time. ``Range: 0 to 1``

**CreatedByMissionOrActivity** (`Bitfield`_)
    Set to 1 if the object was created by a mission or activity. ``Range: 0 to 1``

**DontTransform** (`Bitfield`_)
    ``Range: 0 to 1``

**WorldFree** (`Bitfield`_)
    ``Range: 0 to 1``

**Streaming** (`Bitfield`_)
    Set to 1 if the object is being streamed. ``Range: 0 to 1``

**Streamed** (`Bitfield`_)
    Set to 1 if the object is done being streamed. ``Range: 0 to 1``

**Persistent** (`Bitfield`_)
    ``Range: 0 to 1``

**Original** (`Bitfield`_)
    ``Range: 0 to 1``

**Stub** (`Bitfield`_)
    ``Range: 0 to 1``

**PreserveHandle** (`Bitfield`_)
    ``Range: 0 to 1``

**BpoIndex** (`Bitfield`_)
    ``Range: -2 to 1``

**IsDependent** (`Bitfield`_)
    ``Range: 0 to 1``

**Visited** (`Bitfield`_)
    ``Range: 0 to 1``

**SpecialLifetime** (`Bitfield`_)
    ``Range: 0 to 1``

**SerializeProtected** (`Bitfield`_)
    ``Range: 0 to 1``

**DontUseMe** (`Bitfield`_)
    ``Range: 0 to 1``

**StreamingFixed** (`Bitfield`_)
    ``Range: 0 to 1``

**RenderFlags** (`Bitfield`_)
    ``Range: -8 to 7``


.. _`Bitfield`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`Matrix43`: ./Matrix43.html
.. _`Matrix`: ./Matrix.html
.. _`Vector`: ./Vector.html
.. _`Object`: ./Object.html