#ifndef SQLINFO_H
#define SQLINFO_H

#include <QList>
#include <QPair>
#include <QString>

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

extern "C" MY_EXPORT QString sqlInfoQString();
#ifndef _MSC_VER
extern "C" MY_EXPORT QList<QPair<QString, QString> > sqlInfo();
#endif

#endif // SQLINFO_H
