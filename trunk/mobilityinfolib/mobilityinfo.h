#ifndef MOBILITYINFO_H
#define MOBILITYINFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > mobilityInfo();
}
#endif
