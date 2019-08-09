
Contributing
********************************************************
While the core code of the RSL is written with c++, you'd don't need to be able to write c++ to contribute. There are areas of contribution for all skill levels, such as improving or expanding the documentation or the lua core library.

Basics
========================================================
If you're familiar with git, and know how to fork a repo, push your changes, and make a pull request you can skip or skim over this first section. Otherwise, this section will explain those things and show you the basic process of contributing. The later sections give more details on editing specific parts of the RSL like the docs, the lua core lib, or the c++ core. 

Requirements
---------------------------------------------------------
- A `github <https:\\www.github.com>`_ account (they're free!). You can also get free benefits if you're a student via the `github student pack <https://education.github.com/pack>`_.
- A git client. Any can be used, but `Gitkraken <https://www.gitkraken.com/>`_ will be used in the examples shown in this guide.

Forking
--------------------------------------------------------
Once you've fulfilled the requirements, you can head over to the `RSL github repo <https://github.com/rsl-dev/RSL>`_, where we'll start. The first thing you'll want to do is click the ``Fork`` button in the top right corner of the repo. After pressing the button you'll be brought to your fork of the RSL repo. A fork is a copy created of the original repo at the time you forked it. This is where you'll apply your changes to the code before getting them added to the main codebase. 

Cloning
--------------------------------------------------------
The next thing you'll want to do is clone your fork to your desktop. If you log into gitkraken with your github account, this is quite easy to do. You go to ``File > Clone Repo > GitHub.com`` and then select your fork of RSL and choose the local folder is should be stored in. Gitkraken will clone the repo to your PC for you. This is also explained `here <https://support.gitkraken.com/working-with-repositories/open-clone-init/#cloning-an-existing-project>`_ in the GitKraken docs.

Pushing changes
-------------------------------------------------------
It's at this point that you would make your changes to the codebase. More details on how to make changes and other tools required for that are explained in the later sections of this page, but for now we'll explain how to push your changes back to github. First thing you should do is stage and commit any changes you've made through Gitkraken, and write a brief description of what the commit does. After clicking ``Stage files/changes to commit`` the changes are still local to your PC. To send your changes to GitHub, click the ``Push`` button at the top of the GitKraken window.

Making a pull request
-------------------------------------------------------
Finally, you'll want to create a pull request to request that your changes get applied to the main RSL repo. If you go to your fork after pushing your changes, Github should automatically show a button asking if you'd like to make a new pull request. Click that button, select your changes, and type a description and name for your pull request explaining what it does and any issues it might resolve. If you don't see the button, you can also go to the `RSL PR page <https://github.com/rsl-dev/RSL/pulls>`_, and select ``New pull request``. From here, the RSL code reviewer(s) might request edits to your changes, or if they have no change requests, merge your PR into the main repo. Once a PR is merged, it will automatically be built by appveyor with 30min, `here. <https://ci.appveyor.com/project/Moneyl/rsl/history>`_



Contributing to the docs
========================================================
This section explains how to edit the docs and contribute changes to them. 

Docs requirements
-------------------------------------------------------
- `Python <https://www.python.org/>`_ for building the docs locally. The latest version should be fine.
- `Sphinx <https://www.sphinx-doc.org/en/master/>`_ for generating the docs. If you have python and pip installed you can just run ``pip install -U Sphinx`` on the command line.
- (Optional) `Visual Studio Code <https://code.visualstudio.com/>`_ with the `reStructuredText extension <https://marketplace.visualstudio.com/items?itemName=lextudio.restructuredtext>`_ which will allow you to see a live preview of the page you are editing. This makes editing much smoother instead of needing to regenerate the docs on each edit and open them in your browser.


Editing the docs
------------------------------------------------------
Once you've installed Python and Sphinx you can start making edits to the docs. You'll being editing the rst files in the Docs folder. These files are used by sphinx to generate the docs that you are reading right now. This guide will not go over the syntax of reStructuredText, as there are many existing guides on that. You should check out the `reStructuredText Primer <https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html>`_ and also look at the existing rst files for examples of how it works. This is where the VSCode extension mentioned earlier comes into play as it lets you see the effect of your edits live, which makes learning the syntax much easier.

Once you are done editing you should generate the docs locally and look for any errors before pushing your changes. This can be done by running make.bat on the command line. If you shift + right click the docs folder you should see "open a powershell window here". Once the window is open you can run ``.\make.bat`` to see a list of build options. Running ``.\make.bat html`` will build the docs as html files. After running that command you can find the built docs in ``_build/html/index.html``. When you've fixed any mistakes, and you're ready to move your changes to the main repo, continue to the next step.

Contributing to the Lua Core library
========================================================
The lua core library is a set of lua scripts that are run during RSL startup. Any functions or values provided by the lua core lib are available to all other lua scripts run by the RSL. Currently the core lib is quite barebones, only containing some useful enums such as ``rfg.ObjectTypes``, but there's much opportunity for expansion. Good candidates for addition to the lua core lib are helper functions which people are repeatedly writing themselves in scripts anyways, or wrappers around certain behavior, like for example, providing preset, named teleport locations. Once the overlay guis are bound to lua, some of them will likely be moved into the core lua lib where possible, as more people will be able to edit them in lua form than in c++ form.

Editing the Lua core lib does not require any special tools. Just a text editor. Visual studio code is an excellent free text editor that is good for this, and offers many expansions which can enhance your editing experience. You can test your edits while the game is running. Simply edit the core lib files in your installation of the RSL and then in the overlay menu (opened with F1), select ``System > Reset core lua state``. This will stop all currently running lua scripts, reload the core lib, and reload autorun scripts, as if you were running the scripts for the first time in this game session. 

Contributing the to C++ Core
========================================================
The c++ portion of the RSL is what provides all the primary functionality of the RSL such as the overlay system and scripting system. It manipulates rfg by hooking it's game functions to change or track their inputs, and locating different data structures in the games memory to modify them or provide lua scripts access to them. This part of the codebase is by far the most complex, and will have to be explained more in other guides. This section will give a basic rundown of how to compile the code yourself and edit it.

Editing the c++ side of RSL requires a copy of `Visual Studio 2019 <https://visualstudio.microsoft.com/vs/>`_ with the following features enabled:

- Workloads:
    - Desktop development with C++
- Individual components:
    - VC++ 2019 v142 toolset (x86, x64)
    - Windows 10 SDK for Desktop C++ (x86 and x64, any/latest version)

To compile the project, open RSL.sln with visual studio 2019, and once open select ``Build > Build solution``. Depending on if you selected to build it as Debug or Release, it the resulting rsl.dll, injector.exe, and dinput8.dll, will be in either the ``Releases`` or ``Debug`` folder of the local repo. You can then copy these files over to your RSL install and run the game as normal to see your changes in action. Usually you'll only have to copy over RSL.dll as it's where most of the code is. 

.. note:: Debug builds have a much larger final dll since they include debug information, but also build much more quickly as they have minimum amounts of optimisation. You should generally use debug builds for development since using the debugger will show you more information with them. Release builds are good for sharing with others to test since they are small enough to share on discord.

This is only a very basic guide to the c++ codebase of the RSL, and how it works. Please see the additional guides linked below for more information on important concepts such as function hooking, rfg function calls, and lua binding.

.. note:: These other c++ related guides have not yet been written, and should be up over the course of the next few days. The docs are very much still a work in progress.

