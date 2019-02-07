# RFGR Script Loader Wiki
  RFGR Script Loader is a scripting interface for Red Faction Guerrilla Re-mars-tered edition. Using LuaJIT 2.0.5 as the scripting language. This repo is used to provide public information about the project while keeping the source private. 

### Project goals
  Normally, modding RFGR involves editing xml files included in the game which define things such as AI behavior, the properties of vehicles, weapons, and more. This allows modders to change the game in many ways. Even so, there are many hardcoded values and behaviors that cannot be changed, ultimately limited what modders can do. This tool aims to bypass some of these limitations by allowing modders to change many hardcoded values and giving them access to the power and flexibility which a scripting languages allow for.

  Before this is possible an interface between the game's structures and the scripts must be created. As of now the project is still very early on and few things are accesible by the scripts. The scripting interface will need to be expanded, and ways to easily control the scripts must be added. Another goal would be to provide debugging tools and GUIs in game, allowing modders to view the state of the game world as it changes and to understand the effects that their scripts are having on that world.

See the [wiki](https://github.com/Moneyl/RFGR-Script-Loader-Wiki/wiki) for info on how to install and use the script loader.

### Bugs, features, questions, etc
See the [issues](https://github.com/Moneyl/RFGR-Script-Loader-Wiki/issues) section and search for an issue which already describes your bug/feature/question. If you can't find it, create a new one.

### Future updates
See the [roadmap](https://github.com/Moneyl/RFGR-Script-Loader-Wiki/wiki/Roadmap) on the wiki for a rough plan of future updates, and the [milestones](https://github.com/Moneyl/RFGR-Script-Loader-Wiki/milestones) page for progress on upcoming updates. The milestones are a decent indicator of how close the next update is to release, but keep in mind that some features coming to an update might not have an accompanying issue, or new bugs might be encountered. 

### Gallery
![alt text](https://github.com/Moneyl/RFGR-Script-Loader-Wiki/blob/master/Images/0.02%20Main%20Overlay.jpg?raw=true "Main overlay example from 0.02")
Main overlay from version 0.02. Visible here are the infinite jetpack and invulnerability options. The global explosion strength options, the teleport menu, and finally the prototype player values section.

### Why is this closed source?
  One of my primary concerns with this project being open source is that people will use it to cheat in the MP mode of the game. While the MP mode isn't as active as it used to be, I'd still hate for it to be ruined for everyone. There are many checks which will crash the game if the player enters MP mode while the script loader is active. If the source was public then it would be trivial to remove those checks from the code and use it as a cheating tool.
  
### Libraries used
[Dear ImGui](https://github.com/ocornut/imgui) - Used for the in game overlay GUIs.

[Sol 3](https://github.com/ThePhD/sol2/tree/sol3) - Used for quick and easy lua binding. Currently a branch of Sol2.
