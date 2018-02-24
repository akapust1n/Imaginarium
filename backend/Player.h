#ifndef PLAYER_H
#define PLAYER_H
#include <crow.h>
#include "CardHolder.h"

class Player {
public:
    Player(crow::websocket::connection* _conn, const std::string _viewer_id);
    crow::websocket::connection* getConn() const;

    std::string getViewer_id() const;

    std::vector<CardHolder::Card> getHand() const;

    void addCard(CardHolder::Card card);
    bool removeCard(int id);

    int getScore() const;
    void setScore(int value);

private:
    int score;
    crow::websocket::connection* conn;
    const std::string viewer_id;
    std::vector<CardHolder::Card> hand;

};
using PlayerSP = std::shared_ptr<Player>;
using PlayerWP = std::weak_ptr<Player>;

#endif // PLAYER_H
