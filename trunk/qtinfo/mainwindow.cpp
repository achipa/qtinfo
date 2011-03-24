#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QLibraryInfo>
#include <QImageReader>
#include <QSystemInfo>
#include <QLocale>
#include <QDebug>
#include <QtWebKit>
#include <QSslSocket>
#include <QTextStream>
#include <QDesktopServices>

#ifdef QT_OPENGL_LIB
#include <QGLFormat>
#endif

QTM_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextStream out( &text ) ;
    QFile htmlfile("://Qt_info.html");
    htmlfile.open(QIODevice::ReadOnly);
    html = htmlfile.readAll();
    QString rowstr = "\
            <tr> \
              <td class=\"info\"><strong>%0</strong></td> \
              <td>%1</td> \
            </tr>__TEMPLATE__";

    QString key = "Qt version";
    QString value = qVersion();
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;


    key = "Qt build";
    value = QLibraryInfo::buildDate().toString()+ ", " + QLibraryInfo::buildKey()  + ", " + QLibraryInfo::licensee();
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Webkit";
    value = qWebKitVersion() + " (SSL: " + (QSslSocket::supportsSsl() ? "Yes)" : "No)");
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

#ifdef QT_OPENGL_LIB
    key = "OpenGL";
    value = "";
    if (QGLFormat::hasOpenGL()) {
        int flags = QGLFormat::openGLVersionFlags ();
        if (flags & QGLFormat::OpenGL_Version_4_0) value = "OpenGL 4.0";
        else if (flags & QGLFormat::OpenGL_Version_3_3) value = "OpenGL 3.3";
        else if (flags & QGLFormat::OpenGL_Version_3_2) value = "OpenGL 3.2";
        else if (flags & QGLFormat::OpenGL_Version_3_1) value = "OpenGL 3.1";
        else if (flags & QGLFormat::OpenGL_Version_3_0) value = "OpenGL 3.0";
        else if (flags & QGLFormat::OpenGL_Version_2_1) value = "OpenGL 2.1";
        else if (flags & QGLFormat::OpenGL_Version_2_0) value = "OpenGL 2.0";
        else if (flags & QGLFormat::OpenGL_Version_1_5) value = "OpenGL 1.5";
        else if (flags & QGLFormat::OpenGL_Version_1_4) value = "OpenGL 1.4";
        else if (flags & QGLFormat::OpenGL_Version_1_3) value = "OpenGL 1.3";
        else if (flags & QGLFormat::OpenGL_Version_1_2) value = "OpenGL 1.2";
        else if (flags & QGLFormat::OpenGL_Version_1_1) value = "OpenGL 1.1";
        if (flags & QGLFormat::OpenGL_ES_CommonLite_Version_1_0) value += " OpenGL ES 1.0 Common Lite";
        else if (flags & QGLFormat::OpenGL_ES_Common_Version_1_0) value += " OpenGL ES 1.0 Common";
        else if (flags & QGLFormat::OpenGL_ES_CommonLite_Version_1_1) value += " OpenGL ES 1.1 Common Lite";
        else if (flags & QGLFormat::OpenGL_ES_Common_Version_1_1) value += " OpenGL ES 1.1 Common";
        else if (flags & QGLFormat::OpenGL_ES_Version_2_0) value += " OpenGL ES 2.0";
    } else {
        value = "No";
    }
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;
#endif

    key = "Country";
    QLocale defaultlocale;
    value = QLocale::countryToString(defaultlocale.country());
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Language";
    value = QLocale::languageToString(defaultlocale.language()) + " (" + defaultlocale.name() + ")";
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Qt modules";
    value = "";
    QStringList qtlibs;
    QStringList qtmobilitylibs;
    QStringList installedlibs;

    qtlibs << "Qt3Support";
    qtlibs << "QtBearer";
    qtlibs << "QAxContainer";
    qtlibs << "QAxServer";
    qtlibs << "QtCLucene";
    qtlibs << "QtCore";
    qtlibs << "QtDBus";
    qtlibs << "QtDeclarative";
    qtlibs << "QtDesignerComponents";
    qtlibs << "QtDesigner";
    qtlibs << "QtGui";
    qtlibs << "QtHelp";
    qtlibs << "QtMultimedia";
    qtlibs << "QtMaemo5";
    qtlibs << "phonon";
    qtlibs << "QtNetwork";
    qtlibs << "QtOpenGL";
    qtlibs << "QtScript";
    qtlibs << "QtScriptTools";
    qtlibs << "QtSql";
    qtlibs << "QtSvg";
    qtlibs << "QtTest";
    qtlibs << "QtUiTools";
    qtlibs << "QtWebKit";
    qtlibs << "QtXmlPatterns";
    qtlibs << "QtXml";

    qtmobilitylibs << "QtConnectivity";
    qtmobilitylibs << "QtContacts";
    qtmobilitylibs << "QtFeedback";
    qtmobilitylibs << "QtGallery";
    qtmobilitylibs << "QtLocation";
    qtmobilitylibs << "QtMultimediaKit";
    qtmobilitylibs << "QtSensors";
    qtmobilitylibs << "QtServiceFramework";
    qtmobilitylibs << "QtSystemInfo";
    qtmobilitylibs << "QtOrganizer";
    qtmobilitylibs << "QtPublishSubscribe";
    qtmobilitylibs << "QtVersitOrganizer";
    qtmobilitylibs << "QtVersit";
    qtlibs.append(qtmobilitylibs);

    foreach(QString libname, qtlibs) {
        if (!loadLib(libname).isEmpty()) {
//            if (qtmobilitylibs.contains(libname))
//                ui->modules->setText(ui->modules->text() + " <i>" + libname.replace("lib", "") + "</i>");
//            else
//                ui->modules->setText(ui->modules->text() + " " + libname.replace("lib", ""));
            value += libname.replace("lib", "") + " ";
            installedlibs << libname;
        }
    }
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Mobility version";
    QSystemInfo si;
    QString mobilityver = si.version((QSystemInfo::Version)4);
    if (mobilityver.isEmpty() || mobilityver == "Not Available")
        value = "1.0.x";
    else
        value = si.version((QSystemInfo::Version)4);
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Qt Quick version";
    value = "";
    if (installedlibs.contains("QtDeclarative"))
    {
        QString libname(loadLib("./qtquickinfolib")); // hmm... might need to include ./ as one of the possible prefixes ?
//        QString libname(loadLib("qtquickinfolib"));
        qDebug() << libname;
        if (!libname.isEmpty()) {
            typedef QMap<QString, QString> (*fn)();
            fn v = (fn) QLibrary::resolve(libname, "getInfo");
            if (v) {
                QMap<QString, QString> map = v();
                foreach(QString key, map.keys()) {
                    if (key == "section") continue; // will make it pretty when I get the HTML template
                    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(map[key]));
                    out << key << ": " << value << endl;
                    value = "OK";
                }
            }
        }
    }
    if (value.isEmpty()) {
        value = "Not available";
        html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
        out << key << ": " << value << endl;
    }

    key = "OS / Firmware";
    value = si.version(QSystemInfo::Os) + " / "  + si.version(QSystemInfo::Firmware);
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;


