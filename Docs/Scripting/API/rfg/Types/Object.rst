
Object
********************************************************
Nearly all things you can see in the game, and even some things you can't see, like spawn points or trigger regions, are derived from this type.


- :ref:`Object-variables`
- :ref:`Object-functions`

.. _Object-variables:

Variables
========================================================

**Position** (`Vector`_)
    The objects x, y, z position.

**Orientation** (`Matrix`_)
    A 3x3 matrix which describes the orientation of the object. Consists of a right vector, up vector, and forward vector.

**Child** (`Object`_)
    Pointer to one of the objects children. Is nil if it has no children.

**ChildNext** (`Object`_)
    Shortcut for ``Self.Child.FlaggedNext``. Is nil if no children

**ChildPrevious** (`Object`_)
    Shortcut for ``Self.Child.FlaggedPrevious``. Is nil if no children.

.. **ChildConstraintPtr** (`Constraint`_)
    desc (Not yet bound)

.. **HostConstraintPtr** (`Constraint`_)
    desc (Not yet bound)

**AttachInfo** (`AttachInfoData`_)
    Data about how this object is attached to other objects if applicable. May be nil if it is not.

**HavokHandle** (`unsigned int`_)
    This may be the handle for the objects havok rigid body (unconfirmed). This handle is different from an object handle as havok rigid bodies are not objects.

**ContactInfo** (`ObjectContactInfo`_)
    Data about all objects this object is in contact with.

**ObjFlags** (`ObjectFlags`_)
    A set of flags used to track object behavior and state.

**CheckingReset** (`int`_)
    Unknown purpose.

**NameIndex** (`int16`_)
    Used by the game to access to the objects name on a as of yet unlocated list of object names.

**FlaggedNext** (`Object`_)
    Pointer to another object, forming a doubly linked list of "flagged" objects. It's unknown what is meant by them being flagged. May be nil.

**FlaggedPrevious** (`Object`_)
    Pointer to the previous flagged object. May be nil.

**Handle** (`unsigned int`_)
    The objects handle. Handles are often used in place of a pointer to the object all across the game. Use ``rfg.GetObjectByHandle`` to gain access to the object who matches that handle.
    
**Parent** (`unsigned int`_)
    The handle of the objects parent object if it has one.

**BPOHandle** (`HavokBPO`_)
    Contains state data used by havok physics engine. May be nil.

**AllIndex** (`int16`_)
    The index of the object on ``rfg.ActiveWorld.AllObjects``

**TypeIndex** (`int16`_)
    Used by the game to track the objects type. Exact usage/purpose unknown.

**SubtypeIndex** (`int16`_)
    Used by the game to track the objects subtype. Exact usage/purpose unknown.

**Type** (`char`_)
    The objects type. Should match one of the values in `rfg.ObjectTypes`_ a table of object types and their corresponding integer values.

**SubType** (`char`_)
    The objects subtype. Should match one of the values in `rfg.ObjectSubTypes`_ a table of object subtypes and their corresponding integer values.

**LastKnownBMin** (`Vector`_)
    One corner of the objects bounding box. A 3D point.

**LastKnownBMax** (`Vector`_)
    The other corner of the objects bounding box. A 3D point.

**SRID** (`unsigned int`_)
    Exact purpose unknown. Might to be a unique integer identifying the object (unconfirmed).


.. _Object-functions:

Functions
========================================================

.. warning:: Be sure to check an objects type before casting it to avoid having  garbage values or unintentionally changing adjacent memory. For example, if you are casting an object to `Human`_, double check that ``Self.Type == rfg.ObjectTypes.Human`` is true before casting it.

**CastToHuman** (`Object`_)
    Returns this object as a `Human`_. 

**CastToPlayer** (`Object`_)
    Returns this object as a `Player`_. 

**CastToZone** (`Object`_)
    Returns this object as a `WorldZone`_. 

.. _`Object`: ./Object.html
.. _`Vector`: ./Vector.html
.. _`Matrix`: ./Matrix.html
.. _`AttachInfoData`: ./AttachInfoData.html
.. _`ObjectContactInfo`: ./ObjectContactInfo.html
.. _`ObjectFlags`: ./ObjectFlags.html
.. _`Human`: ./Human.html
.. _`Player`: ./Player.html
.. _`WorldZone`: ./WorldZone.html
.. _`District`: ./District.html
.. _`HavokBPO`: ./HavokBPO.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`int16`: ./PrimitiveTypes.html
.. _`char`: ./PrimitiveTypes.html
.. _`rfg.ObjectTypes`: ./ObjectTypes.html
.. _`rfg.ObjectSubTypes`: ./ObjectSubTypes.html