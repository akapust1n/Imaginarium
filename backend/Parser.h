#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <nlohmann/json.hpp>


class Parser
{
public:
    Parser();
    bool checkNewPlayer();
    std::string getType(const std::string &data);
};

#endif // PARSER_H
