$projectRoot = Split-Path $PSScriptRoot -Parent
$paths = @(
    (Join-Path $projectRoot "build"),
    (Join-Path $projectRoot ".pytest_cache"),
    (Join-Path $projectRoot "lab_tests\lab1_mystring_test-master\wrapper_test\__pycache__")
)

foreach ($path in $paths)
{
    if (Test-Path -LiteralPath $path)
    {
        Remove-Item -LiteralPath $path -Recurse -Force
    }
}

Write-Host "Build artifacts and test caches were removed."
