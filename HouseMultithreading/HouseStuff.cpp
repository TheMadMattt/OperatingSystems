//
// Created by mateusz on 01.06.19.
//

#include "HouseStuff.h"

HouseStuff::HouseStuff(int peopleInHouse, Printing &printing)
    :   tv(0,printing),
        shower(0,printing)
{

    if(peopleInHouse <= 2){
        this->peopleInHouse = peopleInHouse;
    }else{
        this->peopleInHouse = peopleInHouse/2;
    }
    for (int i = 0; i < this->peopleInHouse; ++i) {
        chairList.emplace_back(i, std::ref(printing));
    }

}
