//
// Created by mateusz on 25.03.19.
//

#include "HouseSetup.h"

void HouseSetup::waitForStart() {

    std::unique_lock<std::mutex> uniqueLock(mutexLock);

    conditionVariable.wait(uniqueLock, [this]{
        return this->isReady;
    });
}

void HouseSetup::notifyAllThreads() {

    std::unique_lock<std::mutex> uniqueLock(mutexLock);

    isReady = true;

    conditionVariable.notify_all();

}

void HouseSetup::waitForTV() {

    std::unique_lock<std::mutex> uniqueLock(TVmutex);

    conditionVariable.wait(uniqueLock, [this]{
        return this->isTVReady;
    });

}

void HouseSetup::notifyTV() {

    std::unique_lock<std::mutex> uniqueLock(mutexLock);

    isTVReady = true;

    conditionVariable.notify_all();

}
