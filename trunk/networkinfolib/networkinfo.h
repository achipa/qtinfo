#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QList>
#include <QPair>
#include <QString>

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

extern "C" MY_EXPORT QString networkInfoQString();
#ifndef _MSC_VER
extern "C" {
QList<QPair<QString, QString> > networkInfo();
}
#endif

#endif // NETWORKINFO_H
