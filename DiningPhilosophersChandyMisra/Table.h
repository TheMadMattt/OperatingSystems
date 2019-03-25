#ifndef DININGPHILOSOPHERSCHANDYMISRA_TABLE_H
#define DININGPHILOSOPHERSCHANDYMISRA_TABLE_H

#include <vector>
#include "Philosopher.h"
#include "Fork.h"
#include "Printing.h"

class Table {

public:
    Table(int philosopherNumber);

    void startDinner();
    std::vector<std::string> getPhilosophersStates();

    int philosophersNumber;
    TableSetup table;
    Printing print;

private:
    std::vector<Philosopher> philosophersList;
    std::vector<Fork> forksList;

    void createForks();
    void createPhilosophers();

    void stop();
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_TABLE_H
