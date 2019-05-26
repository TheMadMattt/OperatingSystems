//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Adult.h"

Adult::Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv)
    :   houseSetup(houseSetup),
        tv(tv),
        adultStatus(IDLE),
        Person(id, age, print) {}

void Adult::startHouse() {

    houseSetup.waitForStart();

    watchingTV();
}

Adult::~Adult() {

}

std::string Adult::getAdultStatus(){
    std::string message = "Adult " + std::to_string(getId());

    switch (adultStatus){
        case AdultStatus::WATCHING:
            message += " is watching TV";
            break;
        case AdultStatus::SHOWERING:
            message += " is showering";
            break;
        case IDLE:
            message += "is waiting";
            break;
        case STOPPED_WATCHING:
            message += " stopped watching TV";
            break;
    }

    return message;
}

void Adult::setAdultStatus(AdultStatus _adultStatus) {
    this->adultStatus = _adultStatus;
}

void Adult::watchingTV() {

    tv.useTV(getId());
    setAdultStatus(AdultStatus::WATCHING);
    std::cout << getAdultStatus() << std::endl;
    Person::randomSleep(1,4);
    tv.releaseTV(getId());
    setAdultStatus(AdultStatus::STOPPED_WATCHING);
    std::cout << getAdultStatus() << std::endl;
}

