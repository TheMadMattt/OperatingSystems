//
// Created by mateusz on 25.05.19.
//

#include "TV.h"
#include <algorithm>

TV::TV(int id, Printing &printing, Console &console)
    :   id(id),
        printing(printing),
        console(console),
        isTVReady(true),
        canPlay(true),
        isPlayingConsole(false),
        status(TURNED_OFF)
{}

void TV::useTV(int personId) {

    std::scoped_lock<std::mutex> scopedLock(mutexTV);
    while(std::find(persons.begin(),persons.end(),personId)==persons.end()) {
        if(placeCounter != personsCounter && !isPlayingConsole
        && console.getCosnoleStatus() == ConsoleStatus::CONSOLE_TURNED_OFF && console.getPlaceCounter()==0){
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

    std::scoped_lock<std::mutex> scopedLock(releaseMutexTV);
    for (int i = 0; i < this->persons.size(); ++i) {
        if(this->persons[i] == personId){
            this->persons.erase(this->persons.begin()+i);
            --placeCounter;
            notifyThreads();
        }
    }
    if(placeCounter == 0){
        notifyCanPlay();
        setStatus(TURNED_OFF);
    }else{
        setStatus(TURNED_ON);
    }
}

void TV::waitForTV() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isTVReady = false;

    tvVariable.wait(uniqueLock, [this] {
        return this->isTVReady && !this->isPlayingConsole;
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

void TV::playOnConsole(int personId) {

    while(!isPlayingConsole) {
        std::scoped_lock<std::mutex> scopedLock(mutexTV);
        if(canPlay && placeCounter == 0 && console.getPlaceCounter() < console.getMaxPlayers() &&
            status == TURNED_OFF) {
            isPlayingConsole = true;
            console.useConsole(personId);
        }else{
            waitForPlayingConsole();
        }
    }
}

void TV::releaseConsole(int personId) {

    console.releaseConsole(personId);
    if(console.getPlaceCounter() == 0) {
        isPlayingConsole = false;
        notifyThreads();
    }
}

void TV::waitForPlayingConsole() {

    std::unique_lock<std::mutex> uniqueLock(consoleMutex);

    canPlay = false;

    consoleVariable.wait(uniqueLock, [this] {
        return this->canPlay;
    });

}

void TV::notifyCanPlay() {

    std::unique_lock<std::mutex> uniqueLock(consoleMutex);

    canPlay = true;

    consoleVariable.notify_one();

}
