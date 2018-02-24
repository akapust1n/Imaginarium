#include "Match.h"

Match::Match()
    : maxSize(2)
{
}

Match::Match(int _maxSize, CardHolder& cardHolder)
    : maxSize(_maxSize)
    , dropedCards()
{
    deck = cardHolder.getDeck(60);
}

bool Match::isFull() const
{
    return true;
}

void Match::addPlayer(PlayerSP player)
{
    if (!players.size()) {
        master = player->getViewer_id();
        player->setIsMaster(true);
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
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getIsMaster())
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

void Match::setMasterCard(const std::string& value)
{
    masterCard = value;
}

bool Match::dropCard(std::string cardId, PlayerSP player)
{
    //может сразу парсить в инт?
    if (player->dropCard(std::stoi(cardId))) {
        std::lock_guard<std::mutex> lock(dropMutex);
        dropedCards++;

        if (dropedCards == maxSize - 1) {
            dropedCards = 0;
            return true;
        } else
            return false;
    }
}

int Match::getDropedCards() const
{
    return dropedCards;
}

void Match::setMaster(std::string value)
{
    master = value;
}

std::vector<CardHolder::Card> Match::getHandByPlayer(int id)
{
    return players[id]->getHand();
}
