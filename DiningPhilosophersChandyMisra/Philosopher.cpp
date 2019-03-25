
#include <unistd.h>
#include <string>
#include "Philosopher.h"

Philosopher::Philosopher(int id, TableSetup &tableSetup, Fork &right, Fork &left, Printing &print)
    :id(id),
    table(tableSetup),
    rightFork(right),
    leftFork(left),
    philThread(&Philosopher::startDinner, this),
    print(print)
{}

Philosopher::Philosopher(Philosopher && other) noexcept
        : id(other.id)
        , table(other.table)
        , leftFork(other.leftFork)
        , rightFork(other.rightFork)
        , philThread(std::move(other.philThread))
        , print(other.print)
{}

Philosopher::~Philosopher() {
    if(philThread.joinable()){
        philThread.detach();
    }

}

void Philosopher::startDinner() {

    table.channel.wait();

    do{
        think();
        eat();
    }while(!table.done);

}

void Philosopher::requestForks() {
    setStatus(PhilStatus::REQUESTING);
    rightFork.requestFork(id);
    setStatus(PhilStatus::TOOK_RIGH_FORK);
    sleep(500);
    leftFork.requestFork(id);
    setStatus(PhilStatus::TOOK_LEFT_FORK);
    sleep(500);
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
    sleepRandom(2.5,3.5);
}

void Philosopher::eat() {

    requestForks();

    std::lock(leftFork.getMutex(), rightFork.getMutex());

    std::lock_guard<std::mutex> leftForkLock(leftFork.getMutex(), std::adopt_lock);
    std::lock_guard<std::mutex> rightForkLock(rightFork.getMutex(), std::adopt_lock);

    leftFork.setStatus(ForkStatus::DIRTY);
    rightFork.setStatus(ForkStatus::DIRTY);

    setStatus(PhilStatus::EATING);

    sleepRandom(2.5,3.5);

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

    print.updateMenu(id,getStatus());
}

void Philosopher::sleepRandom(double min, double max) {

    int randSleepTime = static_cast<int>(((max - min) * ((double) rand() / (double) RAND_MAX) + min) * 1000000);

    std::this_thread::sleep_for(std::chrono::microseconds(randSleepTime));

}
