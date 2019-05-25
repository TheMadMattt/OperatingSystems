//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Child.h"

Child::Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print)
    :   houseSetup(houseSetup),
        Person(id, age, print) {}

void Child::startHouse() {

    houseSetup.waitForStart();

    for(int i=0;i<10;i++) {
        std::cout << "Child" << std::endl;
        Person::randomSleep(100,200);
    }
}

Child::~Child() {}
