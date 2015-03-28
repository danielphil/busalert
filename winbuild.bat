@echo off

echo Creating build directory...
mkdir build
cd build || goto :error

echo Creating makefile...
qmake "CONFIG+=release" ../main.pro || goto :error

echo Compiling...
nmake || goto :error

echo Building output directory...
mkdir output
copy busalert\release\busalert.exe output\ || goto :error
cd output || goto :error

echo Fetching Qt dependencies
windeployqt busalert.exe || goto :error

echo Building installer
cd ..\.. || goto :error
iscc win_installer.iss || goto :error

echo Build completed!

goto :EOF

:error
echo Failed with error #%errorlevel%.
exit /b %errorlevel%