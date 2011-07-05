#include "declarativeui.h"
#include <QtDeclarative>
#include <QStringList>
#include <QVariant>
#include <QDebug>

QStringList keys;
QStringList values;

QWidget* declarativeUI(QList<QPair<QString, QString> > infoPairs, QObject* mainWindow)
{
    QDeclarativeView* view = new QDeclarativeView();

    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    keys.clear();
    values.clear();

    for (int i = 0; i < infoPairs.length(); i++)
    {
        QPair<QString, QString> infoPair = infoPairs.at(i);

        keys.append(infoPair.first);
        values.append(infoPair.second);
    }


    view->rootContext()->setContextProperty("MainWindow", mainWindow);
    view->rootContext()->setContextProperty("keyModel", QVariant::fromValue(keys));
    view->rootContext()->setContextProperty("valueModel", QVariant::fromValue(values));

    view->setSource(QUrl::fromLocalFile("debug/qml_symbian/main.qml"));

    return view;
}

bool isQmlUiAvailable()
{
    QLatin1String qml("import QtQuick 1.0\nimport com.nokia.symbian 1.0\nimport com.nokia.extras 1.0\nWindow {}");

    QDeclarativeEngine engine;
    QDeclarativeComponent component(&engine);
    component.setData(qml.latin1(), QUrl());
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem *>(component.create());

    if (item) {
        // Components plugin seems to be available
        return true;
    }
    else {
        // Something is wrong, at least output errors
        qDebug() << component.errors();
    }
    return false;
}

