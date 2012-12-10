#include "cascadesui.h"
#include "mylistmodel.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <QtGui/QFontDatabase>

using namespace bb::cascades;

QtInfo::QtInfo(bb::cascades::Application *app)
: QObject(app)
{
    // register the MyListModel C++ type to be visible in QML
    QmlDocument *qml = QmlDocument::create("app/native/assets/main.qml").parent(this);
    qmlRegisterType<MyListModel>("com.rim.example.custom", 1, 0, "MyListModel");

//    QFontDatabase database;

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
//    QDeclarativeContext *derivedContext1 =
//                new QDeclarativeContext(qml->documentContext());
//        derivedContext1->setContextProperty("fontModel", QVariant::fromValue(database.families()));
//    qml->documentContext()->setContextProperty("fontModel", QVariant::fromValue(database.families()));
        qml->documentContext()->setContextProperty("fontModel", QVariant::fromValue(QStringList()));

    // create root object for the UI

    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // set created root object as a scene
    app->setScene(root);
}

