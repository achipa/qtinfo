#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QDebug>
#include <QTextStream>
#include <QDesktopServices>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    infoloader(new InfoLoader())
{
    ui->setupUi(this);
//    connect(infoloader, SIGNAL(finished()), SLOT(showUI()));
    connect(infoloader, SIGNAL(newInfoAvailable(QString)), SLOT(updateLoadScreen(QString)), Qt::DirectConnection);
    QTimer::singleShot(0,this,SLOT(showUI()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget* MainWindow::loadWidget(QString library, const char* function)
{
    typedef QWidget* (*fn)(QList<QPair<QString, QString> >);
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(qApp->applicationDirPath()+"/"+library), function);
    qDebug() << library <<  v;
    if (v) {
        return v(infoloader->resultAsRawpairs());
    }
    return NULL;
}

void MainWindow::showUI()
{
    infoloader->run();
    ui->textBrowser->setHtml(infoloader->resultAsHTML());
//    ui->webView->setHtml(html,QUrl("qrc:/"));

    QTextStream sout(stdout);
    sout << infoloader->resultAsText();

//  uncomment this to enable the future QML powered UI

//    if (installedlibs.contains("QtDeclarative")) { // go for fancy declarative UI instead of QWidgets
//        QWidget* widget = loadWidget("declarativeui", "declarativeUI");
//        if (widget) {
//            widget->setParent(ui->widget);
//            ui->textBrowser->setVisible(false);
//            ui->widget->setEnabled(true);
//            ui->widget->setVisible(true);
//    // Note that QML buttons should call the same methods as the auto-slot-connected buttons
//        }
//    } else {
//        ui->widget->setVisible(false);
//    }

#ifdef Q_WS_MAEMO_5
    ui->closeButton->setVisible(false);
#endif
}

void MainWindow::updateLoadScreen(QString str)
{
    ui->textBrowser->setText(str + "\n" + ui->textBrowser->toPlainText());
    qApp->processEvents();
}
