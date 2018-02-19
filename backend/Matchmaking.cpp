#include "Matchmaking.h"
#include "iostream"

Matchmaking::Matchmaking()
{
}

void Matchmaking::findMath(crow::websocket::connection* conn)
{
    std::lock_guard<std::mutex> guard(find);
   // players.push_back(player);

}

void Matchmaking::addPlayer(crow::websocket::connection* conn)
{

    players.insert({conn,std::make_shared<Player>(conn)});
}
