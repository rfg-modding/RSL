
Log
********************************************************
Logs a message to the lua console, logger window, and log files. This is the default logging function and is equivalent to `rsl.LogInfo`_, meaning it has the ``[Info]`` tag. See the `logging examples`_ for more info on how to use it.

**Arguments:**

- ``string`` **format string**: The format string to be passed into the logger.

- ``several types`` **arguments**: ``optional`` Values to be substituted into the format string, as explained in more detail in the `logging examples`_.

**Returns:**

- None

.. _`logging examples`: ../../../Examples/Logging.html
.. _`rsl.LogInfo`: ./LogInfo.html