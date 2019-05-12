#ifndef VALUELIST_H
#define VALUELIST_H

#include <QAbstractListModel>
#include<QModelIndex>
#include"dataobject.h"

class ValueList:public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        valueRole = Qt::UserRole + 1,
    };

    ValueList(QObject* parent = nullptr);
    void addElem(int );
    int getValue(int);
    void replace(int num, int value);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index ,int role) const;
    virtual QHash <int, QByteArray> roleNames() const;
    Q_INVOKABLE void add();

private:
    QList<int> m_data;
};

#endif // VALUELIST_H
