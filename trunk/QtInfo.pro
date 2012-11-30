TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = glinfolib \
          webkitinfolib \
          mobilityinfolib \
          multimediainfolib \
          sqlinfolib \
          qtinfo 

qtinfo.depends = qtquickinfolib glinfolib webkitinfolib mobilityinfolib sqlinfolib multimediainfolib

!contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    SUBDIRS += qtquickinfolib
    qtinfo.depends += qtquickinfolib
    !qnx {
        SUBDIRS += declarativeui 
        qtinfo.depends += declarativeui 
    } else {
        SUBDIRS += cascadesui bb10infolib
        qtinfo.depends += cascadesui bb10infolib
        SUBDIRS += webkitinfolib
        qtinfo.depends += webkitinfolib
    }
}
else  {
symbian: {
    SUBDIRS -= glinfolib
    qtinfo.depends -= glinfolibs
    }
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
