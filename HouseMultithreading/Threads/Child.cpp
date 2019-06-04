//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include <thread>
#include "Child.h"

Child::Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, HouseStuff &houseStuff, int adultsNumber)
    :   houseStuff(houseStuff),
        childStatus(IDLE),
        adultsNumber(adultsNumber),
        Person(id, age, print, houseSetup) {
}

Child::~Child() = default;

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

    std::string message = " | Child " + std::to_string(id-adultsNumber);

    switch (childStatus){
        case WATCHING:
            message += "    is watching TV";
            break;
        case SHOWERING:
            message += "      is showering";
            break;
        case PLAYING:
            message += "   is playing game";
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

void Child::setChildStatus(ChildStatus _childStatus) {
    this->childStatus = _childStatus;

    print.updateMenu(id, getPersonStatus(), getProgress());

}

void Child::watchingTV() {

    int randWatch = Person::randInt();
    progress = 0.0;

    houseStuff.tv.useTV(id);
    for (int i = 1; i <= randWatch; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = (100.0*i)/randWatch;
        setChildStatus(WATCHING);
    }
    houseStuff.tv.releaseTV(id);
    setChildStatus(IDLE);
}

void Child::showering() {

    int randShower = Person::randInt();
    progress = 0.0;

    houseStuff.shower.takeShower(id);
    for (int i = 1; i <= randShower; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = (100.0*i)/randShower;
        setChildStatus(SHOWERING);
    }
    houseStuff.shower.releaseShower();
    setChildStatus(IDLE);
}

void Child::eating() {

    int randEat = Person::randInt();
    progress = 0.0;

    for (auto & chair : houseStuff.chairList) {
        if(!chair.isChairAvailable()){
            chair.takeChair(id);
            std::scoped_lock scopedLock(chair.getMutexChair());
            for (int i = 1; i <= randEat; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                progress = (100.0*i)/randEat;
                setChildStatus(EATING);
            }
            chair.releaseChair();
            setChildStatus(IDLE);
            return;
        }
    }
}

void Child::playingConsole() {

    int randPlay = Person::randInt();
    progress = 0.0;

    houseStuff.tv.playOnConsole(id);
    for (int i = 1; i <= randPlay; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = (100.0*i)/randPlay;
        setChildStatus(PLAYING);
    }
    houseStuff.tv.releaseConsole(id);
    setChildStatus(IDLE);

}
