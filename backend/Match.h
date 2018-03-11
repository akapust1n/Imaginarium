#ifndef MATCH_H
#define MATCH_H
#include "CardHolder.h"
#include <Player.h>
#include <vector>
#include <mutex>

class Match {
public:
    enum Phase{
        BeforeStart = 0,
        NewTurn,
        MasterTurn,
        PlayerTurn,
        PlayerGuess
    };
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
    bool guessCard(int cardId, PlayerSP player);
    bool nextTurn(PlayerSP player);

    int getDropedCards() const;
    bool prepareTurn();

    Phase getPhase() const;
    void setPhase(const Phase &value);

    //afk section
    void lock();
    void unlock();
    bool masterAfk() ;

private:
    std::vector<PlayerSP> players;
    const int maxSize;
    std::string master;
    int masterNum;
    std::vector<CardHolder::Card> deck;
    int dropedCards;
    int guessCards;
    int masterCard;
    int nextTurnCounter;
    std::shared_ptr<std::mutex> mutex;
    Phase phase;

};
using MatchSP = std::shared_ptr<Match>;
#endif // MATCH_H
