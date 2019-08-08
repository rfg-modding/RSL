
Write-Host $env:BuildID
Write-Host $env:Build.BuildID

Set-Content -Path '.\RSL\Version.h' -Value "#pragma once`n`nconstexpr auto RSL_VERSION = `"$env:Build.BuildID`";"
Get-Content '.\RSL\Version.h'