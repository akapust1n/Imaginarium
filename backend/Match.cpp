#include "Match.h"

Match::Match():
    maxSize(6)
{

}

Match::Match(int _maxSize):
    maxSize(_maxSize)
{

}

bool Match::isFull() const
{
    return players.size()==maxSize;
}

void Match::addPlayer()
{

}
