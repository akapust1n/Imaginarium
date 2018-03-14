#include "Parser.h"
#include "Player.h"
#include <QtTest/QtTest>
#include <nlohmann/json.hpp>
#include <vector>

class TestParser : public QObject {
    Q_OBJECT
public:
    explicit TestParser(QObject* parent = 0)
        : QObject(parent){};

private:
    Parser parser;
private slots:
    void viewer_id()
    {
        QCOMPARE(parser.viewev_id("{\"content\":{\"viewer_id\":\"123\"}}"), std::string("123"));
    }
    void get_card_id()
    {
        QCOMPARE(parser.getCardId("{\"content\": 123}"), 123);
    }
    void gameover()
    {
        std::vector<PlayerSP> players;
        players.push_back(std::make_shared<Player>(nullptr, "111"));
        players[0]->addMainScore(123);
        players.push_back(std::make_shared<Player>(nullptr, "222"));
        players[0]->addMainScore(558);
        QCOMPARE(parser.gameOver(players), std::string("{\"content\":[{\"score\":681,\"viewer_id\":\"111\"},{\"score\":0,\"viewer_id\":\"222\"}],\"type\":\"GameOver\"}"));
    }
};

QTEST_MAIN(TestParser)
#include "TestParser.moc"
