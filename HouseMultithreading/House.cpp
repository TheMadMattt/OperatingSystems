//
// Created by mateusz on 24.05.19.
//

#include "House.h"
#include "Child.h"
#include "Adult.h"

House::House(int adultsNumber, int childrenNumber)
    :   adultsNumber(adultsNumber),
        childrenNumber(childrenNumber),
        print(houseSetup)
{
    createPersons();
}

void House::createPersons() {

    for(int i = 0; i < adultsNumber; ++i) {
        persons.emplace_back(Adult(i,35,houseSetup,print));
    }

    for (int j = 0; j < childrenNumber; ++j) {
        persons.emplace_back(Child(j+adultsNumber,16,houseSetup,print));
    }

}

void House::start() {

    houseSetup.syncChannel.notifyAllThreads();

    stop();

}

void House::stop() {

    houseSetup.finishedDinner = true;

}
