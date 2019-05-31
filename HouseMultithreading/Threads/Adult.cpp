//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Adult.h"

Adult::Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv, Shower &shower)
    :   tv(tv),
        shower(shower),
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
        case STOPPED_WATCHING:
            message += " stopped watching TV";
            break;
    }

    return message;
}

void Adult::setAdultStatus(AdultStatus _adultStatus) {
    this->adultStatus = _adultStatus;

    print.updateMenu(getId(),getPersonStatus());
}

void Adult::watchingTV() {

    tv.waitForTV();
    tv.useTV(getId());
    setAdultStatus(AdultStatus::WATCHING);
    Person::randomSleep(1,4);
    tv.releaseTV(getId());
    setAdultStatus(IDLE);
}

void Adult::showering() {

    shower.takeShower(getId());
    setAdultStatus(SHOWERING);
    Person::randomSleep(1,4);
    shower.releaseShower();
    setAdultStatus(IDLE);
}

