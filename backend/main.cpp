#include "Matchmaking.h"
#include "crow.h"
#include "Parser.h"



int main()
{

    crow::SimpleApp app;
    Matchmaking mk;
    Parser parser;
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
            mk.addPlayer(&conn );

        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
            CROW_LOG_INFO << "websocket connection closed: " << reason;

        })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            CROW_LOG_INFO << "connection message";
            std::string type =parser.getType(data);
            if (type=="GameJoin"){
                if (parser.checkNewPlayer(data)){
              //  mk.findMath(crow::websocket::connection& conn);
                    conn.send_text(parser.inQueue());
                }
                else{
                    conn.send_text(parser.authError());
                }
            }
            conn.send_text(data);
        });

    app.port(5001).multithreaded().run();
}
