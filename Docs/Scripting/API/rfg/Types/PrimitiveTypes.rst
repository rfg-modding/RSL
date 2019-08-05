
Primitive types
********************************************************
These are primitive types used by rfg. While Lua sees many of them as numbers, it's important to consider how the game sees them. For example, a char is an 8 bit type, meaning that it's values really only range from -127 to 127. While you can set it to higher values with a script, it won't make a difference trying to set it to a value beyond it's limits. In most circumstances this is unimportant, but you should keep it in the back of your mind.

Numbers
========================================================

.. note:: You can set integers to decimal values, and vice-versa without issue. Just understand that rounding may occur as a result of this.

Integral types
--------------------------------------------------------
These types can only be integers. That means that if you try setting one of these to a decimal value it will round towards zero.

============================= =====================================
Type                          Range             
============================= =====================================
**unsigned int**              ``0 to 4,294,967,2965``
**int**                       ``-2147483648 to 2147483647`` 
**unsigned int16**            ``0 to 65,535``
**int16**                     ``-32768 to 32767``     
**unsigned char**             ``0 to 255``    
**char**                      ``-127 to 127``             
============================= =====================================

Floating point types
--------------------------------------------------------------------
These types can be set to decimal values. The two floating point types are ``float``, which is the most common with rfg, and ``double``. The key difference between the two is that a double has greater precision and number range.

=========== ================ ==============
Type        Range            Precision 
=========== ================ ==============
**float**   ``+/- 3.4E38``   ``7 digits``
**double**  ``+/- 1.7E308``  ``15 digits``       
=========== ================ ==============

Bool
========================================================
A bool (or boolean) type can either be ``true`` or ``false``. You can use boolean values as expressions in if statements, like so:

.. code-block:: lua

    a = true
    if a then
        rsl.Log("a is true!", LogType.Info)
    end

Bitfields
========================================================
A bitfield is a type that allows the game to make variables smaller than 1 byte in size so that it may pack data in more tightly, and save on RAM usage. The important thing to know about this type is that it can widely vary in size and number range. As such, each bitfield will have it's number range listed. Bitfields are always an integral type so if you set a bitfield to a decimal value it will be rounded towards zero.

String
========================================================
A string is an array of characters. Declaring an array should be done by surrounding a value with quotation marks, like so:

.. note:: ``const char*`` types can generally be treated as strings.

.. code-block:: lua

    MyString = "Hello World!"

Strings can be concatenated using ``..``

.. code-block:: lua

    MyString = "Hello"
    MyString = MyString .. " World!"
    -- Now MyString == "Hello World!"
