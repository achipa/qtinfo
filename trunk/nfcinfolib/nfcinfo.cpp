#include "nfcinfo.h"
#include <QStringList>
#include <QNearFieldManager>

QList<QPair<QString, QString> > nfcInfo()
{
    QList<QPair<QString, QString> > info;

    QStringList valuelist;
    QNearFieldManager nfcmgr;
    info.append(QPair<QString,QString>("section", "NFC"));
//    info.append(QPair<QString,QString>("Host / Domain", QHostInfo::localHostName() + " / " + QHostInfo::localDomainName()));
    info.append(QPair<QString,QString>("NFC support", (nfcmgr.isAvailable() ? "YES" : "NO")));
    if (nfcmgr.targetAccessModes().testFlag(QNearFieldManager::NdefReadTargetAccess))
        valuelist << "Read";
    if (nfcmgr.targetAccessModes().testFlag(QNearFieldManager::NdefWriteTargetAccess))
        valuelist << "Write";
    if (nfcmgr.targetAccessModes().testFlag(QNearFieldManager::TagTypeSpecificTargetAccess))
        valuelist << "Raw access";

    if (!valuelist.isEmpty())  info.append(QPair<QString,QString>("Capabilities", valuelist.join(", ")));

    return info;
}


#ifdef _MSC_VER
QString nfcInfoQString()
{
    QStringList qsl;
    typedef QPair<QString, QString> StringPair;
    QList<StringPair> info = nfcInfo();
    foreach (StringPair pair, info)
    {
       qsl << pair.first + "##PAIRSEPARATOR##" + pair.second;
    }
    return qsl.join("##LINESEPARATOR##");
}
#endif


