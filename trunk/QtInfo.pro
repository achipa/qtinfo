TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = glinfolib \
          webkitinfolib \
          mobilityinfolib \
          multimediainfolib \
          sqlinfolib \
          qtquickinfolib \
          declarativeui \
          qtinfo 

qtinfo.depends = qtquickinfolib glinfolib webkitinfolib mobilityinfolib sqlinfolib multimediainfolib qtquickinfolib declarativeui

# Qt prior to 4.7 has no declarative module
contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    SUBDIRS -= qtquickinfolib declarativeui
    qtinfo.depends -= qtquickinfolib declarativeui
}

# Symbian doesn't do the GL module
symbian: {
    SUBDIRS -= glinfolib
    qtinfo.depends -= glinfolibs
}

# BB10 uses cascades, has no webkit, gl or the sysinfo from mobility libs
qnx {
    SUBDIRS += cascadesui bb10infolib
    qtinfo.depends += cascadesui bb10infolib
    SUBDIRS -= webkitinfolib
#glinfolib
    qtinfo.depends -= webkitinfolib
#glinfolib
}

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    qtc_packaging/meego.spec \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

unix:!symbian { # not funny
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}

symbian:OTHER_FILES += magic.pkg
