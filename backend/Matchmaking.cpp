#include "Matchmaking.h"
#include "iostream"

Matchmaking::Matchmaking()
{
}

void Matchmaking::findMath(crow::websocket::connection* conn)
{
    std::lock_guard<std::mutex> guard(find);
   // players.push_back(player);

    if (matches[matches.size() - 1].isFull())
        matches.emplace_back();
}

void Matchmaking::addPlayer(crow::websocket::connection* conn)
{
    Player pl{conn};
    players.insert({conn,pl});
}
