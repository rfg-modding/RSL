
Explosions
***************************
RSL lets you spawn explosions, create custom explosions, and globally modify explosion values via lua scripts. 

Getting explosion info
---------------------------
`ExplosionInfo`_ is a very important type when it comes to handling explosions. There are several ways to get the `ExplosionInfo`_ instance for the games preset explosions. One way is by passing the explosions name to `rfg.GetExplosionInfo`_ as shown in the example below:

.. code-block:: lua

    MineExpInfo = rfg.GetExplosionInfo("mine")
    if MineExpInfo ~= nil then
        rsl.Log("Radius: {}\n", MineExpInfo.Radius)
    end

You can find the names of all the explosion presets in the explosion spawner gui. The other way is to loop through the `ExplosionInfo`_ list. As shown below:

.. code-block:: lua

    for i = 0, rfg.ExplosionInfos:Size(), 1 do --Go through the ExplosionInfo list with a for loop
        rsl.Log("{}: {}\n", i, rfg.ExplosionInfos[i].Name) --Log the name of each explosion preset.
    end

Global and local explosion infos
--------------------------------------
Using the two previous methods provides you with what would be considered "global" `ExplosionInfo`_ instances. That means that if you edit the values of these instances, it will change those values for all explosions spawned from that preset. If you wanted to have a "local" `ExplosionInfo`_ instance you should make a copy of the explosion preset you want to edit, and edit that copy. Then spawn the explosion using that copy. The example below shows this:

.. code-block:: lua

    ChargeExpInfo = rfg.GetExplosionInfo("remote_charge") --Get the remote charge ExplosionInfo preset. 
    ChargeExpInfo.Radius = 20.0 
    --Set the radius for the remote charge preset. 
    --Since no copy was made this is editing the global instance of this preset. 
    --Meaning that all remote charge explosions will have increased radius now.

    ChargeExpInfoCopy = rfg.ExplosionInfo:new(ChargeExpInfo)
    ChargeExpInfoCopy.ImpulseMagnitude = 120000 
    --Since this is editing the copy, normal remote charge explosions will not be effected. 
    --Only explosions you spawn by using the copy will have this increased impulse.

Spawning explosions
---------------------------
Explosions can be spawned by using `rfg.ExplosionCreate`_, as shown below:

.. code-block:: lua

    GrenadeExp = rfg.GetExplosionInfo("grenade_exp") --Get grenade explosion info
    rfg.ExplosionCreate(GrenadeExp, 1434.0, 15.0, 693.3) --Spawn grenade explosion outside the Oasis safehouse

Be sure to check the page for `rfg.ExplosionCreate`_ for additional overloads of the spawning function.

More examples
--------------------------------------
This first example goes over a bit of each of the previous subjects.

.. code-block:: lua

    -- Get a pointer to the remote charge ExplosionInfo instance
    RemoteChargeExp = rfg.GetExplosionInfo("remote_charge")
    RemoteChargeExp.Radius = 12.0 --Change the remote charge damage radius
    RemoteChargeExp.SecondaryRadius = 15.0

    -- If you don't want to edit the actual explosion values you need to make a copy
    RemoteChargeExpCopy = rfg.ExplosionInfo:new(RemoteChargeExp)
    -- Now we can edit the values of RemoteChargeExpCopy without changing the global
    -- remote charge explosion values.
    RemoteChargeExpCopy.AiSoundRadius = 2.0
    RemoteChargeExpCopy.Radius = 25.0
    RemoteChargeExpCopy.SecondaryRadius = 30.0
    RemoteChargeExpCopy.ImpulseMagnitude = -100000.0

    SpawnPosition = rfg.Vector:new(rfg.ActivePlayer.Position)
    SpawnPosition.y = SpawnPosition.y + 10.0
    -- Note that here we're not exactly spawning a remote charge explosion
    -- But a modified version of it
    rfg.ExplosionCreate(RemoteChargeExpCopy, SpawnPosition) 
    -- ^^ Also has an overload with many more args. Check the docs for more info on that.

    -- You can also iterate through the games explosion list, as shown with the func below:

    -- Normally it's good practice to stick console commands like this func 
    -- in their own file and to label them as such. Placing it here for examples sake.
    function ListExplosionInfoNames()
        for i = 0, rfg.ExplosionInfos:Size(), 1 do
            rsl.Log("{}: {}\n", i, rfg.ExplosionInfos[i].Name)
        end
    end

The next example shows an example of how to change the values of all explosion presets.

.. code-block:: lua

    Multiplier = 2.0

    for i = 0, rfg.ExplosionInfos:Size(), 1 do
        IndexExp = rfg.ExplosionInfos[i];
        IndexExp.Radius = IndexExp.Radius * Multiplier
        IndexExp.SecondaryRadius = IndexExp.SecondaryRadius * Multiplier
        IndexExp.Impulse = IndexEx.Impulse * Multiplier
    end


.. _`ExplosionInfo`: ../API/rfg/Types/ExplosionInfo.html
.. _`rfg.GetExplosionInfo`: ../API/rfg/Functions/GetExplosionInfo.html
.. _`rfg.ExplosionCreate`: ../API/rfg/Functions/ExplosionCreate.html