#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include "MatchLogic.h"
#include "Player.h"
#include <CardHolder.h>
#include <Parser.h>
#include <mutex>
#include <unordered_map>
#include <vector>

class MatchLogic {
public:
    MatchLogic();
    void findMath(crow::websocket::connection* conn, const std::string viewer_id);
    void removePlayer(crow::websocket::connection* conn);
    void masternTurn(crow::websocket::connection* conn, Parser::MasterTurn data);
    void dropCard(crow::websocket::connection* conn, int cardId);
    void guessCard(crow::websocket::connection* conn, int cardId);
    void nextTurn(crow::websocket::connection* conn);

private:
    void sendNotifyStartGame(MatchSP &match);
    bool checkConn(crow::websocket::connection* conn, Match::Phase phase);
private:
    std::unordered_map<crow::websocket::connection*, PlayerSP> players;
    std::vector<PlayerWP> queue;
    std::unordered_map<crow::websocket::connection*, MatchSP> matches;

    std::mutex find;
    Parser parser;
    CardHolder cardHolder;
};

#endif // MATCHMAKING_H
