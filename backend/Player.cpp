#include "Player.h"

Player::Player(crow::websocket::connection* _conn, const std::string _viewer_id)
    : score(0)
    , conn(_conn)
    , viewer_id(_viewer_id)
{
}

crow::websocket::connection* Player::getConn() const
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

bool Player::removeCard(int id)
{
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].cardId == id) {
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

