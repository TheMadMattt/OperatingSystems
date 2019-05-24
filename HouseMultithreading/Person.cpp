//
// Created by mateusz on 24.05.19.
//

#include <random>
#include "Person.h"

Person::Person(int id, unsigned int age, HouseSetup &houseSetup, Printing &print)
    :   id(id),
        age(age),
        houseSetup(houseSetup),
        print(print)
{}


Person::Person(Person &&other) noexcept
    :   id(other.id),
        age(other.age),
        houseSetup(other.houseSetup),
        print(other.print)
{}

Person::~Person() {}

void Person::randomSleep(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> generator(min, max);

    int randSleepTime = generator(mt);

    std::this_thread::sleep_for(std::chrono::milliseconds(randSleepTime));

}