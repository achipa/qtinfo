#ifndef BB10INFO_H
#define BB10INFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > bb10Info();
}
#endif
