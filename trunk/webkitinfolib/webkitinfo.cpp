#include "webkitinfo.h"
#include <QtWebKit>
#include <QStringList>

QList<QPair<QString, QString> > webkitInfo()
{
    QList<QPair<QString, QString> > info;
    info.append(QPair<QString,QString>("section", "WebKit"));

    info.append(QPair<QString,QString>("WebKit version", qWebKitVersion()));
    info.append(QPair<QString,QString>("SSL support", (QSslSocket::supportsSsl() ? "YES" : "NO")));

    return info;
}
