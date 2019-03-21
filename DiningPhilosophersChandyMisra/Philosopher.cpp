//
// Created by mateusz on 21.03.19.
//

#include <unistd.h>
#include <string>
#include "Philosopher.h"

Philosopher::Philosopher(int id, TableSetup& tableChannel, Fork & right, Fork & left)
    :id(id),
    table(tableChannel),
    rightFork(right),
    leftFork(left)
{
}

Philosopher::~Philosopher() {

    philThread.join();

}

void Philosopher::startDinner() {

    table.channel.wait();

    do{
        think();
        eat();
    }while(1);

}

void Philosopher::requestForks() {
    setStatus(PhilStatus::REQUESTING);
    rightFork.requestFork(id);
    setStatus(PhilStatus::TOOK_RIGH_FORK);
    leftFork.requestFork(id);
    setStatus(PhilStatus::TOOK_LEFT_FORK);
}

void Philosopher::putDownForks() {

    leftFork.freeFork();
    setStatus(PhilStatus::PUT_DOWN_LEFT_FORK);
    sleep(500);

    rightFork.freeFork();
    setStatus(PhilStatus::PUT_DOWN_RIGHT_FORK);
    sleep(500);

    setStatus(PhilStatus::THINKING);

    leftFork.setStatus(ForkStatus::CLEAN);
    rightFork.setStatus(ForkStatus::CLEAN);

}

void Philosopher::think() {
    setStatus(PhilStatus::THINKING);
    usleep(static_cast<__useconds_t>(getRandom(2.5, 3.5)));
}

void Philosopher::eat() {

    requestForks();

    std::lock(leftFork.getMutex(), rightFork.getMutex());

    std::lock_guard<std::mutex> leftForkLock(leftFork.getMutex(), std::adopt_lock);
    std::lock_guard<std::mutex> rightForkLock(rightFork.getMutex(), std::adopt_lock);

    leftFork.setStatus(ForkStatus::DIRTY);
    rightFork.setStatus(ForkStatus::DIRTY);

    setStatus(PhilStatus::EATING);

    usleep(static_cast<__useconds_t>(getRandom(2.5, 3.5)));

    putDownForks();

}

std::string Philosopher::getStatus(){

    std::string message = "Phil" + std::to_string(id);

    switch(status){
        case PhilStatus::THINKING:
            message += " is THINKING";
            break;
        case PhilStatus::EATING:
            message += " is EATING";
            break;
        case PhilStatus::REQUESTING:
            message += " is REQUESTING forks";
            break;
        case PhilStatus::PUT_DOWN_RIGHT_FORK:
            message += " is PUTTING DOWN RIGHT FORK";
            break;
        case PhilStatus::PUT_DOWN_LEFT_FORK:
            message += " is PUTTING DOWN LEFT FORK";
            break;
        case PhilStatus::TOOK_LEFT_FORK:
            message += " TOOK LEFT FORK";
            break;
        case PhilStatus::TOOK_RIGH_FORK:
            message += " TOOK RIGHT FORK";
            break;
    }

    return message;

}

void Philosopher::setStatus(PhilStatus status) {
    Philosopher::status = status;
}

int Philosopher::getRandom(double min, double max) {

    return static_cast<int>(((max - min) * ((double) rand() / (double) RAND_MAX) + min) * 1000000);

}
