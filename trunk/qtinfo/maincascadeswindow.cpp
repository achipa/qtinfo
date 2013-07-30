#include "maincascadeswindow.hpp"
//#include "mylistmodel.hpp"

#include <bb/cascades/Application>
#include <qdebug.h>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/GroupDataModel>

#define applicationDirPath QString("")

using namespace bb::cascades;

MainCascadesWindow::MainCascadesWindow(bb::cascades::Application *app)
: QObject(app), infoloader(new InfoLoader(this))
{
    qml = QmlDocument::create("asset:///loading.qml").parent(app);
    root = qml->createRootObject<AbstractPane>();
    app->setScene(root);

    connect(infoloader, SIGNAL(newInfoAvailable(QString)), SLOT(updateLoadScreen(QString)), Qt::DirectConnection);
    connect(infoloader, SIGNAL(progressChange(int)), SLOT(updateProgress(int)), Qt::DirectConnection);
    QTimer::singleShot(0,this,SLOT(showUI()));

}


QObject* MainCascadesWindow::loadWidget(QString library, const char* function)
{
    typedef QObject* (*fn)(QList<QPair<QString, QString> >, QObject*);
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(applicationDirPath+"/"+library), function);
    qDebug() << library <<  v;
    if (v) {
        return v(infoloader->resultAsRawpairs(), this);
    }
    return NULL;
}

bool MainCascadesWindow::callBoolFunction(QString library, const char *function)
{
    typedef bool (*fn)();
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(applicationDirPath+"/"+library), function);
//    qDebug() << "calling " << library << function << v;
    QTextStream sout(stdout);
    sout << "calling ";
    sout << library;
    sout << function << endl;
//    sout << v;
    if (v != 0) {
        return v();
    }
    sout << "Could not resolve func/lib " << applicationDirPath << "/lib" << library << " " << infoloader->loadLib(applicationDirPath+"/lib"+library) << " " << function << endl;
//    sout << QLibrary::errorString() << endl;
    return false;
}

void MainCascadesWindow::showUI()
{
    infoloader->run();

//    ui->webView->setHtml(html,QUrl("qrc:/"));

    QTextStream sout(stdout);
    sout << infoloader->resultAsText();
    qDebug() << infoloader->resultAsText();
//    QString jsondata = "{";
    qml = QmlDocument::create("asset:///main.qml").parent(bb::cascades::Application::instance());
    root = qml->createRootObject<AbstractPane>();
    bb::cascades::Application::instance()->setScene(root);

    bb::cascades::GroupDataModel *dmobj = (bb::cascades::GroupDataModel*) root->findChild<QObject*>("dm");
    typedef QPair<QString, QString> pairtype;
    QString lastsection = "Qt";
    QVariantMap headervm;
    headervm["first"] = "Qt";
    headervm["type"] = "header";
    dmobj->insert(headervm);
    foreach(pairtype pair, infoloader->resultAsRawpairs())
    {
        qDebug() << pair.first << pair.second;
        QVariantMap qvm;
        if (pair.first == "section") {
            lastsection = pair.second;
            qvm["first"]= lastsection;
            qvm["second"]= lastsection;
            qvm["section"]= lastsection;
            qvm["type"]= "header";
        } else {
            qvm["first"]  = pair.first;
            qvm["second"] = pair.second.replace("<br>","\n");
            qvm["section"]= lastsection;
            qvm["type"]= "item";
        }
        dmobj->insert(qvm);
    }
    dmobj->setSortedAscending(false);

}

void MainCascadesWindow::updateProgress(int perc)
{
    QObject *progress = root->findChild<QObject*>("progress");
    if (progress)
        progress->setProperty("value", perc);

    bb::cascades::Application::instance()->processEvents();
}
void MainCascadesWindow::updateLoadScreen(QString str)
{
    QObject *textArea = root->findChild<QObject*>("loadTicker");
    if (textArea)
        textArea->setProperty("text", str + "\n" + textArea->property("text").toString());

    bb::cascades::Application::instance()->processEvents();
}

