//
// Created by mateusz on 25.05.19.
//

#ifndef HOUSEMULTITHREADING_SHOWER_H
#define HOUSEMULTITHREADING_SHOWER_H


#include <condition_variable>

enum ShowerStatus{
    AVAILABLE, IN_USE
};

class Shower {
public:
    Shower(int id);

    void takeShower(int personId);
    void releaseShower();

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
};


#endif //HOUSEMULTITHREADING_SHOWER_H
