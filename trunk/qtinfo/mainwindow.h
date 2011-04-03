#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QClipboard>
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtGui/QApplication>
#include <QTextStream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString loadLib(QString libName);

public slots:
    void on_closeButton_clicked(bool checked) { this->close(); }
    void on_emailButton_clicked(bool checked) { QDesktopServices::openUrl(QUrl(QString("mailto:user@foo.com?subject=QtInfo&body=%0").arg(text))); }
#ifdef Q_WS_MAEMO_5
//    void on_mailButton_clicked(bool checked) { QDBusInterface browser("com.nokia.modest", "/com/nokia/modest", "com.nokia.modest")  ; browser.call("MailTo", "");}
    void on_saveButton_clicked(bool checked) { QFile outfile("/home/user/MyDocs/qtinfo.html"); outfile.open(QIODevice::WriteOnly); outfile.write(html.toAscii()); outfile.close();  }
#endif
    void on_jsbinButton_clicked(bool checked) { QDesktopServices::openUrl(QUrl("http://pastebin.com")); }
    void on_clipboardButton_clicked(bool checked) { QClipboard *clipboard = QApplication::clipboard(); clipboard->setText(text); }

private:
    void loadInfo(QString key, QString libname, QString libfile, const char* infofunc); // pvt because of out
    bool loadValues(QString library, QString defaultKey, const char* function); // pvt because of out, used by loadInfo
    void addToTemplate(QString key, QString value);
    void addToTemplate(QList<QPair<QString, QString> > list);
    Ui::MainWindow *ui;
    QString html;
    QString text;
    QString rowstr;
    QString sectionstr;
    QTextStream out;
    QStringList installedlibs;
};

#endif // MAINWINDOW_H
