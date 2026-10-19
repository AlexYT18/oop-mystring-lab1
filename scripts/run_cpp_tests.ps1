param(
    [switch]$AddressSanitizer
)

. "$PSScriptRoot\common.ps1"

$projectRoot = Split-Path $PSScriptRoot -Parent
& "$PSScriptRoot\build_cpp_tests.ps1" -AddressSanitizer:$AddressSanitizer
if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

$executable = if ($AddressSanitizer) { "mystring_tests_asan.exe" } else { "mystring_tests.exe" }
Push-Location $projectRoot
try
{
    Invoke-VcCommand "build\$executable"
}
finally
{
    Pop-Location
}
