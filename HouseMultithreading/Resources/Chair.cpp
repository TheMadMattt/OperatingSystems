//
// Created by mateusz on 01.06.19.
//

#include "Chair.h"
#include "../Printing.h"

Chair::Chair(int id, Printing &printing)
    :   id(id),
        ownerId(-1),
        printing(printing),
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
            setStatus(CHAIR_IN_USE);
            ownerId = personId;
        }else{
            waitForChair();
        }
    }

}

void Chair::releaseChair() {

    isChairTaken = false;

    setStatus(CHAIR_AVAILABLE);

    notifyThreads();

}

std::mutex &Chair::getMutexChair() {
    return mutexChair;
}

bool& Chair::isChairAvailable() {
    return isChairTaken;
}

int Chair::getId() const {
    return id;
}

std::string Chair::getStatus() {
    std::string message = "Chair " + std::to_string(getId());

    switch (status){

        case CHAIR_AVAILABLE:
            message += " is AVAILABLE";
            break;
        case CHAIR_IN_USE:
            message += " is IN USE";
            break;
    }

    return message;
}

void Chair::setStatus(ChairStatus chairStatus) {
    Chair::status = chairStatus;

    printing.updateResourcesStates("CHAIR"+std::to_string(getId()), getStatus());
}
