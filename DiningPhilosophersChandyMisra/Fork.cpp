//
// Created by mateusz on 25.03.19.
//

#include "Fork.h"

Fork::Fork(int id, int philosopherId, TableSetup &tableSetup)
    :   id(id),
        ownerId(philosopherId),
        isDirty(true),
        tableSetup(tableSetup)
{
}

Fork::Fork(const Fork &otherFork)
    :   id(otherFork.id),
        ownerId(otherFork.ownerId),
        isDirty(otherFork.isDirty),
        tableSetup(otherFork.tableSetup)
{
}

void Fork::requestFork(int philosopherId) {

    while (ownerId != philosopherId){
        if(isDirty){
            std::lock_guard<std::mutex> lockGuard(forkMutex);
            isDirty = false;
            status = ForkStatus::CLEAN;
            ownerId = philosopherId;
        }else{
            tableSetup.syncChannel.wait();
        }
    }
}

void Fork::putDownFork() {
    isDirty = true;

    tableSetup.syncChannel.notifyAllThreads();
}

std::mutex &Fork::getForkMutex() {
    return forkMutex;
}

std::string Fork::getForkStatus() {

    std::string message = "Fork" + std::to_string(id) + " -> Phil" + std::to_string(ownerId);

    switch(status){
        case ForkStatus::DIRTY:
            message += " : DIRTY";
            break;
        case ForkStatus::CLEAN:
            message += " : CLEAN";
            break;
    }

    return message;
}

void Fork::setForkStatus(ForkStatus newStatus) {
    status = newStatus;
}
