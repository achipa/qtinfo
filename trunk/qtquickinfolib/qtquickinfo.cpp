#include "qtquickinfo.h"
#include <QtDeclarative>
#include <QStringList>

QMap<QString, QString> getInfo()
{
    QMap<QString, QString> map;
    map.insert("section", "QtQuick");

    QDeclarativeEngine engine;
    QStringList importPaths = engine.importPathList();
    QString list;
    foreach(QString path, importPaths)
    {
        list.append(path + " ");
    }
    map.insert("Import paths", list);

    return map;
}
