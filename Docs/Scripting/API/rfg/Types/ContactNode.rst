
ContactNode
********************************************************
Node on a doubly linked list of contact nodes. Contains info about the contacted object for this node, and number of other contacts. The list can be traversed by looping through ``Previous`` and ``Next`` until a ``nil`` value is reached.

Variables
========================================================

**ContactObject** (`unsigned int`_)
    The handle of the contact `Object`_ for this node. 

**NumberOfContacts** (`int16`_)
    The number of contacted objects.

**Previous** (`ContactNode`_)
    The previous contact node. May be ``nil``.

**Next** (`ContactNode`_)
    The next contact node. May be ``nil``.


.. _`Bitfield`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`int16`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`Matrix43`: ./Matrix43.html
.. _`Matrix`: ./Matrix.html
.. _`Vector`: ./Vector.html
.. _`Object`: ./Object.html