//
// Created by mateusz on 25.05.19.
//

#ifndef HOUSEMULTITHREADING_SHOWER_H
#define HOUSEMULTITHREADING_SHOWER_H


#include <condition_variable>
#include "../Printing.h"

enum ShowerStatus{
    AVAILABLE, IN_USE
};

class Shower {
public:
    Shower(int id, Printing &printing);

    void takeShower(int personId);
    void releaseShower();

    std::string getShowerStatus();

    void setShowerStatus(ShowerStatus status);

private:
    int id = 0;
    int owner = -1;

    ShowerStatus showerStatus;

    std::condition_variable showerVariable;
    bool isShowerReady = true;

    std::mutex mutexShower;
    std::mutex waitMutex;

    void waitForShower();
    void notifyThreads();

    Printing &printing;
};


#endif //HOUSEMULTITHREADING_SHOWER_H
