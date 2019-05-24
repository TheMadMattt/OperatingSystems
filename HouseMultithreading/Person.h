//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_PERSON_H
#define HOUSEMULTITHREADING_PERSON_H


#include "SyncingChannel.h"
#include "Printing.h"
#include <thread>

class Person {
public:
    Person(int id, unsigned int age, HouseSetup &houseSetup, Printing &print);
    Person(Person &&other) noexcept;
    ~Person();

    virtual void startHouse() {}

    void randomSleep(int min, int max);

    HouseSetup &houseSetup;

private:
    int id;
    int age;

    Printing &print;
};


#endif //HOUSEMULTITHREADING_PERSON_H
