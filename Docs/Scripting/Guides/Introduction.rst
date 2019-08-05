Introduction
********************************************************

Here you'll find all the info you need to start writing lua scripts for RFGR. While traditional modding involves editing existing data files to change the properties and behavior of the game, lua scripting allows for a much more dynamic modding experience. Some of the advantages of lua scripting are:

- You aren't restricted to editing existing data found in xtbls, due to the nature of the RSL the game can be opened up much more than before. 
- Lua scripts are responsive and can change their behavior over time, unlike xtbls which are simply static data files.
- You can edit lua scripts live instead of needing to restart -> unpack -> edit -> repack -> test -> repeat for even the smallest of changes. The higher iteration rate should speed up mod development and reduce hair pulling.

.. warning:: RSL is still in early stages of development. As such, you may find incomplete features, bugs, and experience breaking changes in updates. Keep this in mind before using it in it's current state.

Calling lua scripts
========================================================
Currently calling lua scripts is as simple as placing a .lua file in your Scripts folder, ``Red Faction Guerrilla Re-MARS-tered\RSL\Scripts`` and running it through the built in script editor, or script select menu. You might need to hit the refresh button if the script was created externally after RSL was started. 

You can also open the built-in script editor after loading RSL and save/load/create scripts right from the game. It's good for quick edits and testing, but I'd still recommend using an external editor for major editing.

A later release will feature more advanced methods for loading and running scripts. Likely having each script, set of scripts, or mod, be it's own package with information like version, and dependent packages.

.. note:: While the RSL includes a built in script editor with some useful features like syntax highlighting and error highlighting, it's still recommended to use a external editor for large amount of editing since they can offer more features than the internal one does.

Core library
=========================================================
The core library, in ``Red Faction Guerrilla Re-MARS-tered\RSL\Core``, includes useful functions, and types. It's loaded when RSL is started. You generally shouldn't distribute edits to this with a mod as it's meant to be a common library that all users have. You should however take a look at it. There are many useful values defined in the core library which are referenced in the docs.

One example of this is ObjectTypes.lua, which defines the table `rfg.ObjectTypes`_. This table has all object types (which will be discussed more in the next section), and their corresponding integer values, which can be used to sort objects by type. 

Objects
=========================================================
RFGR considers many things in the game world to be objects. Many of the things you can see in the game are objects, such as the player, humans, or vehicles, and even some things you can't see, like spawn points and cliff killzones. You can see a full list of object types in ObjectTypes.lua, or in the ObjectTypes page here in the docs.

Since objects are so pervasive, being able to access them is key to interacting with the game world. 

Accessing objects
---------------------------------------------------------
There are several ways to access objects. The first way to is use `rfg.GetObject`_. It takes a string or a number, which is the name or handle of the object you're looking for, respectively. Using this with a name isn't the most reliable way of finding objects, since most of them don't have names. But, passing a handle to it can be quite useful since many objects store handles to other objects. For example, ``Human.ShieldHandle`` is the object handle of that humans shield if they possess one. Another way of accessing objects is by looping through the world object list, like so:

.. code-block:: lua

    HumanCount = 0
    for i=0, rfg.ActiveWorld.AllObjects:Size(), 1 do --Loop through the global object list
        CurrentObject = rfg.ActiveWorld.AllObjects[i] --Make a reference variable to the current object for convenience.
        if CurrentObject.Type == rfg.ObjectTypes.Human then --Check if current object is a human object
            HumanCount = HumanCount + 1
        end
    end

    rsl.Log("HumanCount: {}\n", HumanCount)

.. note:: While lua tables use 1 based indexing, the rfg object list uses 0 based indexing. This is a side effect of c++ using 0 based indexing, but, this may be changed in a future update to avoid inconsistency with existing lua standards.

Note that if you tried accessing a human specific variable (or other derived types variable) before casting to that object type you should experience an error when running the script. You can use functions like ``Object:AsHuman()`` to cast the type to a human type, or the equivalent for the object type you're dealing with. The example below loops through the global object list, finds human objects, then casts the object to a human object and accesses ``HitPoints``, which is a variable that humans have, but other objects dont.

.. code-block:: lua

    for i=0, rfg.ActiveWorld.AllObjects:Size(), 1 do --Loop through the global object list
        CurrentObject = rfg.ActiveWorld.AllObjects[i] --Make a reference variable to the current object for convenience.
        if CurrentObject.Type == rfg.ObjectTypes.Human then --Check if current object is a human object
            if CurrentObject.AllIndex ~= rfg.ActivePlayer.AllIndex then --Make sure this human object isn't the player
                ObjectAsHuman = CurrentObject:AsHuman()
                ObjectAsHuman.HitPoints = 0 --Kill this human instance by setting it's HitPoints to 0
            end
        end
    end

.. important:: As of release 0.5.0 not all object types have been bound to lua yet due to time constraints. Therefore you can only cast to a few of them for now. The available object types for 0.5.0 are Human, Player, Zone, and District. For all other object types you'll only be able to access variables available to all `objects`_.


What next
=====================================================================
There are many other functions, types, and values available to scripts. Too many to list here. To see a list of them and more details you should view the `API`_ page. For more usage examples you should read the rest of the `guides`_, and look through the `examples`_ provided. You should also look through the `useful values`_ page for info on some useful preset values like ``rfg.ActivePlayer`` and ``rfg.PhysicsSolver``. If you'd like to contribute the the docs you should read `contributing`_.


.. _`API`: ../API.html
.. _`contributing`: ../../Contributing.html
.. _`examples`: ../Examples.html
.. _`objects`: ../API/rfg/Types/Object.html
.. _`rfg.ObjectTypes`: ../API/rfg/Types/ObjectTypes.html
.. _`rfg.GetObject`: ../API/rfg/Functions/GetObject.html
.. _`useful values`: ../API/rfg/UsefulValues.html
.. _`guides`: ../Guides.html