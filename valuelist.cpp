#include "valuelist.h"
#include<QDebug>
ValueList::ValueList(QObject* parent):QAbstractListModel (parent)
{

}

//возможно очень плохой способ
void ValueList::replace(int num, int value){
//    qDebug()<<"replace index"<< num<< " size "<< m_data.size();
    m_data.replace(num,value);

    QModelIndex index1 = index(num, 0);
    QModelIndex index2 = index(num,0);
//    qDebug()<<"replace Done";

    emit dataChanged(index1,index2);
}

int ValueList::getValue(int index){
    return m_data.value(index);
}

int ValueList::rowCount(const QModelIndex &parent) const{
    if(parent.isValid()){
        return 0;
    }
    return m_data.size();
}

QVariant ValueList::data(const QModelIndex &index, int role)const {
    if(!index.isValid()){
        return QVariant();
    }
    switch (role) {
        case valueRole:
            return m_data.at(index.row());
        default:
            return QVariant();
    }
}

QHash <int, QByteArray> ValueList::roleNames() const{
    QHash<int,QByteArray> roles = QAbstractItemModel::roleNames();
    roles[valueRole] = "value";

    return roles;
}

void ValueList::add(){
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(10);
    endInsertRows();
}

void ValueList::addElem(int addVal){
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(addVal);
    endInsertRows();
}
