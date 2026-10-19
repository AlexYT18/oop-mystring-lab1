param(
    [switch]$Clean
)

. "$PSScriptRoot\..\scripts\common.ps1"

$projectRoot = Split-Path $PSScriptRoot -Parent
$buildDirectory = Join-Path $PSScriptRoot "build"

if ($Clean -and (Test-Path -LiteralPath $buildDirectory))
{
    Remove-Item -LiteralPath $buildDirectory -Recurse -Force
}
New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null

$dll = Join-Path $buildDirectory "MyString.dll"
$library = Join-Path $buildDirectory "MyString.lib"
$executable = Join-Path $buildDirectory "debug_target.exe"

$dllCommand = "cl /nologo /std:c++17 /O2 /MD /LD /EHsc /Zi " +
    "/DMYSTRING_BUILD_DLL /I. MyString.cpp /Fo:additional_task3\build\ " +
    "/link /DEBUG /IMPLIB:additional_task3\build\MyString.lib " +
    "/OUT:additional_task3\build\MyString.dll"

$exeCommand = "cl /nologo /std:c++17 /O2 /MD /EHsc /Zi " +
    "/DMYSTRING_USE_DLL /I. additional_task3\main.cpp " +
    "/Fo:additional_task3\build\ " +
    "/link /DEBUG /LIBPATH:additional_task3\build MyString.lib " +
    "/OUT:additional_task3\build\debug_target.exe"

Push-Location $projectRoot
try
{
    Invoke-VcCommand $dllCommand
    Invoke-VcCommand $exeCommand
}
finally
{
    Pop-Location
}

Write-Host "Built: $dll"
Write-Host "Built: $executable"
