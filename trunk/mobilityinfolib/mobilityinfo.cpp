#include "mobilityinfo.h"
#include <QStringList>

#ifndef Q_OS_BLACKBERRY
#include <qmobilityglobal.h>
#else
#include <QtMobility/qmobilityglobal.h>
#endif

#ifdef QTM_SYSTEMINFO
#include <QSystemInfo>
#include <QSystemDisplayInfo>
#include <QSystemStorageInfo>
#include <QSystemNetworkInfo>
#include <QSystemDeviceInfo>
#include <QDesktopWidget>
#endif

#ifdef QTM_SENSORS
#include <QSensor>
#endif

// #include <QtServiceFramework/QServiceManager>

QTM_USE_NAMESPACE

QList<QPair<QString, QString> > mobilityInfo()
{
    QList<QPair<QString, QString> > info;
    QString value;
    QStringList valuelist;

    info.append(QPair<QString,QString>("section", "Mobility"));

//    hmm, segfaults on my desktop 1.2
//    QSystemDeviceInfo qsdei;
//    info.append(QPair<QString,QString>("Device", QString("%0 %1 (%2)").arg(qsdei.manufacturer()).arg(qsdei.model()).arg(qsdei.productName())));

#ifdef QTM_SYSTEMINFO
    QSystemInfo si;
    value = si.version(QSystemInfo::Os) + " / "  + si.version(QSystemInfo::Firmware);
    info.append(QPair<QString,QString>("OS / Firmware", value));

    QDesktopWidget qdw;
    QSystemDisplayInfo qsdi;
    for (int i=0; i<qdw.screenCount() ; i++) {
        QRect sg = qdw.screenGeometry(i);
// DPI info needs mobility 1.2
//        info.append(QPair<QString,QString>(QString("Screen (%0)").arg(i), QString("%0x%1, %2 DPI, %3b").arg(sg.width()).arg(sg.height()).arg(qsdi.getDPIWidth(i)).arg(qsdi.colorDepth(i))));
        info.append(QPair<QString,QString>(QString("Screen (%0)").arg(i), QString("%0x%1, %2b").arg(sg.width()).arg(sg.height()).arg(qsdi.colorDepth(i))));
    }
//    info.append(QPair<QString,QString>("section", "Mobility"));

    QString mobilityver = si.version((QSystemInfo::Version)4);
    if (mobilityver.isEmpty() || mobilityver == "Not Available")
        value = "1.0.x";
    else
        value = si.version((QSystemInfo::Version)4);
    info.append(QPair<QString,QString>("Version", value));

    QSystemInfo qsi;
    if (qsi.hasFeatureSupported(QSystemInfo::BluetoothFeature)) valuelist << "Bluetooth";
    if (qsi.hasFeatureSupported(QSystemInfo::CameraFeature)) valuelist << "Camera";
    if (qsi.hasFeatureSupported(QSystemInfo::FmradioFeature)) valuelist << "FM Radio";
    if (qsi.hasFeatureSupported(QSystemInfo::IrFeature)) valuelist << "Infrared";
    if (qsi.hasFeatureSupported(QSystemInfo::LedFeature)) valuelist << "LED";
    if (qsi.hasFeatureSupported(QSystemInfo::MemcardFeature)) valuelist << "Memory card";
    if (qsi.hasFeatureSupported(QSystemInfo::UsbFeature)) valuelist << "USB";
    if (qsi.hasFeatureSupported(QSystemInfo::VibFeature)) valuelist << "Vibra";
    if (qsi.hasFeatureSupported(QSystemInfo::WlanFeature)) valuelist << "WiFi";
    if (qsi.hasFeatureSupported(QSystemInfo::SimFeature)) valuelist << "SIM";
    if (qsi.hasFeatureSupported(QSystemInfo::LocationFeature)) valuelist << "GPS";
    if (qsi.hasFeatureSupported(QSystemInfo::VideoOutFeature)) valuelist << "Video out";
    if (qsi.hasFeatureSupported(QSystemInfo::HapticsFeature)) valuelist << "Haptics";
    if (qsi.hasFeatureSupported((QSystemInfo::Feature)13)) valuelist << "FM Transmitter"; // added in 1.2 so no enum

//    QServiceManager qsm;
//    info.append(QPair<QString,QString>("Services", qsm.findServices().join(", ")));

    // 1.2 API, though exists in undocumented (and segfaulting) form in 1.1, too
//    foreach (QString drive, QSystemStorageInfo::logicalDrives()) {
//        QSystemStorageInfo qssi;
//        info.append(QPair<QString,QString>(QString("Storage (%0)").arg(drive), QString("%0MB (%1 free)").arg(qssi.totalDiskSpace(drive) / (1 << 20) ).arg(qssi.availableDiskSpace(drive) / (1 << 20) )));
//    }

    QSystemNetworkInfo qsni;
    if (!qsni.homeMobileCountryCode().isEmpty()) {
        info.append(QPair<QString,QString>("SIM country", QString("Home: %0, Current: %1").arg(qsni.homeMobileCountryCode()).arg(qsni.currentMobileCountryCode())));
        info.append(QPair<QString,QString>("SIM network", QString("Home: %0, Current: %1").arg(qsni.homeMobileNetworkCode()).arg(qsni.currentMobileNetworkCode())));
    }

#else // No one in their right mind would link us against the wrong version, right?
    info.append(QPair<QString,QString>("Version", QString("Compiled with ") + QTM_VERSION_STR ));
#endif

#ifdef QTM_SENSORS
    info.append(QPair<QString,QString>("Hardware features", valuelist.join(", ")));

    valuelist.clear();
    foreach (QByteArray sensorname, QSensor::sensorTypes()) {
        valuelist << QString(sensorname);
    }
    if (!valuelist.isEmpty())  info.append(QPair<QString,QString>("Sensors", valuelist.join(", ")));
#endif

    return info;
}
