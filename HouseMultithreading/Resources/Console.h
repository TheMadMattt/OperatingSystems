//
// Created by mateusz on 01.06.19.
//

#ifndef HOUSEMULTITHREADING_CONSOLE_H
#define HOUSEMULTITHREADING_CONSOLE_H

#include <condition_variable>
#include <deque>
#include "../Printing.h"

#define playersCounter 2

enum ConsoleStatus{
    CONSOLE_TURNED_OFF, CONSOLE_TURNED_ON
};

class Console {

public:
    Console(int id, Printing &printing);

    void useConsole(int playerId);
    void releaseConsole(int playerId);

    int &getPlaceCounter();

    ConsoleStatus &getCosnoleStatus();

    std::string getStatus();

    void setStatus(ConsoleStatus consoleStatus);

    int getMaxPlayers() const;

private:
    int id;
    std::deque<int> players;

    bool isConsoleReady;

    ConsoleStatus status;

    std::mutex consoleMutex;
    std::mutex releaseConsoleMutex;
    std::mutex waitMutex;

    std::condition_variable consoleVariable;

    void waitForConsole();
    void notifyThreads();

    int placeCounter = 0;
    int maxPlayers = playersCounter;

    Printing &printing;
};


#endif //HOUSEMULTITHREADING_CONSOLE_H
