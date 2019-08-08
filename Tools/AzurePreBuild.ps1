
cmd /c dir

Set-Content -Path '.\RSL\Version.h' -Value "#pragma once`n`nconstexpr auto RSL_VERSION = `"$env:APPVEYOR_BUILD_VERSION`";"
Get-Content '.\RSL\Version.h'