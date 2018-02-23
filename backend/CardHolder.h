#ifndef CARDHOLDER_H
#define CARDHOLDER_H
#include <vector>
#include <string>

class CardHolder
{
public:
    struct Card{
        int cardId;
        std::string cardUrl;
    };
public:
    CardHolder(std::string path);
    std::vector<Card> getDeck(int num);
private:
    std::vector<Card> fullDeck;
    int numCards;
    std::string adress;

};

#endif // CARDHOLDER_H
