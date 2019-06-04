//
// Created by mateusz on 24.05.19.
//

#include <random>
#include <thread>
#include <sstream>
#include "Person.h"

Person::Person(int id, unsigned int age, Printing &print, HouseSetup &houseSetup)
    :   id(id),
        age(age),
        print(print),
        houseSetup(houseSetup),
        progress(0.0)
{}


Person::Person(Person &&other) noexcept
    :   id(other.id),
        age(other.age),
        print(other.print),
        houseSetup(other.houseSetup),
        progress(other.progress)
{}

Person::~Person() = default;

int Person::randInt() {

    int min = 30;
    int max = 50;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> generator(min, max);

    int randInt = generator(mt);

    return randInt;
}

std::string Person::getProgress(){

    std::stringstream stream;
    stream << std::fixed << std::setprecision(0) << progress;
    std::string s = stream.str();

    std::string workProgress = "Progres: " + s + "  %";

    return workProgress;
}
