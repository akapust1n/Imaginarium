#include "Player.h"


Player::Player(crow::websocket::connection *_conn):
     score(0), conn(_conn)
{

}

crow::websocket::connection *Player::getConn() const
{
    return conn;
}
