#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QDebug>
#include <QTextStream>
#include <QDesktopServices>
#include <QTimer>
#include <QStatusBar>

#include "qplatformdefs.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    infoloader(new InfoLoader(this))
{
    ui->setupUi(this);
    ui->clipboardButton->setVisible(false);
    ui->emailButton->setVisible(false);
    ui->closeButton->setVisible(false);
    ui->jsbinButton->setVisible(false);
    ui->saveButton->setVisible(false);
//    this->statusBar()->setVisible(false);
//    connect(infoloader, SIGNAL(finished()), SLOT(showUI()));
    connect(infoloader, SIGNAL(newInfoAvailable(QString)), SLOT(updateLoadScreen(QString)), Qt::DirectConnection);
    connect(infoloader, SIGNAL(progressChange(int)), ui->progressBar, SLOT(setValue(int)), Qt::DirectConnection);
    QTimer::singleShot(0,this,SLOT(showUI()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget* MainWindow::loadWidget(QString library, const char* function)
{
    typedef QWidget* (*fn)(QList<QPair<QString, QString> >, QObject*);
#ifdef Q_OS_SAILFISH
        // due to Harbour policies...
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(TARGETPATH+library), function);
#else
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(qApp->applicationDirPath()+"/"+library), function);
#endif
    qDebug() << library <<  v;
    if (v) {
        return v(infoloader->resultAsRawpairs(), this);
    }
    return NULL;
}

bool MainWindow::callBoolFunction(QString library, const char *function)
{
    typedef bool (*fn)();
#ifdef MEEGO_EDITION_HARMATTAN
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(qApp->applicationDirPath()+"/lib"+library), function);
#elif Q_OS_SAILFISH
        // due to Harbour policies...
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(TARGETPATH + library), function);
#else
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(qApp->applicationDirPath()+"/"+library), function);
#endif
//    qDebug() << "calling " << library << function << v;
    QTextStream sout(stdout);
    sout << "calling ";
    sout << library;
    sout << function << endl;
//    sout << v;
    if (v != 0) {
        return v();
    }
    sout << "Could not resolve func/lib " << qApp->applicationDirPath() << "/lib" << library << " " << infoloader->loadLib(qApp->applicationDirPath()+"/lib"+library) << " " << function << endl;
//    sout << QLibrary::errorString() << endl;
    return false;
}

void MainWindow::showUI()
{
    infoloader->run();

//    ui->webView->setHtml(html,QUrl("qrc:/"));

    QTextStream sout(stdout);
    sout << infoloader->resultAsText();

    ui->progressBar->setVisible(false);
    bool qmlUI = false;

    // If QtDeclarative and Qt Quick Components are available, use QML UI
    QWidget* widget = NULL;
    if (infoloader->isLoaded("Qt5Quick") || infoloader->isLoaded("QtQuick")) { // go for fancy declarative UI instead of QWidgets
        sout << "QtQuick module present, contemplating QML UI";
        qDebug() << "QtQuick module present, contemplating QML UI";
        if (callBoolFunction("qt5declarativeui", "isQmlUiAvailable")) {
            sout << "loading QML5 UI";
            qDebug() << "loading QML5 UI";
            widget = loadWidget("qt5declarativeui", "declarativeUI");
            sout << widget;
            qDebug() << widget;
        }
    }
    if (widget == NULL && (infoloader->isLoaded("QtDeclarative") || infoloader->isLoaded("Qt5Declarative"))) { // go for fancy declarative UI instead of QWidgets
        sout << "Declarative module present, contemplating QML UI";

        if (widget == NULL && callBoolFunction("declarativeui", "isQmlUiAvailable")) {
            sout << "loading QML UI";
            widget = loadWidget("declarativeui", "declarativeUI");
        }
    }
    if (widget != NULL) { // we have a living breathing QtQuick widget!
        sout << "QML UI is a GO!";
        qDebug() << "QML UI is a GO!";
        qmlUI = true;
        widget->setParent(this);
        ui->textBrowser->setVisible(false);
        ui->widget->setEnabled(true);
        ui->widget->setVisible(true);
        widget->showFullScreen();
        // Note that QML buttons should call the same methods as the auto-slot-connected buttons
    } else {
//        this->statusBar()->setVisible(true);
        ui->emailButton->setVisible(true);
        ui->jsbinButton->setVisible(true);
        ui->clipboardButton->setVisible(true);
        ui->saveButton->setVisible(true);
#ifndef Q_WS_MAEMO_5
        ui->closeButton->setVisible(true); // maemo5 has X provided by the window manager
#endif
    }

    if (!qmlUI) {
        ui->textBrowser->setHtml(infoloader->resultAsHTML());
    } else {
        delete ui->textBrowser;
        ui->textBrowser = 0;
    }
}

void MainWindow::updateLoadScreen(QString str)
{
    ui->textBrowser->setText(str + "\n" + ui->textBrowser->toPlainText());
    qApp->processEvents();
}
