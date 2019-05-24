//
// Created by mateusz on 24.05.19.
//

#include <iostream>
#include "Adult.h"

Adult::Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print)
    :   adultThread(&Adult::startHouse, this),
        Person(id, age, houseSetup, print) {}

void Adult::startHouse() {

    houseSetup.syncChannel.wait();

    for(int i=0;i<10;i++) {
        std::cout << "Adult" << std::endl;
        Person::randomSleep(100,200);
    }
}

Adult::~Adult() {

    if(adultThread.joinable()){
        adultThread.detach();
    }else{
        adultThread.join();
    }
}

Adult::Adult(Adult &&other) noexcept : Person(std::move(other)), adultThread(std::move(other.adultThread)) {}
