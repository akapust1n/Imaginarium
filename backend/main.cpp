#include "crow.h"

int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    CROW_ROUTE(app, "/auth")([](){
        return crow::response(200);
    });

    app.port(5000).multithreaded().run();
}
