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
    explicit Printing(HouseSetup &houseSetup);
    ~Printing();

    void menu();
    void createMenu(std::vector<std::pair<std::string, std::string>> personsStatus,
                    std::vector<std::pair<std::string, std::string>> resourcesStatusBegin);
    void updateMenu(int personId, std::string status, std::string progress);
    void updateResourcesStates(const std::string& resourceName, const std::string& status);

private:

    std::mutex menuMutex;
    std::vector<std::pair<std::string, std::string>> personStatus;
    std::vector<std::pair<std::string,std::string>> resourcesStatus;
    int personsNumber;

    HouseSetup &tableSetup;

    ITEM **myMenuItems = nullptr;
    MENU* myMenu = nullptr;

    static void init();

    void stop();

    void closeMenu();
};


#endif //DININGPHILOSOPHERSCHANDYMISRA_PRINTING_H
