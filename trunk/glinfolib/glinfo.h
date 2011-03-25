#ifndef GLINFO_H
#define GLINFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > GLInfo();
}
#endif
