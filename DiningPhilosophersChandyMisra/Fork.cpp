//
// Created by mateusz on 25.03.19.
//

#include "Fork.h"

Fork::Fork(int id, int philosopherId)
    :   id(id),
        ownerId(philosopherId),
        isDirty(true)
{
}

Fork::Fork(const Fork &otherFork)
    :   id(otherFork.id),
        ownerId(otherFork.ownerId),
        isDirty(otherFork.isDirty)
{
}

void Fork::requestFork(int philosopherId) {

    while (ownerId != philosopherId){
        if(isDirty){
            std::lock_guard<std::mutex> lockGuard(forkMutex);
            status = ForkStatus::CLEAN;
            isDirty = false;
            ownerId = philosopherId;
        }else{
            channel.wait();
        }
    }
}

void Fork::putDownFork() {
    isDirty = true;

    channel.notifyAllThreads();
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