/*    if (true || presentqtlibs.contains("libQtSystemInfo")) { // have mobility, yay !
        typedef QString (*versionfunc) ( int type, const QString & parameters);
//        QString 	version ( QSystemInfo::Version type, const QString & parameter = QString() )
        versionfunc v = (versionfunc) QLibrary::resolve("/opt/qt4/lib/libQtSystemInfo", "version");
        qDebug() << v;
        if (v) {
            qDebug() <<"Version func loaded from lib";
            qDebug() << v(1, QString());
        }

    } else {
        ui->mobver->setText(ui->mobver->text() + "None");
    }*/

    key = "Library path";
    value = QLibraryInfo::location(QLibraryInfo::LibrariesPath);
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Plugin path";
    value = QLibraryInfo::location(QLibraryInfo::PluginsPath);
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Import path";
    value = QLibraryInfo::location((QLibraryInfo::LibraryLocation)11); // QLibraryInfo::ImportsPath == 11, but not available in Qt4.6
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    key = "Image formats";
    value = "";
    QList<QByteArray> sif = QImageReader::supportedImageFormats ();
    foreach (QString fmtstr, sif)
    {
        value += fmtstr + ", ";
    }
    html = html.replace("__TEMPLATE__", rowstr.arg(key).arg(value));
    out << key << ": " << value << endl;

    html = html.replace("__TEMPLATE__", "");
    ui->webView->setHtml(html,QUrl("qrc:/"));

    QTextStream sout(stdout);
    sout << text;
#ifdef Q_WS_MAEMO_5
    ui->closeButton->setVisible(false);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::loadLib(QString libname)
{
    QLibrary lib(libname);
//    qDebug() << lib.errorString();
    if (!lib.load()) {
        foreach (QString prefix, QStringList() << "" << "lib") {
            foreach(QString version, QStringList() << "" << "1" << "2" << "3" << "4" << "5") {
                lib.setFileNameAndVersion(prefix + libname, version.toInt()); // Linux naming
                if (lib.load()) break;
                lib.setFileName(prefix + libname + version); // Windows and Symbian naming
                if (lib.load()) break;
                }
        }
    }
    bool loaded = lib.isLoaded();

//    qDebug() << libname << "loaded " << loaded;

    if (loaded) {
        lib.unload();
        return lib.fileName();
    } else {
        return QString();
    }
}
