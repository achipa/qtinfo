#include "multimediainfo.h"
#ifdef QTM_VERSION
#include <qmobilityglobal.h>
#endif
#include <QStringList>
#if (QT_VERSION >= 0x050000)
#include <QAudio>
#include <QAudioDeviceInfo>
#else
#include <qaudio.h>
#include <qaudiodeviceinfo.h>
#endif
//#include <QAudioCaptureSource>
#if (QTM_VERSION >= 0x010100) || (QT_VERSION >= 0x050000)
#include <QCamera>
#endif
#include <qmediarecorder.h>
#include <QDebug>

//QT_USE_NAMESPACE

QList<QPair<QString, QString> > multimediaInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "MultimediaKit Audio"));

    QStringList devices;
    if (!QAudioDeviceInfo::availableDevices(QAudio::AudioInput).isEmpty()) {
        foreach(QAudioDeviceInfo adi, QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
            devices << adi.deviceName();
//            less useful as it initially seems as the codec for an audio device will always be pcm ?
//            info.append(QPair<QString,QString>(QString("Supported codecs (%0)").arg(adi.deviceName()), adi.supportedCodecs().join(",")));
        }
        info.append(QPair<QString,QString>("Input devices", devices.join(",")));
    }

    devices.clear();
    if (!QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).isEmpty())
    {
        foreach(QAudioDeviceInfo adi, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
            devices << adi.deviceName();
//            info.append(QPair<QString,QString>(QString("Supported codecs (%0)").arg(adi.deviceName()), adi.supportedCodecs().join(",")));
        }
        info.append(QPair<QString,QString>("Output devices", devices.join(",")));
    }

#if (QTM_VERSION >= 0x010100) || (QT_VERSION >= 0x050000)

    // "real" audio codecs are actually visible under the QMediaRecorder, so we'll check that under the video section

//    if (1) {
//        QAudioCaptureSource* audioSource = new QAudioCaptureSource;
//        QMediaRecorder audiomediarec(audioSource);
//        info.append(QPair<QString,QString>("Supported inputs", QStringList(audioSource->audioInputs()).join(",").replace("audio/","")));
//        info.append(QPair<QString,QString>("Default input codecs", audioSource->defaultAudioInput()));

    if (!QCamera::availableDevices().isEmpty()) {
//        info.append(QPair<QString,QString>("Supported codecs", audiomediarec.supportedAudioCodecs().join(",").replace("audio/","")));
        QCamera audiocam(QCamera::availableDevices().at(0));
        QMediaRecorder audiomediarec(&audiocam);

        info.append(QPair<QString,QString>("Supported codecs", audiomediarec.supportedAudioCodecs().join(",").replace("audio/","")));
        info.append(QPair<QString,QString>("section", "MultimediaKit Video"));
        foreach(QByteArray camname, QCamera::availableDevices()) {
            devices <<  QCamera::deviceDescription(camname);
            QCamera cam(camname);
            QMediaRecorder mediarec(&cam);
            QStringList values;

            foreach(QString container, mediarec.supportedContainers()){
                values << container;
            }
            if (!values.isEmpty())
                info.append(QPair<QString,QString>(QString("Containers (%0)").arg(QString(camname)), values.join(", ")));
            values.clear();

            if (!mediarec.supportedVideoCodecs().isEmpty()) {
                info.append(QPair<QString,QString>(QString("Supported codecs (%0)").arg(QString(camname)), mediarec.supportedVideoCodecs().join(",").replace("video/","")));
                foreach (QString codecstr, mediarec.supportedVideoCodecs()) {
                    QVideoEncoderSettings ves;
                    ves.setCodec(codecstr);
                    mediarec.setEncodingSettings(QAudioEncoderSettings(), ves); //, "avi"); // cludge. How to pick the "best" container ?
                    qDebug() << codecstr << mediarec.supportedFrameRates().length() << mediarec.supportedResolutions().length() ;

                    foreach(double rate, mediarec.supportedFrameRates()){
                        values << QString::number(rate);
                    }
                    if (!values.isEmpty())
                        info.append(QPair<QString,QString>(QString("Frame rates (%0)").arg(codecstr), values.join(", ")));
                    values.clear();

                    foreach(QSize s, mediarec.supportedResolutions()){
                        values << QString("%0 x %1").arg(s.width()).arg(s.height());
                    }
                    if (!values.isEmpty())
                        info.append(QPair<QString,QString>(QString("Resolutions (%0)").arg(codecstr), values.join(", ")));

                }
            }
        }
    } else {
        // add empty section just for completeness' sake
        info.append(QPair<QString,QString>("Supported codecs", "N/A")); // for the audio block we started above
        info.append(QPair<QString,QString>("section", "MultimediaKit Video"));
        info.append(QPair<QString,QString>("Supported codecs", "N/A"));
    }
    devices.clear();
#endif


    return info;
}


#ifdef _MSC_VER
QString multimediaInfoQString()
{
    QStringList qsl;
    typedef QPair<QString, QString> StringPair;
    QList<StringPair> info = multimediaInfo();
    foreach (StringPair pair, info)
    {
       qsl << pair.first + "##PAIRSEPARATOR##" + pair.second;
    }
    return qsl.join("##LINESEPARATOR##");
}
#endif
