#!/bin/sh
mkdir build
cd build
qmake "CONFIG+=release" ../main.pro
make
mv busalert/busalert.app/Contents/MacOS/busalert "busalert/busalert.app/Contents/MacOS/Edinburgh Buses"
mv busalert/busalert.app "busalert/Edinburgh Buses.app"
cd busalert
macdeployqt "Edinburgh Buses.app" -dmg

mv "Edinburgh Buses.dmg" EdinburghBuses.dmg