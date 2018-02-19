#ifndef MATCH_H
#define MATCH_H
#include <Player.h>
#include <vector>


class Match
{
public:
    Match();
    Match(int _maxSize); //for future
    bool isFull() const;
    void addPlayer(PlayerSP player);

    int getMaxSize() const;

    std::vector<PlayerSP> &getPlayers();

private:
    std::vector<PlayerSP> players;
    const int maxSize;
};

#endif // MATCH_H
