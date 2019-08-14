
Set-Content -Path '.\RSL\Version.h' -Value "#pragma once`n`nconstexpr auto RSL_VERSION = `"$env:RSL_VERSION`";"
Get-Content '.\RSL\Version.h'