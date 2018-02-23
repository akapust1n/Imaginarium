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
    Parser();
    bool checkNewPlayer(const std::string& data);
    std::string getType(const std::string &data);
    std::string viewev_id(const std::string &data);
    std::vector<std::string> createMatch(Match &match);

    std::string inQueue() const;
    std::string authError() const;

};

#endif // PARSER_H
