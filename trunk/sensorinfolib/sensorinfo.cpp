#include "sensorinfo.h"
#include <QSensor>
#include <QStringList>

QList<QPair<QString, QString> > sensorInfo()
{
    QList<QPair<QString, QString> > info;

    QStringList valuelist;
    info.append(QPair<QString,QString>("section", "Sensors"));
//    info.append(QPair<QString,QString>("Hardware features", valuelist.join(", ")));

    valuelist.clear();
    foreach (QByteArray sensorname, QSensor::sensorTypes()) {
        valuelist << QString(sensorname);
    }
    if (!valuelist.isEmpty())
        info.append(QPair<QString,QString>("Sensors", valuelist.join(", ")));
    else
        info.append(QPair<QString,QString>("Sensors", "API present, no physical sensors detected"));

    return info;
}


#ifdef _MSC_VER
QString sensorInfoQString()
{
    QStringList qsl;
    typedef QPair<QString, QString> StringPair;
    QList<StringPair> info = sensorInfo();
    foreach (StringPair pair, info)
    {
       qsl << pair.first + "##PAIRSEPARATOR##" + pair.second;
    }
    return qsl.join("##LINESEPARATOR##");
}
#endif


