#include "cellmanager.h"

CellManager::CellManager(QObject* parent,int cellCount):QObject (parent)
{
    for(int i =0; i< cellCount; i++){
        m_freeCellList.append(i);
    }
}

int CellManager::takeRandCell(){
    srand(QDateTime::currentDateTime().toTime_t());

    int randCellIndex;
    int numberInView;
    if(!m_freeCellList.isEmpty()){
        randCellIndex = rand() % m_freeCellList.size();
        numberInView = m_freeCellList.takeAt(randCellIndex);
        m_useCellSet.insert(numberInView);

        return numberInView;
    }
    return 0;
}

bool CellManager::freeIsEmpty(){
    return m_freeCellList.isEmpty();
}

bool CellManager::useIsEmpty(){
    return m_useCellSet.isEmpty();
}

bool CellManager::selectedIsEmpty(){
    return m_selectedCellSet.isEmpty();
}


void CellManager::printFreeCount(){
    QList<int>::iterator iter = m_freeCellList.begin();
    QList<int>::iterator end = m_freeCellList.end();
    while(iter != end){
        qDebug()<<*iter;
        iter++;
    }
}

void CellManager::insertToFree(int insValue){
    m_useCellSet.remove(insValue);
    m_freeCellList.append(insValue);
}

void CellManager::addToSelected(int addVal){
    if(m_useCellSet.contains(addVal)){
        m_selectedCellSet.insert(addVal);
    }
    else throw "hello";
}

void CellManager::removeFromSelected(int remVal){
    //вытащим конкретный элемент
    if(m_selectedCellSet.contains(remVal)){
        m_selectedCellSet.remove(remVal);
    }
}

int CellManager::getSelectedVal(){
    //просто вытащим один элемент
    int retValue = 0;
    QSet<int>::iterator begin = m_selectedCellSet.begin();
    if(!m_selectedCellSet.isEmpty()){
        retValue = *begin;
        m_selectedCellSet.remove(retValue);
    }

    return retValue;
}

void CellManager::initTmpList(){
    m_tmpList = m_useCellSet.toList();
}

int CellManager::getUniqueVal(){
    srand(QDateTime::currentDateTime().toTime_t());
    int randIndexinUseCellList;
    int tmpCellNum = -1;
    if(!m_tmpList.isEmpty()){
        randIndexinUseCellList = rand() % m_tmpList.size();
        tmpCellNum = m_tmpList.takeAt(randIndexinUseCellList);
    }

    return tmpCellNum;
}

void CellManager::clearTmpList(){
    m_tmpList.clear();
}
