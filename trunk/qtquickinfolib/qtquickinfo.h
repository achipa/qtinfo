#ifndef QTQUICKINFO_H
#define QTQUICKINFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > qtQuickInfo();
}
#endif
