// List with context menu project template
/*
 * ListModel.h
 *
 *  Created on: 17 Apr 2012
 *      Author: fvacek@rim.com
 */

#ifndef MyListModel_HPP_
#define MyListModel_HPP_

#include <QObject>
#include <QString>
#include <QVariant>
#include <QMetaType>
#include <bb/cascades/QListDataModel>

/*!
 * @brief Mutable list model implementation
 */
class MyListModel : public bb::cascades::QVariantListDataModel
{
    Q_OBJECT
public:
    /*!
     * @brief Convenience method for loading data from JSON file.
     *
     * @param file_name  file to load
     */
    Q_INVOKABLE void load(const QString& file_name);
    /*!
     * @brief Convenience method to read the model data.
     *
     * @param ix  index of the list item
     * @param fld_name  name of data field
     */
    Q_INVOKABLE QVariant value(int ix, const QString &fld_name);
    /*!
     * @brief Convenience method to set the model data.
     *
     * @param ix  index of the list item
     * @param fld_name  name of data field
     * @param val  new value
     */
    Q_INVOKABLE void setValue(int ix, const QString &fld_name, const QVariant &val);
public:
    MyListModel(QObject* parent = 0);
    virtual ~MyListModel();
};


#endif /* MyListModel_HPP_ */
