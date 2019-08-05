Autorun scripts
********************************************************

RSL supports scripts which automatically run once RSL activation is complete (when you hear the 3 activation beeps). Using them is simple. All it requires is that a script named ``main.lua`` exists in one of the subfolders of the Scripts folder. RSL checks all the subfolders of the scripts folder ``/RSL/Scripts/some_subfolder`` for files named main.lua and tries to run them upon RSL activation.

.. note:: Depending on when you inject the RSL your autorun scripts could run before certain certain values like the player or world structures have been initialized. You should double check that ``rfg.ActivePlayer``, ``rfg.ActiveWorld``, ``rfg.ExplosionInfos``, and ``rfg.PhysicsSolver``, are not ``nil`` before using them in an autorun scripts code that is immediately executed.


Console commands
--------------------------------------------------------

A lua console is provided by the RSL. It's available by pressing F4. The console's inputs are ran directly by the lua interpreter, they're essentially single line scripts. This also means that adding console commands is very easy. You simply run a script with a function definition, and as long as there are no errors that function will be available for use in the lua console. The only downside to this is that you'll need to run the script with that function every time you start the game, by using an autorun script you can automate that process. Below is an example of an autorun script which adds a useful console command:

.. code-block:: lua

    -- Takes an object name or handle and reports back on if an object with that 
    -- name/handle exists and what it's position is.
    function ObjectExists(TargetName)

    	TargetObject = rfg.GetObject(TargetName) --GetObject has an overload 
        --that takes a name, and an overload that takes a handle.

    	if TargetObject == nil then
    		rsl.Log("Target object of name/handle \"{}\" not found\n", TargetName)
    	else
    		rsl.Log("Target object of name/handle \"{}\" found\n", TargetName)
    		rsl.Log("Position: {}\n", TargetObject.Position:GetDataString())
    	end
    end

If you don't want a function to be available in the lua console, simply mark it as a local function with the ``local`` keyword.