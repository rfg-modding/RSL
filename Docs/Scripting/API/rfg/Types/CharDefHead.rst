
CharDefHead
********************************************************
Contains info about a characters head such as it's mesh and animation rig.

Variables
========================================================

**Name** (`char*`_)
    Character head name.

**LodName** (`char*`_)
    Lod file name.

**MorphMatSRID** (`int`_)
    Unique ID for the heads material.

**HeadMorph** (`int`_)
    Unknown value. Likely related to animation.

**BaseHeadMorph** (`int`_)
    Unknown value. Likely related to animation.

**NumSkinShaderParams** (`int`_)
    Number of skin shader params. Actual skin shader params not bound to lua yet.

.. _`Bitfield`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`int16`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`char*`: ./PrimitiveTypes.html