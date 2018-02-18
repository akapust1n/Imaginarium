#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include <mutex>
#include "Player.h"

class Matchmaking
{
public:
    Matchmaking();
    void findMath(Player player);
    void addPlayer(Player player);
private:
    std::vector<Match> matches;
    std::vector<Player> players;

    std::mutex find;

};

#endif // MATCHMAKING_H
