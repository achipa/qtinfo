TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = qtquickinfolib \
          qtinfo

qtinfo.depends = qtquickinfolib

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog


maemo5 {
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}
