#ifndef MATCHMAKING_H
#define MATCHMAKING_H
#include "Match.h"
#include <mutex>

class Matchmaking
{
public:
    Matchmaking();
    void findMath(/*params*/);
private:
    std::vector<Match> matches;
    std::mutex find;

};

#endif // MATCHMAKING_H
