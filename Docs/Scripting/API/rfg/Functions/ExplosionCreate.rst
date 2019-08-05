
ExplosionCreate
********************************************************
Spawns an explosion.

**Arguments:**

- `ExplosionInfo`_ **Info**: The properties of the explosion to be spawned. You can use `rfg.GetExplosionInfo`_ to get one of the games explosion presets, or iterate the preset list as shown in the `explosion examples`_.

- `Vector`_ **Position**: The position to spawn the explosion in. 

Alternative:

- `ExplosionInfo`_ **Info**: The properties of the explosion to be spawned. You can use `rfg.GetExplosionInfo`_ to get one of the games explosion presets, or iterate the preset list as shown in the `explosion examples`_.

- `float`_ **x**: The x position to spawn the explosion in.

- `float`_ **y**: The y position to spawn the explosion in.

- `float`_ **z**: The z position to spawn the explosion in.

Alternative:

- `ExplosionInfo`_ **Info**: The properties of the explosion to be spawned.

- `Object`_ **Source**: The source of the explosion.

- `Object`_ **Owner**: The owner of the explosion.

- `Vector`_ **Position**: The position to spawn the explosion in.

- `Matrix`_ **Orientation**: The orientation to spawn the explosion at.

- `Vector`_ **Direction**: The direction the explosion should point in. 

**Returns:**

- None

.. _`float`: ../Types/PrimitiveTypes.html
.. _`Vector`: ../Types/Vector.html
.. _`Matrix`: ../Types/Matrix.html
.. _`Object`: ../Types/Object.html
.. _`ExplosionInfo`: ../Types/ExplosionInfo.html
.. _`rfg.GetExplosionInfo`: ./GetExplosionInfo.html
.. _`explosion examples`: ../../../Examples/Explosions.html