#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include <mutex>
#include "Player.h"
#include <unordered_set>


class Matchmaking
{
public:
    Matchmaking();
    void findMath(Player player);
    void addPlayer(crow::websocket::connection *conn);
private:
    std::vector<Match> matches;
    std::vector<Player> players;

    std::mutex find;

};

#endif // MATCHMAKING_H
