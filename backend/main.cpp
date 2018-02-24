#include "MatchLogic.h"
#include "crow.h"
#include "Parser.h"
#include "../3rd_part/md5/md5.h"
//для корректной работы сервака  в ("../../static/cards/") должны лежать картинки


int main()
{

    crow::SimpleApp app;
    MatchLogic mk;
    Parser parser;
    std::cout<<md5("a");
    CROW_ROUTE(app, "/")
    ([]() {
        crow::response res;
       // res.add_header("Access-Control-Allow-Origin", "*");
        res.body = "Hello world!";
        return res;
    });

    CROW_ROUTE(app, "/ws")
        .websocket()
        .onopen([&](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "new websocket connection";

        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
            CROW_LOG_INFO << "websocket connection closed: " << reason;
            mk.removePlayer(&conn);

        })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            CROW_LOG_INFO << "connection message";
            std::string type =parser.getType(data);
            if (type=="GameJoin"){
                if (parser.checkNewPlayer(data)){
                    conn.send_text(parser.inQueue());
                    mk.findMath(&conn, parser.viewev_id(data));
                }
                else{
                    conn.send_text(parser.authError());
                }
            }
            else if (type=="MasterTurn"){
                  auto masterTurn =  parser.getMasterTurn(data);
                  mk.masternTurn(&conn, masterTurn);
            }
            else if (type=="PlayerTurn"){
                std::string cardId =parser.getCardId(data);
            }
        });
    crow::logger::setLogLevel(crow::LogLevel::Info);

    app.port(5001).multithreaded().run();
}
