#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Player.h"
#include <nlohmann/json.hpp>
#include <CardHolder.h>
#include "Match.h"

/*! Парсер-запросов */
class Parser
{
public:
    struct  MasterTurn
    {
        int cardId;
        std::string association;
    };
public:
    Parser();
    bool checkNewPlayer(const std::string& data);
    std::string getType(const std::string &data);
    std::string viewev_id(const std::string &data);
    std::vector<std::string> createMatch(MatchSP &match);

    MasterTurn getMasterTurn(const std::string &data);
    std::string inQueue() const;
    std::string authError() const;
    std::string wrongPhase() const;
    std::string noMatch() const;
    std::string association(MasterTurn masterTurn) const;
    int getCardId(const std::string &data) const;
    std::string cardsOnBoard(PlayerSP &player, std::vector<CardHolder::Card> &dropedCards) const;
    std::string turnEnd(std::vector<PlayerSP>& players, int mastedCardId);
    std::string gameOver(std::vector<PlayerSP>&players );

};

#endif // PARSER_H
