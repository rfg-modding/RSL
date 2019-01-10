# RFGR-Script-Loader
RFGR Script Loader is a scripting interface for Red Faction Guerrilla Re-mars-tered edition. Using LuaJIT 2.0.5 as the scripting language. 

Normally, modding RFGR involves editing xtbl files which are just xml's with a different extension. The problem with this method is that
there are many hardcoded values in the xtbl files meaning modders are limited on what they can change. Also the fact that these files do 
not allow anything dynamic behavior or logic lessens what they can do. This tool aims to bypass those limitations by allowing modders to 
run lua scripts in the game which will be able to access many of the games structures and functions which previously were inaccesible. With this, hardcoded values may be changed, and the flexibility and power of scripting may be used for modding.

Of course, first an interface between the games structures and the scripts must be created. As of now (January 10th, 2019) the project is 
still very early on and very few things are accesible to them. The interface will need to be expanded, and ways to easily control the 
scripts must be added.

Another roadblock facing modders of RFGR is the fact that many of the games file formats do not have tools that allow for modders to change and replace them. It is not an immediate goal of this project to provide ways of modifying these other file formats, however, it is feasible that through hooking of the functions which handle these assets, and memory edits that live replacement and change of them might be possible. While it's not a primary goal, this may still be explored at some point.
