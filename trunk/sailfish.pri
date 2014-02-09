contains(QT_MAJOR_VERSION,5): {
    packagesExist(sailfishapp) {
        target.path = /usr/share/harbour-qtinfo/bin
        DEFINES += Q_OS_SAILFISH TARGETPATH='\\"/usr/share/harbour-qtinfo/bin/\\"'
        SAILFISH = 1
    }
}

