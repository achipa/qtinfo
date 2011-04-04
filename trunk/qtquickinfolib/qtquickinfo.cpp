#include "qtquickinfo.h"
#include <QtDeclarative>
#include <QStringList>
#include <QDebug>

QString qtQuickVersion()
{
    QDeclarativeView view;
    view.setSource(QUrl("qrc:///qml/qtquick20.qml"));
    if (view.status() == QDeclarativeView::Ready) return "2.0";
    view.setSource(QUrl("qrc:///qml/qtquick11.qml"));
    if (view.status() == QDeclarativeView::Ready) return "1.1";
    view.setSource(QUrl("qrc:///qml/qtquick10.qml"));
    if (view.status() == QDeclarativeView::Ready) return "1.0";
    view.setSource(QUrl("qrc:///qml/qt47.qml"));
    if (view.status() == QDeclarativeView::Ready) return "1.0 (import Qt 4.7)";

    return "Could not determine Qt Quick version";
}

void searchPlugin(QString path, QString plugin, QStringList& pluginList)
{
    QDir directory(path);
    QStringList dirs = directory.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    if (directory.exists("qmldir"))
    {
        // This directory contains file qmldir, so it's probably
        // a plugin
        pluginList.append(plugin);
    }

    // Go through all subdirs
    foreach(QString entry, dirs)
    {
        QString prefix = plugin == "" ? "" : ".";
        searchPlugin(path+"/"+entry, plugin+prefix+entry, pluginList);
    }
}

QString qtQuickPlugins()
{
    QDeclarativeEngine engine;
    QStringList importPaths = engine.importPathList();
    QStringList plugins;

    foreach(QString path, importPaths)
    {
        searchPlugin(path,"",plugins);
    }

    QString pluginList;
    foreach(QString plugin, plugins)
    {
        pluginList += plugin + "<br>";
    }

    return pluginList;
}

QList<QPair<QString, QString> > qtQuickInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "Qt Quick"));

    info.append(QPair<QString,QString>("Qt Quick version", qtQuickVersion()));
    info.append(QPair<QString,QString>("Qt Quick plugins", qtQuickPlugins()));

    QDeclarativeEngine engine;
    QStringList importPaths = engine.importPathList();
    QString list;
    foreach(QString path, importPaths)
    {
        list.append(path + "<br>");
    }

    info.append(QPair<QString,QString>("Qt Quick import path", list));

    return info;
}


