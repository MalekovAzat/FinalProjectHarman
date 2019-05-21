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
        isVisibleRole,
        isSelectedRole,
    };

    ValueList(QObject* parent = nullptr);
    void addElem(int , bool, bool);
    int getValue(int);
    bool getIsSelected(int);
    bool getIsVisible(int);

    //замена значений в списках
    void replaceNumber(int num, int value);
    void replaceVisibleStatus(int num,bool status);
    void replaceSelectedStatus(int num, bool status);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index ,int role) const;
    virtual QHash <int, QByteArray> roleNames() const;

private:
    QList<int> m_data;// значения в сетке
    QList<bool> m_isVisibleInfo; //отображаются или нет
    QList<bool> m_isSelectedInfo;// выбран элемент или нет
};

#endif // VALUELIST_H
