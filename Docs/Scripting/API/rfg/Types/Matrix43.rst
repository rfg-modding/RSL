
Matrix43
********************************************************
A 4x3 matrix. Can contain both rotation and translation info. Supports the following operators: ``+``, ``-``, ``==``.

- :ref:`Matrix43-variables`
- :ref:`Matrix43-functions`

.. _Matrix43-variables:

Variables
========================================================

**Rotation** (`Matrix`_)
    Rotation data. See the page on `Matrix`_ for more info.

**Translation** (`Vector`_)
    Translation data. See the page on `Vector`_ for more info.
    

.. _Matrix43-functions:

Functions
========================================================

**new** (`Matrix43`_ CopyMatrix)
    Creates a new Matrix43 and sets it's values to the values of ``CopyMatrix``.

**new** (`float`_ InitialValue)
    Creates a new Matrix43 and sets it's values to ``InitialValue``.

**new** (`Matrix`_ InitialRotation, `Vector`_ InitialTranslation)
    Creates a new Matrix43 and sets Rotation and Translation to InitialRotation and InitialTranslation respectively.

**SetAll** (`float`_ Value)
    Sets all the values of ``Self.Rotation`` and ``Self.Translation`` to ``Value``


.. _`float`: ./PrimitiveTypes.html
.. _`Matrix43`: ./Matrix43.html
.. _`Matrix`: ./Matrix.html
.. _`Vector`: ./Vector.html