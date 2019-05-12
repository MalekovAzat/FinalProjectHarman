#ifndef DATAOBJECT_H
#define DATAOBJECT_H
#include<QObject>
#include <QAbstractItemModel>

class DataObject:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
public:
    DataObject(QObject* parent = nullptr);
    DataObject(int);

    int value(){
       return m_value;
    }

    void setValue(int newValue){
        m_value = newValue;
        emit valueChanged(m_value);
    }

signals:
    void valueChanged(int);
private:
    int m_value;
};


#endif // DATAOBJECT_H
