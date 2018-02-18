#include "crow.h"
using namespace crow;

int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.body= "Hello world!";
        return res;
    });

    CROW_ROUTE(app, "/auth")([](){
        return crow::response(200);
    });

    app.port(5001).multithreaded().run();
}
