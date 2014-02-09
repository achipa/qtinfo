#ifndef INFOLOADER_H
#define INFOLOADER_H

#include <QThread>
#include <QPair>
#include <QTextStream>
#include <QStringList>


class InfoLoader : public QThread
{
    Q_OBJECT
public:
    explicit InfoLoader(QObject *parent = 0);

signals:
    void newInfoAvailable(QString str);
    void progressChange(int percent);

public slots:

public:
    void run();
    QString resultAsHTML() { return html.replace("__ROWTEMPLATE__", "").replace("__SECTIONTEMPLATE__", ""); }
    QString resultAsText() { return text; }
    QList<QPair<QString, QString> > resultAsRawpairs() { return rawpairs; }

    bool isLoaded(QString library) { return installedlibs.contains(library); }

    int divineMobilityVersion();
    static QString loadLib(QString libname);
    static QString lastPathHit; // hack - these two are static public to speed up loadLib. Real solution coming soon TM
    static QString lastVersionHit;

private:
    QString html;
    QString text;
    QString rowstr;
    QString sectionstr;
    QTextStream out;
    QStringList installedlibs;
    QString Qt4LibPath;
    QString Qt5LibPath;
    QList<QPair<QString, QString> > rawpairs;
    void loadInfo(QString key, QString libname, QString libfile, const char* infofunc); // pvt because of out
    bool loadValues(QString library, QString defaultKey, const char* function); // pvt because of out, used by loadInfo
    void addToTemplate(QString key, QString value);
    void addToTemplate(QList<QPair<QString, QString> > list);
};

#endif // INFOLOADER_H
