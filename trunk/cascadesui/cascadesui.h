// List with context menu project template
#ifndef QtInfo_HPP_
#define QtInfo_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class QtInfo : public QObject
{
    Q_OBJECT
public:
    QtInfo(bb::cascades::Application *app);
    virtual ~QtInfo() {}
};

#endif /* QtInfo_HPP_ */
