#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <future>
#include <iostream>
void timer(int secs)
{
    std::cout << "Start\n";

    std::this_thread::sleep_for(std::chrono::seconds(secs));

    std::cout << "DONE\n";
}
#endif // TIMER_H
