#include "declarativeui.h"
#include <QtDeclarative>
#include <QStringList>
#include <QDebug>

QWidget* declarativeUI(QList<QPair<QString, QString> > infoPairs)
{
    QDeclarativeView* view = new QDeclarativeView(QUrl("qrc:///qml/main.qml"));

    return view;
}



