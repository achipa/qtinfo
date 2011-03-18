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

#ifdef QT_OPENGL_LIB
#include <QGLFormat>
#endif

QTM_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QLibraryInfo::licensee() << QLibraryInfo::licensedProducts();
    ui->qtver->setText(ui->qtver->text() + qVersion() + " (" + QLibraryInfo::buildDate().toString()+ ", " + QLibraryInfo::buildKey()  + ", " + QLibraryInfo::licensee() +")");
    ui->qtinfover->setText(ui->qtinfover->text() + QT_VERSION_STR + QString(")") );
    ui->webkitver->setText(ui->webkitver->text() + qWebKitVersion() + "(SSL: " + (QSslSocket::supportsSsl() ? "Yes)" : "No)") );
#ifdef QT_OPENGL_LIB
    if (QGLFormat::hasOpenGL()) {
        int flags = QGLFormat::openGLVersionFlags ();
        QString glverstr = "";
        if (flags & QGLFormat::OpenGL_Version_4_0) glverstr = "OpenGL 4.0";
        else if (flags & QGLFormat::OpenGL_Version_3_3) glverstr = "OpenGL 3.3";
        else if (flags & QGLFormat::OpenGL_Version_3_2) glverstr = "OpenGL 3.2";
        else if (flags & QGLFormat::OpenGL_Version_3_1) glverstr = "OpenGL 3.1";
        else if (flags & QGLFormat::OpenGL_Version_3_0) glverstr = "OpenGL 3.0";
        else if (flags & QGLFormat::OpenGL_Version_2_1) glverstr = "OpenGL 2.1";
        else if (flags & QGLFormat::OpenGL_Version_2_0) glverstr = "OpenGL 2.0";
        else if (flags & QGLFormat::OpenGL_Version_1_5) glverstr = "OpenGL 1.5";
        else if (flags & QGLFormat::OpenGL_Version_1_4) glverstr = "OpenGL 1.4";
        else if (flags & QGLFormat::OpenGL_Version_1_3) glverstr = "OpenGL 1.3";
        else if (flags & QGLFormat::OpenGL_Version_1_2) glverstr = "OpenGL 1.2";
        else if (flags & QGLFormat::OpenGL_Version_1_1) glverstr = "OpenGL 1.1";
        if (flags & QGLFormat::OpenGL_ES_CommonLite_Version_1_0) glverstr += " OpenGL ES 1.0 Common Lite";
        else if (flags & QGLFormat::OpenGL_ES_Common_Version_1_0) glverstr += " OpenGL ES 1.0 Common";
        else if (flags & QGLFormat::OpenGL_ES_CommonLite_Version_1_1) glverstr += " OpenGL ES 1.1 Common Lite";
        else if (flags & QGLFormat::OpenGL_ES_Common_Version_1_1) glverstr += " OpenGL ES 1.1 Common";
        else if (flags & QGLFormat::OpenGL_ES_Version_2_0) glverstr += " OpenGL ES 2.0";
        ui->oglver->setText(ui->oglver->text() + glverstr);
    } else {
        ui->oglver->setText(ui->oglver->text() + "No");
    }
#else
    ui->oglver->setVisible(false);
#endif
    QLocale defaultlocale;
    ui->lang->setText(ui->lang->text() + QLocale::languageToString(defaultlocale.language()) + " / " + QLocale::countryToString(defaultlocale.country()) + " (" + defaultlocale.name() + ")");
    QStringList qtlibs;
    QStringList qtmobilitylibs;
    QStringList presentqtlibs;
    qtlibs << "libQt3Support";
    qtlibs << "libQtBearer";
    qtlibs << "libQAxContainer";
    qtlibs << "libQAxServer";
    qtlibs << "libQtCLucene";
    qtlibs << "libQtCore";
    qtlibs << "libQtDBus";
    qtlibs << "libQtDeclarative";
    qtlibs << "libQtDesignerComponents";
    qtlibs << "libQtDesigner";
    qtlibs << "libQtGui";
    qtlibs << "libQtHelp";
    qtlibs << "libQtMultimedia";
    qtlibs << "libphonon";
    qtlibs << "libQtNetwork";
    qtlibs << "libQtOpenGL";
    qtlibs << "libQtScript";
    qtlibs << "libQtScriptTools";
    qtlibs << "libQtSql";
    qtlibs << "libQtSvg";
    qtlibs << "libQtTest";
    qtlibs << "libQtUiTools";
    qtlibs << "libQtWebKit";
    qtlibs << "libQtXmlPatterns";
    qtlibs << "libQtXml";
    qtmobilitylibs << "libQtConnectivity";
    qtmobilitylibs << "libQtContacts";
    qtmobilitylibs << "libQtFeedback";
    qtmobilitylibs << "libQtGallery";
    qtmobilitylibs << "libQtLocation";
    qtmobilitylibs << "libQtMultimediaKit";
    qtmobilitylibs << "libQtServiceFramework";
    qtmobilitylibs << "libQtSystemInfo";
    qtmobilitylibs << "libQtOrganizer";
    qtmobilitylibs << "libQtPublishSubscribe";
    qtmobilitylibs << "libQtVersitOrganizer";
    qtmobilitylibs << "libQtVersit";
    qtlibs.append(qtmobilitylibs);

    foreach(QString libname, qtlibs) {
//        QLibrary lib("/opt/qt4/lib/" + libname);
        QLibrary lib(libname);
//        qDebug() << lib.errorString();
        if (!lib.load()) {
            lib.setFileName(libname.replace("lib", ""));
            lib.load();
        }
//        if (!lib.isLoaded()) {
//            lib.setFileName(libname.replace("lib", "/usr/lib/lib"));
//            lib.load();
//        }
//        if (!lib.isLoaded()) {
//            lib.setFileName(libname.replace("lib", "/opt/qt4/lib/lib"));
//            lib.load();
//        }
        if (lib.isLoaded()) {
            qDebug() << "Has " << lib.fileName();
            if (qtmobilitylibs.contains(libname))
                ui->modules->setText(ui->modules->text() + " <i>" + libname.replace("lib", "") + "</i>");
            else
                ui->modules->setText(ui->modules->text() + " " + libname.replace("lib", ""));
            presentqtlibs << libname;
        }
    }
    QSystemInfo si;
    QString mobilityver = si.version((QSystemInfo::Version)4);
    if (mobilityver.isEmpty() || mobilityver == "Not Available")
    {
        ui->mobver->setText(ui->mobver->text() + "1.0.x");
    }
    else
    {
        ui->mobver->setText(ui->mobver->text() + si.version((QSystemInfo::Version)4));
    }
    ui->osver->setText(ui->osver->text() + si.version(QSystemInfo::Os) + " / "  + si.version(QSystemInfo::Firmware));
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
    ui->path->setText(ui->path->text() + " " + QLibraryInfo::location(QLibraryInfo::LibrariesPath) + "(lib), " + QLibraryInfo::location(QLibraryInfo::PluginsPath) + "(plugin), " + QLibraryInfo::location((QLibraryInfo::LibraryLocation)11) + "(import)" );
    // QLibraryInfo::ImportsPath is 11
    QList<QByteArray> sif = QImageReader::supportedImageFormats ();
    foreach (QString fmtstr, sif)
    {
        ui->image->setText(ui->image->text() + fmtstr + ", ");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
