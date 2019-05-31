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
    bool isReady = false;
    std::atomic<bool> finishedHouse {false};

private:
    std::mutex mutexLock;
    std::condition_variable conditionVariable;

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
