#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include "Player.h"
#include <mutex>
#include <unordered_map>

class Matchmaking {
public:
    Matchmaking();
    void findMath(crow::websocket::connection *conn);
    void addPlayer(crow::websocket::connection* conn);

private:
    std::vector<Match> matches;
    std::unordered_map<crow::websocket::connection*, Player> players;

    std::mutex find;

private:
};

#endif // MATCHMAKING_H
