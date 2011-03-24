#ifndef QTQUICKINFO_H
#define QTQUICKINFO_H

#include <QMap>

extern "C" {
QMap<QString, QString> getInfo();
}
#endif
