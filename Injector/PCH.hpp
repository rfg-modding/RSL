#pragma once

#pragma warning(push, 0) //Disable warnings on included files since I can't / won't modify them.
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <ctype.h>
#include <tlhelp32.h>
#include <math.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include <filesystem>
#include <experimental/filesystem>

#include <nlohmann/json.hpp>
#pragma warning(pop)