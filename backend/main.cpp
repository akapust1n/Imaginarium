#include "crow.h"
#include "../3rd_part/md5/md5.h"
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
    char cstring[] = "Foo baz, testing.";
    std::string str = cstring;

    /* MD5 from std::string */
    printf("md5sum: %s\n",  md5(  str ).c_str());

    /* MD5 from c-string */
    printf("md5sum: %s\n",  md5(  cstring ).c_str());

    /* Short MD5 from c-string */
    printf("md5sum6: %s\n", md5sum6( cstring ).c_str());

    /* Short MD5 from std::string */
    printf("md5sum6: %s\n", md5sum6( str ).c_str());
    app.port(5001).multithreaded().run();
}
