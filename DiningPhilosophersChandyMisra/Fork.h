//
// Created by mateusz on 21.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_FORK_H
#define DININGPHILOSOPHERSCHANDYMISRA_FORK_H


#include <mutex>
#include "SyncingChannel.h"

enum ForkStatus{
    DIRTY, CLEAN
};

class Fork {
private:
    int id;
    int ownerId;
    ForkStatus status;

    std::mutex mutex;
    SyncingChannel channel;

public:
    Fork(int id, int ownerId);
    Fork(const Fork& other);

    void requestFork(int ownerId);
    void freeFork();

    std::mutex& getMutex();

    std::string getStatus() const;
    void setStatus(ForkStatus status);

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_FORK_H
