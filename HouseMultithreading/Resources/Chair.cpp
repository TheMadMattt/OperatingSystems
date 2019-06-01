//
// Created by mateusz on 01.06.19.
//

#include "Chair.h"

Chair::Chair(int id)
    :   id(id),
        ownerId(-1),
        isChairTaken(false),
        status(CHAIR_AVAILABLE)
{}

void Chair::notifyThreads() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    chairVariable.notify_all();
}

void Chair::waitForChair() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    chairVariable.wait(uniqueLock, [this] {
        return this->isChairTaken;
    });
}

void Chair::takeChair(int personId) {

    while (ownerId != personId){
        if(!isChairTaken){
            std::scoped_lock scopedLock(mutexChair);
            isChairTaken = true;
            status = ChairStatus::CHAIR_AVAILABLE;
            ownerId = personId;
        }else{
            waitForChair();
        }
    }

}

void Chair::releaseChair() {

    isChairTaken = false;

    notifyThreads();

}

std::mutex &Chair::getMutexChair() {
    return mutexChair;
}

void Chair::setStatus(ChairStatus status) {
    Chair::status = status;
}

bool& Chair::isChairAvailable() {
    return isChairTaken;
}
