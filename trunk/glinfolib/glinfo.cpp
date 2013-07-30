#include "glinfo.h"
#include <QStringList>

#ifdef QT_OPENGL_LIB
#include <QGLFormat>
#endif

#include <QApplication>

QList<QPair<QString, QString> > GLInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "OpenGL"));
    QString value = "";
#ifdef QT_OPENGL_LIB
#ifdef Q_OS_BLACKBERRY
    info.append(QPair<QString,QString>("OpenGL support", "N/A (Cascades is incompatible with QtOpenGL)"));
    // ... and this shouldn't be hardcoded, except the BB10 Qt SIGSEGVs if we call hasOpenGL
#else
    if (QGLFormat::hasOpenGL()) {
        int flags = QGLFormat::openGLVersionFlags ();
        if (flags & QGLFormat::OpenGL_Version_4_0) value += "OpenGL 4.0";
        else if (flags & QGLFormat::OpenGL_Version_3_3) value += "OpenGL 3.3";
        else if (flags & QGLFormat::OpenGL_Version_3_2) value += "OpenGL 3.2";
        else if (flags & QGLFormat::OpenGL_Version_3_1) value += "OpenGL 3.1";
        else if (flags & QGLFormat::OpenGL_Version_3_0) value += "OpenGL 3.0";
        else if (flags & QGLFormat::OpenGL_Version_2_1) value += "OpenGL 2.1";
        else if (flags & QGLFormat::OpenGL_Version_2_0) value += "OpenGL 2.0";
        else if (flags & QGLFormat::OpenGL_Version_1_5) value += "OpenGL 1.5";
        else if (flags & QGLFormat::OpenGL_Version_1_4) value += "OpenGL 1.4";
        else if (flags & QGLFormat::OpenGL_Version_1_3) value += "OpenGL 1.3";
        else if (flags & QGLFormat::OpenGL_Version_1_2) value += "OpenGL 1.2";
        else if (flags & QGLFormat::OpenGL_Version_1_1) value += "OpenGL 1.1";
        if (flags & QGLFormat::OpenGL_ES_CommonLite_Version_1_0) value += " OpenGL ES 1.0 Common Lite";
        else if (flags & QGLFormat::OpenGL_ES_Common_Version_1_0) value += " OpenGL ES 1.0 Common";
        else if (flags & QGLFormat::OpenGL_ES_CommonLite_Version_1_1) value += " OpenGL ES 1.1 Common Lite";
        else if (flags & QGLFormat::OpenGL_ES_Common_Version_1_1) value += " OpenGL ES 1.1 Common";
        else if (flags & QGLFormat::OpenGL_ES_Version_2_0) value += " OpenGL ES 2.0";
    } else {
        value = "No";
    }
    info.append(QPair<QString,QString>("OpenGL support", "YES"));
    info.append(QPair<QString,QString>("OpenGL version", value));
#endif
#endif

    return info;
}


#ifdef _MSC_VER
QString GLInfoQString()
{
    QStringList qsl;
    typedef QPair<QString, QString> StringPair;
    QList<StringPair> info = GLInfo();
    foreach (StringPair pair, info)
    {
       qsl << pair.first + "##PAIRSEPARATOR##" + pair.second;
    }
    return qsl.join("##LINESEPARATOR##");
}
#endif

