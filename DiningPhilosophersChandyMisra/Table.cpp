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
    print.createMenu(getPhilosophersStatus(), getPhilosophersCycle());
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
        forksList.emplace_back(i%philosophersNumber, i%philosophersNumber, tableSetup);
    }
}

void Table::createPhilosophers() {

    for(int i = 0; i < philosophersNumber; i++) {
        philosophersList.emplace_back(i, tableSetup, forksList[i % philosophersNumber], forksList[(i+1)%philosophersNumber], print);
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

std::vector<std::string> Table::getPhilosophersCycle() {

    auto cycles = std::vector<std::string>();

    for(auto &philosopher : philosophersList)
        cycles.emplace_back(philosopher.getDinnerCycle());
    cycles.emplace_back("\0");

    return cycles;
}
