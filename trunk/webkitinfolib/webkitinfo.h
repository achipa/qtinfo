#ifndef WEBKITINFO_H
#define WEBKITINFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > webkitInfo();
}
#endif
