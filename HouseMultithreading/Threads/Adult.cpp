//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include <thread>
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

    print.updateMenu(id, getPersonStatus(), getProgress());
}

void Adult::watchingTV() {

    int randWatch = Person::randInt(20,30);
    progress = 0.0;

    houseStuff.tv.useTV(id);
    for (int i = 1; i <= randWatch; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = (100.0*i)/randWatch;
        setAdultStatus(WATCHING);
    }
    houseStuff.tv.releaseTV(id);
    setAdultStatus(IDLE);
}

void Adult::showering() {

    int randShower = Person::randInt(20,30);
    progress = 0.0;

    houseStuff.shower.takeShower(id);
    for (int i = 1; i <= randShower; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = (100.0*i)/randShower;
        setAdultStatus(SHOWERING);
    }
    houseStuff.shower.releaseShower();
    setAdultStatus(IDLE);
}

void Adult::eating() {

    int randEat = Person::randInt(20,30);
    progress = 0.0;

    for (auto & chair : houseStuff.chairList) {
        if(!chair.isChairAvailable()){
            chair.takeChair(id);
            std::scoped_lock scopedLock(chair.getMutexChair());
            for (int i = 1; i <= randEat; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                progress = (100.0*i)/randEat;
                setAdultStatus(EATING);
            }
            chair.releaseChair();
            setAdultStatus(IDLE);
            return;
        }
    }
}

