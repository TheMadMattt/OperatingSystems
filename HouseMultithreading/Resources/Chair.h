//
// Created by mateusz on 01.06.19.
//

#ifndef HOUSEMULTITHREADING_CHAIR_H
#define HOUSEMULTITHREADING_CHAIR_H

#include <mutex>
#include <condition_variable>

enum ChairStatus{
    CHAIR_AVAILABLE, CHAIR_IN_USE
};

class Chair {

public:
    Chair(int id);

    void takeChair(int personId);
    void releaseChair();

    std::mutex& getMutexChair();

    void setStatus(ChairStatus status);

    bool& isChairAvailable();

private:
    int id;
    int ownerId;
    ChairStatus status;

    std::condition_variable chairVariable;
    bool isChairTaken;

    std::mutex mutexChair;
    std::mutex waitMutex;

    void notifyThreads();
    void waitForChair();

};


#endif //HOUSEMULTITHREADING_CHAIR_H
