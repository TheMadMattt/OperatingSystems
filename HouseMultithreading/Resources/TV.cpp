//
// Created by mateusz on 25.05.19.
//

#include "TV.h"

TV::TV(int id, HouseSetup &houseSetup)
    :   id(id),
        houseSetup(houseSetup)
{}

void TV::useTV(int personId) {

    if(placeCounter == personsCounter){
        houseSetup.waitForTV();
    }else{
        std::scoped_lock<std::mutex> scopedLock(mutexTV);
        this->persons.push_back(personId);
        ++placeCounter;
    }

}

void TV::releaseTV(int personId) {

    for (int i = 0; i < this->persons.size(); ++i) {
        if(this->persons[i] == personId){
            this->persons.erase(this->persons.begin()+i);
        }
    }
    --placeCounter;

    houseSetup.notifyTV();

}
