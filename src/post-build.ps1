param($sourcedir, $builddir, $arch)

$ErrorActionPreference = 'Stop'

if (!$sourcedir -or !$builddir -or !$arch) {
    Write-Host "This script must be called with the source and build directories and archetecture:"
    Write-Host "   post-build.ps1 ""C:\ARInside\src"" ""C:\ARInside\src\x64\Release"" x64"
    Exit 1
}

# This will build apires.tgz with all of the JavaScript, CSS and images required for the ARInside pages.
# This requires 7-Zip (https://www.7-zip.org) to be installed. If it's not installed at the
# default path (C:\Program Files\7-Zip), then set an environment variable Path7Zip with the path.

if ($Env:Path7Zip) {
    $Path7Zip = $Env:Path7Zip
} else {
    $Path7Zip = "C:\Program Files\7-Zip"
}

if (!(Test-Path "$Path7Zip\7z.exe")) {
    Write-Host "ERROR: Install 7-Zip ^(https://www.7-zip.org^) so that the resource archive can be created."
	Write-Host "If it is already installed, set the Path7Zip environment variable with the install path."
    Exit 1
}

if (Test-Path "$builddir\arires.tgz") {
    Remove-Item "$builddir\arires.tgz"
}

if (!(Test-Path "$builddir\img")) {
    New-Item "$builddir\img" -ItemType Directory
}

Copy-Item -Path "$sourcedir\res\*" -Destination "$builddir\img" -Force

Copy-Item -Path "$sourcedir\thirdparty\jquery\jquery-ui-custom.css" -Destination "$builddir\img" -Force
Copy-Item -Path "$sourcedir\thirdparty\jquery\jquery-ui.js" -Destination "$builddir\img" -Force
Copy-Item -Path "$sourcedir\thirdparty\jquery\jquery.address.min.js" -Destination "$builddir\img" -Force
Copy-Item -Path "$sourcedir\thirdparty\jquery\jquery.js" -Destination "$builddir\img" -Force
Copy-Item -Path "$sourcedir\thirdparty\jquery\jquery.timers.js" -Destination "$builddir\img" -Force

if (!(Test-Path "$builddir\img\images")) {
    New-Item "$builddir\img\images" -ItemType Directory
}

Copy-Item -Path "$sourcedir\thirdparty\jquery\images\*" -Destination "$builddir\img\images" -Force

& "$Path7Zip\7z.exe" a -ttar "$builddir\arires.tar" "$builddir\img"
& "$Path7Zip\7z.exe" a -tgzip "$builddir\arires.tgz" "$builddir\arires.tar"
Remove-Item "$builddir\arires.tar"
Remove-Item "$builddir\img" -Recurse

# Move the DLLs to the build directory

if ($arch -eq "64") {
    $bin = "bin64"
} else {
    $bin = "bin"
}

Copy-Item -Path "$sourcedir\thirdparty\arapi\$($bin)\*" -Destination "$builddir" -Force
Copy-Item -Path "$sourcedir\thirdparty\zlib\$($bin)\*" -Destination "$builddir" -Force
