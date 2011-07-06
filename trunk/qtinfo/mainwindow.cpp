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
    ui->textBrowser->setHtml(infoloader->resultAsHTML());
//    ui->webView->setHtml(html,QUrl("qrc:/"));

    QTextStream sout(stdout);
    sout << infoloader->resultAsText();

    // If QtDeclarative and Qt Quick Components are available, use QML UI
    if (infoloader->isLoaded("QtDeclarative")) { // go for fancy declarative UI instead of QWidgets
        if (callBoolFunction("declarativeui", "isQmlUiAvailable")) {
            qDebug() << "loading QML UI";
            QWidget* widget = loadWidget("declarativeui", "declarativeUI");
            if (widget) {
                ui->textBrowser->setVisible(false);
                ui->widget->setEnabled(true);
                ui->widget->setVisible(true);
                widget->showFullScreen();
                // Note that QML buttons should call the same methods as the auto-slot-connected buttons
            }
        }
    }

#ifdef Q_WS_MAEMO_5
    ui->closeButton->setVisible(false);
#endif
}

void MainWindow::updateLoadScreen(QString str)
{
    ui->textBrowser->setText(str + "\n" + ui->textBrowser->toPlainText());
    qApp->processEvents();
}
