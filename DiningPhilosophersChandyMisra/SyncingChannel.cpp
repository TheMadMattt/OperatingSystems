//
// Created by mateusz on 25.03.19.
//

#include "SyncingChannel.h"

void SyncingChannel::wait() {

    std::unique_lock<std::mutex> uniqueLock(mutexLock);

    conditionVariable.wait(uniqueLock);
}

void SyncingChannel::notifyAllThreads() {

    std::unique_lock<std::mutex> uniqueLock(mutexLock);

    conditionVariable.notify_all();

}
