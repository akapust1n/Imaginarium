#include "CardHolder.h"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <set>

CardHolder::CardHolder(std::string path)
    : adress("https://kapust1n.ru:5000/files/cards/")
{
    const std::string target_path(path);
    if (boost::filesystem::exists(path)) {
        const boost::regex my_filter(".*\.jpg");

        boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
        int counter = 0;
        for (boost::filesystem::directory_iterator i(target_path); i != end_itr; ++i) {
            // Skip if not a file
            if (!boost::filesystem::is_regular_file(i->status()))
                continue;

            boost::smatch what;

            // Skip if no match for V2:
            if (!boost::regex_match(i->path().filename().string(), what, my_filter))
                continue;
            else {
                counter++;
            }
        }
        numCards = counter;

        std::cout << "\n NUM_CARDS__" << numCards << std::endl;
    }

    else {
        numCards = 0;
    }
}

//can be inf loop!
//num<numcards
//name of card is 001 002 (3 chars)
std::vector<CardHolder::Card> CardHolder::getDeck(int num)
{
    std::vector<Card> temp;

    if (numCards) {
        std::set<int> hash;
        int counter = 1;
        while (counter <= num) {
            int num = (rand() % (numCards-1)) +1;
            if (!hash.count(num)) {
                counter++;
                std::string path;
                if (num < 10) {
                    path = adress +std::string(2, '0').append(std::to_string(num) + ".jpg");
                } else {
                    if (num < 100) {
                        path = adress +std::string(1, '0').append(std::to_string(num) + ".jpg") ;
                    }
                    else {
                        path = (adress + std::to_string(num) + ".jpg");
                    }
                }
                temp.push_back({num,path});
            }
        }
        return temp;
    }
}
