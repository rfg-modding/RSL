mkdir ".\Red Faction Guerrilla Re-mars-tered"
mkdir ".\Red Faction Guerrilla Re-mars-tered\RSL"

Copy-Item ".\Release\dinput8.dll" ".\Red Faction Guerrilla Re-mars-tered"
Copy-Item ".\Release\RSL.dll" ".\Red Faction Guerrilla Re-mars-tered\RSL"
Copy-Item ".\Core" ".\Red Faction Guerrilla Re-mars-tered\RSL\Core" -Recurse
Copy-Item ".\Content\*" ".\Red Faction Guerrilla Re-mars-tered\RSL\" -Recurse

Copy-Item ".\LICENSE" ".\Red Faction Guerrilla Re-mars-tered\RSL"
Copy-Item ".\readme.md" ".\Red Faction Guerrilla Re-mars-tered\RSL"

cmd /c 7z a "$env:APPVEYOR_BUILD_VERSION.zip" ".\Red Faction Guerrilla Re-mars-tered"

Push-AppveyorArtifact "$env:APPVEYOR_BUILD_VERSION.zip"