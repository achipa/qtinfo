// List with context menu project template
#ifndef MainCascadesWindow_HPP_
#define MainCascadesWindow_HPP_

#include <QObject>

#include "infoloader.h"

namespace bb { namespace cascades { class Application; }}
namespace bb { namespace cascades { class QmlDocument; }}
namespace bb { namespace cascades { class AbstractPane; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class MainCascadesWindow : public QObject
{
    Q_OBJECT
public:
    MainCascadesWindow(bb::cascades::Application *app);
    virtual ~MainCascadesWindow() {}
public slots:
    void showUI();
    void updateProgress(int perc);
    void updateLoadScreen(QString str);
private:
    QObject *loadWidget(QString library, const char *function);
    bool callBoolFunction(QString library, const char *function);
    InfoLoader* infoloader;
    bb::cascades::QmlDocument *qml;
    bb::cascades::AbstractPane *root;
};

#endif /* MainCascadesWindow_HPP_ */
