$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

function Get-VsInstallationPath
{
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path -LiteralPath $vswhere))
    {
        throw "vswhere.exe was not found. Install the Visual Studio C++ workload."
    }

    $installationPath = & $vswhere -latest -products * `
        -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        -property installationPath
    if ($LASTEXITCODE -ne 0 -or [string]::IsNullOrWhiteSpace($installationPath))
    {
        throw "Visual Studio with the x64 C++ tools was not found."
    }

    return $installationPath.Trim()
}

function Get-VcVarsPath
{
    $vcvars = Join-Path (Get-VsInstallationPath) "VC\Auxiliary\Build\vcvars64.bat"
    if (-not (Test-Path -LiteralPath $vcvars))
    {
        throw "vcvars64.bat was not found at $vcvars"
    }
    return $vcvars
}

function Get-ClangPath
{
    $clang = Join-Path (Get-VsInstallationPath) "VC\Tools\Llvm\x64\bin\clang++.exe"
    if (-not (Test-Path -LiteralPath $clang))
    {
        throw "clang++.exe was not found at $clang"
    }
    return $clang
}

function Invoke-VcCommand([string]$Command)
{
    $vcvars = Get-VcVarsPath
    $fullCommand = "call `"$vcvars`" >nul && $Command"
    & cmd.exe /d /c $fullCommand
    if ($LASTEXITCODE -ne 0)
    {
        throw "The Visual C++ command failed with exit code $LASTEXITCODE."
    }
}
