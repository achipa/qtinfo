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
