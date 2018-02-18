#include "Player.h"


Player::Player(crow::websocket::connection *_conn):
     score(0), conn(_conn)
{

}

void *Player::userdata() const
{
    return conn->userdata();
}
