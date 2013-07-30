#include "sqlinfo.h"
#include <QSqlDatabase>
#include <QStringList>

QList<QPair<QString, QString> > sqlInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "SQL"));

    info.append(QPair<QString,QString>("Drivers", QSqlDatabase::drivers().join(", ")));

    return info;
}

#ifdef _MSC_VER
QString sqlInfoQString()
{
    QStringList qsl;
    typedef QPair<QString, QString> StringPair;
    QList<StringPair> info = sqlInfo();
    foreach (StringPair pair, info)
    {
       qsl << pair.first + "##PAIRSEPARATOR##" + pair.second;
    }
    return qsl.join("##LINESEPARATOR##");
}
#endif
