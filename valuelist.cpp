#include "valuelist.h"
#include<QDebug>
ValueList::ValueList(QObject* parent):QAbstractListModel (parent)
{

}

void ValueList::replaceNumber(int num, int value){

    m_data.replace(num,value);

    QModelIndex index1 = index(num, 0);
    QModelIndex index2 = index(num,0);

    emit dataChanged(index1,index2);
}

void ValueList::replaceVisibleStatus(int num, bool status){
    m_isVisibleInfo.replace(num, status);
    QModelIndex index1 = index(num,0);
    QModelIndex index2 = index(num,0);

    emit dataChanged(index1,index2);
}

void ValueList::replaceSelectedStatus(int num, bool status){
    m_isSelectedInfo.replace(num,status);
    QModelIndex index1 = index(num,0);
    QModelIndex index2 = index(num,0);

    emit dataChanged(index1,index2);
}


int ValueList::getValue(int index){
    return m_data.value(index);
}

bool ValueList::getIsVisible(int index){
    return m_isVisibleInfo.value(index);
}

bool ValueList::getIsSelected(int index){
    return m_isSelectedInfo.value(index);
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
        case isVisibleRole:
            return m_isVisibleInfo.at(index.row());
        case isSelectedRole:
            return m_isSelectedInfo.at(index.row());
        default:
            return QVariant();
    }
}

QHash <int, QByteArray> ValueList::roleNames() const{
    QHash<int,QByteArray> roles = QAbstractItemModel::roleNames();
    roles[valueRole] = "value";
    roles[isVisibleRole] = "isVisible";
    roles[isSelectedRole] = "isSelected";
    return roles;
}

void ValueList::addElem(int addVal,bool isVisible,bool isSelected){
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(addVal);
    m_isVisibleInfo.append(isVisible);
    m_isSelectedInfo.append(isSelected);
    endInsertRows();
}
