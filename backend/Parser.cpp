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

std::string Parser::association(MasterTurn masterTurn) const
{
    json j;
    j["type"] = "Association";
    j["content"] = masterTurn.association;
    return j.dump();
}

std::string Parser::getCardId(const std::string& data) const
{
    json j_complete = json::parse(data);
    std::string res = j_complete["content"];
    return res;
}

std::string Parser::cardsOnBoard(PlayerSP& player, std::vector<CardHolder::Card>& dropedCards) const
{
    json j_complete;
    j_complete["type"] = "CardsOnBoard";
    json j_array;
    for (auto& card : dropedCards) {
        json temp;
        CardHolder::Card dropedCard = player->getDropedCard();
        if (dropedCard.cardId = card.cardId)
            temp["isOwn"] = true;
        else
            temp["isOwn"] = false;
        temp["card_id"] = card.cardId;
        temp["card_url"] = card.cardUrl;
        j_array.push_back(temp);
    }
    j_complete["content"] = j_array;
    return j_complete.dump();
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
    json viewers;
    auto players = match.getPlayers();
    for (auto& player : players) {
        json temp;
        temp["viewer_id"] = player->getViewer_id();
        temp["score"] = player->getScore();
        viewers.push_back(temp);
    }

    json res;
    res["type"] = "MasterTurn";
    res["content"]["players"] = viewers;
    res["content"]["master"] = match.getMasterNum();
    res["content"]["deck"] = match.getDeckSize();

    for (int i = 0; i < match.getMaxSize(); i++) {
        json resHand;

        auto hand = match.getHandByPlayer(i);
        for (auto& element : hand) {
            json temp;

            temp["card_id"] = element.cardId;
            temp["card_url"] = element.cardUrl;

            resHand.push_back(temp);
        }
        res["content"]["hand"] = resHand;
        summury.push_back(res.dump());
    }
    return summury;
}

//TODO: сделать нормальную обработку ошибок
Parser::MasterTurn Parser::getMasterTurn(const std::string& data)
{
    json j_complete = json::parse(data);
    std::string card_id, association;
    try {
        card_id = j_complete["content"]["card_id"];
        association = j_complete["content"]["association"];
        return { card_id, association };

    } catch (...) {
        std::cout << "\nWrong json!\n";
        return {};
    }
    return {};
}
