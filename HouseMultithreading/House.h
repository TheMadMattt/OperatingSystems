//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_HOUSE_H
#define HOUSEMULTITHREADING_HOUSE_H

#include <deque>
#include "Threads/Person.h"
#include "Resources/TV.h"
#include "Resources/Shower.h"
#include "HouseStuff.h"
#include <thread>


class House {
public:
    House(int adultsNumber, int childrenNumber);

    void start();

    std::vector<std::string> getPersonsStatus();

    std::vector<std::pair<std::string,std::string>> getResourcesStatus();

    HouseSetup houseSetup;
    Printing print;
    HouseStuff houseStuff;
private:
    int adultsNumber;
    int childrenNumber;

    std::deque<std::thread> personsThread;
    std::deque<Person*> persons;

    void createPersons();

    void stop();
};


#endif //HOUSEMULTITHREADING_HOUSE_H
