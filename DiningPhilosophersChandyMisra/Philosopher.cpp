//
// Created by mateusz on 25.03.19.
//

#include <random>
#include "Philosopher.h"

Philosopher::Philosopher(int id, TableSetup &tableSetup, Fork &leftFork, Fork &rightFork, Printing &print)
    :   id(id),
        tableSetup(tableSetup),
        leftFork(leftFork),
        rightFork(rightFork),
        philosopherThread(&Philosopher::startDinnerThread,this),
        print(print),
        status(PhilosopherStatus::THINKING),
        cycle(0)
{
}

Philosopher::Philosopher(Philosopher &&other) noexcept
    :   id(other.id),
        tableSetup(other.tableSetup),
        leftFork(other.leftFork),
        rightFork(other.rightFork),
        philosopherThread(std::move(other.philosopherThread)),
        print(other.print),
        status(other.status),
        cycle(other.cycle)
{
}

Philosopher::~Philosopher() {
    if(philosopherThread.joinable()){
        philosopherThread.detach();
    }
}



void Philosopher::thinking() {

    for (int i = 0; i < 8; ++i) {
        sleepRandom(0,800);

        setStatus(PhilosopherStatus::THINKING);
    }

}

void Philosopher::eating() {

    requestForks();

    std::scoped_lock scopedLock(leftFork.getForkMutex(), rightFork.getForkMutex());

    leftFork.setForkStatus(ForkStatus::DIRTY);
    rightFork.setForkStatus(ForkStatus::DIRTY);

    for (int i = 0; i < 8; ++i) {
        sleepRandom(0,800);

        setStatus(PhilosopherStatus::EATING);
    }

    putDownForks();
}

void Philosopher::requestForks() {

    setStatus(PhilosopherStatus::REQUESTING);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> generator(1, 2);

    if(generator(mt) == 1){
        leftFork.requestFork(id);
        setStatus(PhilosopherStatus::TOOK_LEFT_FORK);
        rightFork.requestFork(id);
    }else{
        rightFork.requestFork(id);
        setStatus(PhilosopherStatus::TOOK_RIGHT_FORK);
        leftFork.requestFork(id);
    }
}

void Philosopher::putDownForks() {

    leftFork.putDownFork();
    setStatus(PhilosopherStatus::PUT_DOWN_LEFT_FORK);

    rightFork.putDownFork();
    setStatus(PhilosopherStatus::PUT_DOWN_RIGHT_FORK);

    setStatus(PhilosopherStatus::THINKING);

    rightFork.setForkStatus(ForkStatus::CLEAN);
    leftFork.setForkStatus(ForkStatus::CLEAN);
}

std::string Philosopher::getPhilosopherStatus() {

    std::string forkMessage = leftFork.getForkStatus();
    std::string message = "| Phil" + std::to_string(id);

    switch(status){
        case PhilosopherStatus::THINKING:
            message += " is THINKING                ";
            break;
        case PhilosopherStatus::EATING:
            message += " is EATING                  ";
            break;
        case PhilosopherStatus::REQUESTING:
            message += " is REQUESTING forks        ";
            break;
        case PhilosopherStatus::PUT_DOWN_RIGHT_FORK:
            message += " is PUTTING DOWN RIGHT FORK ";
            break;
        case PhilosopherStatus::PUT_DOWN_LEFT_FORK:
            message += " is PUTTING DOWN LEFT FORK  ";
            break;
        case PhilosopherStatus::TOOK_LEFT_FORK:
            message += " TOOK LEFT FORK             ";
            break;
        case PhilosopherStatus::TOOK_RIGHT_FORK:
            message += " TOOK RIGHT FORK            ";
            break;
        case PhilosopherStatus::FINISHED_DINNER:
            message += " FINISHED DINNER            ";
            break;
    }

    return message + " " + forkMessage;
}

void Philosopher::startDinnerThread() {

    tableSetup.syncChannel.wait();

    do{
        thinking();
        eating();
        ++cycle;
    }while(!tableSetup.finishedDinner);

    finishDinner();

}

void Philosopher::sleepRandom(int min, int max) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> generator(min, max);

    int randSleepTime = generator(mt);

    std::this_thread::sleep_for(std::chrono::milliseconds(randSleepTime));

}

void Philosopher::setStatus(PhilosopherStatus status) {

    this->status = status;

    print.updateMenu(id,getPhilosopherStatus(), getDinnerCycle());

}

void Philosopher::finishDinner() {

    putDownForks();

    setStatus(PhilosopherStatus::FINISHED_DINNER);

    if(philosopherThread.joinable()){
        philosopherThread.detach();
    }
}

std::string Philosopher::getDinnerCycle() {

    return "Cykl: " + std::to_string(cycle);

}

std::string Philosopher::getPhiloForks() {

    return "Philo"+std::to_string(id)+" has Forks " + std::to_string(leftFork.getId()) + " and " +
            std::to_string(rightFork.getId());
}
