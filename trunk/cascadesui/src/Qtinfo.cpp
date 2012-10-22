#include "Qtinfo.hpp"
#include "mylistmodel.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

Qtinfo::Qtinfo(bb::cascades::Application *app)
: QObject(app)
{
    // register the MyListModel C++ type to be visible in QML
    qmlRegisterType<MyListModel>("com.rim.example.custom", 1, 0, "MyListModel");

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

