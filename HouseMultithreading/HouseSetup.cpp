//
// Created by mateusz on 25.03.19.
//

#include "HouseSetup.h"

void HouseSetup::wait() {

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
