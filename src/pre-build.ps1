param($sourcedir, $builddir)

$ErrorActionPreference = 'Stop'

if (!$sourcedir -or !$builddir) {
    Write-Host "This script must be called with the source and build directories:"
    Write-Host "   pre-build.ps1 ""C:\ARInside\src"" ""C:\ARInside\src\x64\Release"""
    Exit 1
}

((Get-Content -path "$($sourcedir)FileSystemUtilTest.h.in" -Raw) -replace '@CMAKE_CURRENT_BINARY_DIR@', $builddir) | Set-Content -Path "$($sourcedir)FileSystemUtilTest.h"

Set-Location $sourcedir
((Get-Content -path "$($sourcedir)gitrev.h.in" -Raw) -replace '@GIT_REV@', (git rev-parse --short HEAD)) | Set-Content -Path "$($sourcedir)gitrev.h"
