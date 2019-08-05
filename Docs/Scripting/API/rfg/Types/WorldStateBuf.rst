
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


WorldStateBuf
********************************************************
Buffer containing info about the players movements throughout a `WorldZone`_.

Variables
========================================================

**PlayerStartPos** (`Vector`_)
    The players starting position in this zone.

**PlayerStartOrient** (`Matrix`_)
    The players starting orientation in this zone.

**PlayerStartPosSafehouse** (`Vector`_)
    The players starting safehouse position.

**PlayerStartOrientSafehouse** (`Matrix`_)
    The player starting safehouse orient.

**Buf** (`char*`_)
    Unknown value. Likely an array that needs to be wrapped first to be used through lua.

**CurSize** (`int`_)
    The current size in bytes of ``Buf``.

**MaxSize** (`int`_)
    The max size in bytes of ``Buf``.

.. _`Vector`: ./Vector.html
.. _`Matrix`: ./Matrix.html
.. _`char*`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`WorldZone`: ./WorldZone.html
