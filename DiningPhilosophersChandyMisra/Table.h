//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_TABLE_H
#define DININGPHILOSOPHERSCHANDYMISRA_TABLE_H

#include <deque>
#include "Philosopher.h"

class Table {

public:

    Table(int philosophersNumber);

    std::vector<std::string> getPhilosophersStatus();

    void startDinner();

    int philosophersNumber;

    TableSetup tableSetup;
    Printing print;
private:

    std::deque<Philosopher> philosophersList;
    std::deque<Fork> forksList;

    void createPhilosophers();
    void createForks();
    void stopDinner();
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_TABLE_H
