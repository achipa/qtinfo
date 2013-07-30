#ifndef DECLARATIVEUI_H
#define DECLARATIVEUI_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

extern "C" {
QWidget* declarativeUI(QList<QPair<QString, QString> >, QObject* mainWindow );
bool isQmlUiAvailable();
bool checkQml(QLatin1String qml);
}
#endif
