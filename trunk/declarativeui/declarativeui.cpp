#include "declarativeui.h"
#include <QtDeclarative>
#include <QStringList>
#include <QVariant>
#include <QDebug>

QStringList keys;
QStringList values;
/* QList<QObject*> dataList;

class QataObject : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString key READ key WRITE setKey)
    Q_PROPERTY(QString value READ value WRITE setValue)
    Q_PROPERTY(QString section READ section WRITE setSection)
public:
    QataObject () {}
    QataObject (QString k, QString v, QString s) : m_key(k), m_value(v), m_section(s) {}
    ~QataObject () {}
    QString key() { return m_key; }
    QString value() { return m_value; }
    QString section() { return m_section; }
public slots:
    void setKey(QString k) { m_key = k; }
    void setValue(QString k) { m_value = k; }
    void setSection(QString k) { m_section = k; }
private:
    QString m_key, m_value, m_section;
};
*/
QWidget* declarativeUI(QList<QPair<QString, QString> > infoPairs, QObject* mainWindow)
{
    QDeclarativeView* view = new QDeclarativeView();
    QString section;
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    keys.clear();
    values.clear();

    for (int i = 0; i < infoPairs.length(); i++)
    {
        QPair<QString, QString> infoPair = infoPairs.at(i);

        if (infoPair.first == "Section") {
            section = infoPair.second;
        } else {
//            dataList.append(new QataObject(infoPair.first, infoPair.second, section));
        }
        keys.append(infoPair.first);
        values.append(infoPair.second);
    }

    view->rootContext()->setContextProperty("MainWindow", mainWindow);
    view->rootContext()->setContextProperty("keyModel", QVariant::fromValue(keys));
    view->rootContext()->setContextProperty("valueModel", QVariant::fromValue(values));
//    view->rootContext()->setContextProperty("sectionModel", QVariant::fromValue(dataList));

#ifdef Q_OS_SYMBIAN
    view->setSource(QUrl::fromLocalFile("qml_symbian/main.qml"));
#else
    view->setSource(QUrl::fromLocalFile(qApp->applicationDirPath() + "/../qml/main.qml"));
#endif

    return view;
}

bool checkQml(QLatin1String qml)
{

    QDeclarativeEngine engine;
    QDeclarativeComponent component(&engine);
    component.setData(qml.latin1(), QUrl());
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem *>(component.create());

    if (item) {
        // Components plugin seems to be available
        return true;
    }
    else {
        // Something is wrong, at least output errors
        qDebug() << component.errors();
    }
    return false;
}

bool isQmlUiAvailable()
{
    if (checkQml(QLatin1String("import QtQuick 1.0\nimport com.nokia.symbian 1.0\nimport com.nokia.extras 1.0\nWindow {}")))
            return true;
    if (checkQml(QLatin1String("import QtQuick 1.0\nimport com.nokia.meego 1.0\nWindow {}")))
            return true;
    if (checkQml(QLatin1String("import QtQuick 1.0\nimport com.nokia.meego 1.1\nWindow {}")))
            return true;
    if (checkQml(QLatin1String("import QtQuick 1.1\nimport Sailfish.Silica 1.0\nApplicationWindow {}")))
            return true;
    return false;
}

