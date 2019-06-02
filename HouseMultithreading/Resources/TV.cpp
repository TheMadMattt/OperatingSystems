//
// Created by mateusz on 25.05.19.
//

#include "TV.h"
#include <algorithm>

TV::TV(int id, Printing &printing)
    :   id(id),
        printing(printing),
        isTVReady(true),
        status(TURNED_OFF)
{}

void TV::useTV(int personId) {

    std::scoped_lock<std::mutex> scopedLock(mutexTV);
    while(std::find(persons.begin(),persons.end(),personId)==persons.end()) {
        if(placeCounter!=personsCounter){
            this->persons.push_back(personId);
            ++placeCounter;
            setStatus(TURNED_ON);
            if(placeCounter == personsCounter){
                isTVReady = false;
            }
        }else{
            waitForTV();
        }
    }
}

void TV::releaseTV(int personId) {

    for (int i = 0; i < this->persons.size(); ++i) {
        if(this->persons[i] == personId){
            this->persons.erase(this->persons.begin()+i);
            --placeCounter;
            notifyThreads();
        }
    }
    if(placeCounter == 0){
        setStatus(TURNED_OFF);
    }else{
        setStatus(TURNED_ON);
    }
}

void TV::waitForTV() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isTVReady = false;

    tvVariable.wait(uniqueLock, [this] {
        return this->isTVReady;
    });
}

void TV::notifyThreads() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isTVReady = true;

    tvVariable.notify_one();

}

std::string TV::getStatus() {

    std::string message = "TV ";

    switch (status){
        case TURNED_OFF:
            message += "is TURNED OFF";
            break;
        case TURNED_ON:
            message += "is TURNED ON";
            break;
    }

    return message;

}

void TV::setStatus(TVStatus tvStatus) {
    this->status = tvStatus;

    printing.updateResourcesStates("TV", getStatus());
}
