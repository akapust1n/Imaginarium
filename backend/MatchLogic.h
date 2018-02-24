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



class MatchLogic {
public:
    MatchLogic();
    void findMath(crow::websocket::connection *conn, const std::string viewer_id);
    void removePlayer(crow::websocket::connection* conn);
    void masternTurn(crow::websocket::connection *conn, Parser::MasterTurn data);

private:
    void sendNotifyStartGame(Match &match);
private:
    std::unordered_map<crow::websocket::connection*, PlayerSP> players;
    std::vector<PlayerWP> queue;
    std::unordered_map<crow::websocket::connection*, Match> matches;

    std::mutex find;
    Parser parser;
    CardHolder cardHolder;

};

#endif // MATCHMAKING_H
