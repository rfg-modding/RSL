
HumanRaycastHitInfo
********************************************************
Stores raycast data used for collision detection of weapons.

Variables
========================================================

**FirePosition** (`Vector`_)
    3D position that the weapon was fired from.

**TargetPos** (`Vector`_)
    3D position that the weapon was aiming at.

**HitPoint** (`Vector`_)
    3D position that the raycast impacted at.

**HitLocation** (`ObjectHitLocations`_)
    If the ray hit a human this represents the location on their body it impacted. This is an enum value.

**HitBone** (`int`_)
    If the ray hit a human this will be the index of the bone it hit.

.. _`int`: ./PrimitiveTypes.html
.. _`Vector`: ./Vector.html
.. _`ObjectHitLocations`: ./ObjectHitLocations.html