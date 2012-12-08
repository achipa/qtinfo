#include "bb10infolib.h"

#include <bb/platform/PlatformInfo>
#include <bb/device/HardwareInfo>
#include <bb/MemoryInfo>
#include <bb/device/DisplayInfo>
#include <bb/device/CellularNetworkInfo>
#include <bb/device/CellularRadioInfo>
#include <bb/device/SimCardInfo>
#include <QStringList>


QList<QPair<QString, QString> > bb10Info()
{
    QList<QPair<QString, QString> > info;
    QStringList valuelist;
    QString value;

//    hmm, segfaults on my desktop 1.2
//    QSystemDeviceInfo qsdei;
//    info.append(QPair<QString,QString>("Device", QString("%0 %1 (%2)").arg(qsdei.manufacturer()).arg(qsdei.model()).arg(qsdei.productName())));

//    QSystemInfo si;
//    value = si.version(QSystemInfo::Os) + " / "  + si.version(QSystemInfo::Firmware);
//    info.append(QPair<QString,QString>("OS / Firmware", value));

    bb::platform::PlatformInfo pi;
    info.append(QPair<QString,QString>("OS / Firmware", "BlackBerry10 " + pi.osVersion()));

    info.append(QPair<QString,QString>("section", "BB10 Device Info"));

    bb::MemoryInfo mi;
    info.append(QPair<QString,QString>("Total memory", QString::number(mi.totalDeviceMemory() / 1024 / 1024) + " MB"));

    bb::device::HardwareInfo hi;

    if (!hi.pin().isEmpty()) info.append(QPair<QString,QString>("PIN", hi.pin()));
    if (!hi.serialNumber().isEmpty()) info.append(QPair<QString,QString>("Serial Number", hi.serialNumber()));
    if (!hi.imei().isEmpty()) info.append(QPair<QString,QString>("IMEI", hi.imei()));
    if (!hi.meid().isEmpty()) info.append(QPair<QString,QString>("MEID", hi.meid()));
    if (!hi.hardwareId().isEmpty()) info.append(QPair<QString,QString>("Hardware ID", hi.hardwareId()));
    if (!hi.deviceName().isEmpty()) info.append(QPair<QString,QString>("Device Name", hi.deviceName()));
    if (!hi.property("modelName").toString().isEmpty()) info.append(QPair<QString,QString>("Model Name", hi.property("modelName").toString()));
    if (!hi.property("modelNumber").toString().isEmpty()) info.append(QPair<QString,QString>("Model Number", hi.property("modelNumber").toString()));
//    info.append(QPair<QString,QString>("Keyboard", hi.isPhysicalKeyboardDevice() ? "Yes" : "No" ));

    QList<int> dids;
    dids << bb::device::DisplayInfo::primaryDisplayId() << bb::device::DisplayInfo::secondaryDisplayId();
    foreach (int displayId, dids ) {
        bb::device::DisplayInfo *di = new bb::device::DisplayInfo(displayId,0);
        if (di->isValid())
            info.append(QPair<QString,QString>(QString("Screen (%0)").arg(di->displayName()), QString("%0x%1, %2").arg(di->pixelSize().width()).arg(di->pixelSize().height()).arg(di->isDetachable() ? (di->isAttached() ? "Attached" : "Off") : "")));
    }

    bb::device::CellularNetworkInfo cni;
    bb::device::SimCardInfo sci;
    info.append(QPair<QString,QString>("SIM country", QString("Home: %0, Current: %1").arg(sci.mobileCountryCode()).arg(cni.mobileCountryCode())));
    info.append(QPair<QString,QString>("SIM network", QString("Home: %0, Current: %1").arg(sci.mobileNetworkCode()).arg(cni.mobileNetworkCode())));

    bb::device::CellularRadioInfo cri;
    valuelist.clear();
    if (cri.technologies() & 0x01) valuelist << "GSM";
    if (cri.technologies() & 0x02) valuelist << "UMTS";
    if (cri.technologies() & 0x04) valuelist << "CDMA2000 1xRTT";
    if (cri.technologies() & 0x08) valuelist << "CDMA2000 1xEV-DO";
    if (cri.technologies() & 0x10) valuelist << "LTE";
    info.append(QPair<QString,QString>("Cellular technologies", valuelist.join(", ")));


    valuelist.clear();
    if (cri.services() & 0x01) valuelist << "Emergency calls";
    if (cri.services() & 0x02) valuelist << "Voice";
    if (cri.services() & 0x04) valuelist << "911 callback/locator";
    if (cri.services() & 0x100) valuelist << "Data transfer";
    if (cri.services() & 0x400) valuelist << "Simultaneous Voice+Data";
    if (cri.services() & 0x1000) valuelist << "GPRS data";
    if (cri.services() & 0x2000) valuelist << "EDGE data";
    if (cri.services() & 0x4000) valuelist << "UMTS data";
    if (cri.services() & 0x8000) valuelist << "HSPA data";
    if (cri.services() & 0x10000) valuelist << "HSPA+ data";
    if (cri.services() & 0x20000) valuelist << "CDMA 1x data";
    if (cri.services() & 0x40000) valuelist << "EV-DO release 0 data";
    if (cri.services() & 0x80000) valuelist << "EV-DO revision A data";
    if (cri.services() & 0x100000) valuelist << "eHRPD data";
    if (cri.services() & 0x200000) valuelist << "LTE data";
    info.append(QPair<QString,QString>("Cellular services", valuelist.join(", ")));

    return info;
}
