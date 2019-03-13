//
// Created by mateusz on 08.03.19.
//

#ifndef DININGPHILOSOPHERS_FORK_H
#define DININGPHILOSOPHERS_FORK_H

#include <string>

using namespace std;

class Fork {
private:
    int status;

public:
    Fork();

    const int &getStatus() const;

    void setStatus(const int &status);

    void takeFork();

    void putDownFork();

    enum ForkStatus{
        FREE, TAKEN
    };
};


#endif //DININGPHILOSOPHERS_FORK_H
