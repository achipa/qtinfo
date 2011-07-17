#include "infoloader.h"

#include <QFile>
#include <QDebug>
#include <QLibrary>
#include <QLibraryInfo>
#include <QImageReader>
#include <QFontDatabase>
#include <QLocale>
#include <QTextBrowser>
#include <QApplication>

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

InfoLoader::InfoLoader(QObject *parent) :
    QThread(parent),
    rowstr(ROWTEMPLATE),
    sectionstr(SECTIONTEMPLATE),
    out(&text)
{
}

void InfoLoader::run()
{
    QFile htmlfile("://Qt_info.html");
    htmlfile.open(QIODevice::ReadOnly);
    html = htmlfile.readAll();
//    QString loadinghtml = html;
//    loadinghtml.replace("__SECTIONTEMPLATE__", "Please wait, reading data");
//    ui->webView->setHtml(loadinghtml,QUrl("qrc:/"));

    QString key = "Qt version";
    QString value = qVersion();
    QStringList valuelist;

    qDebug() << key << value ;

    addToTemplate(key, value);

    emit newInfoAvailable("Checking build date...");
    key = "Qt build";
    value = QLibraryInfo::buildDate().toString()+ ", " + QLibraryInfo::buildKey()  + ", " + QLibraryInfo::licensee();
    addToTemplate(key, value);

    emit newInfoAvailable("Checking country/language...");
    key = "Country";
    QLocale defaultlocale;
    value = QLocale::countryToString(defaultlocale.country());
    addToTemplate(key, value);

    key = "Language";
    value = QLocale::languageToString(defaultlocale.language()) + " (" + defaultlocale.name() + ")";
    addToTemplate(key, value);

    emit newInfoAvailable("Checking Qt modules...");
    key = "Qt modules";
    value = "";
    QStringList qtlibs;
    QStringList qtmobilitylibs;

    qtlibs << "Qt3Support";
    qtlibs << "QAxContainer";
    qtlibs << "QAxServer";
    qtlibs << "QtCLucene";
    qtlibs << "QtCore";
    qtlibs << "QtDBus";
    qtlibs << "QtDeclarative";           // 4.7
    qtlibs << "QtDesignerComponents";
    qtlibs << "QtDesigner";
    qtlibs << "QtGui";
    qtlibs << "QtHelp";
    qtlibs << "QtMultimedia";
    qtlibs << "QtMaemo5";                // 4.6
    qtlibs << "phonon";
    qtlibs << "QtNetwork";               // includes QtBearer starting w 4.7
    qtlibs << "QtOpenGL";
    qtlibs << "QtOpenVG";                // 4.6
    qtlibs << "QtScript";
    qtlibs << "QtScriptTools";
    qtlibs << "QtSql";
    qtlibs << "QtSvg";
    qtlibs << "QtTest";
    qtlibs << "QtUiTools";
    qtlibs << "QtWebKit";
    qtlibs << "QtXmlPatterns";
    qtlibs << "QtXml";

    qtmobilitylibs << "QtBearer";          // 1.0.x ONLY
    qtmobilitylibs << "QtConnectivity";    // 1.2
    qtmobilitylibs << "QtContacts";
    qtmobilitylibs << "QtFeedback";        // 1.1
    qtmobilitylibs << "QtGallery";         // 1.1
    qtmobilitylibs << "QtLocation";
    qtmobilitylibs << "QtMultimediaKit";
    qtmobilitylibs << "QtSensors";
    qtmobilitylibs << "QtServiceFramework";
    qtmobilitylibs << "QtSystemInfo";
    qtmobilitylibs << "QtOrganizer";       // 1.1
    qtmobilitylibs << "QtPublishSubscribe";
    qtmobilitylibs << "QtVersitOrganizer"; // 1.1
    qtmobilitylibs << "QtVersit";
    qtlibs.append(qtmobilitylibs);

    int progressTotalSteps = qtlibs.count() + 11; // 11 = number of loadInfos we're going to do later. #automateme
    int progressStep = 0;

    foreach(QString libname, qtlibs) {
        emit newInfoAvailable(QString("Locating %0...").arg(libname));
        QString libfilename = loadLib(libname);
        if (!libfilename.isEmpty()) {
            emit newInfoAvailable(QString("Found as %0 ").arg(libfilename));
            value += libname.replace("lib", "") + " ";
            installedlibs << libname;
        } else {
            emit newInfoAvailable(QString("Not found"));
        }
        emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));
    }
    addToTemplate(key, value);

    emit newInfoAvailable("Checking Qt Mobility version...");
    int mobver = divineMobilityVersion();
    QString libsuffix;
    if (mobver >= 0x010200) {
        libsuffix = "12";
    } else if (mobver >= 0x010100) {
        libsuffix = "11";
    }
    else // 1.0
    {
        libsuffix = "10";
    }

