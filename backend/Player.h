#ifndef PLAYER_H
#define PLAYER_H
#include <crow.h>

class Player {
public:
    Player(crow::websocket::connection* _conn);
    void* userdata() const;

private:
    int score;
    crow::websocket::connection* conn;
};

#endif // PLAYER_H
