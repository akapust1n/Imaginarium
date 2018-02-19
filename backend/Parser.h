#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <nlohmann/json.hpp>


class Parser
{
public:
    Parser();
    bool checkNewPlayer(const std::string& data);
    std::string getType(const std::string &data);
    std::string inQueue() const;
    std::string authError() const;
};

#endif // PARSER_H
