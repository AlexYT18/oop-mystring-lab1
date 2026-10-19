& "$PSScriptRoot\clean.ps1"
if (-not $?)
{
    exit 1
}

& "$PSScriptRoot\run_all.ps1"
if (-not $?)
{
    exit 1
}
