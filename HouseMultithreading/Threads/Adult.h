//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_ADULT_H
#define HOUSEMULTITHREADING_ADULT_H


#include "Person.h"

class Adult: public Person {

public:
    Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print);

    ~Adult();

    void startHouse() override;

private:
    HouseSetup &houseSetup;
};


#endif //HOUSEMULTITHREADING_ADULT_H
