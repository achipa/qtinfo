TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = qtquickinfolib \
          glinfolib \
          webkitinfolib \
          mobilityinfolib \
          multimediainfolib \
          sqlinfolib \
          qtinfo 

qtinfo.depends = qtquickinfolib glinfolib webkitinfolib mobilityinfolib multimediainfolib sqlinfolib

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    qtc_packaging/meego.spec

maemo5 {
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}
