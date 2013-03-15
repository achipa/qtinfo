#ifndef QTQUICK2INFO_H
#define QTQUICK2INFO_H

#include <QList>
#include <QPair>
#include <QString>

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

extern "C" MY_EXPORT QString qtQuick2InfoQString();
#ifndef _MSC_VER
extern "C" {
QList<QPair<QString, QString> > qtQuick2Info();
}
#endif

#endif // QTQUICK2INFO_H
