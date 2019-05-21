#include "manager.h"

Manager::Manager(QObject* parent):QObject (parent),p_cellList(new ValueList)
{

    m_selCellSum = 0;
    m_addCellCount = 5;
    m_visibleCellCount = 0;

    //создание элементов при задании занчения cellCount
    QObject::connect(this,&Manager::cellCountChanged,this,&Manager::createStartCell);
    QObject::connect(this,&Manager::signalRightAnswer, this, &Manager::slotRightAnsver);
}

ValueList* Manager::cellList(){
    return p_cellList;
}

int Manager::addCellCount(){
    return m_addCellCount;
}

void Manager::setAddCellCount(int newVal){
    m_addCellCount = newVal;
    emit addCellCountChanged(m_addCellCount);
}

int Manager::cellCount(){
    return m_cellCount;
}

void Manager::setMinAddVal(int newVal){
    m_minAddValue = newVal;
    emit minAddValChanged(m_minAddValue);
}

void Manager::setMaxAddVal(int newVal){
    m_maxAddValue = newVal;
    emit maxAddValChanged(m_maxAddValue);
}

int Manager::maxAddVal(){
    return m_maxAddValue;
}

int Manager::minAddVal(){
    return m_minAddValue;
}

void Manager::setCellCount(int newCount){
    m_cellCount = newCount;
    emit cellCountChanged( m_cellCount);
}

void Manager::createStartCell(){
    for (int i = 0;i< m_cellCount;i++) {
        p_cellList->addElem(i,false,false);
    }

    p_cellManager = new CellManager(nullptr, m_cellCount);
}

void Manager::slotRightAnsver(){
    /* Что нужно сделать:
     *  обнулить счетчик суммы
     *  перетащить ячейки из используемых в свободные
     *  скрыть элементы
     *  пустить сигнал о перезапуске таймера
    */
    m_selCellSum = 0;
    int selectedCellIndex;

    while(!p_cellManager->selectedIsEmpty()){
        selectedCellIndex = p_cellManager->getSelectedVal();
        p_cellManager->insertToFree(selectedCellIndex);
        m_visibleCellCount--;
        p_cellList->replaceVisibleStatus(selectedCellIndex,false);
        p_cellList->replaceSelectedStatus(selectedCellIndex,false);
    }
    emit restartTimer();
}

void Manager::changeGeneralState(){
    /*общая идея:
     * есть такие значения:
     * - максимальное кол-во элементов которое может участвует в сумме (1)
     * - кол-во элементов которое действительно участвует в сумме (2)
     * - кол-во элементов с игрового поля которые будут учавствовать в сумме (3)
     * - кол-во элементов которое есть сейчас на поле (4)
     * - кол-во новых элементов которые учавствуют в сумме(5)
     *  - кол-во элементов без внесения их в сумму суммы(пустышки) (6)
     * Как их делим:
     *  Случайное число из диапазона от 2-х до (1) ->
     *      записываем результат в (2).
     *  Генерируем случайное число из диапазона от 0 до min( (4) (2) ) ->
     *      записываем результат в (3).
     *  В (5) записываем разницу между (2) и (3) ->
     *      это кол-во элементов которые нужно отобразить и придумать для них числа.
     *  В (6) запишем разницу между (1) и (5) ->
     *      это кол-во элементов для добавления на поле но не в сумму.
     * Как формируется новое значение для целевого числа:
     *  Все числа геренируются от и до какого то диапазона
     *  сначала в сумму добавляем числа которые уже есть на игровом поле,
     *  после генерируюется (5) чисел и так же добавляются в сумму
     *  получившееся значение становится новым целевым числом которое и
     *  отобразится на экране
     * Поялвение элементов на поле:
     *  добавляем (5) элементов на поле,
     * а так же добавляем (1) минус (5) элементов(фейковых) на поле
     */
    srand(QDateTime::currentDateTime().toTime_t());

    int countElemInSum;//(2)
    int countElemInSumFromGameField;//(3)
    int countNewElemForSum;//(5)
    int countNewElem;//(6)

    countElemInSum = rand() % (m_addCellCount - 1) + 2;
    int min = ( m_visibleCellCount < countElemInSum ? m_visibleCellCount : countElemInSum);
    countElemInSumFromGameField = (min > 0) ? rand() % min : 0;
    countNewElemForSum = countElemInSum - countElemInSumFromGameField;
    countNewElem = m_addCellCount - countNewElemForSum;
    int newMainSum = 0;
    newMainSum += getSumFromRandomCells(countElemInSumFromGameField);

    for(int i =0; i < countNewElemForSum;i++){
        newMainSum+=showCellWithNewValue();
        if(p_cellManager->freeIsEmpty()){
            //прямо как в мстителях))))
            emit endGame();
        }
        m_visibleCellCount++;
    }

    for(int i = 0; i < countNewElem;i++){
        showCellWithNewValue();
        if(p_cellManager->freeIsEmpty()){
            //прямо как в мстителях))))
            emit endGame();
        }
        m_visibleCellCount++;
    }
    m_mainValue = newMainSum;

    emit changeMainValue(newMainSum);
}


int Manager::getSumFromRandomCells(int count){
    int sum = 0;
    int curCount = 0;
    int tmpCellNum;

    if(!p_cellManager->useIsEmpty()){
        p_cellManager->initTmpList();

        while(curCount < count){
            tmpCellNum = p_cellManager->getUniqueVal();
            sum += p_cellList->getValue(tmpCellNum);
            curCount++;
        }
        p_cellManager->clearTmpList();
    }

    return sum;
}

void Manager::zeroingSum(){
    m_selCellSum = 0;
    int selectedCellIndex;
    while(!p_cellManager->selectedIsEmpty()){
        selectedCellIndex = p_cellManager->getSelectedVal();
        p_cellList->replaceSelectedStatus(selectedCellIndex,false);
        p_cellList->replaceVisibleStatus(selectedCellIndex,false);
    }
}

int Manager::showCellWithNewValue(){
    srand(QDateTime::currentDateTime().toTime_t() * rand());
    int numberInView;
    int newValue;

    newValue = rand() % (m_maxAddValue - m_minAddValue) + m_minAddValue;
    if(!p_cellManager->freeIsEmpty()){
        numberInView = p_cellManager->takeRandCell();
        p_cellList->replaceNumber(numberInView, newValue);//!+
        p_cellList->replaceVisibleStatus(numberInView,true);
    }

    return newValue;
}

void Manager::cellClicked(int index){
    if(p_cellList->getIsSelected(index)){
        m_selCellSum  -= p_cellList->getValue(index);
        p_cellManager->removeFromSelected(index);
    }
    else{
        m_selCellSum += p_cellList->getValue(index);
        p_cellManager->addToSelected(index);
    }
    //изменение положения ячейки

    if(p_cellList->getIsSelected(index)){
        p_cellList->replaceSelectedStatus(index,false);
    }
    else{
        p_cellList->replaceSelectedStatus(index,true);
    }

    qDebug()<<m_selCellSum<<"|"<<m_mainValue;

    if(m_selCellSum == m_mainValue){
        emit signalRightAnswer();
    }
}
