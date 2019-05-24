//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Child.h"

Child::Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print)
    :   childThread(&Child::startHouse, this),
        Person(id, age, houseSetup, print) {}

void Child::startHouse() {

    houseSetup.syncChannel.wait();

    for(int i=0;i<10;i++) {
        std::cout << "Child" << std::endl;
        Person::randomSleep(100,200);
    }
}

Child::~Child() {

    if(childThread.joinable()){
        childThread.detach();
    }else{
        childThread.join();
    }
}

Child::Child(Child &&other) noexcept : Person(std::move(other)), childThread(std::move(other.childThread)) {}

