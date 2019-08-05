
GetExplosionInfo
********************************************************
Attempts to get the `ExplosionInfo`_ data for an explosion of the inputted name. Alternatively you could iterate the explosion preset list, as explained in one of the `explosion examples`_.

**Arguments:**

- `String`_ **Name**: The name of the explosion preset to get info for.

**Returns:**

- `ExplosionInfo`_ or ``nil`` **Info**: The explosion info. Will be ``nil`` if no explosion with the specified name was found. You can use the explosion spawning menu or write a simple logging script to get a list of all explosion preset names.

.. _`String`: ../Types/PrimitiveTypes.html
.. _`Vector`: ../Types/Vector.html
.. _`Matrix`: ../Types/Matrix.html
.. _`Object`: ../Types/Object.html
.. _`ExplosionInfo`: ../Types/ExplosionInfo.html
.. _`rfg.GetExplosionInfo`: ./GetExplosionInfo.html
.. _`explosion examples`: ../../../Examples/Explosions.html