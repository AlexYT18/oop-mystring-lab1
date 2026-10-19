& "$PSScriptRoot\run_cpp_tests.ps1"
if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

& "$PSScriptRoot\run_clang_tests.ps1"
if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

& "$PSScriptRoot\run_cpp_tests.ps1" -AddressSanitizer
if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

& "$PSScriptRoot\run_python_tests.ps1"
exit $LASTEXITCODE
