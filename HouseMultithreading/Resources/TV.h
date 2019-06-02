//
// Created by mateusz on 25.05.19.
//

#ifndef HOUSEMULTITHREADING_TELEWIZOR_H
#define HOUSEMULTITHREADING_TELEWIZOR_H

#include "../HouseSetup.h"
#include "../Threads/Person.h"
#include "Console.h"
#include <deque>

#define personsCounter 3

enum TVStatus{
    TURNED_OFF, TURNED_ON
};

class TV {
public:
    TV(int id, Printing &printing, Console &console);

    void useTV(int personId);
    void releaseTV(int personId);

    void playOnConsole(int personId);
    void releaseConsole(int personId);

    std::string getStatus();
    void setStatus(TVStatus tvStatus);

private:
    int id = 0;
    std::deque<int> persons;

    std::condition_variable tvVariable;
    std::condition_variable consoleVariable;
    bool isTVReady;
    bool isPlayingConsole;
    bool canPlay;

    Console &console;

    TVStatus status;

    std::mutex mutexTV;
    std::mutex waitMutex;
    std::mutex consoleMutex;

    int placeCounter = 0;

    void notifyThreads();
    void waitForTV();

    void notifyCanPlay();
    void waitForPlayingConsole();

    Printing &printing;
};


#endif //HOUSEMULTITHREADING_TELEWIZOR_H
