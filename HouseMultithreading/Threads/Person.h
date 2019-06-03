//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_PERSON_H
#define HOUSEMULTITHREADING_PERSON_H


#include "../HouseSetup.h"
#include "../Printing.h"

class Person {
public:
    Person(int id, unsigned int age, Printing &print, HouseSetup &houseSetup);
    Person(Person &&other) noexcept;
    ~Person();

    virtual void startHouse() {}

    virtual std::string getPersonStatus(){};
    std::string getHouseCycle(){return "Cykl " + std::to_string(cycle);};

    void randomSleep(int min, int max);

    virtual void watchingTV() {};
    virtual void showering() {};
    virtual void eating() {};

    Printing &print;
    HouseSetup &houseSetup;

protected:
    int id;
    int age;
    int cycle;
};


#endif //HOUSEMULTITHREADING_PERSON_H
