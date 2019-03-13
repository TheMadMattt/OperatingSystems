//
// Created by mateusz on 08.03.19.
//

#include "Fork.h"

Fork::Fork() {
    this->status = ForkStatus::FREE;
}

const int &Fork::getStatus() const {
    return status;
}

void Fork::setStatus(const int &status) {
    Fork::status = status;
}

void Fork::takeFork() {

    this->status = Fork::ForkStatus::TAKEN;
}

void Fork::putDownFork() {

    this->status = Fork::ForkStatus::FREE;
}
