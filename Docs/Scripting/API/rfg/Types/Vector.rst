
Vector
********************************************************
Used to represent several different values in the 3D world. For example, a 3D coordinate, direction, velocity, or a surface normal direction. Supports the following operators: ``+``, ``-``, ``*``, ``==``.

- :ref:`Vector-variables`
- :ref:`Vector-functions`

.. _Vector-variables:

Variables
========================================================

**x** (`float`_)
    Coordinate or magnitude on the x axis. Positive x points east on the world map and negative x points west.

**y** (`float`_)
    Coordinate or magnitude on the y axis. Positive y points directly up in the game world while negative y points directly down.

**z** (`float`_)
    Coordinate or magnitude on the z axis. Positive z points north on the world map and negative z points south.


.. _Vector-functions:

Functions
========================================================

**new** (`Vector`_ CopyVector)
    Creates a new vector and sets it's values to the values of ``CopyVector``.

**new** (`float`_ InitialValue)
    Creates a new vector and sets it's values to ``InitialValue``.

**new** (`float`_ x, `float`_ y, `float`_ z)
    Creates a new vector and sets it's values directly with ``x``, ``y``, and ``z``. 

**Cross** (`Vector`_ B)
    Returns the cross product (a vector) of the calling vector and vector ``B``.

**Magnitude** ( )
    Returns the magnitude of the vector as a `float`_

**Scale** (`float`_ Multiplier)
    Returns a new vector made up of the components of the this vector times ``Multiplier``. You can use ``1 / x`` as a multiplier to divide all the components by that number. Be sure to check that ``x ~= 0``.

**SetAll** (`float`_ Value)
     Sets all the vectors components to ``Value``

**UnitVector** ( )
    Returns the `unit vector`_ of this vector. Which is a vector with the same direction of this vector, but a magnitude of 1.

**GetDataString** (`bool`_ Parentheses = false, `bool`_ Labels = true)
    Returns a `string`_ with the vector coordinates listed. If no arguments are provided it has false, then true as it's default args. Example usage:

    .. code-block:: lua

        a = rfg.Vector:new(1434.0, 15.0, 693.3)
        DataString = a.GetDataString()
        -- DataString == "x: 1434.0, y: 15.0, z: 693.3"


.. _`bool`: ./PrimitiveTypes.html
.. _`float`: ./PrimitiveTypes.html
.. _`Vector`: ./Vector.html
.. _`unit vector`: https://en.wikipedia.org/wiki/Unit_vector
.. _`string`: ./PrimitiveTypes.html