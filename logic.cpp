#include "logic.h"

#include <QDebug> // for dbg

#define SIZE 8

int board[8][8];
QVector<QVector<QVector<int> > > boards;

Logic::Logic()
{
    /* Empty constructor */
}

bool Logic::tryQueen(int a, int b)
{
    for(int i = 0; i < a; ++i)
    {
        if(board[i][b])
        {
            return false;
        }
    }
    for(int i = 1; i <= a && b-i >= 0; ++i)
    {
        if(board[a-i][b-i])
        {
            return false;
        }
    }
    for(int i = 1; i <= a && b+i < SIZE; i++)
    {
        if(board[a-i][b+i])
        {
            return false;
        }
    }
    return true;
}

void Logic::setQueen(int a)
{
    if(a == SIZE)
    {
        QVector<QVector<int> > temp2;
        for(int a = 0; a < SIZE; ++a)
        {
            QVector<int> temp;
            for(int b = 0; b < SIZE; ++b)
            {
                temp.push_back((board[a][b]) ? 1 : 0);
            }
            temp2.push_back(temp);
        }
        boards.push_back(temp2);
    }
    for(int i = 0; i < SIZE; ++i)
    {
        if(tryQueen(a, i))
        {
            board[a][i] = 1;
            setQueen(a+1);
            board[a][i] = 0;
        }
    }
}

Logic::~Logic()
{
    /* Empty destructor */
}

