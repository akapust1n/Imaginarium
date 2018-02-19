#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Player.h"
#include <nlohmann/json.hpp>


class Parser
{
public:
    Parser();
    bool checkNewPlayer(const std::string& data);
    std::string getType(const std::string &data);
    std::string viewev_id(const std::string &data);
    std::string createMatch(std::vector<PlayerSP>& players);

    std::string inQueue() const;
    std::string authError() const;
};

#endif // PARSER_H
