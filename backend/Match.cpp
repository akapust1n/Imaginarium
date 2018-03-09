#include "Match.h"

Match::Match()
    : maxSize(2)
{
}

Match::Match(int _maxSize, CardHolder& cardHolder)
    : maxSize(_maxSize)
    , dropedCards(0)
    , guessCards(0)
    , nextTurnCounter(0)
    , masterNum(0)
{
    mutex.reset(new std::mutex());
    deck = cardHolder.getDeck(20);
    phase = Phase::BeforeStart;
}

bool Match::isFull() const
{
    return true;
}

void Match::addPlayer(PlayerSP player)
{
    mutex->lock();
    if (!players.size()) {
        master = player->getViewer_id();
        player->setIsMaster(true);
    }
    mutex->unlock();

    for (int i = 0; i < 6; i++) {
        player->addCard(deck.back());
        deck.pop_back();
    }
    players.push_back(player);
}

void Match::masterAfk()
{
    for(int i=0;i<maxSize;i++){
        if (!players[i]->getIsMaster()){
            players[i]->addMainScore(3);
        }
        players[i]->dropCard();
    }
    prepareTurn();
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
        std::cout << "\nDROP_CARD \n";
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

bool Match::nextTurn(PlayerSP player)
{
    player->addMainScore(player->getScore());
    player->setScore(0);
    mutex->lock();
    nextTurnCounter++;

    if (nextTurnCounter == maxSize) {
        nextTurnCounter = 0;
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

bool Match::prepareTurn()
{
    if (deck.empty()) {
        int counterEmpty = 0;
        for (auto& player : players) {
            if (player->getHand().empty())
                counterEmpty++;
        }
        if (counterEmpty == players.size())
            return false;
        else
            return true;
    }
    dropedCards = 0;
    guessCards = 0;
    masterCard = 0;
    nextTurnCounter = 0;
    players[masterNum]->setIsMaster(false);
    masterNum = (masterNum + 1) % maxSize;
    master = players[masterNum]->getViewer_id();
    players[masterNum]->setIsMaster(true);
    for (int i = 0; i < maxSize; i++) {
        players[i]->addCard(deck.back());
        deck.pop_back();
    }
    return true;
}

Match::Phase Match::getPhase() const
{
    return phase;
}

void Match::setPhase(const Phase& value)
{
    phase = value;
}

void Match::lock()
{
    mutex->lock();
}

void Match::unlock()
{
    mutex->unlock();
}

void Match::setMaster(std::string value)
{
    master = value;
}

std::vector<CardHolder::Card> Match::getHandByPlayer(int id)
{
    return players[id]->getHand();
}
