//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Child.h"

Child::Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv, Shower &shower)
    :   tv(tv),
        shower(shower),
        childStatus(IDLE),
        Person(id, age, print, houseSetup) {}

Child::~Child() {}

void Child::startHouse() {

    houseSetup.waitForStart();

    do {
        watchingTV();
        showering();
    }while(!houseSetup.finishedHouse);


}

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

    tv.waitForTV();
    tv.useTV(getId());
    setChildStatus(ChildStatus::WATCHING);
    Person::randomSleep(1,4);
    tv.releaseTV(getId());
    setChildStatus(ChildStatus ::STOPPED_WATCHING);
}

void Child::showering() {

    shower.takeShower(getId());
    setChildStatus(SHOWERING);
    Person::randomSleep(1,4);
    shower.releaseShower();
    setChildStatus(IDLE);
}
