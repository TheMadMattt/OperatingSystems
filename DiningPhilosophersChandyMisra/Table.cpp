//
// Created by mateusz on 25.03.19.
//

#include "Table.h"

Table::Table(int philosophersNumber)
    :   philosophersNumber(philosophersNumber),
        print(tableSetup)
{
    createForks();
    createPhilosophers();
    print.createMenu(getPhilosophersStatus());
}

std::vector<std::string> Table::getPhilosophersStatus() {

    auto status = std::vector<std::string>();
    for(auto &philosopher : philosophersList)
        status.emplace_back(philosopher.getPhilosopherStatus());
    status.emplace_back("\0");
    return status;

}

void Table::createForks() {

    for(int i = 0; i < philosophersNumber; i++) {
        if(i == philosophersNumber - 1)
            forksList.emplace_back(i, 0, tableSetup);
        else
            forksList.emplace_back(i, i, tableSetup);
    }
}

void Table::createPhilosophers() {

    for(uint i = 0; i < philosophersNumber; i++) {
        if (i == philosophersNumber - 1)
            philosophersList.emplace_back(i, tableSetup, forksList[i], forksList[0], print);
        else
            philosophersList.emplace_back(i, tableSetup, forksList[i], forksList[i+1], print);
    }
}

void Table::startDinner() {

    tableSetup.syncChannel.notifyAllThreads();

    print.menu();

    stopDinner();

}

void Table::stopDinner() {

    tableSetup.finishedDinner = true;
}
