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
#include <QDir>

#ifdef Q_OS_BLACKBERRY
#include <bb/cascades/Application>
#endif

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

QString InfoLoader::lastPathHit = ""; // statics are evil. (pre-)C++11 C++ makes them heinous
QString InfoLoader::lastVersionHit = "";

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

#if QT_VERSION >= 0x050000
    addToTemplate("Platform", qApp->platformName());
#endif
/*
#ifdef Q_OS_ANDROID
    // This does not work. WHY?!
    qApp->addLibraryPath("/data/data/org.kde.necessitas.ministro/files/dl/0/stable/lib");
    qApp->addLibraryPath("/data/local/tmp/qt/lib/lib");
    qApp->addLibraryPath("/data/data/eu.licentia.necessitas.ministro/files/dl/0/stable/lib");
#endif
*/
    emit newInfoAvailable("Checking build date...");
    key = "Qt build";
    value = QLibraryInfo::buildDate().toString()+ ", ";
#if QT_VERSION < 0x050000
    value += QLibraryInfo::buildKey() + ", ";
#endif
    value += QLibraryInfo::licensee();
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

    qtlibs << "Qt5AndroidExtras";         // 5.2
    qtlibs << "Qt5Bluetooth";             // 5.2
    qtlibs << "Qt5CLucene";
    qtlibs << "Qt5Concurrent";
    qtlibs << "Qt5Core";
    qtlibs << "Qt5Declarative";
    qtlibs << "Qt5DBus";
    qtlibs << "Qt5Designer";
    qtlibs << "Qt5DesignerComponents";
    qtlibs << "Qt5Gui";
    qtlibs << "Qt5Help";
    qtlibs << "Qt5MacExtras";             // 5.2
    qtlibs << "Qt5Multimedia";
    qtlibs << "Qt5MultimediaQuick_p";
    qtlibs << "Qt5MultimediaWidgets";
    qtlibs << "Qt5Network";
    qtlibs << "Qt5Nfc";                   // 5.2
    qtlibs << "Qt5OpenGL";
    qtlibs << "Qt5Positioning";           // 5.2
    qtlibs << "Qt5PrintSupport";
    qtlibs << "Qt5Qml";
    qtlibs << "Qt5Quick";
    qtlibs << "Qt5QuickParticles";
    qtlibs << "Qt5QuickTest";
    qtlibs << "Qt5SerialPort";            // 5.1
    qtlibs << "Qt5Script";
    qtlibs << "Qt5ScriptTools";
    qtlibs << "Qt5Sensors";               // 5.1
    qtlibs << "Qt5Sql";
    qtlibs << "Qt5Svg";
    qtlibs << "Qt5Test";
    qtlibs << "Qt5V8";
    qtlibs << "Qt5WebKit";
    qtlibs << "Qt5WebKitWidgets";
    qtlibs << "Qt5Widgets";
    qtlibs << "Qt5WinExtras";             // 5.2
    qtlibs << "Qt5X11Extras";             // 5.1
    qtlibs << "Qt5Xml";
    qtlibs << "Qt5XmlPatterns";


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

    int progressTotalSteps = qtlibs.count() + 14; // 14 = number of loadInfos we're going to do later. #automateme
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

#ifdef Q_OS_BLACKBERRY
    emit newInfoAvailable("Loading bb10info...");
    loadInfo("BB10", "QtCore", "bb10infolib", "bb10Info");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));
