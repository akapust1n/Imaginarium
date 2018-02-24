#include "Match.h"

Match::Match()
    : maxSize(2)
{
}

Match::Match(int _maxSize, CardHolder& cardHolder)
    : maxSize(_maxSize)
{
    deck = cardHolder.getDeck(60);
}

bool Match::isFull() const
{
    return true;
}

void Match::addPlayer(PlayerSP player)
{
   if (!players.size()){
       master = player->getViewer_id();
   }
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

PlayerSP Match::getMaster()
{
    for(int i=0;i<players.size();i++){
        if(players[i]->getViewer_id()==master)
            return players[i];
    }
    return nullptr;
}

std::string Match::getMasterNum() const
{
    return master;
}

std::string Match::getMasterCard() const
{
    return masterCard;
}

void Match::setMasterCard(const std::string &value)
{
    masterCard = value;
}

void Match::setMaster(std::string value)
{
    master = value;
}

std::vector<CardHolder::Card> Match::getHandByPlayer(int id)
{
    return players[id]->getHand();
}
