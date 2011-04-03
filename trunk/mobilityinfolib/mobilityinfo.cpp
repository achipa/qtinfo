#include "mobilityinfo.h"
#include <qmobilityglobal.h>
#include <QStringList>
#include <qsysteminfo.h>

QTM_USE_NAMESPACE

QList<QPair<QString, QString> > mobilityInfo()
{
    QSystemInfo si;
    QList<QPair<QString, QString> > info;
    QString value;

    value = si.version(QSystemInfo::Os) + " / "  + si.version(QSystemInfo::Firmware);
    info.append(QPair<QString,QString>("OS / Firmware", value));

    info.append(QPair<QString,QString>("section", "Mobility"));

    QString mobilityver = si.version((QSystemInfo::Version)4);
    if (mobilityver.isEmpty() || mobilityver == "Not Available")
        value = "1.0.x";
    else
        value = si.version((QSystemInfo::Version)4);
    info.append(QPair<QString,QString>("Version", value));

    return info;
}
