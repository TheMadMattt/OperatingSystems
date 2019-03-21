//
// Created by mateusz on 21.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_TABLE_H
#define DININGPHILOSOPHERSCHANDYMISRA_TABLE_H


#include <vector>
#include "Philosopher.h"

class Table {

private:
    std::vector<Philosopher> philosophersList;
    std::vector<Fork> forksList;

public:

    Table(int philosopherNumber);

    int philosophersNumber;
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_TABLE_H
