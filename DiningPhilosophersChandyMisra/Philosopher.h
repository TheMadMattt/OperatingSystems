//
// Created by mateusz on 21.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H
#define DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H


#include <thread>
#include "Fork.h"

enum PhilStatus{
    EATING, THINKING, REQUESTING, TOOK_RIGH_FORK, TOOK_LEFT_FORK, PUT_DOWN_LEFT_FORK, PUT_DOWN_RIGHT_FORK
};

class Philosopher {

private:
    int id;
    Fork& rightFork;
    Fork& leftFork;
    std::thread philThread;
    PhilStatus status;

    TableSetup& table;

public:
    Philosopher(int id, TableSetup& tableChannel, Fork & right, Fork & left);
    ~Philosopher();

    void startDinner();

    void eat();
    void think();

    void requestForks();
    void putDownForks();

    std::string getStatus();

    void setStatus(PhilStatus status);

    int getRandom(double min, double max);

};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PHILOSOPHER_H