//    loadInfo("Section Name", "Qt module name needed to load", "our local lib name", "our local extern C function name");


    emit newInfoAvailable("Loading systeminfo...");
    loadInfo("Mobility", "QtSystemInfo", QString("mobilityinfolib%0").arg(libsuffix), "mobilityInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable(QString("Loading multimediakit (%0)...").arg(libsuffix));
    loadInfo("MultimediaKit", "QtMultimediaKit", QString("multimediainfolib%0").arg(libsuffix), "multimediaInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading declarative...");
    loadInfo("Qt Quick", "QtDeclarative", "qtquickinfolib", "qtQuickInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading OpenGL...");
    loadInfo("OpenGL", "QtOpenGL", "glinfolib", "GLInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading webkit...");
    loadInfo("WebKit", "QtWebKit", "webkitinfolib", "webkitInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading sql...");
    loadInfo("SQL", "QtSql", "sqlinfolib", "sqlInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Determining default paths...");
    key = "Library path";
    value = QLibraryInfo::location(QLibraryInfo::LibrariesPath);
    addToTemplate(key, value);
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    key = "Plugin path";
    value = QLibraryInfo::location(QLibraryInfo::PluginsPath);
    addToTemplate(key, value);
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    key = "Import path";
    value = QLibraryInfo::location((QLibraryInfo::LibraryLocation)11); // QLibraryInfo::ImportsPath == 11, but not available in Qt4.6
    addToTemplate(key, value);
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Determining image drivers...");
    key = "Image formats";
    valuelist.clear();
    QList<QByteArray> sif = QImageReader::supportedImageFormats ();
    foreach (QString fmtstr, sif)
    {
        valuelist << fmtstr;
    }
    addToTemplate(key, valuelist.join(", "));
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Determining system fonts...");
    QList<QPair<QString, QString> > list;
    list.append(QPair<QString,QString>("section", "Fonts"));
    QFontDatabase database;
    list.append(QPair<QString,QString>("Installed fonts", database.families().join(", ")));
    // database.pointSizes(family) // One day...
    valuelist.clear();
    foreach(QFontDatabase::WritingSystem ws, database.writingSystems()) {
        valuelist << QString("%0 (%1)").arg(QFontDatabase::writingSystemName(ws)).arg(QFontDatabase::writingSystemSample(ws));
    }
    list.append(QPair<QString,QString>("Writing systems", valuelist.join(", ")));
    valuelist.clear();
    foreach(int size, database.standardSizes()) {
        valuelist << QString("%0").arg(size);
    }
    list.append(QPair<QString,QString>("Standard sizes", valuelist.join(", ")));
    addToTemplate(list);
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));


}
bool InfoLoader::loadValues(QString library, QString defaultKey, const char* function)
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

void InfoLoader::addToTemplate(QString key, QString value)
{
    html = html.replace("__ROWTEMPLATE__", rowstr.arg(key).arg(value).arg("__ROWTEMPLATE__"));
    rawpairs.append(qMakePair(key, value));

    QTextBrowser tb;
    tb.setHtml(value);
    out << key << ": " << tb.toPlainText() << endl;
}

void InfoLoader::addToTemplate(QList<QPair<QString, QString> > list)
{
    bool insection = false;
    for (int i = 0; i < list.length(); i++)
    {
        QPair<QString, QString> key = list.at(i);
        rawpairs.append(key);
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

QString InfoLoader::loadLib(QString libname)
{
// very very dirty hack
// to sort out why when 4.6.x is installed loading QtBearer appears to hang the app
#ifdef Q_OS_SYMBIAN
    if(QString(qVersion()).startsWith("4.6") && libname=="QtBearer" )
        return QString("QtBearer");
#endif
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

void InfoLoader::loadInfo(QString key, QString libname, QString libfile, const char* infofunc)
{
    if (installedlibs.contains(libname))
    {
        QString libname(loadLib(qApp->applicationDirPath()+"/"+libfile)); // hmm... might need to include ./ as one of the possible prefixes ?

        if (!libname.isEmpty())
        {
            loadValues(libname, key, infofunc);
        }
    }
}

int InfoLoader::divineMobilityVersion()
{
    if (installedlibs.contains("QtConnectivity"))
        return 0x010200;
    if (installedlibs.contains("QtGallery"))
        return 0x010100;
#ifdef Q_WS_MAEMO_5
    // check if we might have the community edition installed somewhere
    if (!loadLib("/opt/qtm12/lib/libQtConnectivity").isEmpty())
        return 0x010200;
    if (!loadLib("/opt/qtm11/lib/libQtGallery").isEmpty())
        return 0x010100;
#endif
    if (installedlibs.contains("QtBearer")) // bearer is present ONLY in 1.0
        return 0x010000;

    return 0;
}
