//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Child.h"

Child::Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv)
    :   tv(tv),
        childStatus(IDLE),
        Person(id, age, print, houseSetup) {}

void Child::startHouse() {

    houseSetup.waitForStart();

    watchingTV();
}

Child::~Child() {}

std::string Child::getPersonStatus(){

    std::string message = "Child " + std::to_string(getId());

    switch (childStatus){
        case WATCHING:
            message += " is watching TV";
            break;
        case SHOWERING:
            message += " is showering";
            break;
        case PLAYING:
            message += " is playing game";
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

void Child::setChildStatus(ChildStatus _childStatus) {
    this->childStatus = _childStatus;

    print.updateMenu(getId(),getPersonStatus());

}

void Child::watchingTV() {

    tv.useTV(getId());
    setChildStatus(ChildStatus::WATCHING);
    //std::cout << getPersonStatus() << std::endl;
    Person::randomSleep(1,4);
    tv.releaseTV(getId());
    setChildStatus(ChildStatus ::STOPPED_WATCHING);
    //std::cout << getPersonStatus() << std::endl;
}
