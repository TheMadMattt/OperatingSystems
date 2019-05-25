//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Adult.h"

Adult::Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print)
    :   houseSetup(houseSetup),
        Person(id, age, print) {}

void Adult::startHouse() {

    houseSetup.waitForStart();

    for(int i=0;i<10;i++) {
        std::cout << "Adult" << std::endl;
        Person::randomSleep(100,200);
    }
}

Adult::~Adult() {

}

