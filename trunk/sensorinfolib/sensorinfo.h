#ifndef SENSORINFO_H
#define SENSORINFO_H

#include <QList>
#include <QPair>
#include <QString>

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

extern "C" MY_EXPORT QString sensorInfoQString();
#ifndef _MSC_VER
extern "C" MY_EXPORT QList<QPair<QString, QString> > sensorInfo();
#endif

#endif // SENSORINFO_H
