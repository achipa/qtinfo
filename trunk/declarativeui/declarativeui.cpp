#include "declarativeui.h"
#include <QtDeclarative>
#include <QStringList>
#include <QVariant>
#include <QDebug>

QStringList keys;
QStringList values;

QWidget* declarativeUI(QList<QPair<QString, QString> > infoPairs)
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

    view->rootContext()->setContextProperty("keyModel", QVariant::fromValue(keys));
    view->rootContext()->setContextProperty("valueModel", QVariant::fromValue(values));

    view->setSource(QUrl("qrc:///qml/main.qml"));

    return view;
}



