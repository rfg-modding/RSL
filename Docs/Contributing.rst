Contributing
********************************************************
RSL is closed source primarily to prevent people from creating custom versions which work for MP and cheating with it. Most people should know better than to do so but all it takes is one person to ruin MP for everyone else. This makes contributing to it more complicated. This will change over time, but, the current policy is to selectively give people access to the source if they're a trusted member of the community and have shown they can contribute.

The docs however are a different case. They are completely open, with their source available on the `RSL wiki repo <https://github.com/Moneyl/RFGR-Script-Loader-Wiki>`_. Contributing to them is encouraged and welcome.

Contributing to the docs
========================================================
The following sections will go over the process of creating a github fork, cloning it, editing it, pushing changes back to the fork, and then finally creating a pull request for approval. If you're already familiar with this process then you can skim over most of it. You should still read :ref:`Editing the docs` if you haven't used sphinx before.

What you'll need
--------------------------------------------------------
To contribute to the docs you'll need the following:

- A `github <www.github.com>`_ account, you can register for free or register as student for more benefits if applicable.
- A git client. You can use the console application if you'd like, but it's reccommended that you use a gui client for ease of use. `Github desktop <https://desktop.github.com/>`_ and `Gitkraken <https://www.gitkraken.com/>`_ are both excellent git clients available for free.
- `Python <https://www.python.org/>`_ for building the docs locally. The latest version should be fine.
- `Sphinx <https://www.sphinx-doc.org/en/master/>`_ for generating the docs. If you have python and pip installed you can just run ``pip install -U Sphinx`` on the command line.
- (Optional) `Visual Studio Code <https://code.visualstudio.com/>`_ with the `reStructuredText extension <https://marketplace.visualstudio.com/items?itemName=lextudio.restructuredtext>`_ which will allow you to see a live preview of the page you are editing. This makes editing much smoother instead of needing to regenerate the docs on each edit and open them in your browser.

Preparing the repo
----------------------------------------------------------
The first thing you'll want to do is create a fork of the RSL wiki repo. To do this, you'll want to go `the wiki repo <https://github.com/Moneyl/RFGR-Script-Loader-Wiki>`_ and locate and click the fork button in the top right corner of the page. Github will create a fork of the repo, and now you should be on a new page: ``https://github.com/your_username/RFGR-Script-Loader-Wiki`` This is your own copy of the repo that you'll be editing before moving your changes to the main repo.

Next thing you'll want to do is clone your fork to your desktop. Through github desktop you can do this with File > Clone repository... > URL, and then simply paste the URL for your fork there and select a folder to clone it to. You can also log into your github account through Github Desktop and get a list of all of your repos, including the fork. Once complete you should have a folder with your fork cloned to it. Open that folder for the next step.

Editing the docs
------------------------------------------------------------
At this point you can start making edits to the docs. You'll being editing the rst files in the Docs folder. These files are used by sphinx to generate the docs that you are reading right now. This guide will not go over the syntax of reStructuredText, as there are many existing guides on that. You should check out the `reStructuredText Primer <https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html>`_ and also look at the existing rst files for examples of how it works. This is where the VSCode extension mentioned earlier comes into play as it lets you see the effect of your edits live, which makes learning the syntax much easier.

Once you are done editing you should generate the docs and look for any errors before continuing to the next step. This can be done by running make.bat on the command line. If you shift + right click the docs folder you should see "open a powershell window here". Once the window is open you can run ``.\make.bat`` to see a list of build options. Running ``.\make.bat html`` will build the docs as html files. After running that command you can find the built docs in ``_build/html/index.html``. When you've fixed any mistakes, and you're ready to move your changes to the main repo, continue to the next step.

Pushing your changes and making a pull request
-------------------------------------------------------------
For this next step you should re-open your git client of choice, and push your changes to your fork. For example, if you're using Github Desktop you should see a list of changes on the left side of your screen. Check any changes you wish to push, enter a commit message and description, and click "commit to master". After doing that your should see a blue square in the center of your screen asking if you'd like to push to origin. Do so to push your changes to your fork on github.

For the final step you'll want to make a pull request with your changes. Go back to the github page for your fork, and look for the "New pull request" button under the number of commits. You should now see a list of changes you've made and a green button labeled "Create pull request". After creating your pull request all you must do is wait for it to be accepted into the main repo by a maintainer. Once your pull request is accepted the docs will automatically be rebuilt with your new changes within a few minutes. 

If you are making frequent changes to the docs we can simplify the process by giving you contributor status so you can push directly to the main repo. Just ask the current maintainer about it.