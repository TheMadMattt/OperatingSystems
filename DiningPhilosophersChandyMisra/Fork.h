//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_FORK_H
#define DININGPHILOSOPHERSCHANDYMISRA_FORK_H

#include <mutex>
#include "SyncingChannel.h"

enum ForkStatus{
    DIRTY, CLEAN
};


class Fork {

public:

    Fork(int id, int philosopherId);
    Fork(const Fork& otherFork);

    void requestFork(int philosopherId);
    void putDownFork();

    std::mutex& getForkMutex();

    std::string getForkStatus();
    void setForkStatus(ForkStatus newStatus);

private:
    int id;
    int ownerId;
    ForkStatus status = ForkStatus::DIRTY;
    bool isDirty;

    std::mutex forkMutex;
    SyncingChannel channel;

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_FORK_H
