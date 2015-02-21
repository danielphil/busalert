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