#endif

    emit newInfoAvailable("Loading systeminfo...");
    loadInfo("Mobility", "QtSystemInfo", QString("mobilityinfolib%0").arg(libsuffix), "mobilityInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable(QString("Loading multimediakit (%0)...").arg(libsuffix));
    loadInfo("MultimediaKit", "QtMultimediaKit", QString("multimediainfolib%0").arg(libsuffix), "multimediaInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading Multimedia...");
    loadInfo("Multimedia", "Qt5Multimedia", "multimediainfolib", "multimediaInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading declarative...");
    loadInfo("Qt Quick", "QtDeclarative", "qtquickinfolib", "qtQuickInfo");
    loadInfo("Qt Quick", "Qt5Declarative", "qtquickinfolib", "qtQuickInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading qml...");
    loadInfo("Qt Quick2", "Qt5Qml", "qtquick2infolib", "qtQuick2Info");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading OpenGL...");
    loadInfo("OpenGL", "QtOpenGL", "glinfolib", "GLInfo");
    loadInfo("OpenGL", "Qt5OpenGL", "glinfolib", "GLInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading sensors...");
    loadInfo("Sensors", "Qt5Sensors", "sensorinfolib", "sensorInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading nfc...");
    loadInfo("NFC", "Qt5Nfc", "nfcinfolib", "nfcInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading network...");
    loadInfo("Network", "QtNetwork", "networkinfolib", "networkInfo");
    loadInfo("Network", "Qt5Network", "networkinfolib", "networkInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading webkit...");
    loadInfo("WebKit", "QtWebKit", "webkitinfolib", "webkitInfo");
    loadInfo("WebKit", "Qt5WebKit", "webkitinfolib", "webkitInfo");
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));

    emit newInfoAvailable("Loading sql...");
    loadInfo("SQL", "QtSql", "sqlinfolib", "sqlInfo");
    loadInfo("SQL", "Qt5Sql", "sqlinfolib", "sqlInfo");
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
    qApp->processEvents();

    emit newInfoAvailable("Determining system fonts...");
    QList<QPair<QString, QString> > list;
    list.append(QPair<QString,QString>("section", "Fonts"));
#ifdef Q_OS_BLACKBERRY
    list.append(QPair<QString,QString>("Installed fonts", "N/A (Cascades incompatible with QFontDatabase)"));
    list.append(QPair<QString,QString>("Writing systems", "N/A (Cascades incompatible with QFontDatabase)"));
    list.append(QPair<QString,QString>("Standard sizes", "N/A (Cascades incompatible with QFontDatabase)"));
    // and all this shouldn't be hardcoded except BB10 Qt SIGSEGVs if we create a QFontDatabase object
#else
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
#endif
    addToTemplate(list);
    emit progressChange((int)(++progressStep*100.0/(float)progressTotalSteps));


}
bool InfoLoader::loadValues(QString library, QString defaultKey, const char* function)
{
    QString key = defaultKey;
    typedef QList<QPair<QString, QString> > (*fn)();
    QLibrary lib(library);
    fn v = (fn) lib.resolve(function);
//    fn v = (fn) QLibrary::resolve(library, function);
    qDebug() << library <<  v;
    QList<QPair<QString, QString> > list;
    if (v) {
        list = v();
        addToTemplate(list);


    } else { // one more try for the overly pedantic MSVC
        qDebug() << lib.errorString() << endl;
        typedef QString (*fnstr)();
        fnstr strfunc = (fnstr) lib.resolve(QString(QString(function)+"QString").toUtf8());
        if (strfunc) {
            QString str = strfunc();
            QStringList lines = str.split("##LINESEPARATOR##");
            foreach (QString line, lines) {
                QStringList pairstring = line.split("##PAIRSEPARATOR##");
                if (pairstring.size() < 2) continue;
                QPair<QString, QString> pair(pairstring[0], pairstring[1]);
                list.append(pair);
            }
            addToTemplate(list);



        } else {
            qDebug() << lib.errorString() << endl;
            addToTemplate(key, "Not Available");
            return false;
        }
    }
    return true;
}

