//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_PERSON_H
#define HOUSEMULTITHREADING_PERSON_H


#include "../HouseSetup.h"
#include "../Printing.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream

class Person {
public:
    Person(int id, unsigned int age, Printing &print, HouseSetup &houseSetup);
    Person(Person &&other) noexcept;
    ~Person();

    virtual void startHouse() {}

    virtual std::string getPersonStatus(){};

    void randomSleep(int min, int max);
    int randInt(int min, int max);

    virtual void watchingTV() {};
    virtual void showering() {};
    virtual void eating() {};

    std::string getProgress();

    Printing &print;
    HouseSetup &houseSetup;

protected:
    int id;
    int age;
    float progress;
};


#endif //HOUSEMULTITHREADING_PERSON_H
