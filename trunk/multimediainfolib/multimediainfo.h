#ifndef MULTIMEDIAINFO_H
#define MULTIMEDIAINFO_H

#include <QList>
#include <QPair>
#include <QString>

extern "C" {
QList<QPair<QString, QString> > multimediaInfo();
}
#endif
