//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
#define DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H


#include <mutex>
#include <condition_variable>
#include <atomic>

class HouseSetup {

public:

    void waitForStart();
    void notifyAllThreads();
    void waitForTV();
    void notifyTV();
    bool isReady = false;
    bool isTVReady = false;
    std::atomic<bool> finishedDinner {false};

private:

    std::mutex mutexLock;
    std::mutex TVmutex;
    std::condition_variable conditionVariable;

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
