//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
#define DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H


#include <mutex>
#include <condition_variable>
#include <atomic>

class SyncingChannel {

public:

    void wait();
    void notifyAllThreads();

private:

    std::mutex mutexLock;
    std::condition_variable conditionVariable;

};

struct HouseSetup{
    SyncingChannel syncChannel;
    std::atomic<bool> finishedDinner {false};
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
