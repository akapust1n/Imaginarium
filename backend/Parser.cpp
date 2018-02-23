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

std::string Parser::viewev_id(const std::string& data)
{
    json j_complete = json::parse(data);

    std::string viewer_id = j_complete["content"]["viewer_id"];
    return viewer_id;
}

//У КАЖДОГО ИГРОКА ИНДИВИДУАЛЬНАЯ РУКА
std::vector<std::string> Parser::createMatch(Match& match)
{
    std::vector<std::string> summury;
    std::vector<std::string> viewers;
    auto players = match.getPlayers();
    for (auto& player : players)
        viewers.push_back(player->getViewer_id());

    json j_vec(viewers);
    json res;
    res["type"] = "MasterTurn";
    res["content"]["players"] = j_vec;
    res["content"]["master"] = match.getMaster();
    res["content"]["deck"] = match.getDeckSize();

    json resHand;
    for (int i = 0; i < match.getMaxSize(); i++) {

        auto hand = match.getHandByPlayer(i);
        json temp;
        for (auto& element : hand) {

            temp["card_id"] = element.cardId;
            temp["card_url"] = element.cardUrl;

            resHand.push_back(temp);
        }
        res["content"]["hand"] = temp;
        summury.push_back(res.dump());
    }
    return summury;
}
