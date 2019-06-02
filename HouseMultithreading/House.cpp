//
// Created by mateusz on 24.05.19.
//

#include "House.h"
#include "Threads/Child.h"
#include "Threads/Adult.h"

House::House(int adultsNumber, int childrenNumber)
    :   adultsNumber(adultsNumber),
        childrenNumber(childrenNumber),
        houseStuff(adultsNumber + childrenNumber, std::ref(print)),
        print(std::ref(houseSetup))
{
    createPersons();
    print.createMenu(getPersonsStatus(), getResourcesStatus());
}

void House::createPersons() {

    for (int i = 0; i < adultsNumber; ++i) {
        auto *adult = new Adult(i,35,std::ref(houseSetup),std::ref(print), std::ref(houseStuff));
        persons.emplace_back(adult);
        personsThread.emplace_back(std::thread(&Adult::startHouse, adult));
    }

    for (int j = 0; j < childrenNumber; ++j) {
        auto *child = new Child(j+adultsNumber,16,std::ref(houseSetup),std::ref(print), std::ref(houseStuff));
        persons.emplace_back(child);
        personsThread.emplace_back(std::thread(&Child::startHouse, child));
    }

}

void House::start() {

    houseSetup.notifyAllThreads();

    print.menu();

    stop();

}

void House::stop() {

    houseSetup.finishedHouse = true;
    for (auto & person : personsThread) {
        if(person.joinable()) {
            person.join();
        }
    }

}

std::vector<std::string> House::getPersonsStatus() {

    auto status = std::vector<std::string>();
    for(auto &person : persons)
        status.emplace_back(person->getPersonStatus());
    status.emplace_back("\0");
    return status;

}

std::vector<std::pair<std::string,std::string>> House::getResourcesStatus() {

    auto status = std::vector<std::pair<std::string,std::string>>();
    status.emplace_back("TV", houseStuff.tv.getStatus());
    status.emplace_back("SHOWER",houseStuff.shower.getShowerStatus());
    status.emplace_back("CONSOLE", houseStuff.console.getStatus());
    for (auto & chair : houseStuff.chairList) {
        status.emplace_back("CHAIR"+ std::to_string(chair.getId()),chair.getStatus());
    }
    status.emplace_back("", "\0");
    return status;

}
