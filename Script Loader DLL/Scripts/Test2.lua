--[[
Name: Test2.lua
Author: moneyl
Description: Test script used to ensure that basic script loading and running is functional.
]]

require("os")
time1 = os.clock()
print("time1: ", time1)

time2 = os.clock()
print("time2: ", time2)
print("Time difference: ", time2 - time1, " seconds") 

Logger.Log("Test message", 63, false, false)





