#ifndef MAINQQVIEW_H
#define MAINQQVIEW_H

#include "infoloader.h"
#include <QtQuick/QQuickView>

class MainQQView : QObject
{
Q_OBJECT
public:
    MainQQView(QQuickView *qqv);
public slots:
    void showUI();
    void updateProgress(int perc);
    void updateLoadScreen(QString str);
private:
    QQuickView *qqview;
    InfoLoader* infoloader;
};

#endif // MAINQQVIEW_H
