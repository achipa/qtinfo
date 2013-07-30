QtInfo
======

Display basic Qt-related information in an easy-to-report-to-developer way. It is *NOT* a hardware-info tool, nor does it try to display information that is not available via Qt APIs

Platforms known to run QtInfo in some shape or form (see screenshots below), in reverse order of appearance:  

 - SailfishOS
 - BlackberryOS 10
 - MeeGo (meego.com MeeGo)
 - MeeGo Harmattan 1.2
 - Symbian^3
 - MacOS X
 - Windows
 - Maemo
 - Linux

	Qt 4.5 needs to be installed for the application to work. For a declarative UI, Qt 4.7 or better is needed. QtInfo has preliminary Qt5 support, but unlike the rest of the libraries, it is not runtime-detected yet (the plan is to have dual binaries eventually).  

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


