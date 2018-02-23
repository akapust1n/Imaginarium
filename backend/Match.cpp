#include "Match.h"

Match::Match()
    : maxSize(2)
{
}

Match::Match(int _maxSize, CardHolder& cardHolder)
    : maxSize(_maxSize)
{
    master = rand() % maxSize;
    deck = cardHolder.getDeck(60);
}

bool Match::isFull() const
{
    return true;
}

void Match::addPlayer(PlayerSP player)
{
    for (int i = 0; i < 6; i++) {
        player->addCard(deck.back());
        deck.pop_back();
    }
    players.push_back(player);
}

int Match::getMaxSize() const
{
    return maxSize;
}

std::vector<PlayerSP> Match::getPlayers() const
{
    return players;
}

int Match::getDeckSize() const
{
    return deck.size();
}

int Match::getMaster() const
{
    return master;
}

void Match::setMaster(int value)
{
    master = value;
}

std::vector<CardHolder::Card> Match::getHandByPlayer(int id)
{
    return players[id]->getHand();
}
