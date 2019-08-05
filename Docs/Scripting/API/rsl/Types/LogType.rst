
LogType
********************************************************
Used by logger to categorize each message logged. Also used to determine which log files the message will be printed to. For example, a message with ``LogType.All`` will show up in all logs, while one with ``LogType.Info`` will only show up in logs with that flag set with their filtering settings.

============================= =====================================
Value                         Resulting Log Tag            
============================= =====================================
**None**                      No tag
**Info**                      ``[Info]`` 
**Warning**                   ``[Warning]``
**Error**                     ``[Error]``     
**Fatal Error**               ``[Fatal Error]``    
**Lua**                       ``[Lua]``      
**Json**                      ``[Json]``             
**All**                       No tag             
============================= =====================================