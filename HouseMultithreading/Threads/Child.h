//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_CHILD_H
#define HOUSEMULTITHREADING_CHILD_H


#include "Person.h"

class Child: public Person {
public:
    Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print);
    ~Child();

    void startHouse() override;

private:

    HouseSetup &houseSetup;
};


#endif //HOUSEMULTITHREADING_CHILD_H
