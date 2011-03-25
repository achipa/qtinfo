#include "qtquickinfo.h"
#include <QtDeclarative>
#include <QStringList>

QList<QPair<QString, QString> > qtQuickInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "Qt Quick"));

    QDeclarativeEngine engine;
    QStringList importPaths = engine.importPathList();
    QString list;
    foreach(QString path, importPaths)
    {
        list.append(path + " ");
    }

    info.append(QPair<QString,QString>("Qt Quick version", "1.0"));
    info.append(QPair<QString,QString>("Qt Quick import path", list));

    return info;
}
