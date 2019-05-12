#ifndef CELLMANAGER_H
#define CELLMANAGER_H
#include<QSet>
#include<QObject>
#include<cstdLib>
#include<QDateTime>
#include<QDebug>

class CellManager : public QObject
{
    Q_OBJECT

private:
    QList<int> m_freeCellList;
    QSet<int> m_useCellSet;
    QSet<int> m_selectedCellSet;

    QList<int> m_tmpList;
public:
    CellManager(QObject* parent = nullptr,int cellCount = 0);
    int takeRandCell();//Получение свободной ячейки
    int getRandCell();
    void insertToFree(int);//возврат в свободную ячейку
    void addToSelected(int);
    void removeFromSelected(int);
    int getSelectedVal();
    bool freeIsEmpty();
    bool selectedIsEmpty();
    void printFreeCount();
    //методы дял получения уникального набора значений
    void initTmpList();
    int getUniqueVal();
    void clearTmpList();

signals:
    void freeCellEmpty();
};

#endif // CELLMANAGER_H
