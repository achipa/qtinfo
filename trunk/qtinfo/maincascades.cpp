#include <bb/cascades/Application>
#include "maincascadeswindow.hpp"
#include <QLocale>
#include <QTranslator>
#include <QStringList>
#include <QDebug>

#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

int main(int argc, char **argv)
{
/*
    QApplication* tmpapp = new QApplication(argc, argv);
    tmpapp->processEvents();
    QFontDatabase database;
    QString familiesList = database.families().join(", ");
    QStringList valuelist;
    foreach(QFontDatabase::WritingSystem ws, database.writingSystems()) {
        valuelist << QString("%0 (%1)").arg(QFontDatabase::writingSystemName(ws)).arg(QFontDatabase::writingSystemSample(ws));
    }
    QString writingsystemList = valuelist.join(", ");
    valuelist.clear();
    foreach(int size, database.standardSizes()) {
        valuelist << QString("%0").arg(size);
    }
    QString standardsizesList = valuelist.join(", ");
    qDebug() << familiesList << writingsystemList << standardsizesList;
    tmpapp->processEvents();
    delete tmpapp; // stuff you don't see normally. BB10 is special.
*/
    // this is where the server is started etc
    Application app(argc, argv);
//    app.setProperty("families", QString("TehFontList"));
//    app.setProperty("families", familiesList);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "QtInfo_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    // create the application pane object to init UI etc.
    new MainCascadesWindow(&app);
//    QmlDocument *qml = QmlDocument::create("asset:///loading.qml").parent(&app);
//    AbstractPane *root = qml->createRootObject<AbstractPane>();
//    app.setScene(root);


    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}

