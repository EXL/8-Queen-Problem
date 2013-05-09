#ifndef LOGIC_H
#define LOGIC_H

#include <QVector>

extern int board[8][8];
extern QVector<QVector<QVector<int> > > boards; // 3D Arr O_O

class Logic
{
private:

    bool tryQueen(int, int);
public:
    Logic();
    void setQueen(int);
    ~Logic();
};

#endif // LOGIC_H
