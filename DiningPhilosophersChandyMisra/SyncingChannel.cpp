//
// Created by mateusz on 21.03.19.
//

#include "SyncingChannel.h"

void SyncingChannel::wait() {

    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock);
}

void SyncingChannel::notifyAll() {

    std::unique_lock<std::mutex> lock(mutex);
    condition.notify_all();
}
