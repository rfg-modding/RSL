
Matrix
********************************************************
A 3x3 matrix. Commonly used to represent orientation of objects and also used to represent the orientation of the player camera. Supports the following operators: ``+``, ``-``, ``==``.

- :ref:`Matrix-variables`
- :ref:`Matrix-functions`

.. _Matrix-variables:

Variables
========================================================

**rvec** (`Vector`_)
    The right vector. For the free cam this points directly right of the forward vector (90° offset).

**uvec** (`Vector`_)
    The up vector. For the free cam this points up from the forward vector (90° offset).

**fvec** (`Vector`_)
    The forward vector. For the free cam this points the direction the camera is pointing.


.. _Matrix-functions:

Functions
========================================================

**new** (`Matrix`_ CopyMatrix)
    Creates a new matrix and sets it's values to the values of ``CopyMatrix``.

**new** (`float`_ InitialValue)
    Creates a new matrix and sets it's values to ``InitialValue``.

**new** (`Vector`_ Right, `Vector`_ Up, `Vector`_ Forward)
    Creates a new matrix and sets it's vectors directly with ``Right``, ``Up``, ``Forward``.

**SetAll** (`float`_ Value)
    Sets all the Matrices variables to ``Value``


.. _`float`: ./PrimitiveTypes.html
.. _`Matrix`: ./Matrix.html
.. _`Vector`: ./Vector.html