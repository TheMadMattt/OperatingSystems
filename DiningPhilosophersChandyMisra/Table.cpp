#include "Table.h"

Table::Table(int philosopherNumber): print(table, philosopherNumber),philosophersNumber(philosopherNumber) {

    createForks();
    createPhilosophers();
    print.createMenu(getPhilosophersStates());
}

void Table::createForks() {

    for (int i = 0; i < philosophersNumber; ++i) {
        if(i != philosophersNumber-1){
            forksList.emplace_back(i,i);
        }else{
            forksList.emplace_back(i,0);
        }
    }
}

void Table::createPhilosophers() {

    for (int i = 0; i < philosophersNumber; ++i) {
        if(i != philosophersNumber-1){
            philosophersList.emplace_back(i, table, forksList[i], forksList[0], print);
        }else{
            philosophersList.emplace_back(i, table, forksList[i], forksList[i+1], print);
        }
    }

}

std::vector<std::string> Table::getPhilosophersStates() {

    auto states = std::vector<std::string>();

    for(Philosopher &philosopher : philosophersList){
        states.emplace_back(philosopher.getStatus());
    }
    states.emplace_back("\0");

    return states;

}

void Table::startDinner() {

    table.channel.notifyAll();

    print.start();

    stop();

}

void Table::stop() {

    table.done = true;
}
