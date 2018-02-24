#ifndef MATCH_H
#define MATCH_H
#include "CardHolder.h"
#include <Player.h>
#include <vector>
#include <mutex>

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
    void setMaster(std::string value);
    std::vector<CardHolder::Card> getHandByPlayer(int id);
    std::string getMasterNum() const;

    std::string getMasterCard() const;
    void setMasterCard(const std::string &value);
    bool dropCard(std::string cardId, PlayerSP player);

    int getDropedCards() const;

private:
    std::vector<PlayerSP> players;
    const int maxSize;
    std::string master;
    std::string masterCard;
    std::vector<CardHolder::Card> deck;
    int dropedCards;
    std::mutex dropMutex;
};

#endif // MATCH_H
