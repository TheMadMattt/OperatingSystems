//
// Created by mateusz on 25.05.19.
//

#ifndef HOUSEMULTITHREADING_TELEWIZOR_H
#define HOUSEMULTITHREADING_TELEWIZOR_H

#include "../HouseSetup.h"
#include <deque>

#define personsCounter 3

enum ForkStatus{
    IN_USE, AVAILABLE
};

class TV {

    TV(int id, HouseSetup &houseSetup);

    void useTV(int personId);
    void releaseTV(int personId);

private:
    int id;
    std::deque<int> persons;
    HouseSetup &houseSetup;

    std::mutex mutexTV;

    int placeCounter = 0;

};


#endif //HOUSEMULTITHREADING_TELEWIZOR_H
