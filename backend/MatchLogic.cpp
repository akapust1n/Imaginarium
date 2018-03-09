#include "MatchLogic.h"
#include "iostream"
#include "Timer.h"

MatchLogic::MatchLogic()
    : cardHolder("../../static/cards/")
{
}

void MatchLogic::findMath(crow::websocket::connection* conn, const std::string viewer_id)
{
    std::cout << "Try to find game" << std::endl;
    MatchSP match = std::make_unique<Match>(2, cardHolder);
    int maxSize = match->getMaxSize();
    players.insert({ conn, std::make_shared<Player>(conn, viewer_id) });

    std::lock_guard<std::mutex> guard(find);
    if (match->getPhase() != Match::BeforeStart) {
        conn->send_text(parser.wrongPhase());
    }
    queue.push_back(players[conn]);

    if (queue.size() >= maxSize) {
        auto iterator = queue.begin();
        auto size = queue.size();
        int counter = 0;

        for (int i = 0; i < size && counter < maxSize; i++) {
            std::cout << "||Queue work...\n";
            if (iterator->lock()) {
                match->addPlayer(iterator->lock());
                counter++;

                std::cout << "\nCan lock pointer!\n";
                std::cout << iterator->lock()->getViewer_id();
            }
            queue.erase(iterator);
        }
        if (counter < maxSize) {
            auto returningPlayers = match->getPlayers();
            for (auto& player : returningPlayers) {
                queue.push_back(player);
            }
            std::cout << "\n Cant find game!\n";
        } else {
            std::cout << "\nFind game!\n";

            std::vector<PlayerSP> gamers = match->getPlayers();
            for (int i = 0; i < gamers.size(); i++) {
                matches[gamers[i]->getConn()] = match;
            }
            match->setPhase(Match::Phase::NewTurn);
            std::cout << "\nMatch created!\n";
            sendNotifyStartGame(match);
        }
    }
}

void MatchLogic::removePlayer(crow::websocket::connection* conn)
{
    players.erase(conn);
}

void MatchLogic::masternTurn(crow::websocket::connection* conn, Parser::MasterTurn data)
{
    if (!matches.count(conn) or !players.count(conn)) {
        conn->send_text(parser.noMatch());
        return;
    }
    MatchSP match = matches[conn];
    match->lock();
    if (!players[conn]->getIsMaster()) {
        match->unlock();
        return;
    }
    match->unlock();

    if (match->getPhase() != Match::NewTurn) {
        conn->send_text(parser.wrongPhase());
        return;
    }
    match->setPhase(Match::MasterTurn);

    match->setMasterCard(data.cardId);
    auto player = match->getPlayers();
    std::cout << "\n Erase MasterCard viewer_id=" << match->getMaster()->getViewer_id();
    match->getMaster()->dropCard(data.cardId);
    std::string response = parser.association(data);
    for (int i = 0; i < match->getMaxSize(); i++) {
        player[i]->getConn()->send_text(response);
    }
}
void MatchLogic::dropCard(crow::websocket::connection* conn, int cardId)
{
    //TODO: если отключится игрок, то всё плохо
    if (!matches.count(conn)) {
        conn->send_text(parser.noMatch());
        return;
    }
    MatchSP match = matches[conn];

    if (match->getPhase() != Match::MasterTurn) {
        conn->send_text(parser.wrongPhase());
        return;
    }
    if (match->dropCard(cardId, players[conn])) {
        auto gamers = match->getPlayers();
        match->setPhase(Match::PlayerTurn);
        std::vector<CardHolder::Card> dropedCards;
        for (int i = 0; i < gamers.size(); i++) {
            dropedCards.push_back(gamers[i]->getDropedCard());
        }

        for (int i = 0; i < gamers.size(); i++) {
            if (!gamers[i]->getIsMaster()) {
                std::string response = parser.cardsOnBoard(gamers[i], dropedCards);
                gamers[i]->getConn()->send_text(response);
            }
        }
    };
}

void MatchLogic::guessCard(crow::websocket::connection* conn, int cardId)
{
    if (!matches.count(conn)) {
        conn->send_text(parser.noMatch());
        return;
    }
    MatchSP match = matches[conn];

    if (match->getPhase() != Match::PlayerTurn) {
        conn->send_text(parser.wrongPhase());
        return;
    }
    if (match->guessCard(cardId, players[conn])) {
        match->setPhase(Match::PlayerGuess);
        auto gamers = match->getPlayers();
        for (int i = 0; i < gamers.size(); i++) {
            int cardId = gamers[i]->getDropedCard().cardId;
            for (int j = 0; j < gamers.size(); j++) {
                if (gamers[j]->getGuessCard() == cardId && i != j) {

                    gamers[i]->setScore(gamers[i]->getScore() + 1);
                    std::cout << "\nSET SCORE " << gamers[i]->getScore() << std::endl;
                }
            }
        }
        PlayerSP master = match->getMaster();
        if (master->getScore() && (master->getScore() != (gamers.size() - 1))) {
            master->setScore(master->getScore() + 3);
        } else {
            for (int j = 0; j < gamers.size(); j++) {
                if (!gamers[j]->getIsMaster())
                    gamers[j]->setScore(3);
            }
        }

        std::string points = parser.turnEnd(gamers, match->getMasterCard());
        for (int i = 0; i < gamers.size(); i++) {
            gamers[i]->getConn()->send_text(points);
        }
    }
}

void MatchLogic::nextTurn(crow::websocket::connection* conn)
{
    if (!matches.count(conn)) {
        conn->send_text(parser.noMatch());
        return;
    }
    MatchSP match = matches[conn];

    if (match->getPhase() != Match::PlayerGuess) {
        conn->send_text(parser.wrongPhase());
        return;
    }
    if (match->nextTurn(players[conn])) {
        if (!match->prepareTurn()) {
            auto gamers = match->getPlayers();
            std::string response = parser.gameOver(gamers);
            for (int i = 0; i < gamers.size(); i++) {
                gamers[i]->getConn()->send_text(response);
            }
        } else {
            match->setPhase(Match::NewTurn);
            sendNotifyStartGame(match);
        }
    }
}

void MatchLogic::sendNotifyStartGame(MatchSP& match)
{
    std::vector<std::string> response = parser.createMatch(match);
    const std::vector<PlayerSP>& players = match->getPlayers();
    for (int i = 0; i < players.size(); i++) {
        std::cout << "\n Response \n"<< players[i]->getViewer_id()
                  << response[i];
        players[i]->getConn()->send_text(response[i]);
        
    }
    int deckSize = match->getDeckSize();
    auto timer_1 = [&](){
        std::cout<<"\nTimer start!\n�";
        timer(20);
        match->lock();
        if (match->getDeckSize()==deckSize){
            std::cout<<"\n master afk\n";
            match->masterAfk();
            sendNotifyStartGame(match);        
        }
        match->unlock();;
        std::cout<<"\n timer finished\n";
           };
   auto temp =    std::async(std::launch::async,timer_1);


}

bool MatchLogic::checkConn(crow::websocket::connection* conn, Match::Phase phase)
{
    //TODO
}
