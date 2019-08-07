mkdir "./Red Faction Guerrilla Re-mars-tered"
mkdir "./Red Faction Guerrilla Re-mars-tered/RSL"

Copy-Item ".\Release\dinput8.dll" -Destination ".\Red Faction Guerrilla Re-mars-tered"
Copy-Item ".\Release\Injector.exe" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL"
Copy-Item ".\Release\RSL.dll" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL"
Copy-Item ".\Core" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL\Core" -Recurse
Copy-Item ".\Scripts" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL\Scripts" -Recurse
Copy-Item ".\Fonts" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL\Fonts" -Recurse

Copy-Item ".\LICENSE" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL"
Copy-Item ".\readme.md" -Destination ".\Red Faction Guerrilla Re-mars-tered\RSL"

cmd /c 7z a "$env:APPVEYOR_BUILD_VERSION.zip" ".\Red Faction Guerrilla Re-mars-tered"

cmd /c dir

$build_version = $env:APPVEYOR_BUILD_VERSION
$zip_name = "$build_version.zip"

Write-Host $build_version
Write-Host $zip_name

Push-AppveyorArtifact $zip_name