void InfoLoader::addToTemplate(QString key, QString value)
{
    html = html.replace("__ROWTEMPLATE__", rowstr.arg(key).arg(value).arg("__ROWTEMPLATE__"));
    rawpairs.append(qMakePair(key, value));

#if !defined(Q_OS_BLACKBERRY) && !defined(Q_OS_SAILFISH)
    QTextBrowser tb;
    tb.setHtml(value);
    out << key << ": " << tb.toPlainText() << endl;
#else
    out << key << ": " << value << endl;
#endif
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
    QTextStream sout(stdout);
    sout << lib.errorString() << endl;
//    qDebug() << lib.errorString();
    QString pathHit = "";
    QString versionHit = "";

    if (!lib.load()){
        QStringList prefixlist = QStringList() << "" << "lib" << qApp->applicationDirPath() + "/" << qApp->applicationDirPath() + "/lib" ;
#ifdef Q_OS_ANDROID
       prefixlist << "/data/data/org.kde.necessitas.ministro/files/dl/0/stable/lib/lib";
       prefixlist << "/data/local/tmp/qt/lib/lib";
       prefixlist << "/data/data/eu.licentia.necessitas.ministro/files/dl/0/stable/lib";
#endif
        if (!InfoLoader::lastPathHit.isEmpty()) {
            prefixlist.removeAll(InfoLoader::lastPathHit);
            prefixlist.prepend(InfoLoader::lastPathHit);
        }
        qDebug() << qApp->libraryPaths().join(',');
        foreach (QString prefix, prefixlist) {
            pathHit = prefix;

            foreach(QString version, QStringList() << "" << "1" << "2" << "3" << "4" << "5") {
                versionHit = version;

                lib.setFileNameAndVersion(prefix + libname, version.toInt()); // Linux naming
                sout << "try " << prefix << libname << "outcome: " << lib.errorString() << endl;
                if (lib.load()) break;
                else
                   qDebug() << "try " << prefix << libname << "outcome: " << lib.errorString();

                lib.setFileName(prefix + libname + version); // Windows Symbian Android naming
                sout << "try " << prefix << libname << version << "outcome: " << lib.errorString() << endl;
                qDebug() << "try " << prefix << libname << version << "outcome: " << lib.errorString();
                if (lib.load()) break;
                else
                   qDebug() << "try " << prefix << libname << "outcome: " << lib.errorString();

            }
            if (lib.isLoaded()) break;
        }
    }
    bool loaded = lib.isLoaded();

    qDebug() << libname << "loaded " << loaded;

    if (loaded) {
        lastPathHit = pathHit;
        lastVersionHit = versionHit;
        qDebug() << "Found at " << pathHit + versionHit;
        if (lastPathHit != pathHit && !pathHit.isEmpty()) {
            qDebug () << "Found in non-default path, adding to library path";
            qApp->addLibraryPath(pathHit);
        }

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_SAILFISH)
        // Android:
        // for some Android reason, if it's not originally linked to the .so location and you randomly dlopen, the lib-paths will not respected
        // thus after trying to load the Qt* libs we KEEP them in memory so when the infolibs get dlopen'd it doesn't bork
        // For background, see: https://code.google.com/p/android/issues/detail?id=34416 and https://github.com/ikonst/android-dl

        // Sailfish:
        // The 5.1 Qt in there seems quite crashy - esp the qtquick module doesn't seem to like being unloaded and reloaded
        // (or just conflicts somehow with qtdeclarative) and segfauls, so not unloading helps

        lib.unload();
#endif
        return lib.fileName();
    } else {
    sout << lib.errorString() << endl;
        qDebug() << "ERR: " << lib.errorString();
        return QString();
    }
}

void InfoLoader::loadInfo(QString key, QString libname, QString libfile, const char* infofunc)
{
    if (installedlibs.contains(libname))
    {
#ifdef Q_OS_BLACKBERRY
        QString libname(loadLib("app/native/lib"+libfile+".so")); // hmm... might need to include ./ as one of the possible prefixes ?
#elif defined(Q_OS_SAILFISH)
        // due to Harbour policies...
        QString libname(loadLib(QString() + TARGETPATH+"lib"+libfile+".so")); // hmm... might need to include ./ as one of the possible prefixes ?
#elif defined(Q_OS_ANDROID)
        QString libname(loadLib(libfile)); // hmm... might need to include ./ as one of the possible prefixes ?
#else
        QString libname(loadLib(qApp->applicationDirPath()+"/"+libfile)); // hmm... might need to include ./ as one of the possible prefixes ?
#endif

        if (!libname.isEmpty())
        {
            loadValues(libname, key, infofunc);
        }
    }
}

int InfoLoader::divineMobilityVersion()
{
#ifdef Q_OS_BLACKBERRY
    // BB is unable to tell which version it has :/
    return 0x010200;
#endif
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
