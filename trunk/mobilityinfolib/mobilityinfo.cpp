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

    QStringList valuelist;
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

    info.append(QPair<QString,QString>("Hardware features", valuelist.join(", ")));
    info.append(QPair<QString,QString>("Available languages", qsi.availableLanguages().join(", ")));

    return info;
}
