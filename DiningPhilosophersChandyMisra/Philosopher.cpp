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
        print(print)
{
}

Philosopher::Philosopher(Philosopher &&other) noexcept
    :   id(other.id),
        tableSetup(other.tableSetup),
        leftFork(other.leftFork),
        rightFork(other.rightFork),
        philosopherThread(std::move(other.philosopherThread)),
        print(other.print)
{
}

Philosopher::~Philosopher() {
    if(philosopherThread.joinable()){
        philosopherThread.detach();
    }
}



void Philosopher::thinking() {

    sleepRandom(2.5,3.5);

    setStatus(PhilosopherStatus::THINKING);
}

void Philosopher::eating() {

    requestForks();

    std::lock(leftFork.getForkMutex(), rightFork.getForkMutex());

    std::lock_guard<std::mutex> leftForkLock(leftFork.getForkMutex(), std::adopt_lock);
    std::lock_guard<std::mutex> rightForkLock(rightFork.getForkMutex(), std::adopt_lock);

    leftFork.setForkStatus(ForkStatus::DIRTY);
    rightFork.setForkStatus(ForkStatus::DIRTY);

    setStatus(PhilosopherStatus::EATING);
    sleepRandom(2.5,3.5);

    putDownForks();
}

void Philosopher::requestForks() {

    setStatus(PhilosopherStatus::REQUESTING);

    std::random_device rd;
    std::mt19937 mt(rd());
    static thread_local std::uniform_int_distribution<> generator(1, 2);

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
    sleepRandom(0,0.5);

    setStatus(PhilosopherStatus::THINKING);

    rightFork.setForkStatus(ForkStatus::CLEAN);
    leftFork.setForkStatus(ForkStatus::CLEAN);
}

std::string Philosopher::getPhilosopherStatus() {

    std::string forkMessage = leftFork.getForkStatus();
    std::string message = "Phil" + std::to_string(id);

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
    }while(!tableSetup.finishedDinner);

    finishDinner();

}

void Philosopher::sleepRandom(double min, double max) {

    int randSleepTime = static_cast<int>(((max - min) * ((double) rand() / (double) RAND_MAX) + min) * 1000000);

    std::this_thread::sleep_for(std::chrono::microseconds(randSleepTime));

}

void Philosopher::setStatus(PhilosopherStatus status) {

    this->status = status;

    print.updateMenu(id,getPhilosopherStatus());

}

void Philosopher::finishDinner() {

    putDownForks();

    setStatus(PhilosopherStatus::FINISHED_DINNER);

    if(philosopherThread.joinable()){
        philosopherThread.detach();
    }
}
