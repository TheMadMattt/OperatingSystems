//
// Created by mateusz on 21.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H
#define DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H


#include <thread>
#include "Fork.h"
#include "Printing.h"

enum PhilStatus{
    EATING, THINKING, REQUESTING, TOOK_RIGH_FORK, TOOK_LEFT_FORK, PUT_DOWN_LEFT_FORK, PUT_DOWN_RIGHT_FORK
};

class Philosopher {

private:
    int id = -1;
    TableSetup &table;
    Fork &rightFork;
    Fork &leftFork;
    std::thread philThread;
    PhilStatus status;

    Printing &print;

    void eat();
    void think();

    void requestForks();
    void putDownForks();

    void sleepRandom(double min, double max);

public:
    Philosopher(int id, TableSetup& tableSetup, Fork & right, Fork & left, Printing &print);
    Philosopher(Philosopher&& other) noexcept ;
    ~Philosopher();

    void startDinner();

    std::string getStatus();

    void setStatus(PhilStatus status);

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H
