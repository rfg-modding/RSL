
BaseArray
********************************************************
A generic array used by the game to store different types. It can store any type, such as `Objects`_ or `Humans`_, or literally anything else. You can access it's elements just like any other array by using brackets and specifying the index of the element you wish to access, like so: 

.. code-block:: lua

    -- Set `Object` equal to the first element in world object array. 
    -- Note that this array, unlike lua tables, is 0 based. That is, the first element has an index of 0.
    Object = rfg.ActiveWorld.AllObjects[0] 

The most common usage of this type is to iterate through the world object list, which contains all of the games objects, and perform some action on them. In this example the a for loop runs through the world object and counts the number of human objects currently in the game.

.. code-block:: lua

    HumanCount = 0
    ObjectList = rfg.ActiveWorld.AllObjects -- Make an alias to the list for convenience
    for i=0, rfg.ActiveWorld.AllObjects:Size(), 1 do -- Loop through all valid indices of the list 
        Object = ObjectList[i] -- Get the object at this index for convenience.

        if Object.Type == rfg.ObjectTypes.Human then -- Check if the object is a human.
            HumanCount = HumanCount + 1
        end
    end

    rsl.Log("Human count: " .. tostring(HumanCount))


Functions
========================================================

**Size** (`BaseArray`_)
    Returns the number of elements in this array as an `int`_.

**Capacity** (`BaseArray`_)
    Returns the maximum number of elements this array can contain as an `int`_.

.. _`int`: ./PrimitiveTypes.html
.. _`BaseArray`: ./BaseArray.html
.. _`Object`: ./Object.html
.. _`Human`: ./Human.html