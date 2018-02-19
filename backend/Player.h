#ifndef PLAYER_H
#define PLAYER_H
#include <crow.h>

class Player {
public:
    Player(crow::websocket::connection* _conn, const std::string _viewer_id);
    crow::websocket::connection* getConn() const;

    std::string getViewer_id() const;

private:
    int score;
    crow::websocket::connection* conn;
    const std::string viewer_id;
};
using PlayerSP = std::shared_ptr<Player>;
using PlayerWP = std::weak_ptr<Player>;

#endif // PLAYER_H
