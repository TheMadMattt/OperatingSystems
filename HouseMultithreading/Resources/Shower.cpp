//
// Created by mateusz on 25.05.19.
//

#include <mutex>
#include "Shower.h"

Shower::Shower(int id, Printing &printing)
    :   id(id),
        owner(-1),
        printing(printing),
        isShowerReady(true),
        showerStatus(AVAILABLE)
{}

void Shower::takeShower(int personId) {

    while(owner != personId){
        if(isShowerReady){
            std::scoped_lock<std::mutex> scopedLock(mutexShower);
            isShowerReady = false;
            setShowerStatus(IN_USE);
            owner = personId;
        }else{
            waitForShower();
        }
    }

}

void Shower::releaseShower() {

    owner = -1;

    setShowerStatus(AVAILABLE);

    notifyThreads();
}

void Shower::waitForShower() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isShowerReady = false;

    showerVariable.wait(uniqueLock, [this]{
        return this->isShowerReady;
    });
}

void Shower::notifyThreads() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isShowerReady = true;

    showerVariable.notify_one();

}

std::string Shower::getShowerStatus() {

    std::string message = "Shower ";

    switch (showerStatus){

        case AVAILABLE:
            message += "is AVAILABLE";
            break;
        case IN_USE:
            message += "is IN USE";
            break;
    }

    return message;
}

void Shower::setShowerStatus(ShowerStatus status) {
    Shower::showerStatus = status;

    printing.updateResourcesStates("SHOWER", getShowerStatus());
}
