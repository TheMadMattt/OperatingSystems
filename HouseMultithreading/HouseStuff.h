//
// Created by mateusz on 01.06.19.
//

#ifndef HOUSEMULTITHREADING_HOUSESTUFF_H
#define HOUSEMULTITHREADING_HOUSESTUFF_H


#include "Resources/Shower.h"
#include "Resources/TV.h"
#include "Resources/Chair.h"

class HouseStuff {

public:
    HouseStuff(int peopleInHouse, Printing &printing);
    TV tv;
    Shower shower;
    std::deque<Chair> chairList;
private:
    int peopleInHouse;
};


#endif //HOUSEMULTITHREADING_HOUSESTUFF_H
