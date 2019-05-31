//
// Created by mateusz on 25.05.19.
//

#include <mutex>
#include "Shower.h"

Shower::Shower(int id)
    :   id(id),
        owner(-1),
        isShowerReady(true),
        showerStatus(AVAILABLE)
{}

void Shower::takeShower(int personId) {

    while(owner != personId){
        if(isShowerReady){
            std::scoped_lock<std::mutex> scopedLock(mutexShower);
            isShowerReady = false;
            showerStatus = IN_USE;
            owner = personId;
        }else{
            waitForShower();
        }
    }

}

void Shower::releaseShower() {

    owner = -1;

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
