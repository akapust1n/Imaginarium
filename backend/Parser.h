#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Player.h"
#include <nlohmann/json.hpp>
#include <CardHolder.h>
#include "Match.h"

class Parser
{
public:
    struct  MasterTurn
    {
        std::string cardId;
        std::string association;
    };
public:
    Parser();
    bool checkNewPlayer(const std::string& data);
    std::string getType(const std::string &data);
    std::string viewev_id(const std::string &data);
    std::vector<std::string> createMatch(Match &match);

    MasterTurn getMasterTurn(const std::string &data);
    std::string inQueue() const;
    std::string authError() const;
    std::string association(MasterTurn masterTurn) const;
    std::string getCardId (const std::string &data) const;
    std::string cardsOnBoard(PlayerSP &player, std::vector<CardHolder::Card> &dropedCards) const;

};

#endif // PARSER_H
