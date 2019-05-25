//
// Created by mateusz on 25.03.19.
//

#ifndef DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
#define DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H


#include "HouseSetup.h"
#include <ncurses.h>
#include <menu.h>
#include <vector>

class Printing {

public:
    explicit Printing(HouseSetup &tableSetup);
    ~Printing();


    void menu();
    void createMenu(std::vector<std::string> philosophersCycles, std::vector<std::string> philosophersStatus,
            std::vector<std::string> philoForks);

    void updateMenu(int philosopherId, std::string status, std::string cycle);

private:

    std::mutex menuMutex;
    std::vector<std::string> philosophersStatus;
    std::vector<std::string> philosophersCycles;
    std::vector<std::string> philoForksStatus;
    int philosophersNumber;

    HouseSetup &tableSetup;

    ITEM **myMenuItems = nullptr;
    MENU* myMenu = nullptr;

    void init();

    void stop();

    void closeMenu();
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
