#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QDebug>
#include <QTextStream>
#include <QDesktopServices>
#include <QTimer>
#include <QStatusBar>

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
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(qApp->applicationDirPath()+"/"+library), function);
    qDebug() << library <<  v;
    if (v) {
        return v(infoloader->resultAsRawpairs(), this);
    }
    return NULL;
}

bool MainWindow::callBoolFunction(QString library, const char *function)
{
    typedef bool (*fn)();
    fn v = (fn) QLibrary::resolve(infoloader->loadLib(qApp->applicationDirPath()+"/"+library), function);
    qDebug() << library <<  v;
    if (v) {
        return v();
    }
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
    if (infoloader->isLoaded("QtDeclarative")) { // go for fancy declarative UI instead of QWidgets
        if (callBoolFunction("declarativeui", "isQmlUiAvailable")) {
            qDebug() << "loading QML UI";
            QWidget* widget = loadWidget("declarativeui", "declarativeUI");
            if (widget) {
                qmlUI = true;
                ui->textBrowser->setVisible(false);
                ui->widget->setEnabled(true);
                ui->widget->setVisible(true);
                widget->showFullScreen();
                // Note that QML buttons should call the same methods as the auto-slot-connected buttons
            }
        }
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
