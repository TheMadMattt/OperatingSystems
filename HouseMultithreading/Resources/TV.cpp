//
// Created by mateusz on 25.05.19.
//

#include "TV.h"

TV::TV(int id)
    :   id(id),
        isTVReady(true)
{}

void TV::useTV(int personId) {

    std::scoped_lock<std::mutex> scopedLock(mutexTV);
    if(placeCounter!=personsCounter){
        ++placeCounter;
        this->persons.push_back(personId);
        if(placeCounter == personsCounter){
            isTVReady = false;
        }
    }
}

void TV::releaseTV(int personId) {

    for (int i = 0; i < this->persons.size(); ++i) {
        if(this->persons[i] == personId){
            this->persons.erase(this->persons.begin()+i);
            --placeCounter;
        }
    }

    notifyThreads();
}

void TV::waitForTV() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    if(personsCounter==placeCounter) {
        isTVReady = false;

        tvVariable.wait(uniqueLock, [this] {
            return this->isTVReady;
        });
    }
}

void TV::notifyThreads() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isTVReady = true;

    tvVariable.notify_one();

}
