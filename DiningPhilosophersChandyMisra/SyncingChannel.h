//
// Created by mateusz on 21.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
#define DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H


#include <mutex>
#include <condition_variable>
#include <atomic>

class SyncingChannel {
    std::mutex mutex;
    std::condition_variable condition;

public:

    void wait();
    void notifyAll();
};

struct TableSetup{
    std::atomic<bool> done{false};
    SyncingChannel channel;
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_SYNCINGCHANNEL_H
