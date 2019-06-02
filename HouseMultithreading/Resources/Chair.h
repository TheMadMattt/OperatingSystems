//
// Created by mateusz on 01.06.19.
//

#ifndef HOUSEMULTITHREADING_CHAIR_H
#define HOUSEMULTITHREADING_CHAIR_H

#include <mutex>
#include <condition_variable>
#include "../Printing.h"

enum ChairStatus{
    CHAIR_AVAILABLE, CHAIR_IN_USE
};

class Chair {

public:
    Chair(int id, Printing &printing);

    void takeChair(int personId);
    void releaseChair();

    std::mutex& getMutexChair();

    std::string getStatus();

    void setStatus(ChairStatus chairStatus);

    bool& isChairAvailable();

    int getId() const;

private:
    int id;
    int ownerId;
    ChairStatus status;

    std::condition_variable chairVariable;
    bool isChairTaken;

    Printing &printing;

    std::mutex mutexChair;
    std::mutex waitMutex;

    void notifyThreads();
    void waitForChair();

};


#endif //HOUSEMULTITHREADING_CHAIR_H
