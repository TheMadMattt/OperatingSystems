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
        watchingTV();
        showering();
    }while(!houseSetup.finishedHouse);
}

Adult::~Adult() {

}

std::string Adult::getPersonStatus(){
    std::string message = "Adult " + std::to_string(getId());

    switch (adultStatus){
        case AdultStatus::WATCHING:
            message += " is watching TV";
            break;
        case AdultStatus::SHOWERING:
            message += " is showering";
            break;
        case IDLE:
            message += " is waiting";
            break;
    }

    return message;
}

void Adult::setAdultStatus(AdultStatus _adultStatus) {
    this->adultStatus = _adultStatus;

    print.updateMenu(getId(),getPersonStatus());
}

void Adult::watchingTV() {

    houseStuff.tv.useTV(getId());
    setAdultStatus(WATCHING);
    Person::randomSleep(1,4);
    houseStuff.tv.releaseTV(getId());
    setAdultStatus(IDLE);
}

void Adult::showering() {

    houseStuff.shower.takeShower(getId());
    setAdultStatus(SHOWERING);
    Person::randomSleep(1,4);
    houseStuff.shower.releaseShower();
    setAdultStatus(IDLE);
}

