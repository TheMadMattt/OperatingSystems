//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_HOUSE_H
#define HOUSEMULTITHREADING_HOUSE_H

#include <deque>
#include "Threads/Person.h"
#include <thread>


class House {
public:
    House(int adultsNumber, int childrenNumber);

    void start();

    HouseSetup houseSetup;
    Printing print;
private:
    int adultsNumber;
    int childrenNumber;

    std::deque<std::thread> persons;

    void createPersons();

    void stop();
};


#endif //HOUSEMULTITHREADING_HOUSE_H
