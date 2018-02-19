#include "Player.h"


Player::Player(crow::websocket::connection *_conn, const std::string _viewer_id):
     score(0), conn(_conn), viewer_id(_viewer_id)
{

}

crow::websocket::connection *Player::getConn() const
{
    return conn;
}

std::string Player::getViewer_id() const
{
    return viewer_id;
}
