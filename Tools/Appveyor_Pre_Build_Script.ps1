
$rsl_version_string = "$env:APPVEYOR_BUILD_VERSION-latest"
Set-Content -Path '.\RSL\Version.h' -Value "#pragma once`n`nconstexpr auto RSL_VERSION = `"$rsl_version_string`";"