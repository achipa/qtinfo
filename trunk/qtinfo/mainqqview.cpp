#include "mainqqview.h"
#include <QTimer>
#include <QDebug>
#include <QtQml/QQmlContext>
#include <QGuiApplication>

MainQQView::MainQQView(QQuickView* qqv) : qqview(qqv), infoloader(new InfoLoader(this))
{
//    qqv->setSource( QUrl::fromLocalFile("/usr/share/harbour-qtinfo/qml/LoadingPage.qml"));

    connect(infoloader, SIGNAL(newInfoAvailable(QString)), SLOT(updateLoadScreen(QString)), Qt::DirectConnection);
    connect(infoloader, SIGNAL(progressChange(int)), SLOT(updateProgress(int)), Qt::DirectConnection);
    QTimer::singleShot(0,this,SLOT(showUI()));
}


void MainQQView::showUI()
{
     infoloader->run();

     QTextStream sout(stdout);
     sout << infoloader->resultAsText();
     qDebug() << infoloader->resultAsText();
    //    QString jsondata = "{";

     QString section;

     QStringList keys;
     QStringList values;

     QList<QPair<QString, QString> > infoPairs = infoloader->resultAsRawpairs();
//     keys.clear();
//     values.clear();

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

     qqview->rootContext()->setContextProperty("keyModel", QVariant::fromValue(keys));
     qqview->rootContext()->setContextProperty("valueModel", QVariant::fromValue(values));
 //    view->rootContext()->setContextProperty("sectionModel", QVariant::fromValue(dataList));

     qqview->setSource(QUrl::fromLocalFile("/usr/share/harbour-qtinfo/qml/main.qml"));


}

void MainQQView::updateProgress(int perc)
{
//     qqview->rootContext()->setContextProperty("MainWindow", mainWindow);
//     QObject *progress = root->findChild<QObject*>("progress");
//     if (progress)
//         progress->setProperty("value", perc);

//     bb::cascades::Application::instance()->processEvents();
}

void MainQQView::updateLoadScreen(QString str)
{
//     QObject *textArea = root->findChild<QObject*>("loadTicker");
//     if (textArea)
//         textArea->setProperty("text", str + "\n" + textArea->property("text").toString());

//     bb::cascades::Application::instance()->processEvents();
}

