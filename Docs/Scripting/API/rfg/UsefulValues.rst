
Useful values
************************
These are useful variables that the RSL finds at runtime and provides for use in scripts.

`Player`_ ``rfg.ActivePlayer``: This is the player type instance. Allows you to easily access the player without needing to iterate the world object list and look for them.

`World`_ ``rfg.ActiveWorld``: The rfg world instance. Holds the global/world object list which you can loop through to manipulate and collect data on all the objects in the game world.

.. Document rfg.ActivePhysicsWorld here once it's bound. For now only the solver is bound since it has real uses.

`hkpSolverInfo`_ ``rfg.PhysicsSolver``: Contains values which influence the physics solvers behavior. You can already change these values in the physics tweaks gui. Be careful changing these if you want a stable game experience. The physics sim is in a very delicate balance and changing these values can easily make it unstable.

`ExplosionInfo`_ ``rfg.ExplosionInfos``: A list of the games explosion presets. You generally shouldn't edit these unless you intend to change an explosions properties globally. You can see examples on how to use this in `explosion examples`_.

.. _`Player`: ./Types/Player.html
.. _`World`: ./Types/World.html
.. _`hkpSolverInfo`: ./Types/hkpSolverInfo.html
.. _`ExplosionInfo`: ./Types/ExplosionInfo.html
.. _`explosion examples`: ../../Examples/Explosions.html