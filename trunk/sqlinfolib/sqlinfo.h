#ifndef SQLINFO_H
#define SQLINFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > sqlInfo();
}
#endif
