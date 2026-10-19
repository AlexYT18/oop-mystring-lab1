param(
    [switch]$AddressSanitizer
)

. "$PSScriptRoot\common.ps1"

$projectRoot = Split-Path $PSScriptRoot -Parent
$buildDirectory = Join-Path $projectRoot "build"
New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null

$executable = if ($AddressSanitizer) { "mystring_tests_asan.exe" } else { "mystring_tests.exe" }
$compilerFlags = "/nologo /std:c++17 /EHsc /Zi /W4 /permissive-"
$linkerFlags = "/link /DEBUG"
if ($AddressSanitizer)
{
    $compilerFlags += " /fsanitize=address"
}

$macroDefinition = '/DIMYSTRING=\"MyString.h\"'
$command = "cl $compilerFlags $macroDefinition /I. " +
    "/Ilab_tests\lab1_mystring_test-master " +
    "lab_tests\lab1_mystring_test-master\main.cpp " +
    "lab_tests\lab1_mystring_test-master\tests\test_logger.cpp " +
    "MyString.cpp /Fo:build\ /Fd:build\mystring_tests.pdb " +
    "/Fe:build\$executable $linkerFlags"

Push-Location $projectRoot
try
{
    Invoke-VcCommand $command
}
finally
{
    Pop-Location
}

Write-Host "Built: $buildDirectory\$executable"
