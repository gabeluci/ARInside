@echo off

REM This will build apires.tgz with all of the JavaScript, CSS and images required for the ARInside pages."
REM This requires 7-Zip (https://www.7-zip.org) to be installed. If it's not installed at the
REM default path (C:\Program Files\7-Zip), then set an environment variable Path7Zip with the path.
REM Call this batch file with the path of the source code and the path of the build folder"
REM e.g. CreateResourceArchive.bat "C:\ARInside\src" "C:\ARInside\src\x64\Release"

IF "%Path7Zip%" == "" SET Path7Zip=C:\Program Files\7-Zip

IF NOT EXIST "%Path7Zip%\7z.exe" (
	ECHO ERROR: Install 7-Zip ^(https://www.7-zip.org^) so that the resource archive can be created.
	ECHO        If it is already installed, set the Path7Zip environment variable with the install path.
	EXIT /b 1
)

IF EXIST "%~2\arires.tgz" del "%~2\arires.tgz"

IF NOT EXIST "%~2\img" mkdir "%~2\img"
copy /Y "%~1\res\*" "%~2\img"
copy /Y "%~1\thirdparty\jquery\jquery-ui-custom.css" "%~2\img"
copy /Y "%~1\thirdparty\jquery\jquery-ui.js" "%~2\img"
copy /Y "%~1\thirdparty\jquery\jquery.address.min.js" "%~2\img"
copy /Y "%~1\thirdparty\jquery\jquery.js" "%~2\img"
copy /Y "%~1\thirdparty\jquery\jquery.timers.js" "%~2\img"
IF NOT EXIST "%~2\img\images" mkdir "%~2\img\images"
copy /Y "%~1\thirdparty\jquery\images\*" "%~2\img\images"

"%Path7Zip%\7z.exe" a -ttar "%~2\arires.tar" "%~2\img"
"%Path7Zip%\7z.exe" a -tgzip "%~2\arires.tgz" "%~2\arires.tar"
del "%~2\arires.tar"
