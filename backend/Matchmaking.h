#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include "Player.h"
#include <mutex>
#include <unordered_map>
#include <vector>
#include <Parser.h>
#include <CardHolder.h>
#include "MatchLogic.h"



class Matchmaking {
public:
    Matchmaking();
    void findMath(crow::websocket::connection *conn, const std::string viewer_id);
    void removePlayer(crow::websocket::connection* conn);

private:
    void sendNotifyStartGame(Match &match);
private:
    std::unordered_map<crow::websocket::connection*, PlayerSP> players;
    std::vector<PlayerWP> queue;
    std::unordered_map<crow::websocket::connection*, Match> matches;

    std::mutex find;
    Parser parser;
    CardHolder cardHolder;
    MatchLogic mLogick;

};

#endif // MATCHMAKING_H
