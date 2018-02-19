#ifndef MATCH_H
#define MATCH_H
#include <vector>

class Match
{
public:
    Match();
    Match(int _maxSize);
    bool isFull() const;
    void addPlayer(/*params*/);
private:
    const int maxSize ;
};

#endif // MATCH_H
