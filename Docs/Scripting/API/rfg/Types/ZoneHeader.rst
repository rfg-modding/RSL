
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


ZoneHeader
********************************************************
The header data found in the first 24 bytes of rfgzone_pc files. Each `WorldZone`_ stores this data from it's own rfgzone_pc file.

Variables
========================================================

**Signature** (`unsigned int`_)
    Magic header / unique signature found at the start of every valid rfgzone_pc file. Used to confirm that the file was properly extracted and to identify the format from other types. For a valid rfgzone_pc file this equals 1162760026. The same value is shared by layer_pc files which likely means they are the same format.

**Version** (`unsigned int`_)
    The file format version. For RFGR this should always equal 36.

**NumObjects** (`int`_)
    The number of objects in this zone when it's unaltered.

**NumHandles** (`int`_)
    The number of handles in this zone when it's unaltered. Object handles can be used to reference an object. You can get an object using it's handle by passing it's handle to ``rfg.GetObject``, which has two overloads. One which takes an objects name, a `string`_, and one that takes an objects handle, an `unsigned int`_.

**DistrictHash** (`unsigned int`_)
    Likely a hash of the zones district name. Unconfirmed.

**Flags** (`unsigned int`_)
    Stores flags determining the zones state or behavior. Exact values and uses unknown.

.. _`unsigned int`: ./PrimitiveTypes.html
.. _`string`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`WorldZone`: ./WorldZone.html