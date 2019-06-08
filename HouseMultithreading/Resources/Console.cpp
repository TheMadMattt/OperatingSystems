//
// Created by mateusz on 01.06.19.
//

#include <mutex>
#include <algorithm>
#include "Console.h"

Console::Console(int id, Printing &printing)
    :   id(id),
        isConsoleReady(true),
        printing(printing),
        status(CONSOLE_TURNED_OFF)
{}

void Console::useConsole(int playerId) {

    std::scoped_lock<std::mutex> scopedLock(consoleMutex);
    while(std::find(players.begin(),players.end(),playerId)==players.end()) {
        if(playersCounter != placeCounter && isConsoleReady){
            ++placeCounter;
            if(placeCounter == playersCounter){
                isConsoleReady = false;
            }
            this->players.push_back(playerId);
            setStatus(CONSOLE_TURNED_ON);
        }else{
            waitForConsole();
        }
    }
}

void Console::releaseConsole(int playerId) {

    std::scoped_lock<std::mutex> scopedLock(releaseConsoleMutex);
    for (int i = 0; i < this->players.size(); ++i) {
        if(this->players[i] == playerId){
            this->players.erase(this->players.begin()+i);
            --placeCounter;
            notifyThreads();
        }
    }

    if(placeCounter == 0){
        setStatus(CONSOLE_TURNED_OFF);
    }else{
        setStatus(CONSOLE_TURNED_ON);
    }
}

void Console::waitForConsole() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isConsoleReady = false;

    consoleVariable.wait(uniqueLock, [this] {
        return this->isConsoleReady;
    });

}

void Console::notifyThreads() {

    std::unique_lock<std::mutex> uniqueLock(waitMutex);

    isConsoleReady = true;

    consoleVariable.notify_one();

}

int &Console::getPlaceCounter() {
    return placeCounter;
}

std::string Console::getStatus(){

    std::string message = "Console ";

    switch (status){
        case CONSOLE_TURNED_OFF:
            message += "is TURNED OFF";
            break;
        case CONSOLE_TURNED_ON:
            message += "is TURNED ON";
            break;
    }

    return message;

}

void Console::setStatus(ConsoleStatus consoleStatus) {
    Console::status = consoleStatus;

    printing.updateResourcesStates("CONSOLE", getStatus());
}

int Console::getMaxPlayers() const {
    return maxPlayers;
}

ConsoleStatus &Console::getCosnoleStatus() {
    return status;
}
