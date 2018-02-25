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
    //Match (Match&& a);
    bool isFull() const;
    void addPlayer(PlayerSP player);

    int getMaxSize() const;

    std::vector<PlayerSP> getPlayers() const; //TODO: оптимизировать по памяти

    int getDeckSize() const;

    PlayerSP getMaster();
    void setMaster(std::string value);
    std::vector<CardHolder::Card> getHandByPlayer(int id);
    std::string getMasterNum() const;

    int getMasterCard() const;
    void setMasterCard(const int &value);
    bool dropCard(int cardId, PlayerSP player);

    int getDropedCards() const;

private:
    std::vector<PlayerSP> players;
    const int maxSize;
    std::string master;
    int masterCard;
    std::vector<CardHolder::Card> deck;
    int dropedCards;
    std::shared_ptr<std::mutex> dropMutex;
};
using MatchSP = std::shared_ptr<Match>;
#endif // MATCH_H
