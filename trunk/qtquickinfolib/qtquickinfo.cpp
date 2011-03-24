#include "qtquickinfo.h"
#include <QtDeclarative>
#include <QStringList>

QString getInfo()
{
    QDeclarativeEngine engine;
    QStringList importPaths = engine.importPathList();
    QString list;
    foreach(QString path, importPaths)
    {
        list.append(path + " ");
    }

    return list;
}
