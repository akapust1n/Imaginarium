#include "Parser.h"
#include "../3rd_part/md5/md5.h"
#include "crow.h"
#include <iostream>
using json = nlohmann::json;

Parser::Parser()
{
}

bool Parser::checkNewPlayer(const std::string& data)
{
    json j_complete = json::parse(data);
    std::string viewer_id, api_id, auth_key;
    try {
        viewer_id = j_complete["content"]["viewer_id"];
        api_id = j_complete["content"]["api_id"];
        auth_key = j_complete["content"]["auth_key"];
    } catch (...) {
        std::cout << "\nWrong json!\n";
        return false;
    }

    std::ifstream api_key_secret("../../api_key_secret.txt");
    std::string api_secret;
    api_key_secret >> api_secret;

    //https://vk.com/dev/apps_init?f=3.%20auth_key
    std::string md5_user = md5(api_id + "_" + viewer_id + "_" + api_secret);
    return md5_user == auth_key;
}

std::string Parser::getType(const std::string& data)
{
    std::cout << data;
    json j_complete = json::parse(data);
    std::string type = j_complete["type"];

    return type;
}

std::string Parser::inQueue() const
{
    json j;
    j["type"] = "Queue";
    return j.dump();
}

std::string Parser::authError() const
{
    json j;
    j["type"] = "Error";
    j["content"] = "AuthError";
    return j.dump();
}
