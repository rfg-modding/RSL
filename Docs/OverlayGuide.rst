Overlay Guide
********************************************************

This guide will provide you with the basic info you'll need to use the RSL and it's different GUIs and controls. This guide assumes that you've already followed the installation guide and have it working. 

Keyboard Shortcuts
========================================================

- ``F1`` - Toggle RSL overlay
- ``F2`` - Toggle script editor
- ``Hold F3`` - Deactivate RSL
- ``F4`` - Toggle lua console
- ``F5`` - Run current script editor script
- ``Numpad 1`` - Toggle game hud
- ``Numpad 2`` - Toggle fog
- ``Numpad 3`` - Toggle free cam
- ``Numpad 4`` - Lock object in crossharis to introspection menu
- ``Numpad 5`` - Ragdoll player

Menus
========================================================

When opening the overlay for the first time you'll see the Welcome menu which includes buttons for several often used menus, and a list of keyboard shortcuts. These menus and others not listed there can be opened through the menu bar at the top of the screen. Below is a short list of each menu and what they do, sorted by their menu bar category.


System
---------------------------------------------------------

Deactivate script loader
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Deactivates the script loader and any running scripts. Can also be accomplished by holding F3. Main use is to re-inject the script loader to attempt to fix a bug.

Reset core lua state
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Disables all scripts and fully resets the script loader lua state. This means that any scripts, event, variables, etc, will be completely reset as if the script loader was just started. Also reloads the core library in the Core folder.


Tweaks
---------------------------------------------------------

General Tweaks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Contains a large amount of useful tweaks for the player such as invincibility, infinite jetpack, ignored by ai, no ragdoll, custom move speed, custom jump height, custom explosion spawning, and more. 

Teleport
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Has a preset list of teleport locations and lets you create your own to teleport the player anywhere on the map. Preset locations include places like  the tutorial area, each safehouse, and mount vogel.

Logger
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Lists logging system output. Has options to filter by message type. This is the same output that can be found in the script loader Logs folder.

Theme editor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Lets you customize and save the script loader overlay color scheme and style. Saved to Settings/GUI Config.json. You can share this with anyone and have them put it in their settings folder so they can use you custom theme.

Camera settings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Includes settings for the free cam, experimental first person cam, and other camera settings like the far clip distance which is the distance at which nothing is rendered past.

Physics settings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Has general settings like gravity, frametime multiplier (pseudo slo-mo at values less than 1.0), and settings for the physics solver.


Scripting
-----------------------------------------------------------

Scripts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
A list of scripts detected in the script loader scripts folder. Allows you to individually run or edit each of the scripts listed.

Lua console
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Directly executes an input as a lua script. You can call lua functions and set lua variables here. So, for example, you might set the far clip distance to 1200 with ``rfg.SetFarClipDistance(1200)``. You can also add new functions to be called in the console by calling a script with a non local function declaration.

Script editor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Built in script editor. Has all the common text editor shortcuts like copy, paste, select all, etc. This is mainly intended for quick edits. I recommend that you use an external editor like VSCode for larger scripts to take advantage of better syntax highlighting and error checking. Eventually people could also write there own extensions for external editors that highlight RSL specific lua functions and types. See the starbound lua VSCode extension as an example of this.


Help
----------------------------------------------------------

Welcome
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The welcome menu that shows up each time the script loader overlay is opened. Has buttons for commonly used menus and a shortcuts list.

Metrics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Lists some debug metrics about the RSL overlay. 

About
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Lists info about the current RSL version and info about some of the libraries (such as Dear ImGUi) used by RSL.