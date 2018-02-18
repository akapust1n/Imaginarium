#include "Matchmaking.h"
#include "iostream"

Matchmaking::Matchmaking()
{

}

void Matchmaking::findMath(Player player)
{
    std::lock_guard<std::mutex> guard(find);
    players.push_back(player);

    if (matches[matches.size()-1].isFull())
        matches.emplace_back();

}

void Matchmaking::addPlayer(Player player)
{
   // char* c = static_cast<char*>(player.userdata());
    //std::cout<<c<<"__DATA"<<std::endl;
}
