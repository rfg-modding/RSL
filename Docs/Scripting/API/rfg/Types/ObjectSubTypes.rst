
ObjectSubTypes
========================================================
Another value that can be used to differentiate objects from each other and figure out what specifically they are. A good example of where this will be useful (once vehicles are binded to lua) is figuring out what type of vehicle an object is (flyer, walker, automobile). These are defined in ``./Core/rfg/ObjectSubTypes.lua``. You can get an objects subtype via ``Object.SubType``. A simple example of this would be counting the number of flyers and walkers, which both have the object type of vehicle, but different subtypes.

.. code-block:: lua

    WalkerCount = 0
    FlyerCount = 0
    for i=0, rfg.ActiveWorld.AllObjects:Size(), 1 do
        Object = rfg.ActiveWorld.AllObjects[i]
        if Object.Type == rfg.ObjectTypes.Vehicle then
            if Object.SubType == rfg.ObjectSubTypes.Flyer then
                FlyerCount = FlyerCount + 1
            elif Object.SubType == rfg.ObjectSubTypes.Walker then
                WalkerCount = WalkerCount + 1
            end
        end
    end
    rsl.Log("Number of flyer objects found: {}\n", FlyerCount)
    rsl.Log("Number of walker objects found: {}\n", WalkerCount)

====================== ========================================= ==========
Object Type            Access Variable                           Value     
====================== ========================================= ==========
GeneralMover           ``rfg.ObjectSubTypes.MoverGeneral``       0
RfgMover               ``rfg.ObjectSubTypes.MoverRfg``           1
Npc                    ``rfg.ObjectSubTypes.HumanNpc``           2
`Player`_              ``rfg.ObjectSubTypes.HumanPlayer``        3 
Automobile             ``rfg.ObjectSubTypes.VehicleAuto``        4 
Flyer                  ``rfg.ObjectSubTypes.VehicleFlyer``       5 
Walker                 ``rfg.ObjectSubTypes.VehicleWalker``      6
Weapon                 ``rfg.ObjectSubTypes.ItemWeapon``         7
Projectile             ``rfg.ObjectSubTypes.ItemProjectile``     8  
MultiObjectFlag        ``rfg.ObjectSubTypes.ItemMultiFlag``      9    
MultiObjectFlag        ``rfg.ObjectSubTypes.ItemMultiBackpack``  10 
N/A                    ``rfg.ObjectSubTypes.NumObjectSubTypes``  11    
N/A                    ``rfg.ObjectSubTypes.Invalid``            4294967295          
====================== ========================================= ==========

.. _`Object`: ./Object.html
.. _`Human`: ./Human.html
.. _`Zone`: ./Zone.html
.. _`Player`: ./Player.html