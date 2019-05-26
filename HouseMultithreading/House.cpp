//
// Created by mateusz on 24.05.19.
//

#include "House.h"
#include "Threads/Child.h"
#include "Threads/Adult.h"

House::House(int adultsNumber, int childrenNumber)
    :   adultsNumber(adultsNumber),
        childrenNumber(childrenNumber),
        tv(0),
        print(houseSetup)
{
    createPersons();
}

void House::createPersons() {

    for (int i = 0; i < adultsNumber; ++i) {
        auto *adult = new Adult(i,35,std::ref(houseSetup),std::ref(print), std::ref(tv));
        persons.emplace_back(std::thread(&Adult::startHouse, adult));
    }

    for (int j = 0; j < childrenNumber; ++j) {
        auto *child = new Child(j+adultsNumber,16,std::ref(houseSetup),std::ref(print), std::ref(tv));
        persons.emplace_back(std::thread(&Child::startHouse, child));
    }

}

void House::start() {

    houseSetup.notifyAllThreads();

    stop();

}

void House::stop() {

    houseSetup.finishedDinner = true;
    for (auto & person : persons) {
        person.join();
    }

}
