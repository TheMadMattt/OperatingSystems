#ifndef DININGPHILOSOPHERS_PHILOSOPHER_H
#define DININGPHILOSOPHERS_PHILOSOPHER_H

#include <vector>
#include "Fork.h"

using namespace std;


class Philosopher {

private:
    int id;
    Fork rightFork;
    Fork leftFork;
    int state;
public:
    int getId() const;

    void setId(int id);

public:;

    Philosopher();
    Philosopher(int id);

    void eat();
    void think();
    void hungry();

    void takeUpForks();
    void returnForks();

    int getState() const;

    void setState(int state);

    int getRandom();

    enum State{
        HUNGRY, THINKING, SLEEPING, EATING
    };
};


#endif //DININGPHILOSOPHERS_PHILOSOPHER_H
