#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include "Player.h"
#include <mutex>
#include <unordered_map>
#include <vector>
#include <Parser.h>




class Matchmaking {
public:
    Matchmaking();
    void findMath(crow::websocket::connection *conn, const std::string viewer_id);
    void removePlayer(crow::websocket::connection* conn);

private:
    void sendNotifyStartGame(std::vector<PlayerSP> &players);
private:
    std::unordered_map<crow::websocket::connection*, PlayerSP> players;
    std::vector<PlayerWP> queue;
    std::unordered_map<crow::websocket::connection*, Match> matches;

    std::mutex find;
    Parser parser;
private:
};

#endif // MATCHMAKING_H
