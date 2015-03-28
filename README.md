# busalert
Simple Qt application for viewing Edinburgh bus arrivals

## Building

Before building, you'll need to copy `busalert/busalert/ApiKeyEXAMPLE.h` to `busalert/busalert/ApiKey.h` and edit `MyBusTrackerKey` to match the API key obtained from MyBusTracker. API keys can be obtained from http://www.mybustracker.co.uk/?page=API%20Key.

### Mac OS X

The Mac version was built with:
* Qt 5.3.0 clang 64bit
* Clang
* Mac OS X 10.7

### Windows

The Windows version was built with:
* Qt 5.4.0 32bit
* Visual Studio 2013 Update 4
* Windows 7 32 bit
* Inno Setup 5.5.5 Unicode with Inno Setup Preprocessor

To build:
 1. Make sure that the Inno Setup compiler (`iscc`) is installed and in your path.
 2. Open the Qt Command Prompt (MSVC 2013) from the Start menu.
 3. Run `vcvarsall.bat` in the command prompt. On my system, this is located in `C:\Program Files\Microsoft Visual Studio 12.0\VC\vcvarsall.bat`.
 4. cd back to your clone of `busalert` and run `winbuild.bat`.
 5. If everything goes well, you should end up with `setup.exe` in `build\Installer`.
