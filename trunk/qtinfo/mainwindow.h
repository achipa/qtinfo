#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QClipboard>
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtGui/QApplication>
#include <QTextStream>
#include <QtGui/QFileDialog>
#include "infoloader.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    void startLoading() { infoloader->start(); }
//    void startLoading() { infoloader->run(); showUI(); }

public slots:
    void updateLoadScreen(QString str);
    void on_closeButton_clicked(bool checked) { this->close(); }
    void on_emailButton_clicked(bool checked) { QDesktopServices::openUrl(QUrl(QString("mailto:user@foo.com?subject=QtInfo&body=%0").arg(infoloader->resultAsText()))); }
#ifdef Q_WS_MAEMO_5
//    void on_mailButton_clicked(bool checked) { QDBusInterface browser("com.nokia.modest", "/com/nokia/modest", "com.nokia.modest")  ; browser.call("MailTo", "");}
#endif
    void on_saveButton_clicked(bool checked) { QFile outfile(QFileDialog::getSaveFileName(this, "Save output as", "/home/user/MyDocs/qtinfo.html")); outfile.open(QIODevice::WriteOnly); outfile.write(infoloader->resultAsHTML().toAscii()); outfile.close();  }
    void on_jsbinButton_clicked(bool checked) { QDesktopServices::openUrl(QUrl("http://pastebin.com")); }
    void on_clipboardButton_clicked(bool checked) { QClipboard *clipboard = QApplication::clipboard(); clipboard->setText(infoloader->resultAsText()); }
    void showUI();

private:
    QWidget * loadWidget(QString library, const char *function);
    Ui::MainWindow *ui;
    InfoLoader* infoloader;
};

#endif // MAINWINDOW_H
