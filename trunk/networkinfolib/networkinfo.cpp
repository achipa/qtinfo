#include "networkinfo.h"
#include <QStringList>
#include <QSslSocket>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QNetworkConfigurationManager>

QList<QPair<QString, QString> > networkInfo()
{
    QList<QPair<QString, QString> > info;

    QStringList valuelist;
    info.append(QPair<QString,QString>("section", "Networking"));
    info.append(QPair<QString,QString>("Host / Domain", QHostInfo::localHostName() + " / " + QHostInfo::localDomainName()));
    info.append(QPair<QString,QString>("SSL support", (QSslSocket::supportsSsl() ? "YES" : "NO")));
    foreach (QNetworkInterface qni, QNetworkInterface::allInterfaces () ) {
        if (!qni.addressEntries().isEmpty())
            info.append(QPair<QString,QString>(qni.name(), QString("%0 - %1").arg(qni.hardwareAddress()).arg(qni.addressEntries().at(0).ip().toString())));
        else
            info.append(QPair<QString,QString>(qni.name(), qni.hardwareAddress()));
    }

    QNetworkConfigurationManager qncm;
    QList<QNetworkConfiguration> networkcfglist = qncm.allConfigurations();
    foreach (QNetworkConfiguration networkcfg, networkcfglist) {
        info.append(QPair<QString,QString>("Configuration", networkcfg.name() + " (" + networkcfg.bearerTypeName() + ")"));
    }

    // 4.7 functionality, for an eventual networkinfo plugin
    // QList<QNetworkConfiguration> QNetworkConfigurationManager::allConfigurations

    return info;
}


#ifdef _MSC_VER
QString networkInfoQString()
{
    QStringList qsl;
    typedef QPair<QString, QString> StringPair;
    QList<StringPair> info = networkInfo();
    foreach (StringPair pair, info)
    {
       qsl << pair.first + "##PAIRSEPARATOR##" + pair.second;
    }
    return qsl.join("##LINESEPARATOR##");
}
#endif


