$projectRoot = Split-Path $PSScriptRoot -Parent
& "$PSScriptRoot\build_python_module.ps1"
if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

$env:PYTHONPATH = Join-Path $projectRoot "build"
& py -m pytest "$projectRoot\lab_tests\lab1_mystring_test-master\wrapper_test" -v
exit $LASTEXITCODE
