// List with context menu project template
#ifndef Qtinfo_HPP_
#define Qtinfo_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class Qtinfo : public QObject
{
    Q_OBJECT
public:
    Qtinfo(bb::cascades::Application *app);
    virtual ~Qtinfo() {}
};

#endif /* Qtinfo_HPP_ */
