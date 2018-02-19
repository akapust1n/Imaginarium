#include "Match.h"

Match::Match():
    maxSize(2)
{

}

Match::Match(int _maxSize):
    maxSize(_maxSize)
{

}

bool Match::isFull() const
{
    return true;
}

void Match::addPlayer(PlayerSP player)
{
    players.push_back(player);
}



int Match::getMaxSize() const
{
    return maxSize;
}

std::vector<PlayerSP> &Match::getPlayers()
{
    return players;
}
