#ifndef MATCH_H
#define MATCH_H
#include "Player.h"
#include <vector>

class Match
{
public:
    Match();
    Match(int _maxSize);
    bool isFull() const;
    void addPlayer(/*params*/);
private:
    std::vector<Player> players;
    const int maxSize ;
};

#endif // MATCH_H
