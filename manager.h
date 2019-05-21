#ifndef MANAGER_H
#define MANAGER_H
#include<QObject>
#include"valuelist.h"
#include<QList>
#include<QDebug>
#include<cstdlib>
#include <QDateTime>
#include <cellmanager.h>

class Manager:public QObject
{
    Q_OBJECT
    Q_PROPERTY(ValueList* cellList READ cellList NOTIFY cellListChanged)
    Q_PROPERTY(int cellCount READ cellCount WRITE setCellCount NOTIFY cellCountChanged)
    Q_PROPERTY(int maxAddVal READ maxAddVal WRITE setMaxAddVal NOTIFY maxAddValChanged)
    Q_PROPERTY(int minAddVal READ minAddVal WRITE setMinAddVal NOTIFY minAddValChanged)
    Q_PROPERTY(int addCellCount READ addCellCount WRITE setAddCellCount NOTIFY addCellCountChanged)

public:
    Manager(QObject* parent = nullptr);
    ValueList* cellList();
    int cellCount();

    int addCellCount();
    int maxAddVal();
    int minAddVal();

    void setCellCount(int );
    void setStartCellCount(int );

    void setMaxAddVal(int newVal);
    void setMinAddVal(int newVal);
    void setAddCellCount(int newVal);

signals:
    //конец игры
    void endGame();

    void startCellCountChanged(int);

    void signalRightAnswer();
    void maxAddValChanged(int);
    void minAddValChanged(int);
    void addCellCountChanged(int);

//    void changeValue(int number,int newValue);
    void changeMainValue(int newMainValue);
    void cellCountChanged(int );
    void cellListChanged();

//    void showCell(int cellNum);
//    void hideCell(int cellNum);

//    void changeStateSignal(int cellNum);
    //для таймера
    void restartTimer();
public slots:

    void cellClicked(int index);

    void zeroingSum();
    void slotRightAnsver();

    // начальные настройки для отображения всех элементов(возможно не нужно)
    void createStartCell();

    //функция которая срабатывает про событии таймера
    void changeGeneralState();

private:
    CellManager* p_cellManager;
    //модель для представления
    ValueList* p_cellList;
    //список свободных полей (заменить на множества)
    QSet<int > m_freeCellSet;
    QSet<int> m_useCellSet;

    //список индексов выбранных ячеек (неупорядоченный)
    QSet<int> m_selectedCellSet;

    //некоторые суммы на поле
//    QSet<int> m_valuesOnFieldSet;

    //общее кол-во ячеек на игровом поле
    int m_cellCount;

    //кол-во выбранных ячеек(возможно не нужно)
    int m_selectedCellCount;

    //сумма выбранных ячеек
    int m_selCellSum;
    //целевое число
    int m_mainValue;
    //кол-во ячек при каждом добавлении
    int m_addCellCount;
    //кол-во показываемых чисел на поле
    int m_visibleCellCount;

    //границы добавляемых значений
    int m_minAddValue;
    int m_maxAddValue;

    //завершение игры
    int showCellWithNewValue();
    int getSumFromRandomCells(int );
};

#endif // MANAGER_H
