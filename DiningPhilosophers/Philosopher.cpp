//
// Created by mateusz on 08.03.19.
//

#include <iostream>
#include "Philosopher.h"
#include <vector>

Philosopher::Philosopher() {
}

Philosopher::Philosopher(int id) {
    this->id = id;
}

void Philosopher::eat() {

    cout << "Filozof " << id << " je obiad." << endl;

}

void Philosopher::think() {

    cout << "Filozof " << id << " myśli." << endl;
}

void Philosopher::hungry() {

    cout << "Filozof " << id << " jest głodny." << endl;

}

int Philosopher::getRandom() {

    double max, min;

    max = 3.5;
    min = 2.5;

    return static_cast<int>(((max - min) * ((double) rand() / (double) RAND_MAX) + min) * 1000000);

}

void Philosopher::takeUpForks() {

    if(rightFork.getStatus() == Fork::ForkStatus::FREE){
        rightFork.takeFork();
        cout << "Filozof " << id << " podniósł prawy widelec." << endl;
    }
    if(leftFork.getStatus() == Fork::ForkStatus::FREE){
        leftFork.takeFork();
        cout << "Filozof " << id << " podniósł lewy widelec." << endl;
    }

}

void Philosopher::returnForks() {

    if(rightFork.getStatus() == Fork::ForkStatus::TAKEN){
        rightFork.putDownFork();
        cout << "Filozof " << id << " odłożył prawy widelec." << endl;
    }
    if(leftFork.getStatus() == Fork::ForkStatus::TAKEN){
        leftFork.putDownFork();
        cout << "Filozof " << id << " odłożył lewy widelec." << endl;
    }
}

int Philosopher::getState() const {
    return state;
}

void Philosopher::setState(int state) {
    Philosopher::state = state;
}

int Philosopher::getId() const {
    return id;
}

void Philosopher::setId(int id) {
    Philosopher::id = id;
}
