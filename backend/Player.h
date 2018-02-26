#ifndef PLAYER_H
#define PLAYER_H
#include <crow.h>
#include "CardHolder.h"

class Player {
public:
    Player(crow::websocket::connection* _conn, const std::string _viewer_id);
    crow::websocket::connection* getConn();

    std::string getViewer_id() const;

    std::vector<CardHolder::Card> getHand() const;

    void addCard(CardHolder::Card card);
    bool dropCard(int id);

    int getScore() const;
    void setScore(int value);

    bool getIsMaster() const;
    void setIsMaster(bool value);

    CardHolder::Card getDropedCard() const;
    void setDropedCard(const CardHolder::Card &value);

    int getGuessCard() const;
    void setGuessCard(int value);

    void addMainScore(int value);

    int getMainScore() const;

private:
    int score;
    int mainScore;
    int guessCard;
    crow::websocket::connection* conn;
    bool isMaster;
    const std::string viewer_id;
    std::vector<CardHolder::Card> hand;
    CardHolder::Card dropedCard;

};
using PlayerSP = std::shared_ptr<Player>;
using PlayerWP = std::weak_ptr<Player>;

#endif // PLAYER_H
