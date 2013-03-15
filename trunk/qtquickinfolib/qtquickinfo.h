#ifndef QTQUICKINFO_H
#define QTQUICKINFO_H

#include <QList>
#include <QPair>
#include <QString>

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

extern "C" MY_EXPORT QString qtQuickInfoQString();
#ifndef _MSC_VER
extern "C" {
QList<QPair<QString, QString> > qtQuickInfo();
}
#endif

#endif // QTQUICKINFO_H
