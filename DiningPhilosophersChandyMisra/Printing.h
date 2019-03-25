//
// Created by mateusz on 24.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
#define DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H

#include <ncurses.h>
#include <mutex>
#include <vector>
#include <menu.h>
#include "SyncingChannel.h"


class Printing {
public:
    explicit Printing(TableSetup &table, int philsNumber);
    ~Printing();

    void start();
    void createMenu(std::vector<std::string> philosophersStates);

    void updateMenu(int philId, std::string state);

private:
    std::mutex menuLock;
    std::vector<std::string> philosophersStates;
    int philsNumber;

    TableSetup &table;

    ITEM** myMenuItems = nullptr;
    MENU* myMenu = nullptr;

    void init();
    void stop();
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
