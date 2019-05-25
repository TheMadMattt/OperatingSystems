//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_PERSON_H
#define HOUSEMULTITHREADING_PERSON_H


#include "HouseSetup.h"
#include "Printing.h"

class Person {
public:
    Person(int id, unsigned int age, Printing &print);
    Person(Person &&other) noexcept;
    ~Person();

    virtual void startHouse() {}

    void randomSleep(int min, int max);

private:
    int id;
    int age;

    Printing &print;
};


#endif //HOUSEMULTITHREADING_PERSON_H
