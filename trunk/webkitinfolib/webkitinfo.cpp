#include "webkitinfo.h"
#include <QtWebKit>
#include <QStringList>
#include <QSslSocket>

QList<QPair<QString, QString> > webkitInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "WebKit"));

    info.append(QPair<QString,QString>("WebKit version", qWebKitVersion()));
    info.append(QPair<QString,QString>("SSL support", (QSslSocket::supportsSsl() ? "YES" : "NO")));

    //TODO The QtWebKit version (such as 2.1.0 in Symbian), QTWEBKIT_VERSION is no good as it's compile time

    //TODO presence of the QtWebKit platform plugin would also be interesting.
    //  QtWebKit tries to load platformplugin.dll on startup, and if that is
    //  found, it will be used for certain platform-specific operations.

    //TODO get plugin list (flash, java, etc)

    QStringList valuelist;
    info.append(QPair<QString,QString>("section", "Networking"));
    foreach (QNetworkInterface qni, QNetworkInterface::allInterfaces () ) {
        if (!qni.addressEntries().isEmpty())
            info.append(QPair<QString,QString>(qni.name(), QString("%0 - %1").arg(qni.hardwareAddress()).arg(qni.addressEntries().at(0).ip().toString())));
        else
            info.append(QPair<QString,QString>(qni.name(), qni.hardwareAddress()));
    }

    // 4.7 functionality, for an eventual networkinfo plugin
    // QList<QNetworkConfiguration> QNetworkConfigurationManager::allConfigurations

    return info;
}
