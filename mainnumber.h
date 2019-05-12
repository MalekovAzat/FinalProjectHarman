#ifndef MAINNUMBER_H
#define MAINNUMBER_H
#include<QObject>

class MainNumber:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
private:
    int m_value;
public:
    MainNumber(QObject* parent = nullptr);
    int value(){
        return m_value;
    }
    void setValue(int newVal){
        m_value = newVal;
        emit valueChanged();
    }

signals:
    void valueChanged();
};

#endif // MAINNUMBER_H
