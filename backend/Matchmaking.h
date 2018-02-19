#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include "Player.h"
#include <mutex>
#include <unordered_map>
#include <queue>

using PlayerSP = std::shared_ptr<Player>;
using PlayerWP = std::weak_ptr<Player>;


class Matchmaking {
public:
    Matchmaking();
    void findMath(crow::websocket::connection *conn);
    void addPlayer(crow::websocket::connection* conn);

private:
    std::unordered_map<crow::websocket::connection*, PlayerSP> players;
    std::queue<PlayerWP> queue;
    std::unordered_map<crow::websocket::connection*, Match> matches;

    std::mutex find;

private:
};

#endif // MATCHMAKING_H
