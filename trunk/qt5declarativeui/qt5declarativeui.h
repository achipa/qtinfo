#ifndef QT5DECLARATIVEUI_H
#define QT5DECLARATIVEUI_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>
//#include <QObject>

extern "C" {
QWidget* declarativeUI(QList<QPair<QString, QString> >, QObject* mainWindow );
//QObject* declarativeUI(QList<QPair<QString, QString> >, QObject* mainWindow );
bool isQmlUiAvailable();
bool checkQml(QLatin1String qml);
}
#endif
