#include "Match.h"

Match::Match()
    : maxSize(2)
{
}

Match::Match(int _maxSize, CardHolder& cardHolder)
    : maxSize(_maxSize)
    , dropedCards(0)
    , guessCards(0)
{
    mutex.reset(new std::mutex());
    deck = cardHolder.getDeck(60);
}

//Match::Match(Match &&a):
//    maxSize(a.maxSize)
//{
//   dropMutex = std::move(a.dropMutex);
//}

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

int Match::getMasterCard() const
{
    return masterCard;
}

void Match::setMasterCard(const int& value)
{
    masterCard = value;
}

bool Match::dropCard(int cardId, PlayerSP player)
{
    if (player->dropCard(cardId)) {
        mutex->lock();
        dropedCards++;

        if (dropedCards == maxSize - 1) {
            dropedCards = 0;
            mutex->unlock();
            return true;
        } else {
            mutex->unlock();
            return false;
        }
    }
}

bool Match::guessCard(int cardId, PlayerSP player)
{
    player->setGuessCard(cardId);
    mutex->lock();
    guessCards++;

    if (guessCards == maxSize - 1) {
        guessCards = 0;
        mutex->unlock();
        return true;
    } else {
        mutex->unlock();
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
