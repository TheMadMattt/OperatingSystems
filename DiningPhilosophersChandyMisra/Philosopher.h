//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H
#define DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H

#include <thread>
#include "Fork.h"
#include "Printing.h"

enum PhilosopherStatus{
    EATING,
    THINKING,
    REQUESTING,
    TOOK_RIGHT_FORK,
    TOOK_LEFT_FORK,
    PUT_DOWN_LEFT_FORK,
    PUT_DOWN_RIGHT_FORK,
    FINISHED_DINNER
};

class Philosopher {

public:

    Philosopher(int id, TableSetup &tableSetup, Fork &leftFork, Fork &rightFork, Printing &print);
    Philosopher(Philosopher&& other) noexcept;
    ~Philosopher();

    std::string getPhilosopherStatus();

    void startDinnerThread();

private:
    int id;
    TableSetup &tableSetup;
    Fork &leftFork;
    Fork &rightFork;

    std::thread philosopherThread;

    Printing &print;

    PhilosopherStatus status = PhilosopherStatus::THINKING;

    void thinking();
    void eating();
    void requestForks();
    void putDownForks();
    void finishDinner();

    void setStatus(PhilosopherStatus status);

    void sleepRandom(double min, double max);
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H
