Lua overrides
********************************************************

While a major goal of RSL is to add a lua scripting api to RFG, the game infact already has lua built in. Albeit, it's a very old version of lua 5.0, and it's not used very extensively. RFG uses about a dozen lua scripts to provide some of it's user interface logic. 

This guide describes how to use the lua overrides feature which lets you override rfg lua scripts with your own versions of them. You can already edit these scripts by extracting rfgs vpp_pc and str2_pc files and locating them. There are a few in misc.vpp_pc, and a few hidden in str2_pc files in interface.vpp_pc. That however, is a hassle, and you won't be needing to do that for this. The lua overrides feature lets you access and replace these scripts without ever touching the data folder.

.. important:: Override scripts currently do not have access to the RSL scripting api. This means that override scripts can only use things built into lua 5.0 and things already exposed to the rfg lua state. This is because RSL and rfg have two separate lua states, and manipulating both creates additional technical challenges. This also means that error reporting for override scripts is generally worse and errors in overrides are more likely to crash the game.

Dumping rfg scripts
----------------------------------
Dumping rfg's built in scripts is an automatic process. Each time one is loaded RSL will save a copy of it in ``/RSL/RFG_Lua/Lua_Dumps``. You'll also see a message in the log each time a script is dumped, such as ``[Info] Dumping rfg_ui_safehouse_weapons.lua``, which is the script for the safehouse weapons locker gui. 

Scripts are only dumped when they are run, and some scripts are only run at startup. Therefore, the best practice to dump all rfg scripts is to run the RSL from game startup and open all menus you can except MP and wrecking crew menus, since they'll crash the game with the RSL active.

Overriding rfg scripts
-----------------------------------
To override a script you must make a script with the same name as it in ``RSL/RFG_Lua/Overrides/``. So for example, if you wanted to override ``rfg_ui_globals.lua``, you'd create a file with that name in the overrides folder, and make your edits there. From there the real script will automatically be overriden next time it's ran by the game. A message will be logged each time a script is overriden, such as ``[Info] Overriding rfg_ui_globals.lua``.

.. note:: Some scripts, such as ``rfg_ui_globals.lua`` are only run once at game startup, and so to override them you must run RSL from game startup and have your override script ready in the overrides folder. Scripts that are called many times like the weapons locker ui script can be repeatedly edited and tested while the game is running by repeatedly opening and closing the related ui.