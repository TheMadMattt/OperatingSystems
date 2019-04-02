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

    Fork(int id, int philosopherId, TableSetup &tableSetup);
    Fork(const Fork& otherFork);

    void requestFork(int philosopherId);
    void putDownFork();

    std::mutex& getForkMutex();

    std::string getForkStatus();
    void setForkStatus(ForkStatus newStatus);
    int getId();

private:
    int id;
    int ownerId;
    ForkStatus status;
    bool isDirty;

    std::mutex forkMutex;
    TableSetup &tableSetup;

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_FORK_H
