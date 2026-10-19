. "$PSScriptRoot\common.ps1"

$projectRoot = Split-Path $PSScriptRoot -Parent
$buildDirectory = Join-Path $projectRoot "build"
New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null

$pythonRoot = (& py -c "import sys; print(sys.base_prefix)").Trim()
$pythonInclude = (& py -c "import sysconfig; print(sysconfig.get_path('include'))").Trim()
$pybindInclude = (& py -c "import pybind11; print(pybind11.get_include())").Trim()
$extensionSuffix = (& py -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))").Trim()
if ($LASTEXITCODE -ne 0 -or [string]::IsNullOrWhiteSpace($extensionSuffix))
{
    throw "Python, pybind11, or the extension suffix could not be detected."
}

$outputFile = "build\mystring$extensionSuffix"
$command = "cl /nologo /std:c++17 /EHsc /LD MyString.cpp MyString_wrapper.cpp " +
    "/I`"$pythonInclude`" /I`"$pybindInclude`" /Fo:build\ " +
    "/link /LIBPATH:`"$pythonRoot\libs`" /IMPLIB:build\MyString.lib /OUT:$outputFile"

Push-Location $projectRoot
try
{
    Invoke-VcCommand $command
}
finally
{
    Pop-Location
}

Write-Host "Built: $buildDirectory\mystring$extensionSuffix"
