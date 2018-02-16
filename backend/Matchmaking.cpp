#include "Matchmaking.h"

Matchmaking::Matchmaking()
{

}

void Matchmaking::findMath()
{
    std::lock_guard<std::mutex> guard(find);
    if (matches[matches.size()-1].isFull())
        matches.emplace_back();

}
