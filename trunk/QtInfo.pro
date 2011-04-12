TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = qtquickinfolib \
          glinfolib \
          webkitinfolib \
          mobilityinfolib \
          multimediainfolib \
          sqlinfolib \
          declarativeui \
          qtinfo 

qtinfo.depends = qtquickinfolib glinfolib webkitinfolib mobilityinfolib sqlinfolib multimediainfolib declarativeui

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
