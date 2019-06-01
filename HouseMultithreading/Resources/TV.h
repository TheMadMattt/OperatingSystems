//
// Created by mateusz on 25.05.19.
//

#ifndef HOUSEMULTITHREADING_TELEWIZOR_H
#define HOUSEMULTITHREADING_TELEWIZOR_H

#include "../HouseSetup.h"
#include "../Threads/Person.h"
#include <deque>

#define personsCounter 2

class TV {
public:
    TV(int id);

    void useTV(int personId);
    void releaseTV(int personId);
    void waitForTV();

private:
    int id = 0;
    std::deque<int> persons;

    std::condition_variable tvVariable;
    bool isTVReady;

    std::mutex mutexTV;
    std::mutex waitMutex;

    int placeCounter = 0;

    void notifyThreads();

};


#endif //HOUSEMULTITHREADING_TELEWIZOR_H
