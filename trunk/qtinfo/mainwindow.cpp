#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QLibraryInfo>
#include <QImageReader>
//#include <QSystemInfo>
#include <QLocale>
#include <QDebug>
//#include <QtWebKit>
//#include <QSslSocket>
#include <QTextStream>
#include <QDesktopServices>

//QTM_USE_NAMESPACE

#define ROWTEMPLATE "\n\
            <tr>\n\
              <td class=\"info\" width=\"100\"><strong>%0</strong></td>\n\
              <td>%1</td>\n\
            </tr>%2"

#define SECTIONTEMPLATE "\n\
    <h3>%0</h3>\n\
    <table cellpadding=\"5\" width=\"100%\">\n\
    __SECTIONROWTEMPLATE__\
    </table>\n\
    __SECTIONTEMPLATE__"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rowstr(ROWTEMPLATE),
    sectionstr(SECTIONTEMPLATE),
    out(&text)
{
    ui->setupUi(this);
    QFile htmlfile("://Qt_info.html");
    htmlfile.open(QIODevice::ReadOnly);
    html = htmlfile.readAll();
//    QString loadinghtml = html;
//    loadinghtml.replace("__SECTIONTEMPLATE__", "Please wait, reading data");
//    ui->webView->setHtml(loadinghtml,QUrl("qrc:/"));

    QString key = "Qt version";
    QString value = qVersion();
    QStringList valuelist;

    addToTemplate(key, value);

    key = "Qt build";
    value = QLibraryInfo::buildDate().toString()+ ", " + QLibraryInfo::buildKey()  + ", " + QLibraryInfo::licensee();
    addToTemplate(key, value);

    key = "Country";
    QLocale defaultlocale;
    value = QLocale::countryToString(defaultlocale.country());
    addToTemplate(key, value);

    key = "Language";
    value = QLocale::languageToString(defaultlocale.language()) + " (" + defaultlocale.name() + ")";
    addToTemplate(key, value);

    key = "Qt modules";
    value = "";
    QStringList qtlibs;
    QStringList qtmobilitylibs;

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
            value += libname.replace("lib", "") + " ";
            installedlibs << libname;
        }
    }
    addToTemplate(key, value);

//    loadInfo("Section Name", "Qt module name needed to load", "our local lib name", "our local extern C function name");

    loadInfo("Mobility", "QtSystemInfo", "./mobilityinfolib", "mobilityInfo");

    loadInfo("Qt Quick", "QtDeclarative", "./qtquickinfolib", "qtQuickInfo");

    loadInfo("MultimediaKit", "QtMultimediaKit", "./multimediainfolib", "multimediaInfo");

    loadInfo("OpenGL", "QtOpenGL", "./glinfolib", "GLInfo");

    loadInfo("WebKit", "QtWebKit", "./webkitinfolib", "webkitInfo");

    key = "Library path";
    value = QLibraryInfo::location(QLibraryInfo::LibrariesPath);
    addToTemplate(key, value);

    key = "Plugin path";
    value = QLibraryInfo::location(QLibraryInfo::PluginsPath);
    addToTemplate(key, value);

    key = "Import path";
    value = QLibraryInfo::location((QLibraryInfo::LibraryLocation)11); // QLibraryInfo::ImportsPath == 11, but not available in Qt4.6
    addToTemplate(key, value);

    key = "Image formats";
    valuelist.clear();
    QList<QByteArray> sif = QImageReader::supportedImageFormats ();
    foreach (QString fmtstr, sif)
    {
        valuelist << fmtstr;
    }
    addToTemplate(key, valuelist.join(", "));

    html = html.replace("__ROWTEMPLATE__", "");
    html = html.replace("__SECTIONTEMPLATE__", "");
    ui->textBrowser->setHtml(html);
//    ui->webView->setHtml(html,QUrl("qrc:/"));

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

bool MainWindow::loadValues(QString library, QString defaultKey, const char* function)
{
    QString key = defaultKey;
    typedef QList<QPair<QString, QString> > (*fn)();
    fn v = (fn) QLibrary::resolve(library, function);
    qDebug() << library <<  v;
    if (v) {
        QList<QPair<QString, QString> > list = v();
        addToTemplate(list);
    } else {
        addToTemplate(key, "Not Available");
        return false;
    }
    return true;
}

void MainWindow::addToTemplate(QString key, QString value)
{
    html = html.replace("__ROWTEMPLATE__", rowstr.arg(key).arg(value).arg("__ROWTEMPLATE__"));
    out << key << ": " << value << endl;
}

void MainWindow::addToTemplate(QList<QPair<QString, QString> > list)
{
    bool insection = false;
    for (int i = 0; i < list.length(); i++)
    {
        QPair<QString, QString> key = list.at(i);
        if (key.first == "section") {
            insection = true;
            html = html.replace("__SECTIONROWTEMPLATE__", ""); // close off any previous open sections we might have
            html = html.replace("__SECTIONTEMPLATE__", sectionstr.arg(key.second));
            out << endl << key.second << endl << endl;
        } else {
            if (insection) {
                html = html.replace("__SECTIONROWTEMPLATE__", rowstr.arg(key.first).arg(key.second).arg("__SECTIONROWTEMPLATE__"));
            } else {
                html = html.replace("__ROWTEMPLATE__", rowstr.arg(key.first).arg(key.second).arg("__ROWTEMPLATE__"));
            }
            out << " " << key.first << ": " << key.second << endl;
        }
    }
    html = html.replace("__SECTIONROWTEMPLATE__", ""); // close off any previous open sections we might have
    out << endl;
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
            if (lib.isLoaded()) break;
        }
    }
    bool loaded = lib.isLoaded();

    qDebug() << libname << "loaded " << loaded;

    if (loaded) {
        lib.unload();
        return lib.fileName();
    } else {
        return QString();
    }
}

void MainWindow::loadInfo(QString key, QString libname, QString libfile, const char* infofunc)
{
    if (installedlibs.contains(libname))
    {
        QString libname(loadLib(libfile)); // hmm... might need to include ./ as one of the possible prefixes ?

        if (!libname.isEmpty())
        {
            loadValues(libname, key, infofunc);
        }
    }
}
