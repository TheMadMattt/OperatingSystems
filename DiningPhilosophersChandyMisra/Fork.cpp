//
// Created by mateusz on 21.03.19.
//

#include "Fork.h"

Fork::Fork() {
    this->status = ForkStatus::DIRTY;
}

Fork::Fork(int id, int ownerId) {

    this->id = id;
    this->ownerId = ownerId;
    this->status = ForkStatus::DIRTY;
}

void Fork::requestFork(int ownerId) {

    while(this->ownerId != ownerId){
        if(status == ForkStatus::DIRTY){
            std::lock_guard<std::mutex> lock(mutex);

            status = ForkStatus::CLEAN;

            this->ownerId = ownerId;
        }else{
            channel.wait();
        }
    }

}

std::string Fork::getStatus() const {
    std::string message = "Fork" + std::to_string(id);

    switch(status){
        case ForkStatus::DIRTY:
            message += " is DIRTY";
            break;
        case ForkStatus::CLEAN:
            message += " is CLEAN";
            break;
    }

    return message + " -> Phil" + std::to_string(ownerId);
}

void Fork::setStatus(ForkStatus status) {
    Fork::status = status;
}

std::mutex& Fork::getMutex() {
    return mutex;
}

void Fork::freeFork() {

    this->status = ForkStatus::DIRTY;

    channel.notifyAll();

}
