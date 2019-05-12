#include "dataobject.h"

DataObject::DataObject(QObject* parent):QObject (parent){

}

DataObject::DataObject(int newVal):QObject(),m_value(newVal)
{

}
