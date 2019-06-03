//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Adult.h"

Adult::Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, HouseStuff &houseStuff)
    :   houseStuff(houseStuff),
        adultStatus(IDLE),
        Person(id, age, print, houseSetup) {}

void Adult::startHouse() {

    houseSetup.waitForStart();

    do {
        eating();
        showering();
        watchingTV();
        ++cycle;
    }while(!houseSetup.finishedHouse);

    setAdultStatus(FINISHED);
}

Adult::~Adult() = default;

std::string Adult::getPersonStatus(){
    std::string message = " | Adult " + std::to_string(id);

    switch (adultStatus){
        case AdultStatus::WATCHING:
            message += "    is watching TV";
            break;
        case AdultStatus::SHOWERING:
            message += "      is showering";
            break;
        case IDLE:
            message += "        is waiting";
            break;
        case EATING:
            message += "         is eating";
            break;
        case FINISHED:
            message += " has finished work";
            break;
    }

    return message;
}

void Adult::setAdultStatus(AdultStatus _adultStatus) {
    this->adultStatus = _adultStatus;

    print.updateMenu(id, getPersonStatus(), getHouseCycle());
}

void Adult::watchingTV() {

    houseStuff.tv.useTV(id);
    setAdultStatus(WATCHING);
    Person::randomSleep(1,4);
    houseStuff.tv.releaseTV(id);
    setAdultStatus(IDLE);
}

void Adult::showering() {

    houseStuff.shower.takeShower(id);
    setAdultStatus(SHOWERING);
    Person::randomSleep(1,4);
    houseStuff.shower.releaseShower();
    setAdultStatus(IDLE);
}

void Adult::eating() {

    for (auto & i : houseStuff.chairList) {
        if(!i.isChairAvailable()){
            i.takeChair(id);
            std::scoped_lock scopedLock(i.getMutexChair());
            setAdultStatus(EATING);
            Person::randomSleep(1,4);
            i.releaseChair();
            setAdultStatus(IDLE);
            return;
        }
    }
}

