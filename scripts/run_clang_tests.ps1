. "$PSScriptRoot\common.ps1"

$projectRoot = Split-Path $PSScriptRoot -Parent
$buildDirectory = Join-Path $projectRoot "build"
New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null

$responseFile = Join-Path $buildDirectory "clang_tests.rsp"
$arguments = @(
    "-std=c++17",
    '-DIMYSTRING=\"MyString.h\"',
    "-I.",
    "-Ilab_tests/lab1_mystring_test-master",
    "lab_tests/lab1_mystring_test-master/main.cpp",
    "lab_tests/lab1_mystring_test-master/tests/test_logger.cpp",
    "MyString.cpp",
    "-o",
    "build/mystring_clang_tests.exe"
)
[System.IO.File]::WriteAllLines($responseFile, $arguments, [System.Text.Encoding]::ASCII)

Push-Location $projectRoot
try
{
    $clang = Get-ClangPath
    & $clang "@$responseFile"
    if ($LASTEXITCODE -ne 0)
    {
        exit $LASTEXITCODE
    }
    & "$buildDirectory\mystring_clang_tests.exe"
    if ($LASTEXITCODE -ne 0)
    {
        throw "The Clang test executable failed with exit code $LASTEXITCODE."
    }
}
finally
{
    Pop-Location
}
