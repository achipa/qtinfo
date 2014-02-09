#include "qt5declarativeui.h"
#include <QtQuick>
#include <QStringList>
#include <QVariant>
#include <QDebug>

QStringList keys;
QStringList values;

QWidget* declarativeUI(QList<QPair<QString, QString> > infoPairs, QObject* mainWindow)
//QObject* declarativeUI(QList<QPair<QString, QString> > infoPairs, QObject* mainWindow)
{
//    return NULL;
//    QQuickWindow::setDefaultAlphaBuffer(true);
    QQuickView* view = new QQuickView();
    QWidget* retWidget = QWidget::createWindowContainer(view, qobject_cast<QWidget*>(mainWindow));
//    QObject* retWidget = QWidget::createWindowContainer(view, qobject_cast<QWidget*>(mainWindow));
//    qDebug() << "retW" << retWidget;
    QString section;

//    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    keys.clear();
    values.clear();

    for (int i = 0; i < infoPairs.length(); i++)
    {
        QPair<QString, QString> infoPair = infoPairs.at(i);

        if (infoPair.first == "Section") {
            section = infoPair.second;
        } else {
//            dataList.append(new QataObject(infoPair.first, infoPair.second, section));
        }
        keys.append(infoPair.first);
        values.append(infoPair.second);
    }

    view->rootContext()->setContextProperty("MainWindow", mainWindow);
    view->rootContext()->setContextProperty("keyModel", QVariant::fromValue(keys));
    view->rootContext()->setContextProperty("valueModel", QVariant::fromValue(values));
//    view->rootContext()->setContextProperty("sectionModel", QVariant::fromValue(dataList));

#ifdef Q_OS_SAILFISH
    view->setSource(QUrl::fromLocalFile(QString() + TARGETPATH + "../qml/main.qml"));
            //    view->setSource(QUrl::fromLocalFile("/usr/share/harbour-qtinfo/qml/LoadingPage.qml"));
#else
    view->setSource(QUrl::fromLocalFile("../qml/main.qml"));
#endif

    return retWidget;
//    return NULL;
}

bool checkQml(QLatin1String qml)
{
#ifdef Q_OS_SAILFISH // this check segfaults within libqt5qml on sailfish
    return true;
#endif
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData(qml.latin1(), QUrl());
//    QScopedPointer<QQuickItem> item = qobject_cast<QQuickItem *>(component.create());
    QScopedPointer<QQuickItem> item(qobject_cast<QQuickItem *>(component.create()));

    if (item) {
        // Components plugin seems to be available
        qDebug() << "YAY " << qml;
        return true;
    }
    else {
        // Something is wrong, at least output errors
        qDebug() << "FAIL " << component.errors();
    }
    return false;
}

bool isQmlUiAvailable()
{
    if (checkQml(QLatin1String("import QtQuick 2.0\nimport Sailfish.Silica 1.0\nApplicationWindow {}")))
            return true;
    qDebug() << "Module loadable, but no known QtQuick version available";
    return false;
}

