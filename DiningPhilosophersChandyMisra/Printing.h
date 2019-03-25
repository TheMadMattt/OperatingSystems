//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
#define DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H


#include "SyncingChannel.h"
#include <ncurses.h>
#include <menu.h>
#include <vector>

class Printing {

public:
    explicit Printing(TableSetup &tableSetup);
    ~Printing();


    void menu();
    void createMenu(std::vector<std::string> philosophersStatus);

    void updateMenu(int philosopherId, std::string status);

private:

    std::mutex menuMutex;
    std::vector<std::string> philosopherStatus;

    TableSetup &tableSetup;

    ITEM **myMenuItems = nullptr;
    MENU* myMenu = nullptr;

    void init();

    void stop();

    void closeMenu();
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
