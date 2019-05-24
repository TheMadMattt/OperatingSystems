//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_ADULT_H
#define HOUSEMULTITHREADING_ADULT_H


#include "Person.h"

class Adult: public Person {

public:
    Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print);

    Adult(Adult &&other) noexcept ;

    ~Adult();

    void startHouse() override;

private:
    std::thread adultThread;
};


#endif //HOUSEMULTITHREADING_ADULT_H
