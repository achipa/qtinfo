#include "qtquickinfo.h"
#include <QtDeclarative>
#include <QStringList>

QString qtQuickVersion()
{
    QDeclarativeView view;
    view.setSource(QUrl::fromLocalFile("qtquick20.qml"));
    if (view.status() == QDeclarativeView::Ready) return "2.0";
    view.setSource(QUrl::fromLocalFile("qtquick11.qml"));
    if (view.status() == QDeclarativeView::Ready) return "1.1";
    view.setSource(QUrl::fromLocalFile("qtquick10.qml"));
    if (view.status() == QDeclarativeView::Ready) return "1.0";
    view.setSource(QUrl::fromLocalFile("qt47.qml"));
    if (view.status() == QDeclarativeView::Ready) return "1.0 (import Qt 4.7)";

    return "Could not determine Qt Quick version";
}

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

    info.append(QPair<QString,QString>("Qt Quick version", qtQuickVersion()));
    info.append(QPair<QString,QString>("Qt Quick import path", list));

    return info;
}


