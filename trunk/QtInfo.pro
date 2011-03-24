TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = qtquickinfolib \
          qtinfo

qtinfo.depends = qtquickinfolib
