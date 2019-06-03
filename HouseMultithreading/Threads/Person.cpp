//
// Created by mateusz on 24.05.19.
//

#include <random>
#include <thread>
#include "Person.h"

Person::Person(int id, unsigned int age, Printing &print, HouseSetup &houseSetup)
    :   id(id),
        age(age),
        print(print),
        houseSetup(houseSetup),
        cycle(0)
{}


Person::Person(Person &&other) noexcept
    :   id(other.id),
        age(other.age),
        print(other.print),
        houseSetup(other.houseSetup),
        cycle(other.cycle)
{}

Person::~Person() = default;

void Person::randomSleep(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> generator(min, max);

    int randSleepTime = generator(mt);

    std::this_thread::sleep_for(std::chrono::seconds(randSleepTime));

}