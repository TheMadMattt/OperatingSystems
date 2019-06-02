//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Child.h"

Child::Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, HouseStuff &houseStuff)
    :   houseStuff(houseStuff),
        childStatus(IDLE),
        Person(id, age, print, houseSetup) {}

Child::~Child() {}

void Child::startHouse() {

    houseSetup.waitForStart();

    do {
        eating();
        playingConsole();
        showering();
        watchingTV();
    }while(!houseSetup.finishedHouse);

    setChildStatus(FINISHED);
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
        case EATING:
            message += " is eating";
            break;
        case FINISHED:
            message += " has finished work";
            break;
    }

    return message;
}

void Child::setChildStatus(ChildStatus _childStatus) {
    this->childStatus = _childStatus;

    print.updateMenu(getId(),getPersonStatus());

}

void Child::watchingTV() {

    houseStuff.tv.useTV(getId());
    setChildStatus(WATCHING);
    Person::randomSleep(1,4);
    houseStuff.tv.releaseTV(getId());
    setChildStatus(IDLE);
}

void Child::showering() {

    houseStuff.shower.takeShower(getId());
    setChildStatus(SHOWERING);
    Person::randomSleep(1,4);
    houseStuff.shower.releaseShower();
    setChildStatus(IDLE);
}

void Child::eating() {

    for (auto & i : houseStuff.chairList) {
        if(!i.isChairAvailable()){
            i.takeChair(getId());
            std::scoped_lock scopedLock(i.getMutexChair());
            setChildStatus(EATING);
            Person::randomSleep(1,4);
            i.releaseChair();
            setChildStatus(IDLE);
            return;
        }
    }
}

void Child::playingConsole() {

    houseStuff.tv.playOnConsole(getId());
    setChildStatus(PLAYING);
    Person::randomSleep(1,4);
    houseStuff.tv.releaseConsole(getId());
    setChildStatus(IDLE);

}
