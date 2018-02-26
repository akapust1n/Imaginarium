#include "Player.h"

Player::Player(crow::websocket::connection* _conn, const std::string _viewer_id)
    : score(0)
    , conn(_conn)
    , viewer_id(_viewer_id)
    , isMaster(false),
      mainScore(0)
{
}

crow::websocket::connection* Player::getConn()
{
    return conn;
}

std::string Player::getViewer_id() const
{
    return viewer_id;
}

std::vector<CardHolder::Card> Player::getHand() const
{
    return hand;
}

void Player::addCard(CardHolder::Card card)
{
    hand.push_back(card);
}

bool Player::dropCard(int id)
{
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].cardId == id) {
            dropedCard.cardId = hand[i].cardId;
            dropedCard.cardUrl = hand[i].cardUrl;
            hand.erase(hand.begin() + i);
            return true;
        }
    }
    return false;
}

int Player::getScore() const
{
    return score;
}

void Player::setScore(int value)
{
    score = value;
}

bool Player::getIsMaster() const
{
    return isMaster;
}

void Player::setIsMaster(bool value)
{
    isMaster = value;
}

CardHolder::Card Player::getDropedCard() const
{
    return dropedCard;
}

void Player::setDropedCard(const CardHolder::Card &value)
{
    dropedCard = value;
}

int Player::getGuessCard() const
{
    return guessCard;
}

void Player::setGuessCard(int value)
{
    guessCard = value;
}

void Player::addMainScore(int value)
{
    mainScore += value;
}

int Player::getMainScore() const
{
    return mainScore;
}

