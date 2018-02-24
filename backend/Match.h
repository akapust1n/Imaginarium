#ifndef MATCH_H
#define MATCH_H
#include "CardHolder.h"
#include <Player.h>
#include <vector>

class Match {
public:
    Match();
    Match(int _maxSize, CardHolder& cardHolder);
    bool isFull() const;
    void addPlayer(PlayerSP player);

    int getMaxSize() const;

    std::vector<PlayerSP> getPlayers() const; //TODO: оптимизировать по памяти

    int getDeckSize() const;

    PlayerSP getMaster();
    void setMaster(int value);
    std::vector<CardHolder::Card> getHandByPlayer(int id);
    int  getMasterNum() const;

    std::string getMasterCard() const;
    void setMasterCard(const std::string &value);

private:
    std::vector<PlayerSP> players;
    const int maxSize;
    int master;
    std::string masterCard;
    std::vector<CardHolder::Card> deck;
};

#endif // MATCH_H
