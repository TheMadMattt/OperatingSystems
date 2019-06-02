//
// Created by mateusz on 25.05.19.
//

#ifndef HOUSEMULTITHREADING_TELEWIZOR_H
#define HOUSEMULTITHREADING_TELEWIZOR_H

#include "../HouseSetup.h"
#include "../Threads/Person.h"
#include <deque>

#define personsCounter 2

enum TVStatus{
    TURNED_OFF, TURNED_ON
};

class TV {
public:
    TV(int id, Printing &printing);

    void useTV(int personId);
    void releaseTV(int personId);

    std::string getStatus();
    void setStatus(TVStatus tvStatus);

private:
    int id = 0;
    std::deque<int> persons;

    std::condition_variable tvVariable;
    bool isTVReady;

    TVStatus status;

    std::mutex mutexTV;
    std::mutex waitMutex;

    int placeCounter = 0;

    void notifyThreads();
    void waitForTV();

    Printing &printing;
};


#endif //HOUSEMULTITHREADING_TELEWIZOR_H
