#include "qtquickinfo.h"
#include <QtDeclarative>
#include <QStringList>
#include <QDebug>

QString qtQuickVersion()
{
#ifdef Q_OS_BLACKBERRY
    return "Could not determine Qt Quick version";
#endif
    QDeclarativeView view;
    view.setSource(QUrl("qrc:///qml/qtquick20.qml"));
    if (view.status() == QDeclarativeView::Ready && view.errors().length() == 0) return "2.0";
    view.setSource(QUrl("qrc:///qml/qtquick11.qml"));
    if (view.status() == QDeclarativeView::Ready && view.errors().length() == 0) return "1.1";
    view.setSource(QUrl("qrc:///qml/qtquick10.qml"));
    if (view.status() == QDeclarativeView::Ready && view.errors().length() == 0) return "1.0";
    view.setSource(QUrl("qrc:///qml/qt47.qml"));
    if (view.status() == QDeclarativeView::Ready && view.errors().length() == 0) return "1.0 (import Qt 4.7)";

    return "Could not determine Qt Quick version";
}

// Parses a qmldir file, outputs the components defined in qmldir to result.
void parseQmldir(QString& fileName, QStringList& result)
{
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            QStringList items = line.split(' ');

            if (items.length() > 1)
            {
                // qmldir has a line "plugin dllname", ignore that
                if (items.at(0) != "plugin")
                {
                    // Append component name + version
                    QString component = "&nbsp;&nbsp;&nbsp;&nbsp;";
                    component += items.at(0) + " " + items.at(1);
                    result.append(component);
                }
            }

            line = in.readLine();
        }

        file.close();
    }
}

// Searches for QML plugins in a directory + all its subdirectories
// Outputs plugin import names "e.g. com.nokia.symbian" to pluginList and all the existing
// Qt Quick Components to qtComponentsList
void searchPlugin(QString path, QString plugin, QStringList& pluginList, QStringList& qtComponentsList)
{
    QDir directory(path);
    QStringList dirs = directory.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    if (directory.exists("qmldir"))
    {
        // This directory contains file qmldir, so it's probably
        // a plugin
        pluginList.append(plugin);

        if (plugin == "Qt.labs.components" || plugin == "Qt.labs.components.native" ||
            plugin == "com.nokia.symbian" || plugin == "com.nokia.meego" ||
            plugin == "com.nokia.extras")
        {
            qtComponentsList.append("<b>"+plugin+"</b>");
            QString qmldir = path+"/qmldir";
            parseQmldir(qmldir, qtComponentsList);
        }
    }

    // Go through all subdirs
    foreach(QString entry, dirs)
    {
        QString prefix = plugin == "" ? "" : ".";
        searchPlugin(path+"/"+entry, plugin+prefix+entry, pluginList, qtComponentsList);
    }
}

// Returns a string with all QML plugins found from the QDeclarativeEngine import path
QString qtQuickPlugins(QStringList& qtComponents)
{
    QDeclarativeEngine engine;
    QStringList importPaths = engine.importPathList();
    QStringList plugins;

    foreach(QString path, importPaths)
    {
        searchPlugin(path,"",plugins, qtComponents);
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

    QStringList plugins;
    QStringList qtComponents;

    info.append(QPair<QString,QString>("Qt Quick plugins", qtQuickPlugins(qtComponents)));

    QString components;
    foreach(QString component, qtComponents)
    {
        components += component + "<br>";
    }

    info.append(QPair<QString,QString>("Qt Components", components));

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



