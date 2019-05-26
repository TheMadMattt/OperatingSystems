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

    void randomSleep(int min, int max);

    int getId() const;

    virtual void watchingTV() {};

    Printing &print;
    HouseSetup &houseSetup;
private:
    int id;
    int age;
};


#endif //HOUSEMULTITHREADING_PERSON_H
