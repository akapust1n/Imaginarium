#ifndef MATCH_H
#define MATCH_H
#include <Player.h>
#include <vector>
#include "CardHolder.h"

class Match
{
public:

    Match();
    Match(int _maxSize, CardHolder &cardHolder);
    bool isFull() const;
    void addPlayer(PlayerSP player);

    int getMaxSize() const;

    std::vector<PlayerSP> getPlayers() const; //TODO: оптимизировать по памяти

    int getDeckSize() const;

    int getMaster() const;
    void setMaster(int value);
     std::vector<CardHolder::Card> getHandByPlayer(int id);

private:
    std::vector<PlayerSP> players;
    const int maxSize;
    int master;
    std::vector<CardHolder::Card> deck;


};

#endif // MATCH_H
