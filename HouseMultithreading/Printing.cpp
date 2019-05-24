#include <utility>
#include "Printing.h"

Printing::Printing(HouseSetup &tableSetup)
    :   tableSetup(tableSetup)
{
}

Printing::~Printing() {
    refresh();
    closeMenu();
}

void Printing::menu() {

    int key;
    bool finished = false;

    while((key = getch()) && !finished)
    {
        std::lock_guard<std::mutex> lockGuard(menuMutex);
        switch(key)
        {	case KEY_DOWN:
                menu_driver(myMenu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(myMenu, REQ_UP_ITEM);
                break;
            case KEY_PPAGE:
                menu_driver(myMenu, REQ_SCR_UPAGE);
                break;
            case KEY_NPAGE:
                menu_driver(myMenu, REQ_SCR_DPAGE);
                break;
            case 27: //ESC
                stop();
                finished = true;
                break;
            default:
                break;
        }
        refresh();
    }
}

void Printing::createMenu(std::vector<std::string> philosophersCycles, std::vector<std::string> philosophersStatus,
                          std::vector<std::string> philoForks) {

    init();
    this-> philosophersNumber = static_cast<int>(philosophersStatus.size());
    this->philoForksStatus = std::move(philoForks);
    this->philosophersStatus = std::move(philosophersStatus);
    this->philosophersCycles = std::move(philosophersCycles);
    myMenuItems = new ITEM*[philosophersNumber];

    for (int i = 0; i < philosophersNumber; ++i) {
        myMenuItems[i] = new_item(this->philosophersCycles[i].c_str(), this->philosophersStatus[i].c_str());
    }

    myMenu = new_menu(myMenuItems);
    set_menu_mark(myMenu, " ");
    refresh();
    post_menu(myMenu);

    for (int i = 0; i < philosophersNumber; ++i) {
        mvprintw(LINES - 10 + i, 0, philoForksStatus[i].c_str());
    }

    mvprintw(LINES - 2, 0, "ESC to stop threads");
    refresh();
}

void Printing::init() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
}

void Printing::stop() {
    tableSetup.finishedDinner = true;
}

void Printing::closeMenu() {

    unpost_menu(myMenu);
    free_menu(myMenu);
    for (int i = 0; i < philosophersStatus.size(); ++i) {
        free_item(myMenuItems[i]);
    }

    endwin();

}

void Printing::updateMenu(int philosopherId, std::string status, std::string cycle) {

    std::lock_guard<std::mutex> lockGuard(menuMutex);
    philosophersStatus[philosopherId] = std::move(status);
    philosophersCycles[philosopherId] = std::move(cycle);
    myMenuItems[philosopherId] = new_item(philosophersCycles[philosopherId].c_str(),
            this->philosophersStatus[philosopherId].c_str());

    auto currentMenuItem = myMenu->curitem;
    unpost_menu(myMenu);
    set_menu_items(myMenu,myMenuItems);
    set_current_item(myMenu,currentMenuItem);
    post_menu(myMenu);

    for (int i = 0; i < philosophersNumber; ++i) {
        mvprintw(LINES - 10 + i, 0, philoForksStatus[i].c_str());
    }

    mvprintw(LINES - 2, 0, "ESC to stop threads");
    refresh();
}
