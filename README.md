QtInfo
======

QtInfo has two main goals:

1. Display basic Qt-related information in an easy-to-report-to-developer way. It is *NOT* a hardware-info tool, nor does it try to display information that is not available via Qt APIs

2. Demonstrate how to dynamically detect available functionality to address a fragmented deployment base (optimize for best available featureset instead of lowest common denominator). It's not about having an elegant #WorksForMe, it's about #WhatEverItTakes to run on as many Qt platforms as possible.

Platforms known to run or ran QtInfo in some shape or form (see screenshots below), in reverse order of appearance:  

 - (Windows Phone - Work in progress, waiting for Qt 5.3)
 - Android
 - SailfishOS
 - BlackberryOS 10
 - MeeGo (meego.com MeeGo)
 - MeeGo Harmattan 1.2
 - Symbian^3
 - MacOS X
 - Windows
 - Maemo 5
 - Linux

Qt 4.5 needs to be installed for the application to work. For a declarative UI, Qt 4.7 or better is needed. QtInfo has (preliminary) Qt5 support, but unlike the rest of the libraries, it is not runtime-detected yet (the plan is to have dual binaries eventually).  

Currently displays (all the info is obtained at run-time, not compile-time):  

 - Qt version
 - Mobility version
 - Installed Qt modules
 - Qt build and licensing info
 - Webkit version
 - SSL support
 - QtOpenGL support
 - Qt default paths used
 - Supported image formats
 - OS/Firmware version
 - Country and language as seen from Qt
 - Network (GSM/IP) interfaces and addresses
 - Available sensors
 - Qt Quick version, installed plugins and plugin import paths
 - Installed Qt Components (from packages com.nokia.symbian, qt.labs.components, qt.labs.components.native, etc)
 - Multimedia devices (input/output), supported codecs and containers
 - Installed fonts and respective languages
 - Hardware features available (BT, WiFi, USB, Vibra...)
 - Screen parameters
 - SQL drivers

Channels supported for relaying the info:  
 - Clipboard
 - Pastebin
 - Email
 - File on mass-storage


Screenshots or it didn't happen:  

![Android](/bin/screenshots/qtinfo_android_low.png)
![Sailfish](/bin/screenshots/sailfish-qtinfo.png)
![Blackberry10](/bin/screenshots/IMG_00000020.png)
![Harmattan](/bin/screenshots/harmattan.png)
![Symbian](/bin/screenshots/qtinfo_symbian.png)
![Maemo5](/bin/screenshots/qtinfo_maemo.png)
![Random desktop, circa 1995 AD](/bin/screenshots/qtinfo_snap.png)


