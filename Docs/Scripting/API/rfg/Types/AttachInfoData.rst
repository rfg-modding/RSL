
AttachInfoData
********************************************************
Contains attachment data for an object if it is attached to another object.

.. - :ref:`AttachInfoData-variables`
.. - :ref:`AttachInfoData-functions`

.. _AttachInfoData-variables

Variables
========================================================

**ParentHandle** (`int`_)
    The handle of `Object`_ that this object is attached to.

**ParentPropPoint** (`int`_)
    The parents prop point that the child is attached to.

**ChildPropPoint** (`int`_)
    The prop point on the child which the child is attached to the parent by.

**RelativeTransform** (`Matrix43`_)
    Rotation and translation of the attached object (the child) relative to the parent.

**UseRelativeTransform** (`Bitfield`_)
    Uses the relative transform if set to 1. ``Range: 0-1``

**UpdatePhysics** (`Bitfield`_)
    Set to 1 if the game needs to update it's physics. ``Range: 0 to 1``

**Updated** (`Bitfield`_)
    Set to 1 if the game has updated it's physics. ``Range: 0 to 1``
    

.. _AttachInfoData-functions

.. _`Bitfield`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`unsigned int`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`Matrix43`: ./Matrix43.html
.. _`Matrix`: ./Matrix.html
.. _`Vector`: ./Vector.html
.. _`Object`: ./Object.html